#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"
#include "llvm/ADT/APInt.h"
#include "llvm/Analysis/InstructionSimplify.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
using namespace llvm;

//-----------------------------------------------------------------------------
// MultiInstruction implementation
//-----------------------------------------------------------------------------
namespace {

    // New PM implementation
    struct MultiInstruction : PassInfoMixin<MultiInstruction> {
        // Main entry point, takes IR unit to run the pass on (&F) and the corresponding pass manager
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &) {
            bool changed = false;
            
            errs() << "Avvio \n";
            for (BasicBlock &BB : F) {
                for (auto it = BB.begin(), end = BB.end(); it != end; ++it) {
                    if (auto *I = dyn_cast<Instruction>(&*it)) {
                        auto *add1 = dyn_cast<BinaryOperator>(&*I);
                        if (!add1)
                            continue;
                        
                        if(add1->getOpcode() != Instruction::Add &&
                            add1->getOpcode() != Instruction::Sub &&
                            add1->getOpcode() != Instruction::Mul &&
                            add1->getOpcode() != Instruction::SDiv &&
                            add1->getOpcode() != Instruction::UDiv){
                                continue;
                        }
                        errs() << "---Istruzione: \n";
                        add1->print(errs());
                        errs()<<"\nE' un istruzione che cerchiamo\n";
                        //cerchiamo gli users
                        for (auto *U : add1->users()){
                            U->print(errs());
                            errs() << "\n";
                            if (auto *SI = dyn_cast<StoreInst>(U)){
                                Value *ptr = SI->getPointerOperand();
                                //Cerchiamo il Load allo stesso puntatore
                                for(auto &I : *SI->getParent()->getParent()){
                                    if(auto *LI = dyn_cast<LoadInst>(&I)){
                                        if(LI->getPointerOperand() != ptr)
                                            continue;
                                        
                                        for(auto *U2 : LI->users()){
                                            if(auto *op = dyn_cast<BinaryOperator>(U2)){
                                                errs()<<"Store trovata\n";
                                                op->print(errs());
                                                errs()<<"\n";
                                            }
                                        }
                                    }
                                }
                            }
                            //controlla se l'user è un operazione binaria
                            auto *op = dyn_cast<BinaryOperator>(U);
                            if(!op)
                                continue;
                            errs()<<"user binario\n";
                            //controlla che siano operazioni inverse tra loro
                            bool inverse = 
                            (add1->getOpcode() == Instruction::Add &&
                            op->getOpcode() == Instruction::Sub)
                            ||
                            (add1->getOpcode() == Instruction::Sub &&
                            op->getOpcode() == Instruction::Add)
                            ||
                            (add1->getOpcode() == Instruction::Mul &&
                            op->getOpcode() == Instruction::SDiv)
                            ||
                            (add1->getOpcode() == Instruction::SDiv &&
                            op->getOpcode() == Instruction::Mul)
                            ||
                            (add1->getOpcode() == Instruction::UDiv &&
                            op->getOpcode() == Instruction::Mul);
                            if(!inverse)
                                continue;
                            //op deve avere come operando add1
                            if(op->getOperand(0) != add1)
                                continue;
                            
                            Value *other = op->getOperand(1);

                            //estrae le costanti (se sono presenti)
                            ConstantInt *C1 = dyn_cast<ConstantInt>(add1->getOperand(1));
                            ConstantInt *C2 = dyn_cast<ConstantInt>(other);

                            //controlla che siano costanti
                            if(!C1 || !C2)
                                continue;
                            //controlla che abbiano lo stesso valore
                            if(C1->getValue() != C2->getValue())
                                continue;
                            errs()<<"Inversa trovata\n";
                            //a questo punto abbiamo trovato il match
                            Value *b = add1->getOperand(0);
                            errs()<<"MATCH\n";
                            //sostituisce tutto con b
                            op->replaceAllUsesWith(b);
                            op->eraseFromParent();
                            
                            break;
                        }
                    }
                }
            }

            return changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
        }

        // Senza questa funzione, il pass potrebbe essere saltato per le funzioni con l'attributo optnone
        static bool isRequired() { return true; }
    };

} // namespace

//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getMultiInstructionPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "MultiInstruction", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, FunctionPassManager &FPM,
                    ArrayRef<PassBuilder::PipelineElement>) {
                    if (Name == "terzo-passo") {
                        FPM.addPass(MultiInstruction());
                        return true;
                    }
                    return false;
                });
            }};
}

// Questo è il core dell'interfaccia del plugin. Garantisce che 'opt' riconosca il pass quando aggiunto alla pipeline di passaggi sulla riga di comando, ad esempio con '-passes=terzo-passo'
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
    return getMultiInstructionPluginInfo();
}