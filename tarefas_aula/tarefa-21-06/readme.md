# Resolução do problema do Leetcode, proposto em aula, "Lemonade change"
**Autor: Antônio Brum**

_Como resolvi em tempo de aula, estou deixando apenas 1 arquivo '.c'_

## Descrição do problema 
  O problema é bastante simples: A limonada que estamos vendendo custa $5, os clientes só pagam a limonada com notas de $5, $10, $20. Um de cada vez. Aos clientes que pagam com notas maiores que $5 é preciso devolver o troco. Então é preciso desenvolver um programa que, dado o vetor de notas de clientes (cada elemento equivale a um cliente), retorne 'true' quando todos os clientes que precisavam de troco receberam ou retorne 'false' quando não havia notas para dar o troco a algum cliente.

## Testes
  O programa passa em todos os testes aos quais o leetcode o submete. Vou apresentar apenas 3 destes testes:

1. `input = [5,5,5,10,20]` -> Neste caso é esperado 'true' como output visto que é possível dar troco a todos os clientes;
2. `input = [5,5,10,10,20]` -> Neste caso é esperado 'false' como output pois não nos resta notas de $5 para dar o troco ao último cliente;
3. `input = [5,5,10,20,5,5,5,5,10,20,5,20]` -> Neste caso é esperado 'true' como output pois, mesmo sem notas de $10 para dar troco ao último cliente, possuímos $15 em notas de $5;
