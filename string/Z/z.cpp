vi Zcalc(string s) {
  // Algoritmo que calcula vetor de tamanho s.size() tal que o valor no i-esimo
  // elemento eh o tamanho do maior prefixo comum entre s e o sufixo de s comecando em i
  vi Z(s.size(), 0);
  int l = 0, r = 0;

  for(int k = 1; k < (int)s.size(); k++) {
    if(k > r) {
      l = k; r = k;
      while(r < (int)s.size() and s[r] == s[r - l]) {
        r++;
      }
      Z[k] = r - l;
      r--;
    }
    else {
      int k1 = k - l;

      if(Z[k1] < r - k + 1) {
        Z[k] = Z[k1];
      }
      else {
        l = k;
        while(r < (int)s.size() and s[r] == s[r - l]) {
          r++;
        }
        Z[k] = r - l;
        r--;
      }
    }
  }

  return Z;
}
