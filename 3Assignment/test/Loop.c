int loop(int a, int b, int c) {
  int i, ret = 0;
  int x = 5, y = 3;
  int z;

  // Caso classico LICM: x*y è loop-invariant
  for (i = 0; i < 10; i++) {
    z = x * y;       // loop-invariant deve essere hoistato
    ret = ret + z;   // NON loop-invariant (dipende da ret)
  }

  // Loop con invariant annidato
  for (i = a; i < b; i++) {
    int w = x + y;   // loop-invariant: deve essere hoistato
    ret += w * i;    // NON loop-invariant (dipende da i)
  }

  return ret;
}
