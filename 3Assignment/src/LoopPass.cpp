#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/ADT/APInt.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/CFG.h"
#include "llvm/Support/GraphWriter.h"
#include "llvm/IR/Dominators.h"

#define IS_ES_1 0

using namespace llvm;

namespace {

  void printLoopInformation(Loop *loop){
    //verifica se il loop è in forma normale

    if(loop->isLoopSimplifyForm()){
      errs()<<"Loop in forma normale\n";
    }else{
      errs()<<"Loop non in forma normale\n";
    }

    //recupero header del loop
    BasicBlock *header = loop->getHeader();

    //recuper handle alla funzione padre del loop
    Function *FPadre = header->getParent();

    if(!FPadre)
      errs()<<"Funzione padre non disponibile \n";

    errs()<<"Nome funzione padre: "<<FPadre->getName()<<"\n";

    //stampo cfg
    errs()<<"Stampa CFG:\n";
    errs()<<*FPadre<<"\n";

    errs()<<"Lista blocchi del loop:\n";
    for(Loop::block_iterator BI = loop->block_begin(); BI != loop->block_end(); ++BI){
        BasicBlock *BB = *BI;
        errs()<<*BB<<"\n";
      }
    
      //chiamata ricorsiva sui propri loop interni
    for(Loop *subLoop : loop->getSubLoops()){
      errs()<<"entro nel subloop:\n";
      subLoop->getHeader()->printAsOperand(errs(), false);
      errs()<<"\ndi:\n";
      loop->getHeader()->printAsOperand(errs(), false);
      errs()<<"\n";
      printLoopInformation(subLoop);
    }
  }
// New PM implementation
struct LoopPass : PassInfoMixin<LoopPass> {
  // Main entry point, takes IR unit to run the pass on (&F) and the
  // corresponding pass manager (to be queried if need be)
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
      if(IS_ES_1){
        errs()<<"Nome funzione:\n"<<F.getName()<<"\n";
        LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

        //verifico che il cfg contiente almeno un loop
        if(LI.empty()){
          errs()<<"Nessun loop presente \n";
          return PreservedAnalyses::all();
        }

        //scorriamo tutti i loop
        for(Loop::iterator lit = LI.begin(); lit != LI.end(); lit++){
          Loop *loop = *lit;
          errs()<<"Entro nel loop esterno\n";
          loop->getHeader()->printAsOperand(errs(), false);
          errs()<<"\n";
          printLoopInformation(loop);
        }
      }else{
        DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);

        //radice albero
        DomTreeNode *rootNode = DT.getRootNode();

        //visito il D-Tree attraverso una visita DFS
        for(DomTreeNode *DTN : depth_first(rootNode)){
          BasicBlock *BB = DTN->getBlock();
          DomTreeNode *imm = DTN->getIDom();

          if(imm){
            errs()<<"\nNodo:\n";
            imm->getBlock()->printAsOperand(errs(), false);
            errs()<<"-> Nodo: ";
            BB->printAsOperand(errs(), false);
            errs()<<"\n";
          }
        }
      }  

      return PreservedAnalyses::all();
    }

  };

  static bool isRequired() { return true; }
};

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getLoopPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "LoopPass", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerPipelineParsingCallback(
                [](StringRef Name, FunctionPassManager &FPM,
                   ArrayRef<PassBuilder::PipelineElement>) {
                  if (Name == "loop-pass") {
                    FPM.addPass(LoopPass());
                    return true;
                  }
                  return false;
                });
          }};
}

// This is the core interface for pass plugins. It guarantees that 'opt' will
// be able to recognize LoopPass when added to the pass pipeline on the
// command line, i.e. via '-passes=test-pass'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getLoopPassPluginInfo();
}