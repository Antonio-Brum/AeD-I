#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_INT         sizeof( int )
#define TAM_PONT        sizeof( void * )
#define MAX_NOME        sizeof( char ) * 50


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
    30 char (51 bytes) para o nome;
    25 char (25 bytes) para o email;
    1 unsigned short int (2 bytes) para a idade; 
    1 void *(8 bytes) para armazenar o próximo nodo;
    1 void *(8 bytes) para armazenar o nodo anterior;
        total: 94 bytes por Nodo.
*/

// typedef struct{
//     nodo_t *first;
//     nodo_t *last;
// }fila_t;

void *pBuffer = NULL;
void *pHeap = NULL;




void AlocaBuffer( );
void Menu( );
void Push( void* nodo ); //vai adicionar um nodo a partir do final da fila
void *Pop( ); //vai retornar o nodo do inícido da fila
void Empty( );
void AdPessoa( );
void RmPessoa( );
void BuscaPessoa( );
void ListTodos( );
void LeString( );
void *CriaNodo( char *nome, char *email, int idade );

//pBuffer[0]  = um inteiro que armazena a escolha do usuário (4 bytes) -> pBuffer +0 
//pBuffer[1] = inteiro i, para usar em laços (4 bytes) -> pBuffer +4
//pBuffer[2] = unsigned char, para ler a string de input (1 byte ) -> pBuffer + 8
//pBuffer[3] = char *, guarda a string do usuário ( MAX_NOME ) -> pBuffer + 9
//pBuffer[X] = void *, aponta para o primeiro node na fila -> 
//pBuffer[X+1] = void *, aponta para o último nodo na fila
//pBuffer[x+2] = void *, ponteiro que vai servir como `temp` para manipular os nodos na fila
//pBuffer[x+3] = void *, ponteiro para o primeiro nodo da lista temporária
//pBuffer[x+4] = void *, ponteiro para o último nodo da lista temporária

int main()
{
    AlocaBuffer();
    //pHeap = calloc( 75, sizeof( char ) );//Tenho o primeiro Nodo

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
            free(pBuffer);
			return 0;
		break;
		}
	}
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
    pBuffer = calloc( 60, sizeof( char ) );
    //*( ( void ** )( pBuffer + 8 ) ) = calloc( 75, sizeof( char ) ); 
    return;
}


void AdPessoa( ){

    //char * nome = LeString( );
    LeString( );
    printf( "\n%s\n", ( ( char * )( pBuffer + 9 ) ) );
    //free(nome);
    // char * email = LeString( );
    // int idade;
    // scanf( "%d", &idade );
    
    // void *nodo = CriaNodo( nome, email, idade );

    // Push( nodo );
    
    // printf("adicionei\n");

    return;
}

void LeString( ){
    //char c;
    //char *nome = ( char * )calloc( 1, MAX_NOME);
    //*( ( char * )( pBuffer+9 ) ) = ( char * )calloc( 1, MAX_NOME);
    //int i = 0;

    *( ( int * )pBuffer ) = 0; 

    *( ( char * )( pBuffer + 8 ) ) = getchar( );

    //printf( "\n--%c--\n", *( ( char * )( pBuffer + 8 ) ) );
    //printf( "\n--%d--\n", *( ( int * )( pBuffer ) ) );

    while( *( ( char * )( pBuffer + 8 ) ) != '\n' && *( ( int * )pBuffer ) < MAX_NOME ){
        //nome[ i++ ] = c;
        *( ( char * )( pBuffer + 9 + ( *( ( int * )pBuffer ) ) ) ) = *( ( char * )( pBuffer + 8 ) );
        ( *( ( int * )pBuffer ) )++;
        *( ( char * )( pBuffer + 8 ) ) = getchar( );
    }
    //nome[ i ] = '\0';
    *( ( char * )( pBuffer + 9 + *( ( int * )pBuffer ) ) ) = '\0';

    return;
}