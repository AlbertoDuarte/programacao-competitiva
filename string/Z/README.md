# Algoritmo Z


Questão: https://codeforces.com/group/btcK4I5D5f/contest/247037/problem/H

A ideia da solução é simular Elizardo escrevendo os caracteres e, a cada caractere, verificar se há na string dos caracteres que ele já escreveu uma substring que corresponde a exatamente os próximos caracteres que terá que escrever.

Esta solução terá complexidade O(n²) pois, no pior caso, faremos um loop na string S e, em cada loop, aplicaremos o Algoritmo Z que é linear. O maior tamanho possível de S é 10³ logo nossa solução quadrática passará com tranquilidade.

## Solução

Faremos um loop na string S onde, dado o índice i, a string que corresponde aos caracteres já escritos é o prefixo de S com tamanho i, e a string dos caracteres não escritos é o sufixo de S a partir de i. Portanto, queremos a *maior* substring do prefixo de S que corresponde a um prefixo do sufixo de S

Começaremos do segundo caractere, então a quantidade de passos inicial deverá ser 1

```c++
int passos = 1;

for(int i = 1; i < (int)s.size(); i++) {
  string pre = s.substr(0, i);
  string suf = s.substr(i, (int)s.size()-i);

  // Queremos encontrar a maior substring possivel de pre que
  // de match com algum prefixo de suf para que possamos dar "control c + control v"
  vi Z = Zcalc(suf+"$"+pre);

//...}
```

O vetor Z vai conter, então, o tamanho de cada substring que satisfaz nossos requisitos, mas queremos encontrar a maior substring. Note que não podemos dizer que esse tamanho é simplesmente o maior inteiro em Z pois queremos a maior substring contida no *prefixo de S*, logo devemos achar o maior valor de Z a partir do indice de "$".

```c++
for(int i = (int)suf.size()+1; i < (int)Z.size(); i++) {
  maior = max(maior, Z[i]); // Queremos a maior substring possivel
}
```

Depois de encontrada a substring que podemos dar "control c + control v", devemos incrementar o número de passos (que é o mesmo se for digitada uma única letra ou dado "control c + control v").

Se a maior substring for <= 1 então será considerado que simplesmente escrevemos um caractere. Caso seja > 1, nós damos "control c + control v", o que significa que escrevemos mais de um caractere e, portanto, devemos avançar nosso loop para que não escrevamos o caractere no próximo índice duas vezes.

```c++
passos++;
i += maior-1; // Se copiamos uma string de tamanho n, devemos pular n-1 endereços
```

## Solução completa:
```c++

#includes e defines
...

int Zcalc(string s) {
  ...
}

int main() {
  string s;
  cin >> s;

  int passos = 1;

  for(int i = 1; i < (int)s.size(); i++) {
    string pre = s.substr(0, i);
    string suf = s.substr(i, (int)s.size()-i);

    // Queremos encontrar a maior substring possivel de pre que
    // de match com algum prefixo de suf para que possamos dar "control c + control v"
    vi Z = Zcalc(suf+"$"+pre);

    int maior = 1;

    for(int i = (int)suf.size()+1; i < (int)Z.size(); i++) {
      maior = max(maior, Z[i]); // Queremos a maior substring possivel
    }
    passos++;
    i += maior-1; // Se copiamos uma string de tamanho n, devemos pular n-1 endereços

    //cout << "pre = " << pre << " suf = " << suf << " maior = " << maior << endl;  descomente essa linha para ver cada passo
  }

  cout << passos << endl;
  return 0;
}
```
