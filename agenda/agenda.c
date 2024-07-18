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
void BuscaPush( void* nodo, void* pAux, void* pLast, void* pFirst);
void *Pop( ); //vai retornar o nodo do inícido da fila
void Empty( );
void AdPessoa( );
void RmPessoa( );
void BuscaPessoa( );
void ListTodos( );
void LeString( void *posicao);
void CriaNodo(void *nome, void *email, void *idade);

//pBuffer[0]  = um inteiro que armazena a escolha do usuário (4 bytes) -> pBuffer +0 
//pBuffer[1] = inteiro i, para usar em laços (4 bytes) -> pBuffer +4
//pBuffer[2] = inteiro contador de contatos (4 bytes) -> pBuffer +8
//pBuffer[3] = unsigned char, para ler a string de input (1 byte ) -> pBuffer + 12
//pBuffer[4] = char *, guarda a string do usuário ( MAX_NOME ) -> pBuffer + 13
//pBuffer[5] = char *, guarda o email do contato ( MAX_MAIL ) -> pBuffer + 64
//pBuffer[6] = short unsigned int idade , guarda a idade do contato (2 bytes) -> pBuffer + 90
//pBuffer[x+2] = void *, ponteiro que vai servir como `temp` para manipular os nodos na fila (8 bytes) -> pBuffer + 92
//pBuffer[X] = void *, aponta para o primeiro node na fila -> pBuffer + 100
//pBuffer[X+1] = void *, aponta para o último nodo na fila -> pBuffer + 108
//pBuffer[não sei mais] = void *, ponteiro auxiliar pra fazer a busca -> pBuffer + 116
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
            free(*( ( void** )( pBuffer + 92 ) ));
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
    *(char**)(pBuffer + 100) = NULL;
    *(char**)(pBuffer + 108) = NULL;
    return;
}


void AdPessoa( ){

    //char * nome = LeString( );
    LeString( pBuffer + 13 );
    //printf( "\n%s\n", ( ( char * )( pBuffer + 13 ) ) );
    //free(nome);
    // char * email = LeString( );
    LeString( pBuffer + 64 );
    //printf( "\n%s\n", ( ( char * )( pBuffer + 64 ) ) );

    // int idade;
    scanf( "%hu", ((unsigned short int *)(pBuffer + 90)) );
    //printf("\n%hu\n", *((unsigned short int *)(pBuffer + 90)));

    //void *nodo = CriaNodo( nome, email, idade );
    CriaNodo( pBuffer + 13, pBuffer + 64, pBuffer + 90 );

    // printf("\n%s\n", *((char**)(pBuffer + 92)));
    // printf("\n%s\n", *((char**)(pBuffer + 92))+51);
    // printf("\n%hu\n", *(unsigned short int *)( *( ( char** )( pBuffer + 92 ) ) + 77 ));
    
    // Push( nodo );
    Push(pBuffer + 92);

    //printf("\n%s\n", *((char**)(pBuffer + 108)));
    return;
}

void Push(void* nodo){
    if(*((char**)(pBuffer + 100)) == NULL){
        *((char**)(pBuffer + 100)) = *(char**)nodo;
        *((char**)(pBuffer + 108)) = *(char**)nodo;
        return;
    }
//MEU NODO É UMA STRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
//79 = pnext
//87 = pPrevious
    BuscaPush(nodo, pBuffer + 116, pBuffer + 108, pBuffer + 100);
    printf("\nLast: %s\n", *((char**)(pBuffer + 108)));
    printf("\nFirst: %s\n", *((char**)(pBuffer + 100)));

    // *(void**)(*((char **)(pBuffer + 108)) + 79) = *(char**)nodo;//nodo.pPrevious.pNext = nodo -- ou seja, faço o pnext do anterior apontar pra esse
    // *(void**)((*((char**)nodo)) + 79) = NULL;//pNext = NULL
    // *(void**)((*(char**)nodo) + 87) = *((char**)(pBuffer + 108)); //pPrevious = pLast
    // *((char**)(pBuffer + 108)) = *(char**)nodo;//pLast = nodo

    return;
}


