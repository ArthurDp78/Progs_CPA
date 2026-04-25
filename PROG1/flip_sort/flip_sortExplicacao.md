# 1. Definicao e entendimento do problema

## Qual e o objetivo do problema? O que precisa ser calculado ou determinado?
O objetivo do problema e determinar o numero minimo de trocas adjacentes necessarias para ordenar uma sequencia de numeros.

Em termos computacionais, isso equivale a contar quantas inversoes existem no vetor. Uma inversao acontece quando um elemento que aparece antes e maior do que outro elemento que aparece depois. Cada inversao representa exatamente uma troca adjacente que sera necessaria durante a ordenacao.

Assim, o que precisa ser calculado em cada caso de teste e o numero total de inversoes da sequencia.

## Quais sao as entradas e saidas esperadas?
A entrada e formada por varios casos de teste.

Em cada caso:
- e lido um inteiro `n`, que representa a quantidade de elementos da sequencia;
- depois sao lidos `n` inteiros, que formam o vetor do caso atual.

O valor `0` para `n` indica o fim da entrada e nao deve ser processado como caso de teste.

A saida, para cada caso, deve ser uma linha no formato:
- `Minimum exchange operations : X`

Nesse formato, `X` e o numero minimo de trocas adjacentes necessario para ordenar a lista.

## Como a entrada do problema pode crescer? Isto e, quais sao as variaveis ou parametros de entrada que controlam isso?
A entrada cresce principalmente de acordo com:
- `n`: tamanho da sequencia de cada caso;
- a quantidade total de casos de teste.

Como cada caso contem um vetor de `n` elementos, o custo do algoritmo depende diretamente do tamanho de cada vetor processado.

Assim, o desempenho total do programa depende de:
- quantos casos precisam ser resolvidos;
- quantos elementos existem em cada caso.

## Como voce interpretou determinada parte do enunciado?
Interpretei que o problema nao pede para simular as trocas adjacentes uma a uma. Em vez disso, ele pede apenas a quantidade minima de trocas.

A observacao central e que essa quantidade minima e exatamente igual ao numero de inversoes do vetor:
- se dois elementos estao fora da ordem relativa, sera necessario corrigi-los durante a ordenacao;
- cada troca adjacente corrige no maximo uma inversao;
- logo, contar inversoes resolve o problema de forma direta.

Foi com base nessa interpretacao que o codigo usa Merge Sort com contagem de inversoes, em vez de aplicar um algoritmo de ordenacao por trocas adjacentes como Bubble Sort.

---

# 2. Ideia geral do algoritmo (alto nivel)

## Qual tecnica ou paradigma algoritmico foi utilizado?
Foi utilizado o paradigma de divisao e conquista, por meio do algoritmo Merge Sort adaptado para contar inversoes.

Essa tecnica e apropriada porque permite ordenar o vetor e, ao mesmo tempo, contar quantos pares estao fora de ordem, com custo muito menor do que comparar todos os pares possiveis.

## Como o algoritmo funciona de forma geral? Descreva os passos principais e contextualize a explicacao no paradigma adotado
A ideia geral e dividir o vetor recursivamente em duas metades ate chegar a trechos de tamanho 1, que ja estao naturalmente ordenados.

Depois, durante a etapa de intercalacao:
- a metade esquerda e a metade direita sao combinadas em ordem crescente;
- sempre que um elemento da metade direita precisa ser colocado antes de um elemento da metade esquerda, isso significa que ele forma inversao com todos os elementos restantes da esquerda;
- essa quantidade e somada ao total de inversoes.

Os passos principais sao:
- dividir o vetor em duas metades;
- contar as inversoes da metade esquerda;
- contar as inversoes da metade direita;
- contar as inversoes cruzadas entre as duas metades durante o merge;
- somar tudo.

Esse raciocinio segue exatamente o paradigma de divisao e conquista, porque o problema maior e resolvido a partir da combinacao das solucoes de subproblemas menores.

## Existem estruturas de dados especificas sendo utilizadas? Por que?
Sim. A principal estrutura utilizada e o `vector<int>`.

O codigo usa:
- um vetor com os valores do caso;
- uma copia desse vetor para poder ordenar sem alterar a entrada original;
- um vetor auxiliar `temp`, usado durante a intercalacao do Merge Sort.

Essas estruturas sao necessarias porque:
- o Merge Sort precisa de um espaco auxiliar para combinar as metades ordenadas;
- o acesso por indice e constante;
- o problema trabalha naturalmente com sequencias lineares de numeros.

O programa tambem usa `long long` para armazenar a quantidade de inversoes, pois esse valor pode ser maior do que o limite de `int` em entradas grandes.

---

# 3. Detalhes de implementacao do codigo

## O que esta funcao/trecho de codigo faz especificamente?
A funcao `merge_and_count` intercala duas metades ja ordenadas do vetor e conta quantas inversoes cruzadas existem entre elas.

