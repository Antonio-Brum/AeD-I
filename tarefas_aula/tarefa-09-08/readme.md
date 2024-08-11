# Resolução do leetcode ` 865. Smallest Subtree with all the Deepest Nodes ` 
**Autor: Antônio Brum**

_Esta pasta contém dois arquivos .c: Um deles é o código feito em aula (que não está completo) o outro é o código feito em casa (este sim, completo)_

## Descrição do problema 

* Given the root of a binary tree, the depth of each node is the shortest distance to the root.
* Return the smallest subtree such that it contains all the deepest nodes in the original tree.
* A node is called the deepest if it has the largest depth possible among any node in the entire tree.
* The subtree of a node is a tree consisting of that node, plus the set of all descendants of that node.
\
\
Traduzindo: É preciso descobrir os nodos mais profundos e, então, retornar a menor árvore que contém estes nodos;

## Testes

Os três primeiros testes do github servem para dar uma noção geral de como o código deve se comportar. Os casos são:
1. `input: [3,5,1,6,2,0,8,null,null,7,4]` -- `expected: [2,7,4]` -- `output: [2,7,4]`
2. `input: [1]` -- `expected: [1]` -- `output: [1]`
3. `input: [0,1,3,null,2]` -- `expected: [2]` -- `output: [2]`

## Sobre os programas

### Feito em aula
Em aula eu consegui calcular a profundidade e guardar o nó mais profundo. Também pensei na lógica que usei para fazer o programa em casa. \
\
Ainda assim não consegui avançar muito em tempo da aula pois, seguindo a lógica que pensei inicialmente, estava bem difícil de debuggar. Além disso tentei bastante encontrar outra solução pois tinha certeza que o código poderia ficar menos bagunçado do que ele ficaria usando o jeito que pensei primeiro.

### Feito em casa
Em casa tive tempo para debuggar o programa, acertar os ponteiros e concluir a lógica.\
Passou em todos os testes do leetcode (mas passou longe de performar bem).

## Análise de complexidade
* Complexidade em tempo: O(n*h).\
      - No pior caso, toda vez que o programa encontrar uma folha, esta folha seja tão profunda quanto a anterior. Como o caminho é copiado para um novo espaço de memória, item por item, o algorítmo seria de O(n*h), onde 'n' é o número de nodos e 'h' é a altura do caminho que será copiado.
  
* Complexidade em espaço: O(n).
    - No pior caso será preciso armazenar vários caminhos. Ocupará o espaço para os nodos da árvore, para os vetores de ponteiros que representam as subárvores que contém os nodos mais profundos e mais um espaço de tamanho fixo de alocado para `path`.   