void BuscaPush( void* nodo, void* pAux, void* pLast, void* pFirst){
    *(void**)pAux = *(void**)pLast;

    int sexo = strcmp((*((char**)nodo)), (*((char **)pAux)));

    if(*(void**)((*((char**)pAux)) + 87) == NULL && sexo < 0){//insere no início
        *(void**)((*((char**)nodo)) + 79) = *(void**)pAux;
        *(void**)((*((char**)pAux)) + 87) = *(void**)nodo;
        *(void**)pFirst = *(void**)nodo;
        printf("INseri no inicio");

        return;
    } else if (*(void**)((*((char**)pAux)) + 87) == NULL && sexo >= 0){ //insere no final
        *(void**)((*((char**)pAux)) + 79) = *(void**)nodo;
        *(void**)((*(char**)nodo) + 87) = *(void**)pAux;
        *(void**)pLast = *(void**)nodo;
        printf("INseri no final");
        return;
    }

    for(int i = 0; sexo < 0 && *(void**)((*((char**)pAux)) + 87) != NULL; i++){
        printf("\nONDE EStá auxiliar: %s\n",(*((char **)pAux)) );
        *(void**)pAux = *(void**)((*((char**)pAux)) + 87); //pAu = pAux.prev
        sexo = strcmp((*((char**)nodo)), (*((char **)pAux)));
    }

    if(*(void**)((*((char**)pAux)) + 87) == NULL){
        *(void**)((*((char**)nodo)) + 79) = *(void**)pAux;
        *(void**)((*((char**)pAux)) + 87) = *(void**)nodo;
        *(void**)pFirst = *(void**)nodo;
        return;
    } else if(*(void**)((*((char**)pAux)) + 79) == NULL) {
        *(void**)((*((char**)pAux)) + 79) = *(void**)nodo;
        *(void**)((*(char**)nodo) + 87) = *(void**)pAux;
        *(void**)pLast = *(void**)nodo;
        return;
    } else {
        *(void**)((*((char**)nodo)) + 79) = *(void**)((*((char**)pAux)) + 79);
        *(void**)((*(char**)nodo) + 87) = *(void**)pAux;
        *(void**)((*((char**)pAux)) + 79) = *(void**)nodo;
        *(void**)((*(void**)((*((char**)nodo)) + 79)) + 87) = *(void**)nodo;
        return;
    }

    
    return;
}


void CriaNodo(void *nome, void *email, void *idade){
    *( ( void** )( pBuffer + 92 ) ) = calloc( 1, MAX_NOME + MAX_MAIL + sizeof(unsigned short int) + sizeof(void *) + sizeof(void *) );
    strcpy(*((char**)(pBuffer + 92)),nome);
    strcpy(*((char**)(pBuffer + 92)) + 51, email);
    *(unsigned short int *)( *( ( char** )( pBuffer + 92 ) ) + 77 ) = *((unsigned short int *)idade); //Acessar o nodo como uma string, somar os bytes que preciso e aí sim dar o cast
    *(void**)(*((char **)(pBuffer + 92)) + 79) = NULL;//pNext
    *(void**)(*((char **)(pBuffer + 92)) + 87) = NULL;//pPrevious
    return;
}




void LeString( void *posicao ){

    *( ( int * )( pBuffer + 4 ) ) = 0; 

    *( ( char * )( pBuffer + 12 ) ) = getchar( );

     if( posicao == ( pBuffer + 13 ) ){
        *( ( int * )pBuffer ) = MAX_NOME;
    } else {
        *( ( int * )pBuffer ) = MAX_MAIL;
    }

    while( *( ( char * )( pBuffer + 12 ) ) != '\n' && *( ( int * )( pBuffer + 4 ) ) < *( ( int * )pBuffer ) ){
       
        *( ( char * )( posicao + ( *( ( int * )( pBuffer + 4 ) ) ) ) ) = *( ( char * )( pBuffer + 12 ) );
        ( *( ( int * )( pBuffer + 4 ) ) )++;
        *( ( char * )( pBuffer + 12 ) ) = getchar( );

    }//while
    *( ( char * )( posicao + ( *( ( int * )(pBuffer + 4 ) ) ) ) )= '\0';

    return;
}