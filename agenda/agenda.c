#include <stdio.h>
#include <stdlib.h>

#define TAM_INT         sizeof(int)
#define TAM_PONT        sizeof(void *)


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
    1 unsigned short int (2 bytes) para a idade; 
    1 void *(8 bytes) para armazenar o próximo nodo;
    1 void *(8 bytes) para armazenar o nodo anterior;
        total: 73 bytes por Nodo.
*/

// typedef struct{
//     nodo_t *first;
//     nodo_t *last;
// }fila_t;

void *pBuffer = NULL;
void *pHeap = NULL;




void AlocaBuffer( );
void Menu( );
void Push( ); //vai adicionar um nodo a partir do final da fila
void *Pop( ); //vai retornar o nodo do inícido da fila
void Empty( );
void AdPessoa( );
void RmPessoa( );
void BuscaPessoa( );
void ListTodos( );

//pBuffer[0]  = um inteiro que armazena a escolha do usuário (4 bytes)
//pBuffer[1] = inteiro i, para usar em laços (4 bytes)
//pBuffer[2] = void *, aponta para o primeiro nome na fila
//pBuffer[3] = void *, aponta para o último nome na fila
//pBuffer[x-1] = void *, ponteiro que vai servir como `temp` para manipular os nodos na fila
//pBuffer[x] = void *, ponteiro para o primeiro nodo da lista temporária
//pBuffer[x+1] = void *, ponteiro para o último nodo da lista temporária

int main()
{
    AlocaBuffer();
    pHeap = calloc( 75, sizeof( char ) );//Tenho o primeiro Nodo

    // printf("%p\n", &pBuffer);
    // printf("%p\n", &pBuffer+8);
    // printf("%p\n", &pBuffer+16);
    // printf("%p\n", &((( int* )pBuffer)[2]));
    // //*(((char**)(pBuffer + 8))) = pHeap;//salva o primeiro espaço apontado pelo pHeap em pBuffer[3]
    // //( ( char** ) pBuffer)[2] = pHeap;

    // //printf("%p\n", pHeap);
    // //printf("%p\n", &pHeap);
    // printf("%p\n", &(((void**)pBuffer)[2]));
    // //printf("%p\n", *((void**)(pBuffer+8)));
    // //printf("%p\n", ((char**)pBuffer)[2]);

	for (;;) {
        Menu();
		switch ( *( ( int* ) pBuffer )  ) {
		case 1:
            AdPessoa( );

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

void Menu( )
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


void AlocaBuffer( ){
    pBuffer = calloc( 48, sizeof( char ) );
    //*( ( void ** )( pBuffer + 8 ) ) = calloc( 75, sizeof( char ) ); 
    return;
}


void AdPessoa( ){

    char * nome = leString( );
    char * email = leString( );
    int idade;
    scanf( "%d", &idade );
    
    void *nodo = criaNodo( nome, email, idade );

    Push( nodo );
    
    printf("adicionei\n");

    return;
}