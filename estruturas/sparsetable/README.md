# Sparse Table

Questões solucionadas:

1. [Máximo e Mínimo](#friendsandsubsequences)

Códigos auxiliares:

- [Sparse table](sparsetable.cpp)

## Friends and Subsequences

Questão: https://codeforces.com/contest/689/problem/D

Complexidade: pré-processamento O(nlog(n)) - solução O(nlog(n))

É pedido no problema para que, dado dois vetores de tamanho n, nós respondamos a quantidade de pares (l, r) cujo máximo no intervalo [l, r] no primeiro vetor (A) é igual ao mínimo no intervalo [l, r] no segundo vetor (B).

Para a solução, além da sparse table, será usada busca binária.

### Solução

Utilizaremos a sparse table para encontrar o máximo de um intervalo no vetor A e o mínimo no vetor B com complexidade O(1). Será computada, então, a stA e stB que são a sparse table de A e B respectivamente.

Caso encontre dificuldades para entender o processamento da sparse table e suas queries, este [link](https://cp-algorithms.com/data_structures/sparse-table.html) pode servir como uma boa referência.

Então temos o código do pré-processamento:


```c++
void precomputemax(int N, int array[]) {
  for (int i = 0; i < N; i++)
      stA[i][0] = array[i];

  int k = logg[N];
  for (int j = 1; j <= k; j++)
      for (int i = 0; i + (1 << j) <= N; i++)
          stA[i][j] = max(stA[i][j-1], stA[i + (1 << (j - 1))][j - 1]);
}

void precomputemin(int N, int array[]) {
  for (int i = 0; i < N; i++)
      stB[i][0] = array[i];

  int k = logg[N];
  for (int j = 1; j <= k; j++)
      for (int i = 0; i + (1 << j) <= N; i++)
          stB[i][j] = min(stB[i][j-1], stB[i + (1 << (j - 1))][j - 1]);
}
```

E das queries:

```c++
int querymax(int L, int R) {
  int j = logg[R - L + 1];
  int maximum = max(stA[L][j], stA[R - (1 << j) + 1][j]);

  return maximum;
}

int querymin(int L, int R) {
  int j = logg[R - L + 1];
  int minimum = min(stB[L][j], stB[R - (1 << j) + 1][j]);

  return minimum;
}
```

Para a solução de fato será usada busca binária. Considere o exemplo do primeiro caso de teste do problema:

```
6
1 2 3 2 1 4
6 7 1 2 3 2
```

Sejam l e mid dois inteiros que armazenam índices.

Com indexação começando em 0, suponha l = mid = 2. Então o máximo em A é 3 e o mínimo em B é 1 em [l, mid]. Veja que, com l = 2 fixo, não importa qual mid eu escolha, o máximo de A **nunca** será igual ao mínimo de B. Como o máximo é 3, ele só irá mudar caso haja um número > 3, ou seja, o máximo só irá aumentar. A mesma coisa com o mínimo que só diminuirá.

Isso cria a condição necessária para realizar uma busca binária!

Se o máximo no intervalo [l, mid] for **maior** que o mínimo no mesmo, então qualquer intervalo [l, mid2] com mid2 > mid vai ter o máximo em A maior que o mínimo B.

Para máximo menor que o mínimo em [l, mid] é análogo, de forma que não importa qual mid2 < mid eu escolha, [l, mid2] sempre terá máximo em A menor que o mínimo em B.

Isto, porém, gera outro problema: e se dado um l fixo existem vários r consecutivos que satisfazem o problema? Por exemplo:

```
4
1 2 2 2 3
3 2 2 2 1
```

Com l = 1, temos mid = 1, 2 ou 3 satisfazem o problema. Então devemos procurar não apenas um mid mas um intervalo onde qualquer mid nele satisfaça.

Agora para o código. Fixaremos um l para cada índice possível e depois disso, com uma busca binária, procuraremos um índice mid que satisfaça o problema. Se ele for encontrado, procuraremos através de duas buscas binárias os intervalos da esquerda e direita.

```c++
for(int i = 0; i < n; i++) {
  int l = i, r = n-1; // limites da busca binaria
  int resl = -1, resr = -1; // respostas do intervalo resultado

  // busca binaria
  while(l <= r) {
    int mid = (l + r)/2;

    if(querymax(i, mid) == querymin(i, mid)) {
      // se foi encontrado um valor mid que satisfaz o problema, então
      // procurar o maior intervalo continuo que satisfaz
      resl = bsl(i, i, mid, querymax(i, mid));
      resr = bsr(i, mid, n-1, querymax(i, mid));
      break;
    }
    else if(querymax(i, mid) > querymin(i, mid)) {
      r = mid-1;
    }
    else {
      l = mid+1;
    }
  }
  // somar contagem de [l, r] que resolvem a questão
  if(resl != -1 and resr != -1)
    count += resr-resl+1;
}
```

As funções bsl e bsr encontram os índices resl e resr mais a esquerda e mais a direita de mid, respectivamente, cujos intervalos [i, resl] e [i, resr] tenham a propriedade desejada. A implementação dessas buscas binárias são simples:

```c++
int bsl(int i, int l, int r, int val) {
  // busca binaria esquerda
  int res = -1;
  while(l <= r) {
    int mid = (l + r)/2;
    if(querymax(i, mid) == val and querymin(i, mid) == val) {
      r = mid - 1;
      res = mid;
    }
    else
      l = mid + 1;
  }

  return res;
}

int bsr(int i, int l, int r, int val) {
  busca binaria direita
  int res = -1;
  while(l <= r) {
    int mid = (l + r)/2;
    if(querymax(i, mid) == val and querymin(i, mid) == val) {
      l = mid + 1;
      res = mid;
    }
    else
      r = mid - 1;
  }

  return res;
}
```

Talvez esteja se perguntando *mas por que fazer duas buscas binárias para encontrar os intervalos da esquerda e direita? Por que não ir olhando para a esquerda até o mid não satisfazer mais?*

A razão é simples: em um caso de teste com n = 10⁵ e todos os números tanto em A quanto em B seja 1, fazer isso é equivalente a uma busca linear. Como estamos fazendo um loop de l = 0 até l = n-1, teríamos complexidade O(n²).

### Solução Completa

``` c++
#define MAXN 2000001
#define K 25

int logg[MAXN+1];

int A[MAXN];
int B[MAXN];
int stA[MAXN][K];
int stB[MAXN][K];


void precomputemax(int N, int array[]) {
  for (int i = 0; i < N; i++)
      stA[i][0] = array[i];

  int k = logg[N];
  for (int j = 1; j <= k; j++)
      for (int i = 0; i + (1 << j) <= N; i++)
          stA[i][j] = max(stA[i][j-1], stA[i + (1 << (j - 1))][j - 1]);
}

void precomputemin(int N, int array[]) {
  for (int i = 0; i < N; i++)
      stB[i][0] = array[i];

  int k = logg[N];
  for (int j = 1; j <= k; j++)
      for (int i = 0; i + (1 << j) <= N; i++)
          stB[i][j] = min(stB[i][j-1], stB[i + (1 << (j - 1))][j - 1]);
}

int querymax(int L, int R) {
  int j = logg[R - L + 1];
  int maximum = max(stA[L][j], stA[R - (1 << j) + 1][j]);

  return maximum;
}

int querymin(int L, int R) {
  int j = logg[R - L + 1];
  int minimum = min(stB[L][j], stB[R - (1 << j) + 1][j]);

  return minimum;
}

int bsl(int i, int l, int r, int val) {
  int res = -1;
  while(l <= r) {
    int mid = (l + r)/2;
    if(querymax(i, mid) == val and querymin(i, mid) == val) {
      r = mid - 1;
      res = mid;
    }
    else
      l = mid + 1;
  }

  return res;
}

int bsr(int i, int l, int r, int val) {
  int res = -1;
  while(l <= r) {
    int mid = (l + r)/2;
    if(querymax(i, mid) == val and querymin(i, mid) == val) {
      l = mid + 1;
      res = mid;
    }
    else
      r = mid - 1;
  }

  return res;
}

int main() {
  int n;
  scanf("%d", &n);

  for(int i = 0; i < n; i++)
  scanf("%d", &A[i]);

  for(int i = 0; i < n; i++)
  scanf("%d", &B[i]);

  // pre-computando tabela de log pois log2 do c++ tem constante ruim
  logg[1] = 0;
  for (int i = 2; i <= MAXN; i++)
      logg[i] = logg[i/2] + 1;

  precomputemax(n, A);
  precomputemin(n, B);

  ll count = 0;
  for(int i = 0; i < n; i++) {
    int l = i, r = n-1; // limites da busca binaria
    int resl = -1, resr = -1; // respostas do intervalo resultado

    while(l <= r) {
      int mid = (l + r)/2;

      if(querymax(i, mid) == querymin(i, mid)) {
        // se foi encontrado um valor mid que satisfaz o problema, então
        // procurar o maior intervalo continuo que satisfaz
        resl = bsl(i, i, mid, querymax(i, mid));
        resr = bsr(i, mid, n-1, querymax(i, mid));
        break;
      }
      else if(querymax(i, mid) > querymin(i, mid)) {
        r = mid-1;
      }
      else {
        l = mid+1;
      }
    }
    // somar contagem de [l, r] que resolvem a questão
    if(resl != -1 and resr != -1)
      count += resr-resl+1;
  }

  cout << count << endl;
  return 0;
}
```
