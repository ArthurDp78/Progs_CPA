# 1. Definicao e entendimento do problema

## Qual e o objetivo do problema? O que precisa ser calculado ou determinado?
O objetivo do problema e descobrir qual premio cada aluno deve receber com base em sua pontuacao.

Existem `n` faixas de premiacao e cada faixa possui um premio associado. As fronteiras entre essas faixas sao dadas por uma lista de limites. Para cada uma das `m` pontuacoes informadas, o programa precisa determinar em qual faixa a nota se encaixa e imprimir o premio correspondente.

Em termos computacionais, o problema pede para localizar, para cada pontuacao, a primeira faixa cujo limite superior e maior que a pontuacao do aluno. A partir dessa faixa, o programa acessa o vetor de premios e devolve a resposta.

## Quais sao as entradas e saidas esperadas?
A entrada possui:
- um inteiro `n`, que representa a quantidade de faixas de premiacao;
- um inteiro `m`, que representa a quantidade de alunos;
- `n - 1` inteiros, que representam os limites entre as faixas;
- `n` inteiros, que representam o premio associado a cada faixa;
- `m` inteiros, que representam as pontuacoes dos alunos.

A saida consiste em `m` valores, impressos na mesma ordem em que as pontuacoes foram lidas. Cada valor corresponde ao premio que o respectivo aluno deve receber.

## Como a entrada do problema pode crescer? Isto e, quais sao as variaveis ou parametros de entrada que controlam isso?
A entrada cresce principalmente de acordo com:
- `n`: numero de faixas de premiacao;
- `m`: numero de alunos.

O tamanho do vetor de limites depende de `n - 1`, o tamanho do vetor de premios depende de `n` e o numero de buscas realizadas depende diretamente de `m`.

Assim, o custo total do algoritmo depende de:
- quantas faixas precisam ser consideradas;
- quantas pontuacoes precisam ser classificadas.

## Como voce interpretou determinada parte do enunciado?
Interpretei que os `n - 1` valores de limite separam `n` intervalos de pontuacao.

Isso significa que:
- alunos com nota menor que o primeiro limite ficam na faixa `0`;
- alunos com nota entre dois limites consecutivos ficam em uma faixa intermediaria;
- alunos com nota maior ou igual ao ultimo limite ficam na ultima faixa.

No codigo, isso foi implementado procurando a primeira posicao do vetor `thresholds` em que o limite e estritamente maior que a pontuacao. O indice encontrado ja e exatamente o indice do premio no vetor `awards`.

---

# 2. Ideia geral do algoritmo (alto nivel)

## Qual tecnica ou paradigma algoritmico foi utilizado?
Foi utilizada busca binaria, implementada de forma recursiva.

Esse paradigma e adequado porque os limites das faixas estao organizados em ordem, entao nao e necessario testar um por um. Em vez disso, o algoritmo reduz pela metade o espaco de busca a cada chamada.

## Como o algoritmo funciona de forma geral? Descreva os passos principais e contextualize a explicacao no paradigma adotado
A ideia geral e:
- ler os limites das faixas;
- ler os premios de cada faixa;
- para cada pontuacao de aluno, fazer uma busca binaria no vetor de limites;
- usar o indice encontrado para acessar diretamente o premio correto.

A funcao recursiva recebe:
- o vetor de limites;
- a pontuacao do aluno;
- o intervalo atual de busca, definido por `left` e `right`.

Em cada chamada:
- calcula-se o meio do intervalo;
- se a pontuacao for menor que o limite do meio, a resposta esta na metade esquerda;
- caso contrario, a resposta esta da posicao seguinte ao meio para a direita.

Quando `left` ultrapassa `right`, a busca termina. Nesse momento, `left` aponta exatamente para a faixa correta do aluno.

## Existem estruturas de dados especificas sendo utilizadas? Por que?
Sim. O codigo utiliza principalmente:
- `vector<int> thresholds`, para armazenar os limites entre as faixas;
- `vector<int> awards`, para armazenar o premio de cada faixa;
- `vector<int> scores`, para armazenar as pontuacoes dos alunos;
- `vector<string> result`, para guardar os premios ja convertidos para impressao.

Essas estruturas sao suficientes porque o problema exige apenas:
- acesso por indice em tempo constante;
- percorrer os alunos em ordem;
- consultar rapidamente os limites.

Nao ha necessidade de estruturas mais complexas, pois a busca eficiente ja e garantida pela busca binaria sobre o vetor ordenado de limites.

---

# 3. Detalhes de implementacao do codigo

## O que esta funcao/trecho de codigo faz especificamente?
A funcao `find_award_index` faz uma busca binaria recursiva no vetor `thresholds` para descobrir em qual faixa de premiacao uma pontuacao se encaixa.

