# compilatori2-assignments
Repo per gli assignments di compilatori2

## Struttura delle directory

root/
├── CMakeLists.txt             
├── common/                # Funzioni comuni che i tuoi test chiamano
│   ├── common.c       
│   └── common.h 
├── Assignment1/
│   ├── OptzA/     # Sorgenti ottimizzazione A
│   │   ├── Pass.cpp
│   │   └── CMakeLists.txt
│   │   └── tests/         # TEST SPECIFICI per questo passo
│   │       ├── optaA.c  
│   │       └── optaB.ll
│   └── OptzB/     # Sorgenti ottimizzazione B
│       ├── Pass.cpp
│       └── CMakeLists.txt
├── tests/        
│   ├── source/           # .c file
│   └── IR/                # .ll o .bc                    
└── build/                 # Unica cartella di build
    └── lib/
        └── LLVMAssignment1.so # Un'unica libreria contenente TUTTI i pass
