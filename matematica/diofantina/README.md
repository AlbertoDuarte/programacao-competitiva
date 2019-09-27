# Equação Diofantina Linear

Questões solucionadas:

1. [Soluções Não Negativas para Equações Diofantinas Lineares de 2 Variáveis com DP](#equacoes)

## Equações

Questão: https://codeforces.com/group/btcK4I5D5f/contest/253645/problem/E

Complexidade: O(min(N, 10⁶))

Como o valor máximo de N é 10⁹, uma solução O(n) não passaria. Usaremos então os seguintes fatos sobre equações diofantinas do tipo

> AX + BY = C

Com A,B > 0.

1. Solução inteira existe se, e somente se, gcd(A, B) divide C. E mais, existem infinitas soluções.
2. Para C > (A-1)(B-1)/2, se existe solução inteira então existe solução positiva.

Caso isso não lhe seja familiar, esse [link](https://brilliant.org/wiki/linear-diophantine-equations-one-equation/) pode servir como uma referência rápida.

### Solução

Considere C <= (A-1)(B-1)/2 <= A*B <= 10⁶

Como o maior valor de A*B é 10⁶, podemos realizar um algoritmo com complexidade O(A*B). Uma forma de resolver esse problema de forma linear é utilizando DP. Inicializaremos um vetor cujo índice i representa a existência de solução não negativa para AX + BY = i; 1 se existir, 0 caso contrário.

```c++
vi possivel(1000001, 0);
possivel[0] = 1; // C = 0 é o caso trivial que sempre tem solução X = Y = 0
```

A DP funciona da seguinte maneira: Suponha que exista solução para AX + BY = C - A,  com X, Y >= 0
Logo,

```
    AX + A + BY = C - A + A
    A(X+A) + BY = C
    A(X') + BY = C , com X'= X+A >= 0 pois A > 0
```

Então faremos um loop até min(N, 10⁶) sempre verificando se existe solução para C-A ou C-B para decidirmos a existência de para C.

```c++
for(int c = 1; c <= min(N, (int)1e6); c++) {
  if(c-a >= 0 and possivel[c-a])
    possivel[c] = 1;
  if(c-b >= 0 and possivel[c-b])
    possivel[c] = 1;

  if(possivel[c])
    sol++;
}
```

Agora para C > 10⁶ >= A*B >= (A-1)(B-1)/2, nós podemos verificar a existência de solução não negativa simplesmente verificando se existe solução inteira. Isto é, se gcd(a,b) divide C.

Portanto, a quantidade de C com solução >= 0 é a quantidade de múltiplos de gcd(a,b) no intervalo [10⁶, N] se N > 10⁶:

```c++
d = __gcd(a, b);
if(N > (int)1e6) {
  // Algoritmo para calcular a quantidade de multiplos de d = gcd(a,b) no intervalo [10⁶, N]
  int l = (1e6);
  l = l + (d- (l%d));
  int r = N - (N%d);

  sol += (r-l)/d ;
  sol++;
}
```

### Solução Completa

```c++
int main() {
  int a, b, d, N;
  cin >> a >> b >> N;
  vi possivel(1000001, 0);


  int sol = 0;
  possivel[0] = 1;
  for(int c = 1; c <= min(N, (int)1e6); c++) {
    if(c-a >= 0 and possivel[c-a])
      possivel[c] = 1;
    if(c-b >= 0 and possivel[c-b])
      possivel[c] = 1;

    if(possivel[c])
      sol++;
  }

  d = __gcd(a, b);
  if(N > (int)1e6) {
    int l = (1e6);
    l = l + (d- (l%d));
    int r = N - (N%d);

    sol += (r-l)/d ;
    sol++;
  }

  cout << sol/__gcd(sol, N) << "/" << N/__gcd(sol, N) << endl;
  return 0;
}
```
