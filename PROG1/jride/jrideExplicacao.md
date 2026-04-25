# 1. Definição e entendimento do problema

## Qual é o objetivo do problema? O que precisa ser calculado ou determinado?
O objetivo do problema é, para cada viagem de Jill, encontrar o trecho consecutivo da rota em que vale mais a pena descer do ônibus e pedalar. Em termos computacionais, isso significa encontrar a sequência contínua de valores de *niceness* com a maior soma possível.

Cada valor de *niceness* representa o quanto Jill gosta ou não gosta de um trecho entre duas paradas consecutivas. Portanto, o que precisa ser calculado é o subarray de soma máxima do vetor de *niceness* de cada rota.

Se a melhor soma encontrada não for positiva, então não vale a pena pedalar em nenhum trecho, e a resposta deve indicar que a rota não possui partes agradáveis.

## Quais são as entradas e saídas esperadas?
A entrada começa com um inteiro `b`, que representa a quantidade de viagens.

Para cada viagem:
- é lido um inteiro `s`, que representa o número de paradas de ônibus;
- depois são lidos `s - 1` inteiros, que representam os valores de *niceness* entre paradas consecutivas.

Esses `s - 1` valores formam o vetor que será processado pelo algoritmo.

A saída, para cada rota `r`, deve ser uma das duas:
- `The nicest part of route r is between stops i and j`, quando existe uma soma positiva máxima;
- `Route r has no nice parts`, quando não existe soma máxima positiva.

## Como a entrada do problema pode crescer? Isto é, quais são as variáveis ou parâmetros de entrada que controlam isso?
A entrada cresce principalmente de acordo com:
- `b`: número de viagens;
- `s`: número de paradas em cada viagem.

Como cada viagem possui `s - 1` trechos, o tamanho real do vetor processado em cada caso depende diretamente de `s`.

Assim, o custo do algoritmo depende de:
- quantas viagens precisam ser processadas;
- quantos trechos existem em cada viagem.

## Como você interpretou determinada parte do enunciado?
A interpretação mais importante é que os valores lidos não representam as paradas, e sim os trechos entre paradas consecutivas.

Por exemplo:
- `n1` representa o trecho entre a parada 1 e a parada 2;
- `n2` representa o trecho entre a parada 2 e a parada 3;
- e assim por diante.

Por isso, se o algoritmo encontra o melhor subarray entre os índices `a` e `b` do vetor, a resposta em termos de paradas será:
- início: `a + 1`
- fim: `b + 2`

Também interpretei explicitamente a regra de desempate do enunciado:
1. escolher a maior soma;
2. se houver empate, escolher o trecho mais longo;
3. se o empate continuar, escolher o trecho que começa primeiro.

---

# 2. Ideia geral do algoritmo (alto nível)

## Qual técnica ou paradigma algorítmico foi utilizado?
Foi utilizado o algoritmo de Kadane, que é uma solução clássica para o problema do subarray de soma máxima.

Essa abordagem se encaixa em programação dinâmica, porque o algoritmo aproveita a melhor solução parcial até a posição atual para decidir a melhor solução na posição seguinte.

## Como o algoritmo funciona de forma geral? Descreva os passos principais e contextualize a explicação no paradigma adotado
A ideia do algoritmo é percorrer o vetor de *niceness* apenas uma vez.

Durante esse percurso, ele mantém:
- a soma do trecho atual;
- o início do trecho atual;
- a melhor soma encontrada até o momento;
- o início e o fim do melhor trecho encontrado.

Em cada posição `i`, o algoritmo decide entre duas opções:
- continuar o trecho atual, somando `arr[i]`;
- ou começar um novo trecho a partir de `arr[i]`.

Essa decisão é feita comparando:
- `currentSum + arr[i]`
- `arr[i]`

Se for melhor começar de novo em `i`, o algoritmo reinicia o trecho atual. Caso contrário, continua acumulando.

Depois disso, ele compara a soma atual com a melhor soma global:
- se a soma atual for maior, atualiza a resposta;
- se a soma empatar, aplica a regra de desempate pelo maior comprimento;
- se ainda empatar, mantém a primeira ocorrência, como pede o enunciado.

Essa lógica é típica de programação dinâmica porque, em vez de testar todos os subarrays possíveis, o algoritmo resolve o problema localmente em cada posição usando o melhor resultado parcial disponível.

## Existem estruturas de dados específicas sendo utilizadas? Por quê?
Sim. A principal estrutura de dados utilizada é o `vector<int>`.

Ele é usado para armazenar os valores de *niceness* da rota porque:
- a quantidade de trechos varia conforme a entrada;
- o vetor permite acesso por índice em tempo constante;
- é uma estrutura simples e suficiente para o problema.

