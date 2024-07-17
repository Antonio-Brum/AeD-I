#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_INT         sizeof( int )
#define TAM_PONT        sizeof( void * )
#define MAX_NOME        sizeof( char ) * 51
#define MAX_MAIL        sizeof( char ) * 26

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
    51 char (51 bytes) para o nome;
    26 char (26 bytes) para o email;
    1 unsigned short int (2 bytes) para a idade; 
    1 void *(8 bytes) para armazenar o próximo nodo;
    1 void *(8 bytes) para armazenar o nodo anterior;
        total: 95 bytes por Nodo.
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
void LeString( void *posicao);
void *CriaNodo( char *nome, char *email, int idade );

//pBuffer[0]  = um inteiro que armazena a escolha do usuário (4 bytes) -> pBuffer +0 
//pBuffer[1] = inteiro i, para usar em laços (4 bytes) -> pBuffer +4
//pBuffer[2] = inteiro contador de contatos (4 bytes) -> pBuffer +8
//pBuffer[2] = unsigned char, para ler a string de input (1 byte ) -> pBuffer + 12
//pBuffer[3] = char *, guarda a string do usuário ( MAX_NOME ) -> pBuffer + 13
//pBuffer[4] = char *, guarda o email do contato ( MAX_MAIL ) -> pBuffer + 64
//pBuffer[5] = short unsigned int idade , guarda a idade do contato (2 bytes) -> pBuffer + 90
//CONTADOR DE CONTATOS
//LER STRING VS LER NOME E LER EMAIL
//pBuffer[X] = void *, aponta para o primeiro node na fila -> 
//pBuffer[X+1] = void *, aponta para o último nodo na fila
//pBuffer[x+2] = void *, ponteiro que vai servir como `temp` para manipular os nodos na fila
//pBuffer[x+3] = void *, ponteiro para o primeiro nodo da lista temporária
//pBuffer[x+4] = void *, ponteiro para o último nodo da lista temporária

int main()
{
    AlocaBuffer();
    printf("%s", ((char *)pBuffer));
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
		scanf("%d", ((int*)pBuffer));
	}
	while ( ( ( int* )pBuffer)[0] <= 0 || ((int*)pBuffer)[0] > 5);
	getchar();  
    return;
}


void AlocaBuffer( ){
    pBuffer = calloc( 150, sizeof( char ) );
    //*( ( void ** )( pBuffer + 8 ) ) = calloc( 75, sizeof( char ) ); 
    return;
}


void AdPessoa( ){

    //char * nome = LeString( );
    LeString( pBuffer + 13 );
    printf( "\n%s\n", ( ( char * )( pBuffer + 13 ) ) );
    //free(nome);
    // char * email = LeString( );
    LeString( pBuffer + 64 );
    printf( "\n%s\n", ( ( char * )( pBuffer + 64 ) ) );

    // int idade;
    scanf( "%d", ((int *)(pBuffer + 90)) );
    printf("\n%d\n", *((int *)(pBuffer + 90)));
    
    // void *nodo = CriaNodo( nome, email, idade );

    // Push( nodo );
    
    // printf("adicionei\n");

    return;
}

void LeString( void *posicao ){
    //char c;
    //char *nome = ( char * )calloc( 1, MAX_NOME);
    //*( ( char * )( pBuffer+9 ) ) = ( char * )calloc( 1, MAX_NOME);
    //int i = 0;

    *( ( int * )( pBuffer + 4 ) ) = 0; 

    *( ( char * )( pBuffer + 12 ) ) = getchar( );

    //printf( "\n--%c--\n", *( ( char * )( pBuffer + 8 ) ) );
    //printf( "\n--%d--\n", *( ( int * )( pBuffer ) ) );
    //*((int *)pBuffer) = strlen(((char *)posicao)); //testa o tamanho da string a partir da posição recebida
    if(posicao == (pBuffer + 13)){
        *((int *)pBuffer) = MAX_NOME;
    } else {
        *((int *)pBuffer) = MAX_MAIL;
    }
    printf("%d", *((int *)pBuffer));

    while( *( ( char * )( pBuffer + 12 ) ) != '\n' && *( ( int * )( pBuffer + 4 ) ) < *((int *)pBuffer) ){
        //nome[ i++ ] = c;
        *( ( char * )( posicao + ( *( ( int * )( pBuffer + 4 ) ) ) ) ) = *( ( char * )( pBuffer + 12 ) );
        ( *( ( int * )( pBuffer + 4 ) ) )++;
        *( ( char * )( pBuffer + 12 ) ) = getchar( );
    }
    //nome[ i ] = '\0';
    *( ( char * )( posicao + ( *( ( int * )(pBuffer + 4 ) ) ) ) )= '\0';

    return;
}