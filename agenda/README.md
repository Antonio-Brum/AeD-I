# Agenda pBuffer

**Autor: Antônio Brum**

## Proposta:

  Faça uma agenda com o seguinte menu:
1. Adicionar Pessoa (Nome, Idade, email)
2. Remover Pessoa
3. Buscar Pessoa
4. Listar todos
5. Sair

O desafio é não poder criar variáveis e sim um buffer de memória (void *pBuffer). Nisso vocês terão que fazer o trabalho que o Sistema Operacional faz para vocês ao organizar a memória.

1. Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.

   1.1 Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.

   1.2 Exemplo do que não pode: `int c; char a; int v[10]; void Funcao(int parametro)`

3. Não pode usar struct em todo o programa.

4. Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.

   3.1 Implementar a base de dados da agenda usando lista duplamente ligada.

   3.2 Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um `malloc` para cada nodo.

## Ideias futuras:
- Poder ler as strings dinamicamente;
- Usar mais #defines;
- Refatorar a função Push()