Além disso, o restante da solução usa apenas variáveis inteiras auxiliares para armazenar:
- somas;
- índices de início;
- índices de fim.

Não é necessário usar estruturas mais complexas, pois o problema pode ser resolvido apenas com um vetor e algumas variáveis de controle.

---

# 3. Explicação de como o código funciona

O código está dividido em duas partes principais:
- o `main`, que lê a entrada;
- a função `maxSubarraySum`, que processa cada rota.

No `main`, o programa começa lendo o número total de viagens. Depois, para cada viagem, lê o número de paradas e, em seguida, lê os `s - 1` valores de *niceness* dos trechos. Esses valores são colocados em um `vector<int>`. Depois que o vetor da rota é montado, ele é enviado para a função `maxSubarraySum`, junto com o número da rota, para que a resposta seja calculada.

Na função `maxSubarraySum`, o algoritmo começa inicializando a melhor soma encontrada até o momento e a soma do trecho atual com o primeiro elemento do vetor. Isso é feito porque o algoritmo sempre precisa partir de um valor válido da entrada. Também são criadas variáveis para marcar:
- onde começa o melhor trecho encontrado;
- onde termina o melhor trecho encontrado;
- onde começa o trecho atual em análise.

Depois disso, o algoritmo percorre o vetor da segunda posição até a última. Em cada posição, ele toma a decisão central do Kadane: verificar se vale mais a pena continuar o trecho atual ou abandonar tudo e começar um novo trecho naquela posição. Essa decisão é feita comparando a soma acumulada atual mais o valor novo com o próprio valor novo sozinho.

Se começar do zero for melhor, o algoritmo redefine a soma atual e marca que o trecho atual passa a começar naquela posição. Se continuar for melhor, ele apenas soma o valor atual ao trecho que já vinha sendo construído.

Logo após atualizar a soma atual, o código verifica se esse trecho atual ficou melhor que a melhor resposta já encontrada. Se a soma atual for maior, ele atualiza a melhor soma e salva o início e o fim desse novo melhor trecho.

Se a soma atual empatar com a melhor soma, o código entra na regra de desempate exigida pelo problema. Nesse caso, ele compara o tamanho do trecho atual com o tamanho do melhor trecho já salvo. Se o trecho atual for maior, ele substitui a resposta anterior. Se também tiver o mesmo tamanho, ele não troca, preservando o trecho que começou primeiro, exatamente como o enunciado exige.

Ao final do processamento da rota, o código verifica se a melhor soma encontrada é positiva. Se não for, significa que Jill não deve pedalar em nenhum trecho, então a mensagem impressa é que a rota não possui partes agradáveis. Caso contrário, o programa imprime entre quais paradas está o melhor trecho.

O ajuste dos índices na saída é necessário porque o vetor guarda trechos, não paradas. Se o melhor subarray vai do índice `a` até o índice `b`, então isso corresponde às paradas `a + 1` até `b + 2`.

---

# 4. Complexidade assintótica e análise

## Qual é a complexidade de tempo do seu algoritmo? Justifique
A complexidade de tempo do algoritmo é `O(n)` para cada rota, onde `n` é o número de trechos da viagem, ou seja, o tamanho do vetor de *niceness*.

Isso acontece porque o vetor é percorrido apenas uma vez. Em cada iteração, o algoritmo realiza apenas operações de tempo constante, como:
- somas;
- comparações;
- atribuições.

Portanto, o custo cresce linearmente em relação ao tamanho da rota.

Se considerarmos todas as viagens, a complexidade total pode ser descrita como a soma dos tamanhos de todos os vetores processados.

## Qual é a complexidade de espaço utilizada? Por quê?
A complexidade de espaço adicional da função é `O(1)`, porque além do vetor de entrada ela utiliza apenas um número fixo de variáveis auxiliares:
- `bestSum`
- `currentSum`
- `bestStart`
- `bestEnd`
- `currentStart`

Como essa quantidade de variáveis não depende do tamanho da entrada, o espaço extra é constante.

Se também considerarmos o armazenamento do vetor da rota no `main`, então o espaço total usado para armazenar a entrada daquela rota é `O(n)`.

## Qual é a complexidade deste laço/trecho específico?
O laço principal da função percorre o vetor apenas uma vez, então sua complexidade é `O(n)`.

As verificações internas, como:
- decidir entre continuar ou reiniciar o trecho atual;
- atualizar a melhor resposta;
- aplicar o desempate,

possuem custo `O(1)`, pois envolvem apenas comparações e atribuições simples.

Assim, o trecho dominante do algoritmo continua sendo linear.