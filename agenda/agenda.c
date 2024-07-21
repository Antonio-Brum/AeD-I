#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_INT         sizeof ( int )
#define TAM_PONT        sizeof ( void * )
#define MAX_NOME        sizeof ( char ) * 51
#define MAX_MAIL        sizeof ( char ) * 26

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
    51 char  (51 bytes) para o nome;
    26 char  (26 bytes) para o email;
    1 unsigned short int  (2 bytes) para a idade; 
    1 void * (8 bytes) para armazenar o próximo nodo;
    1 void * (8 bytes) para armazenar o nodo anterior;
        total: 95 bytes por Nodo.
*/

// typedef struct{
//     nodo_t *first;
//     nodo_t *last;
// }fila_t;

void *pBuffer = NULL;




void AlocaBuffer ( );
int *Menu ( );
void Push ( void** nodo, void** pAux, void** pLast, void** pFirst ); //vai adicionar um nodo a partir do final da fila
//Push vai receber o nodo a ser adicionado, o ponteiro auxiliar usado para percorrer a lista, e em qual das stacks ele vai ser adicionado: Na principal ou na temporária
//void BuscaPush ( void* nodo, void* pAux, void* pLast, void* pFirst );
void Pop ( void* pFirst ); //vai retornar o nodo do inícido da fila
void Empty ( );
void AdPessoa ( );
void RmPessoa ( );
void BuscaPessoa ( );
void ListTodos ( );
void LeString ( char *string );
void CriaNodo ( char *nome, char *email, unsigned short int *idade );

//pBuffer[0]  = um inteiro que armazena a escolha do usuário  (4 bytes) -> pBuffer +0 
//pBuffer[1] = inteiro i, para usar em laços  (4 bytes) -> pBuffer +4
//pBuffer[2] = inteiro contador de contatos  (4 bytes) -> pBuffer +8
//pBuffer[3] = unsigned char, para ler a string de input  (1 byte ) -> pBuffer + 12
//pBuffer[4] = char *, guarda a string do usuário  ( MAX_NOME ) -> pBuffer + 13
//pBuffer[5] = char *, guarda o email do contato  ( MAX_MAIL ) -> pBuffer + 64
//pBuffer[6] = short unsigned int idade , guarda a idade do contato  (2 bytes) -> pBuffer + 90
//pBuffer[x+2] = void *, ponteiro que vai servir como `temp` para manipular os nodos na fila  (8 bytes) -> pBuffer + 92
//pBuffer[X] = void *, aponta para o primeiro node na fila -> pBuffer + 100
//pBuffer[X+1] = void *, aponta para o último nodo na fila -> pBuffer + 108
//pBuffer[não sei mais] = void *, ponteiro auxiliar pra fazer a busca -> pBuffer + 116
//pBuffer[x+3] = void *, ponteiro para o primeiro nodo da lista temporária -> pBuffer + 124
//pBuffer[x+4] = void *, ponteiro para o último nodo da lista temporária -> pBuffer + 132

int main ( )
{
    //AlocaBuffer ( );
    pBuffer = calloc(1, sizeof(int) + sizeof(int) + sizeof(void*) + sizeof(void *));//alocando buffer para escolha, contadorContatos, pFirst e pLast
    //int tamanho = sizeof(int) + sizeof(int) + sizeof(void*) + sizeof(void *);
    //printf("%d", tamanho);
    //int *contadorContatos = pBuffer + sizeof( int );
    *( ( int* ) (pBuffer + sizeof( int ) ) ) = 0;
    *((void**)(pBuffer + sizeof(int) * 2)) = NULL; //pFirst = NULL
    *((void**)(pBuffer + sizeof(int) * 2 + sizeof(void*))) = NULL; // pLast = NULL
	for  ( ;; ) {
        int *escolha = Menu ( );
		switch  (*escolha) {
		case 1:
            AdPessoa ( );
			break;
		case 2:
            //RmPessoa ( );
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
            if ( * (  ( void** ) ( pBuffer + 92 ) ) != NULL){
                free ( * (  ( void** ) ( pBuffer + 92 ) ) );
            }
            free ( pBuffer );
			return 0;
		break;
		}
	}
}

