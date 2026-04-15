#include <stdio.h>

int main() {
    int b = 5;
    int a, c;

    // Operazioni
    a = b + 1;
    c = a - 1;
    return 0;
} 
/*
/*il risultato dell'operazione binaria verrà 
                            ora salvato tramite una store e poi ricaricato tramite
                            una load, dobbiamo seguire il valore nella memoria*/
                            if (auto *SI = dyn_cast<StoreInst>(U)){
                                Value *ptr = SI->getPointerOperand();
                                //Cerchiamo il Load allo stesso puntatore
                                for(auto &I : *SI->getParent()->getParent()){
                                    if(auto *LI = dyn_cast<LoadInst>(&I)){
                                        if(LI->getPointerOperand() != ptr)
                                            continue;
                                        
                                        for(auto *U2 : LI->users()){
                                            if(auto *op = dyn_cast<BinaryOperator>(U2)){
                                                //controlla se l'user è un operazione binaria
                                                errs()<<"user binario\n";
                                                //controlla che siano operazioni inverse tra loro
                                                bool inverse = 
                                                (add1->getOpcode() == Instruction::Add &&
                                                op->getOpcode() == Instruction::Sub)
                                                ||
                                                (add1->getOpcode() == Instruction::Sub &&
                                                op->getOpcode() == Instruction::Add);
                                                if(!inverse)
                                                    continue;
                                                errs()<<"Inversa trovata\n";
                                                //op deve avere come operando add1
                                                if(op->getOperand(0) != add1)
                                                    continue;
                                                
                                                Value *other = op->getOperand(1);

                                                //estrae costanti
                                                ConstantInt *C1 = dyn_cast<ConstantInt>(add1->getOperand(1));
                                                ConstantInt *C2 = dyn_cast<ConstantInt>(other);

                                                //controlla che siano costanti
                                                if(!C1 || !C2)
                                                    continue;
                                                //controlla che abbiano lo stesso valore
                                                if(C1->getValue() != C2->getValue())
                                                    continue;
                                                
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
                            }
 */