Ela nao procura um valor igual, e sim a primeira posicao cujo limite e maior que a pontuacao. Por isso, quando a busca termina, o valor de `left` representa exatamente o indice da faixa correta.

Ja o `main` organiza o fluxo do programa:
- le a entrada;
- armazena limites, premios e pontuacoes;
- chama a busca binaria para cada aluno;
- imprime os premios correspondentes.

## Por que voce utilizou esta estrutura de dados/variavel neste ponto?
O vetor `thresholds` foi usado porque os limites precisam ser acessados por indice durante a busca binaria. Como o acesso em `vector` e `O(1)`, ele funciona muito bem para esse tipo de consulta.

O vetor `awards` foi separado de `thresholds` porque cada faixa precisa apontar diretamente para um premio. Assim, depois de descobrir o indice da faixa, basta acessar `awards[award_index]`.

O vetor `scores` foi usado para armazenar todas as pontuacoes lidas da entrada antes do processamento. Isso deixa o fluxo do programa mais organizado.

O vetor `result` guarda a saida parcialmente montada para que todos os premios possam ser impressos depois, na ordem correta e com o espacamento controlado.

As variaveis `left`, `right` e `mid` existem para representar o intervalo atual da busca binaria:
- `left` marca o inicio do intervalo;
- `right` marca o fim;
- `mid` representa o elemento central usado na comparacao.

## Explique o funcionamento deste laco/condicao especifica
O laco `for (int score : scores)` percorre todas as pontuacoes dos alunos. Em cada iteracao, ele resolve um aluno de forma independente:
- descobre a faixa da pontuacao;
- recupera o premio correspondente;
- adiciona esse premio ao vetor de respostas.

A condicao `if (score < thresholds[mid])` e a decisao principal da busca binaria.

Quando ela e verdadeira, significa que o limite central ja e maior que a pontuacao, entao a resposta so pode estar na metade esquerda do vetor. Quando ela e falsa, significa que a pontuacao ainda nao ficou antes daquele limite, entao a busca continua na metade direita.

A condicao `if (left > right)` e o caso base da recursao. Quando isso acontece, o intervalo de busca ficou vazio, e o valor atual de `left` passa a indicar exatamente a posicao em que a pontuacao deve ser encaixada.

## O que acontece nesta linha/bloco de codigo em um cenario especifico?
Se a pontuacao for menor que todos os limites do vetor, a recursao sempre vai caminhar para a esquerda ate terminar com `left = 0`. Nesse caso, o aluno recebe `awards[0]`, isto e, o premio da primeira faixa.

Se a pontuacao for maior ou igual a todos os limites, a recursao vai caminhar para a direita ate terminar com `left = thresholds.size()`. Como o vetor `awards` tem tamanho `n`, essa posicao corresponde exatamente a ultima faixa.

Na linha que faz `result.push_back(to_string(awards[award_index]))`, o programa converte o premio numerico em texto e o armazena. Isso facilita a impressao posterior sem precisar recalcular nada.

Se a leitura inicial `if (!(cin >> n >> m))` falhar, o programa encerra imediatamente. Esse bloco evita que o codigo tente processar uma entrada inexistente ou incompleta.

---

# 4. Complexidade assintotica e analise

## Qual e a complexidade de tempo do seu algoritmo? Justifique
A complexidade de tempo para classificar uma unica pontuacao e `O(log n)`, porque a busca binaria reduz o intervalo de busca pela metade a cada passo.

Como o programa realiza essa busca para cada um dos `m` alunos, a complexidade total do processamento das pontuacoes e `O(m log n)`.

Se tambem considerarmos a leitura da entrada, existe ainda:
- `O(n)` para ler os limites;
- `O(n)` para ler os premios;
- `O(m)` para ler as pontuacoes.

Assim, o custo total do programa e `O(n + m log n)`, considerando o trecho dominante da classificacao.

## Qual e a complexidade de espaco utilizada? Por que?
O programa usa:
- `O(n)` para armazenar os limites;
- `O(n)` para armazenar os premios;
- `O(m)` para armazenar as pontuacoes;
- `O(m)` para armazenar o resultado em formato de texto.

Portanto, o espaco total utilizado pelo programa e `O(n + m)`.

Quanto a pilha de recursao da busca binaria, cada chamada reduz o problema pela metade, entao a profundidade maxima e `O(log n)`.

## Qual e a complexidade deste laco/trecho especifico?
O laco principal do `main` que percorre `scores` executa `m` vezes.

Dentro dele, a operacao dominante e a chamada da busca binaria recursiva, que custa `O(log n)`. Assim, esse trecho tem custo total `O(m log n)`.

As demais operacoes internas, como converter para `string`, inserir no vetor de resposta e imprimir, possuem custo constante por iteracao no contexto da analise principal.