A funcao `merge_sort_and_count` resolve o problema principal de forma recursiva:
- divide o vetor em duas partes;
- conta as inversoes da esquerda;
- conta as inversoes da direita;
- conta as inversoes entre as duas partes durante a intercalacao.

A funcao `count_minimum_exchanges` prepara o processamento criando a copia do vetor original e o vetor auxiliar `temp`.

O `main` le todos os casos de teste, chama a funcao de contagem e monta a saida no formato pedido.

## Por que voce utilizou esta estrutura de dados/variavel neste ponto?
O vetor `arr` foi usado porque o Merge Sort precisa acessar elementos por indice e sobrescrever trechos ordenados ao longo do processo.

O vetor `temp` e necessario para a etapa de merge. Ele funciona como uma area auxiliar onde os elementos das duas metades sao combinados antes de serem copiados de volta para `arr`.

A variavel `long long inversions` foi usada porque o numero de inversoes pode crescer bastante. Em um vetor grande, esse total pode ultrapassar o limite de `int`.

As variaveis `i`, `j` e `k` foram escolhidas porque cada uma controla uma parte diferente da intercalacao:
- `i` percorre a metade esquerda;
- `j` percorre a metade direita;
- `k` indica onde escrever no vetor auxiliar.

As variaveis `left`, `mid` e `right` delimitam o intervalo atual do Merge Sort. Elas sao essenciais para saber quais trechos do vetor estao sendo divididos ou intercalados.

## Explique o funcionamento deste laco/condicao especifica
O laco `while (i <= mid && j <= right)` e o centro da intercalacao. Ele compara os elementos das duas metades enquanto ambas ainda possuem itens disponiveis.

Se a condicao `if (arr[i] <= arr[j])` for verdadeira, o elemento da esquerda entra no vetor auxiliar porque ja esta na ordem correta em relacao ao da direita.

Se essa condicao for falsa, significa que `arr[j] < arr[i]`. Nesse caso, o elemento da direita precisa ser colocado antes, e isso gera inversao com todos os elementos da metade esquerda que ainda nao foram copiados. Por isso o codigo soma `mid - i + 1`.

Os lacos seguintes que copiam os elementos restantes existem porque, depois que uma metade termina, a outra ainda pode ter valores que precisam ser enviados para `temp`.

A condicao `if (left >= right)` em `merge_sort_and_count` e o caso base da recursao. Ela indica que o trecho atual ja esta trivialmente ordenado.

## O que acontece nesta linha/bloco de codigo em um cenario especifico?
Se o vetor ja estiver ordenado, a condicao `arr[i] <= arr[j]` sera favorecida durante as intercalacoes, e nenhuma inversao sera somada. Nesse caso, a resposta final sera `0`.

Se o vetor estiver em ordem decrescente, ele tera o numero maximo de inversoes para aquele tamanho. O algoritmo ainda funcionara corretamente, mas somando muitas inversoes durante as etapas de merge.

Na linha `inversions += mid - i + 1`, suponha que `i` esteja na posicao 2 da metade esquerda e `mid` seja 5. Isso significa que ainda restam 4 elementos na metade esquerda, das posicoes 2 ate 5. Se `arr[j]` for menor que `arr[i]`, entao ele forma inversao com todos esses 4 elementos de uma vez.

Quando o bloco `for (int idx = left; idx <= right; idx += 1)` copia `temp` de volta para `arr`, ele atualiza aquele intervalo para que ele fique ordenado antes de voltar para a chamada recursiva anterior.

No `main`, quando `n == 0`, o laco de leitura termina imediatamente. Esse valor funciona como sentinela de fim de entrada.

---

# 4. Complexidade assintotica e analise

## Qual e a complexidade de tempo do seu algoritmo? Justifique
A complexidade de tempo para cada caso de teste e `O(n log n)`.

Isso acontece porque o Merge Sort divide o vetor ao meio em cada nivel da recursao, gerando `log n` niveis, e em cada nivel o custo total de intercalacao e linear, isto e, `O(n)`.

Como a contagem de inversoes e feita durante a propria intercalacao, nao ha necessidade de um processamento extra mais caro.

## Qual e a complexidade de espaco utilizada? Por que?
A complexidade de espaco adicional e `O(n)`, por causa do vetor auxiliar `temp` usado nas intercalacoes.

Tambem existe o custo da pilha de recursao, que e `O(log n)`, devido a profundidade do Merge Sort.

Se considerarmos a copia do vetor original em `arr`, o programa continua usando espaco linear em relacao ao tamanho da entrada do caso.

## Qual e a complexidade deste laco/trecho especifico?
O trecho mais importante e a intercalacao feita em `merge_and_count`.

Nesse trecho, os indices `i` e `j` percorrem as duas metades uma unica vez, e o indice `k` escreve cada elemento uma unica vez no vetor auxiliar. Por isso, o custo da intercalacao de um intervalo de tamanho `n` e `O(n)`.

Como essa intercalacao acontece em todos os niveis da recursao, o custo total consolidado do algoritmo permanece `O(n log n)`.
