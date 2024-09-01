# Resolução do leetcode ` 826. Most Profit Assigning Work `
**Autor: Antônio Brum**

_Esta pasta contém dois arquivos .c: Um deles é o código feito em aula (que passa em todos os testes mas excede o tempo) o outro é o código feito em casa (este sim, aceito como solução)_

## Descrição do problema

You have n jobs and m workers. You are given three arrays: difficulty, profit, and worker where:
  * difficulty[i] and profit[i] are the difficulty and the profit of the ith job, and
  * worker[j] is the ability of jth worker (i.e., the jth worker can only complete a job with difficulty at most worker[j]).

Every worker can be assigned at most one job, but one job can be completed multiple times.
For example, if three workers attempt the same job that pays $1, then the total profit will be $3. If a worker cannot complete any job, their profit is $0. 

Return the maximum profit we can achieve after assigning the workers to the jobs.

## Testes

Os dois primeiros testes do leetcode servem para dar uma noção geral de como o código deve se comportar. Os casos são:
1. `difficulty = [2,4,6,8,10]` -- `profit = [10,20,30,40,50]` -- `worker = [4,5,6,7]` -- `expected output: 100` -- `output: 100`
2. `difficulty = [85, 47, 57]` -- `profit = [24, 66, 99]` -- `worker = [40, 25, 25]` -- `expected output: 0` -- `output: 0`

## Sobre os programas

### Feito em aula
  Consegui desenvolver o algorítmo que acerta em todos os casos, porém ele excedia o tempo limite de execução determinado pelo
  leetcode. \
  Até comecei a escrever o código para fazer merge sort nos arrays e conseguir otimizar a lógica mas não daria tempo de terminar até o fim da aula.
  Então submeti o código que estava quase funcionando.
  
### Feito em casa
  Em casa terminei de escrever o merge sort que mudaria 2 arrays ao mesmo tempo (`difficulty` e `profit`).
  Otimizei a lógica, que é bastante facilitada quando a ordem crescente dos elementos do array é garantida, e minha submissão no leetcode foi aceita.
  A diferença que a ordenação fez no meu código foi tão grande que era mais rápido executar a ordenação 2 vezes e então partir para procurar os trabalhos mais
  lucrativos para os trabalhadores usando uma lógica um pouco mais otimizada (não muitas linhas de código a mais que o código feito em aula) do que apenas executar a busca
  por força bruta (de longe).
  
## Análise de complexidade
* Complexidade em tempo: O(nlogn + n*m).
  - nlogn é o tempo que leva para a execução do merge sort.
  - No laço principal o array dos trabalhadores é percorrido por inteiro, já o array de dificuldade não é percorrido por inteiro a cada iteração. Ele ignora todos os profits menores
    e parte do maior profit já encontrado e vai até que a dificuldade seja maior que a habilidade do trabalhador.
  - Ainda assim, no pior caso, o trabalho mais lucrativo será o primeiro mas a habilidade dos trabalhadores serão a maior possível. Neste caso todo o array de dificuldade será percorrido a cada iteração. 
  
* Complexidade em espaço: O(n).
  - O espaço usado será apenas o de call stack para a realização do merge sort e após isso haverá somente as variáveis da função principal.