int *Menu ( )
{
    int *escolha = pBuffer;
	do {
		printf ( "-- MENU:\n" );
		printf ( "\t 1. Adicionar pessoa\n" );
		printf ( "\t 2. Remover pessoa\n" );
		printf ( "\t 3. Buscar pessoa\n" );
		printf ( "\t 4. Listar todos\n" );
		printf ( "\t 5. Sair\n" );
		printf ( "-- Digite sua escolha: " );
		scanf ( "%d",  escolha);
	}
	while  (  *escolha <= 0 ||  *escolha > 5 );
	getchar ( );  
    return escolha;
}




// void RmPessoa ( ){
//     LeString ( pBuffer + 13 ); //qual nome vai sair?
//     Pop ( pBuffer + 100 ); //Pega o primeiro nodo da fila principal
//     printf ("\nNo pFirst: %s\n", * ( char** )( pBuffer + 100 ) );
//     printf ("\nNo 'nodo': %s\n", * ( char** )( pBuffer + 92 ) );

//     for((*(int*)(pBuffer + 4)) = 0;(*(int*)(pBuffer + 4)) < (*(int*)(pBuffer + 8)); (*(int*)(pBuffer + 4))++){
//             if (( strcmp ( ( char * )(pBuffer + 13), (* ( char** )(pBuffer + 92) ) ) ) == 0){
//                 free ( * (  ( void** ) ( pBuffer + 92 ) ) );
//                 * ( void** )( pBuffer + 92 ) = *(void**)(pBuffer + 100);
//                 printf("Removi!\n");
//             }

//         if(* ( void** )( pBuffer + 92 ) != NULL){
//             Push ( pBuffer + 92, pBuffer + 132, pBuffer + 124); //põe na fila auxiliar
//             Pop ( pBuffer + 100 );
//             printf("não removi\n");
//         }
//     }
//     *(void**)(pBuffer + 100) = *(void**)(pBuffer + 124);
//     *(void**)(pBuffer + 108) = *(void**)(pBuffer + 132);
//     *(void**)(pBuffer + 124) = NULL;
//     *(void**)(pBuffer + 132) = NULL;
//     return;

//     // if ( ( strcmp ( ( char * )(pBuffer + 13), * ( char** )(pBuffer + 92) ) ) == 0){
//     //     free ( * (  ( void** ) ( pBuffer + 92 ) ) );
//     //     * ( void** )( pBuffer + 92 ) = NULL;
//     //     printf("É igual, doidão");

//     //     return;
//     // } else {
//     //     Push ( pBuffer + 92, pBuffer + 124, pBuffer + 132); //põe na fila auxiliar
//     // }

//     // printf("Não é igual");
// }



void Pop ( void* pFirst ){ //vai retornar o nodo do início da fila

    if(*(void**)pFirst == NULL){
        printf("Fila vazia, filho");
        return;
    }
    * ( void** )( pBuffer + 92 ) = * ( void** ) pFirst; //pNodo aponta para o primeiro nodo da fila
    if( * ( void** )( ( * ( void** )pFirst ) + 79 ) != NULL){ //se o primeiro nodo na fila não for o último
        * ( void** )pFirst = * ( void** )( ( * ( void** )pFirst ) + 79 ); //pFirst = pFirst.next
        * ( void** )( ( * ( void** )( pBuffer + 92 ) ) + 79 ) = NULL; //faz o pNext do nodo retirado apontar para NULL 
        * ( void** )( ( * ( void** )pFirst ) + 87 ) = NULL;//fazer o pPrevious do primeiro apontar para NULL
        return;
    } else {
        *(void**)pFirst = NULL;
        *(void**)(pBuffer + 108) = NULL;
    }


    return;
}

