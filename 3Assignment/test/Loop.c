// Per produrre la IR che sarà l'input del nostro ottimizzatore:
//
// 	clang -O2 -S -emit-llvm -c FILENAME.c -o FILENAME.ll
//
// Per lanciare il nostro passo di analisi come unico passo dell'ottimizzatore:
//
//	opt -load-pass-plugin=lib/libTestPass.so -passes=test-pass -disable-output FILENAME.ll
//
// Il flag `-disable-output` evita la generazione di bytecode in output (non ci serve,
// il nostro passo non trasforma la IR e non genera output)
//

int g;

int g_incr(int c) {
  g += c;
  return g;
}


int loop(int a, int b, int c) {
  int i, ret = 0;
  int a2 = 0;
  int num1 = 0;
  int num2 = 3;
  int num3 = 4;

  for (i = 0; i < 10; i++){
    num1 = num1 + num2;

    if (a < b) {
      printf("if (a < b)\n");
    }
  }

  for (i = a; i < b; i++) {
    g_incr(c);
    a2 = 0;
    num = num1 + num2;
    while(a2 <= 10){
      a++;
    }
  }

  

  return ret + g;
}
