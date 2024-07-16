#include <stdio.h>
#include <stdlib.h>


// typedef struct{
//     char *nome;
//     char *email;
//     int idade;
// }contato_t;

// typedef struct{
//     contato_t pessoa;
//     struct nodo_t *pNext;
//     struct nodo_t *pPrevious;
// }nodo_t;

/*

Nodo_contato vai possuir:
    30 char (30 bytes) para o nome;
    25 char (25 bytes) para o email;
    1 int (4 bytes) para a idade; 
    1 void *(8 bytes) para armazenar o próximo nodo;
    1 void *(8 bytes) para armazenar o nodo anterior;
        total: 75 bytes por Nodo.
*/

// typedef struct{
//     nodo_t *first;
//     nodo_t *last;
// }fila_t;

void *pBuffer;
void *pHeap;





void menu( );



//pBuffer[0] = um inteiro que armazena a escolha do usuário (4 bytes)
//pBuffer[1] = inteiro i, para usar em laços (4 bytes)
//pBuffer[2] = void *, aponta para o primeiro nome na fila
//pBuffer[3] = void *, aponta para o último nome na fila

int main()
{
    pBuffer = calloc( 24, sizeof( char ) ); // 
    pHeap = calloc( 75, sizeof( char ) );//Tenho o primeiro Nodo

 printf("%p\n", pBuffer);
 printf("%p\n", pBuffer);
    *(((void**)(pBuffer + 8))) = pHeap;

    printf("%p\n", pHeap);
    printf("%p\n", &pHeap);
    printf("%p\n", *((void**)(pBuffer+8)));

	for (;;) {
        menu();
		switch ( *( ( int* ) pBuffer )  ) {
		case 1:
            printf("1\n");
    
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			exit(0);
			break;
		}
	}
    free(pBuffer);
	return 0;
}

void menu( )
{
	do {
		printf("-- MENU:\n");
		printf("\t 1. Adicionar pessoa\n");
		printf("\t 2. Remover pessoa\n");
		printf("\t 3. Buscar pessoa\n");
		printf("\t 4. Listar todos\n");
		printf("\t 5. Sair\n");
		printf("-- Digite sua escolha: ");
		scanf("%d", &((int*)pBuffer)[0]);
	}
	while ( ( ( int* )pBuffer)[0] <= 0 || ((int*)pBuffer)[0] > 5);
	getchar();  
    return;
}