//escolha, contadorContatos, pFirst, pLast, nodo, pAux, nome, email, idade 
void AdPessoa ( ){ 
    pBuffer = realloc (pBuffer, sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof (unsigned short int ) ); //REalocando para o nodo, pAux, nome, email, idade

    int *contadorContatos = pBuffer + sizeof( int );
    (*contadorContatos)++;
    char *nome = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *); //nome logo depois de `escolha` e de `contadorContatos`
    //(*((int*)(pBuffer + 8)))++;

    //LeString ( pBuffer + 13 );
    LeString ( nome );

    //contadorContatos = pBuffer + sizeof( int );
    //nome = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *); //nome logo depois de `nodo` e `pAux`
    char *email = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME;//email após `nome`
    //int *idade = pBuffer + sizeof ( int ) * 2 + MAX_NOME + MAX_MAIL;//idade após `email`
        
    LeString ( email );
    nome = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *); //nome logo depois de `nodo` e `pAux`
    email = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME;//email após `nome`

    // printf("\n%s\n", email);
    // printf("\n%s\n", nome);

    unsigned short int *idade = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL;//idade após `email`

    scanf("%hd", idade);
    // printf("%hd", *idade);

    // scanf ( "%hu",  (  ( unsigned short int * ) ( pBuffer + 90 ) ) );
    
    CriaNodo ( nome, email, idade );
    //pBuffer = realloc(pBuffer, sizeof(int) + sizeof(int) + sizeof(void*) + sizeof(void *) + sizeof(void *)); //Dando free no espaço das strings e da idade 

    void **pFirst = pBuffer + sizeof(int) * 2;
    void **pLast = pBuffer + sizeof(int) * 2 + sizeof(void*); 
    void **nodo = pBuffer + sizeof(int) * 2 + sizeof(void*) * 2; 
    void **pAux = pBuffer + sizeof(int) * 2 + sizeof(void*) * 2 + sizeof(void *);
    printf("\n%s\n", *(char**)(nodo));
    printf("\n%s\n", *((char**)(nodo)) + 51 );
    printf("\n%hd\n", *(unsigned short int *)(*((char**)(nodo)) + 77) );


    printf("Endereço do pBuffer: %p\n", pBuffer);
    printf("Endereço apontado por pFirst: %p\n", pFirst);

    printf("Endereço apontado por *pFirst (deve ser NULL): %p\n", *pFirst);
    Push(nodo, pAux, pFirst, pLast);

    printf("Acessado o nodo por pFirst:\nnome:%s\n", *(char**)pFirst);
    printf("Acessando o pFirst->next (Deve ser NULL):%p\n", *(void**)(*((char **)(pFirst)) + 79));

    printf("Acessado o nodo por pLast:\nnome:%s\n", *(char**)pLast);
    printf("Acessando o pLast->next (Deve ser NULL):%p\n", *(void**)(*((char **)(pLast)) + 79));
    // CriaNodo (pBuffer + 13, pBuffer + 64, pBuffer + 90);    
    //Push ( pBuffer + 92, pBuffer + 108, pBuffer + 100 );
    // printf ( "\nLast: %s\n", * (  ( char** ) ( pBuffer + 108 ) ) );
    // printf ( "\nFirst: %s\n", * (  ( char** ) ( pBuffer + 100 ) ) );
  
    return;
}


