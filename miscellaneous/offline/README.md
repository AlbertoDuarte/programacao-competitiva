# Equação Diofantina Linear

Questões solucionadas:

1. [Soma dos N primeiros quadrados](#soma-de-quadrados)

## Soma de quadrados

Questão: https://codeforces.com/group/btcK4I5D5f/contest/253645/problem/J

Complexidade: O(10⁹) offline, O(10³) online

Uma solução simples para esse problema é utilizar a fórmula O(1) para a soma dos n primeiros quadrados. Porém, nem sempre teremos esse tipo de fórmula durante uma competição. Logo, esse método pode ser uma alternativa prática.

Faremos a maior parte dos cálculos necessários em Python e guardaremos o resultado em um txt. Então, copiaremos o resultado no txt para um vetor no programa em C.

### Solução

Como queremos calcular a soma dos N primeiros quadrados com 1 <= N <= 10⁹, por que guardaremos apenas *parte* dos cálculos no txt e não tudo? Imagine que calculemos um vetor de tamanho 10⁹ offline. Além do problema de memória ao colocá-lo no vetor em C, se considerarmos uma média de 8 caracteres por número, teremos 8 * 10⁹ caracteres e isso pode ser um problema.

Portanto, calcularemos de fato a soma dos N primeiros quadrados até 10⁹, mas guardaremos no txt apenas os múltiplos de 10⁶. Assim, o vetor terá apenas 10³ elementos e, caso necessitemos de um número que não é múltiplo de 10⁶, podemos simplesmente calcular o que falta online.

```python
f= open("off.txt","w+") # abrir arquivo com permissão de escrita
f.write("{")


m = 10**9 + 7 # devemos dar a resposta com mod 10^9 + 7
v = 0
for i in range(0, 10**9):
    v = (v + (i*i)%m)%m
    if(i % (10**6) == 0):
        f.write("{},".format(v%m))

f.write("{}".format( (v + ((1000000000*1000000000) %m)) ) )

f.write("}")
f.close()
```

Assim, teremos um vetor tal que para todo índice i, v[i] é a soma dos i * 10⁶ primeiros quadrados.

O vetor em c++ ficará desta forma

```c++
  ll V[1001] = {0,163183,319464,468941,611712,747875,877528,1000769,1117696,1228407,...} // colocar vetor inteiro calculado offline
```

Agora considerando a questão de fato.

Nos é dado dois números L e R e devemos dar a soma de todo x, com L <= x <= R tal que x = y² (ou seja, x é um quadrado perfeito). Por simplicidade calcularemos  Lsqrt = ceil($\sqrt{L}$) <= y <= floor($\sqrt{R}$) = Rsqrt. Desta forma, o resultado é o quadrado da soma de todo y no intervalo [Lsqrt, Rsqrt].

Caso este argumento não lhe convença, pare e pense um pouco pois isso será importante no resto da solução.

```c++
scanf("%lld %lld", &l, &r);

ll lsqrt = sqrtl(l);
if (lsqrt * lsqrt != l)
  lsqrt++;

ll rsqrt = sqrtl(r);
```

Antes de calcular de fato o resultado, devemos verificar antes um caso específico, que é quando o intervalo não possui nenhum inteiro, isto é, quando o limite da esquerda do intervalo é maior que o limite da direita.

```c++
if(lsqrt > rsqrt) {
  printf("0\n");
  return 0;
}
```

Seja f(x) a função que retorna a soma dos primeiros x quadrados

A soma de y² para todo y no intervalo [Lsqrt, Rsqrt] é a mesma coisa que fazer f(rsqrt) - f(lsqrt - 1).
Exemplo:

Considere o primeiro exemplo do problema, com L = 5 e R = 20. Assim, Lsqrt = 3 e Rsqrt = 4:

> (1² + 2² + 3² + 4²) - (1² + 2²) =  3² + 4² = 25

Agora para o caso geral, devemos reaproveitar os cálculos já feitos offline. Se queremos, por exemplo, a soma dos 1010 primeiros quadrados para algum dos limites, devemos pegar a soma dos (2010/1000 = 1) primeiros quadrados que já está calculada no vetor e apenas soma i² para todo i no intervalo [2001, 2010].

```c++
int intervalo = (int)1e6;
idx = lsqrt/intervalo // índice do valor que devemos reaproveitar do vetor calculado offline

ll l2 = V[idx]
ll lim_e = (ll)lsqrt/intervalo;
lim_e = idx*intervalo + 1; // assim, lim_e = lsqrt - (lsqrt%1000000) + 1 , ou seja, um multiplo de 1e6 + 1

for(ll i = lim_e; i < lsqrt; i++) {  // note que é i < lsqrt pois *não* queremos somar lsqrt²
  l2 = (l2 + (i*i)%m)%m ;
}

```

Seguiremos a mesma ideia para rsqrt:

```c++
ll r2 = V[idx]
ll lim_d = (ll)rsqrt/intervalo;
lim_d = lim_d*intervalo + 1;


for(ll i = lim_d; i <= rsqrt; i++) { // aqui i <= rsqrt pois queremos somar rsqrt²
  r2 = (r2 + (i*i)%m)%m ;
}
```

Por fim devemos fazer uma última correção. Lembre-se que o resultado desejado é f(rsqrt) - f(lsqrt - 1). O que aconteceria se lsqrt fosse exatamente um múltiplo de 10⁶? Isso é corrigido no loop fazendo i < lsqrt para que não somemos lsqrt² à l2, mas quando lsqrt é um múltiplo de 10⁶ aquele for não é executado.

Podemos corrigir isso de duas maneiras: subtrair lsqrt² de l2 ou, como a resposta final é

> (r2 - l2) mod 10⁹ + 7

podemos somar lsqrt² em r2. Escolheremos a segunda opção:

```c++
// lembre-se que intervalo = 1e6
if(lsqrt%intervalo == 0) {
  r2 = (r2 + (lsqrt*lsqrt)%m)%m;
}
```

E por fim calculamos a resposta final:

```c++
ll res = (r2 - l2 + m)%m;
printf("%lld\n", res);
```


### Solução Completa

```c++
#includes e defines

int main() {
  ll l, r, idx;
  ll m = 1e9 + 7; // valor para calcular mod
  ll V[1001] = {0,163183,319464,468941,611712,747875,877528,1000769,1117696,1228407,...} // colocar vetor inteiro calculado offline


  // calculo do lsqrt e rsqrt
  scanf("%lld %lld", &l, &r);
  ll lsqrt = sqrtl(l);
  if (lsqrt * lsqrt != l)
    lsqrt++;

  ll rsqrt = sqrtl(r);


  // caso especial
  if(lsqrt > rsqrt) {
    printf("0\n");
    return 0;
  }

  int intervalo = (int)1e6;
  idx = lsqrt/intervalo // índice do valor que devemos reaproveitar do vetor calculado offline

  // calculo de f(lsqrt - 1)
  ll l2 = V[idx]
  ll lim_e = (ll)lsqrt/intervalo;
  lim_e = idx*intervalo + 1; // assim, lim_e = lsqrt - (lsqrt%1000000) + 1 , ou seja, um multiplo de 1e6 + 1

  for(ll i = lim_e; i < lsqrt; i++) {  // note que é i < lsqrt pois *não* queremos somar lsqrt²
    l2 = (l2 + (i*i)%m)%m ;
  }

  // calculo de f(rsqrt)
  ll r2 = V[idx]
  ll lim_d = (ll)rsqrt/intervalo;
  lim_d = lim_d*intervalo + 1;

  for(ll i = lim_d; i <= rsqrt; i++) { // aqui i <= rsqrt pois queremos somar rsqrt²
    r2 = (r2 + (i*i)%m)%m ;
  }

  // caso onde lsqrt é múltiplo de 1e6. lembre-se que intervalo = 1e6
  if(lsqrt%intervalo == 0) {
    r2 = (r2 + (lsqrt*lsqrt)%m)%m;
  }

  // resposta final
  ll res = (r2 - l2 + m)%m;
  printf("%lld\n", res);

  return 0;
}
```