void Push ( void** nodo, void** pAux, void** pFirst, void** pLast ){
    // if (* ( (char**) (pBuffer + 100)) == NULL){
        // * ( (char**) (pBuffer + 100)) = * (char**)nodo;
        // * ( (char**) (pBuffer + 108)) = * (char**)nodo;
    printf("NO PUSH() - Endereço apontado por pFirst: %p\n", pFirst);
    printf("Endereço apontado por *pFirst (deve ser NULL): %p\n", *pFirst);

    if ( *pFirst == NULL ){
        *pFirst = *nodo;
        *pLast = *nodo;
        return;
    }
//MEU NODO É UMA STRINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
//79 = pnext
//87 = pPrevious

//ideias: usar o contador de pessoas; usando o contador é possível separar 0, 1 e mais de 1 contatos; Fazer funções para inserir no início, no final e no meio pro código ficar menos poluído; tentar separar a função de busca também;
    *pAux = *pLast;
    //* ( void** )( pBuffer + 116 ) = * ( void** )pLast;

   // *( int * )pBuffer = strcmp (  ( * (  ( char** )nodo ) ),  ( * (  ( char ** )( pBuffer + 116 ) ) ) );

    //if ( * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 87 ) == NULL && *( int * )pBuffer < 0 ){//insere no início
        // * ( void** ) (  ( * (  ( char** )nodo ) ) + 79 ) = * ( void** )( pBuffer + 116 );
        // * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 87 ) = * ( void** )nodo;
        // * ( void** )pFirst = * ( void** )nodo;
    // } else if  ( * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 87 ) == NULL && *( int * )pBuffer >= 0 ){ //insere no final
    //     * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 79 ) = * ( void** )nodo;
    //     * ( void** ) (  ( * (char**)nodo ) + 87 ) = * ( void** )( pBuffer + 116 );
    //     * ( void** )pLast = * ( void** )nodo;
    //     printf ("Inseri no final");
    //     return;
    // }//if
    if(*(void**)((*pAux) + 87) == NULL && strcmp((*(char**)nodo), (*(char**)pAux)) < 0){
        *(void**)((*(char**)nodo) + 79) = *pAux;
        *(void**)((*(char**)pAux) + 87) = *nodo;
        *pFirst = *nodo;
        printf ("Inseri no inicio\n");

        return;
    } else if (*(void**)((*pAux) + 87) == NULL && strcmp((*(char**)nodo), (*(char**)pAux)) >= 0){
        *(void**)((*(char**)pAux) + 79) = *nodo;
        *(void**)((*(char**)nodo) + 87) = *pAux;
        *pLast = *nodo;
        printf ("Inseri no final\n");
        return;
    }//if

    // while( *( int * )pBuffer < 0 && * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 87 ) != NULL ){
    //     printf ("\nONDE EStá auxiliar: %s\n", (* ( (char **)( pBuffer + 116 ))) );
    //     * ( void** )( pBuffer + 116 ) = * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 87 ); //pAu = pAux.prev
    //     *( int * )pBuffer = strcmp (  ( * (  ( char** )nodo ) ),  ( * (  ( char ** )( pBuffer + 116 ) ) ) ); 
    // }//while
    while( strcmp((*(char**)nodo), (*(char**)pAux)) < 0 && *(void**)((*(char**)pAux) + 87)!= NULL ){
        printf ("\nONDE EStá auxiliar: %s\n", *(char**)pAux);
        *pAux = *(void**)((*(char**)pAux) + 87);
    
    }
    // if(*( int * )pBuffer < 0){
    //     * ( void** ) (  ( * (  ( char** )nodo ) ) + 79 ) = * ( void** )( pBuffer + 116 );//nodo.next = pAux
    //     * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 87 ) = * ( void** )nodo;//pAux.prev = nodo
    //     * ( void** )pFirst = * ( void** )nodo;//pFirst = nodo
    //     printf("Bruno vem antes de antonio ?????????????????????????????????????????????????\n");
    //     return;
    // } else if ( * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 79 ) == NULL ) {//inserir no final
    //     * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 79 ) = * ( void** )nodo;//pAux.next = nodo
    //     * ( void** ) (  ( * ( char** )nodo ) + 87 ) = * ( void** )( pBuffer + 116 );//nodo.prev = pAux
    //     * ( void** )pLast = * ( void** )nodo; //pLast = nodo
    //     printf("Bruno vem dpeois de carlos ?????????????????????????????????????????????????\n");
    //     return;
    // } else { //inserir no meio
    //     * ( void** ) (  ( * (  ( char** )nodo ) ) + 79 ) = * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 79 );//nodo.next = pAux.next
    //     * ( void** ) (  ( * ( char** )nodo ) + 87 ) = * ( void** )( pBuffer + 116 );//nodo.prev = pAux
    //     * ( void** ) (  ( * (  ( char** )( pBuffer + 116 ) ) ) + 79 ) = * ( void** )nodo;//pAux.next = nodo
    //     * ( void** ) (  ( * ( void** ) (  ( * (  ( char** )nodo ) ) + 79 ) ) + 87 ) = * ( void** )nodo;//nodo.next->prev = nodo
    //     printf("N sei alocar no meio :(((((((((\n");
    //     return;
    // }//if
    if (strcmp((*(char**)nodo), (*(char**)pAux)) < 0){
        *(void**)((*(char**)nodo) + 79) = *pAux;
        *(void**)((*(char**)pAux) + 87) = *nodo;
        *pFirst = *nodo;
        printf("Bruno vem antes de antonio ?????????????????????????????????????????????????\n");
        return;
    } else if (*(void**)((*(char**)pAux) + 79) == NULL){
        *(void**)((*(char**)pAux) + 79) = *nodo;
        *(void**)((*(char**)nodo) + 87) = *pAux;
        *pLast = *nodo;
        return;
    } else {
        *(void**)((*(char**)nodo) + 79) = *(void**)((*(char**)pAux) + 79);
        *(void**)((*(char**)nodo) + 87) = *pAux;
        *(void**)((*(char**)pAux) + 79) = *nodo;
        *(void **)(*(void**)((*(char**)nodo) + 79) + 87)= *nodo;
        return;
    }//if 

    
    return;
}



void CriaNodo ( char *nome, char *email, unsigned short int *idade){

    void **nodo = pBuffer + sizeof(int) * 2 + sizeof(void*) * 2; 

    *nodo = calloc(1, MAX_NOME + MAX_MAIL + sizeof(unsigned short int ) + sizeof(void*) + sizeof(void*));
    //* (  ( void** ) ( pBuffer + 92 ) ) = calloc ( 1, MAX_NOME + MAX_MAIL + sizeof (unsigned short int) + sizeof (void *) + sizeof (void *) );
    strcpy (*((char **)(nodo)) , nome);
    //strcpy ( * (  ( char** ) ( pBuffer + 92 ) ),nome );
    strcpy ( * (  ( char** ) ( nodo ) ) + 51, email );

    *(unsigned short int*)(*((char **)(nodo)) + 77) = *idade;
    //* ( unsigned short int * ) (  * (   (  char**  ) (  pBuffer + 92  )  ) + 77  ) = * (  ( unsigned short int * )idade ); //Acessar o nodo como uma string, somar os bytes que preciso e aí sim dar o cast
    *(void**)(*((char **)(nodo)) + 79) = NULL;
    *(void**)(*((char **)(nodo)) + 87) = NULL;
    // * ( void** ) ( * (  ( char ** ) ( pBuffer + 92 ) ) + 79 ) = NULL;//pNext
    // * ( void** ) ( * (  ( char ** ) ( pBuffer + 92 ) ) + 87 ) = NULL;//pPrevious
    return;
}




void LeString ( char *string ){

    if ( string ==  ( pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) ) ){ //testa se a string passada é nome
        pBuffer = realloc (pBuffer, sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) + sizeof ( int ) + sizeof ( char ) + sizeof ( int )); //alocando para o contador do loop, para getchar() e para o tamanho
        string = ( pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) );
    } else {
        pBuffer = realloc (pBuffer, sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) + sizeof ( int ) + sizeof ( char ) + sizeof ( int )); //alocando para o contador do loop, para getchar() e para o tamanho
        string = ( pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME);
    }

    int *i = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) ;//alocando i depois de `idade`;
    *i = 0;

    char *c = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) + sizeof ( int ); //alocando c depois de `i`
    *c = getchar ( );

    int *tamanho = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) + sizeof ( int ) + sizeof ( char );

    if ( string ==  ( pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) ) ){ //verifica se a string passada é nome ou email
        *tamanho = MAX_NOME;
    } else {
        *tamanho = MAX_MAIL;
    }

    while ( *c != '\n' && *i < *tamanho ){
        
        * ( string + (*i) ) = *c; // põe na string passada o valor digitado
        (*i)++;
        *c = getchar ( );

    }//while
    * ( string + *i ) = '\0';
    pBuffer = realloc(pBuffer, sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) +  MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) );
    return;
}

// void AlocaBuffer ( ){
//     pBuffer = calloc ( 150, sizeof ( char ) );
//     * ( char** ) ( pBuffer + 100 ) = NULL;
//     * ( char** ) ( pBuffer + 108 ) = NULL;
//     *(void**)(pBuffer + 124) = NULL;
//     *(void**)(pBuffer + 132) = NULL;
//     (*((int*)(pBuffer + 8))) = 0;
//     //Apontar os outros ponteiros para NULL
//     return;
// }