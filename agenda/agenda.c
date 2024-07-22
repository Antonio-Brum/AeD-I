#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//                      *DEFINES
#define MAX_NOME        sizeof ( char ) * 51
#define MAX_MAIL        sizeof ( char ) * 26

//                      *FUNÇÕES*
int *Menu ( );
void Push ( void **nodo, void **pAux, void **pLast, void **pFirst ); 
void Pop ( void **pFirst, void **nodo ); 
void AdPessoa ( );
void RmPessoa ( );
void BuscaPessoa ( );
void ListarTodos ( );
void LeString ( char *string );
void CriaNodo ( char *nome, char *email, unsigned short int *idade );
void LimpaMemoria();


void *pBuffer = NULL;

/* ====================================================================================== 
Main
    Aloca espaço para o Buffer e direciona o programa para a função baseada na escolha do
    usuário;
====================================================================================== */
int main ( )
{
    pBuffer = calloc( 1, sizeof ( int ) + sizeof ( int ) + sizeof ( void * ) + sizeof ( void * ) );//alocando buffer para escolha, contadorContatos, pFirst e pLast
    *(  (  int *  ) ( pBuffer + sizeof (  int  )  )  ) = 0; //contadorContatos = 0
    *( ( void ** )( pBuffer + sizeof ( int ) * 2 ) ) = NULL; //pFirst = NULL
    *( ( void ** )( pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) ) ) = NULL; // pLast = NULL

	for  ( ;; ) {
        int *escolha = Menu ( );
		switch  ( *escolha ) {
		case 1:
            AdPessoa ( );
            printf ( "Nº de contatos: %d \n", * ( int * )( pBuffer + sizeof ( int ) ) );
			break;
		case 2:
            RmPessoa ( );
            printf ( "Nº de contatos: %d \n",  * ( int * )( pBuffer + sizeof ( int ) ) );
			break;
		case 3:
            BuscaPessoa( );
            printf( "Nº de contatos: %d \n", * ( int * )( pBuffer + sizeof ( int ) ) );
			break;
		case 4:
            ListarTodos ( );
            printf ( "Nº de contatos: %d \n", * ( int * )( pBuffer + sizeof ( int ) ) );
			break;
		case 5:
            LimpaMemoria( );
			return 0;
		break;
		}
	}
}

/* ====================================================================================== 
AdPessoa
    Recebe os dados do contato: Nome, email, idade;
    Cria um nodo para esse contato;
    Dá push neste contato para a Heap principal;
====================================================================================== */
void AdPessoa ( ){ 
    pBuffer = realloc ( pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) + sizeof ( void * ) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) ); 

    int *contadorContatos = pBuffer + sizeof ( int );
    ( *contadorContatos )++;

    char *nome = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) + sizeof( void * ); 

    LeString ( nome );

    char *email = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) + sizeof ( void * ) + MAX_NOME;
        
    LeString ( email );
    nome = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) + sizeof ( void * ); 
    email = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) + sizeof( void * ) + MAX_NOME;

    unsigned short int *idade = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) + sizeof ( void * ) + MAX_NOME + MAX_MAIL;

    scanf ( "%hd", idade );

    
    CriaNodo ( nome, email, idade );

    void **pFirst = pBuffer + sizeof ( int ) * 2;
    void **pLast = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ); 
    void **nodo = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2; 
    void **pAux = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * );
    
    Push ( nodo, pAux, pFirst, pLast );

    pBuffer = realloc ( pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 ); 

    return;
}

/* ====================================================================================== 
RmPessoa
    Recebe o nome de quem o usuário deseja remover;
    Percorre a Heap através do Pop buscando esse nome, e, quando não é o nome procurado,
    dá Push no nodo para a Heap auxiliar;
    Se encontra o contato dado pelo usuário na lista, executa o free() neste nodo;
====================================================================================== */
void RmPessoa ( ){
    pBuffer = realloc ( pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2 + MAX_NOME + sizeof ( void * ) * 2 + sizeof ( int ) + sizeof ( char ) );

    char *nome = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2;

    LeString ( nome  ); 

    pBuffer = realloc ( pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2 + MAX_NOME + sizeof ( void * ) * 2 + sizeof ( int ) + sizeof ( char ) );
    nome = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2;

    int *contadorContatos = pBuffer + sizeof ( int );
    void **pFirst = pBuffer + sizeof ( int ) * 2;
    void **pLast = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ); 
    void **nodo = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2;
    void **pAux =  pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 3;
    void **pFirstTemp = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 4 + MAX_NOME;
    void **pLastTemp =  pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 4 + MAX_NOME + sizeof ( void * );
    int *i = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2 + MAX_NOME + sizeof ( void * ) * 2;
    char *validaRemove = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void* ) * 2 + MAX_NOME + sizeof ( void * ) * 2 + sizeof ( int );
    
    *validaRemove = '0';
    *pFirstTemp = NULL;
    *pLastTemp = NULL;

    Pop ( pFirst, nodo  ); //Pega o primeiro nodo da fila principal
    if ( *nodo == NULL ){
        printf ( "Lista de contatos vazia :(\nFaça alguns amigos!\n" );
        return;
    }

    for(*i = 0; *i < *contadorContatos; ( *i )++ ){
        if ( strcmp ( nome, * ( char ** )nodo ) == 0 && *nodo != NULL ){
            free ( *nodo );
            Pop( pFirst, nodo );
            *validaRemove = '1';
        } else {
            Push ( nodo, pAux, pFirstTemp, pLastTemp );//põe na fila auxiliar
            Pop ( pFirst, nodo );
        }
    }
    if( *validaRemove == '1' ){
        ( *contadorContatos )--;
    } else {
        printf( "Nome não encontrado." );
    }
    *pFirst = *pFirstTemp;
    *pLast = *pLastTemp;
    pBuffer = realloc ( pBuffer, sizeof ( int ) * 2 + sizeof ( void* ) * 2 ); //Voltando ao tamanho original


    return;
}

/* ====================================================================================== 
BuscaPessoa
    Lê o nome que o usuário busca;
    Se o nome estiver na lista, retorna os dados do contato;
    Percorre a Heap dando Pop no primeiro nodo, comparando com o nome dado pelo usuário e
    dando Push para a Heap auxiliar
====================================================================================== */
void BuscaPessoa ( ){
    pBuffer = realloc ( pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2 + MAX_NOME + sizeof ( void * ) * 2 + sizeof ( int ) );

    char *nome = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2;

    LeString (  nome  ); 
    pBuffer = realloc (  pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2 + MAX_NOME + sizeof ( void * ) * 2 + sizeof ( int ) );
    
    nome = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2;

    int *contadorContatos = pBuffer + sizeof ( int );
    void **pFirst = pBuffer + sizeof ( int ) * 2;
    void **pLast = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ); 
    void **nodo = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2;
    void **pAux =  pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 3;
    void **pFirstTemp = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 4 + MAX_NOME;
    void **pLastTemp =  pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 4 + MAX_NOME + sizeof ( void * );
    int *i = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2 + MAX_NOME + sizeof ( void * ) * 2;

    *pFirstTemp = NULL;
    *pLastTemp = NULL;

    Pop (  pFirst, nodo  ); 
    if ( *nodo == NULL ){
        printf ( "Não há contatos para se buscar :( \n" );
        return;
    }
   
    for ( *i = 0; *i < *contadorContatos; ( *i )++ ){
        if ( strcmp ( nome, * ( char ** )nodo ) == 0 && *nodo != NULL ){
            printf( "###Aqui está###\n" );
            printf( "Nome: %s\n", * ( char ** )nodo );
            printf( "Email: %s\n", ( * ( char ** )nodo ) + MAX_NOME );
            printf( "Idade: %hd\n", * ( unsigned short int * )( ( *nodo ) + MAX_NOME + MAX_MAIL  ) );
            printf( "######\n" );
            Pop( pFirst, nodo );
        } else {
            Push (  nodo, pAux, pFirstTemp, pLastTemp );
            Pop ( pFirst, nodo );
        }
    }
    *pFirst = *pFirstTemp;
    *pLast = *pLastTemp;
    pBuffer = realloc (  pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 );

    return;
}

/* ====================================================================================== 
ListarTodos
    Percorre a Heap principal enquanto mostra os dados dos contatos;
    Os dados só são printados depois de ser dado o Pop na Heap;
    Após serem printados são "Pushados" para uma fila auxiliar e depois, ao final, voltam
    para a fila principal;
====================================================================================== */
void ListarTodos ( ){
    pBuffer = realloc ( pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) * 2 + sizeof ( int ) );

    int *contadorContatos = pBuffer + sizeof ( int );
    void **pFirst = pBuffer + sizeof ( int ) * 2;
    void **pLast = pBuffer + sizeof ( int ) * 2 + sizeof ( void* ); 
    void **nodo = pBuffer + sizeof ( int ) * 2 + sizeof ( void* ) * 2;
    void **pAux =  pBuffer + sizeof ( int ) * 2 + sizeof ( void* ) * 3;
    void **pFirstTemp = pBuffer + sizeof ( int ) * 2 + sizeof ( void* ) * 4;
    void **pLastTemp =  pBuffer + sizeof ( int ) * 2 + sizeof ( void* ) * 4 + sizeof ( void* );
    int *i = pBuffer + sizeof ( int ) * 2 + sizeof ( void* ) * 6;

    *pFirstTemp = NULL;
    *pLastTemp = NULL;

    Pop ( pFirst, nodo );
    if ( *nodo == NULL ){
        printf ( "Lista de contatos vazia:(.\nSério, faça alguns amigos.\n" );
        return;
    }

    for ( *i = 0; *i < *contadorContatos; ( *i )++ ){
            printf( "Nome: %s\n", * ( char ** )nodo );
            printf( "Email: %s\n", ( * ( char ** )nodo ) + MAX_NOME );
            printf( "Idade: %hd\n", * ( unsigned short int * )( ( *nodo ) + MAX_NOME + MAX_MAIL  ) );
            printf( "##################\n" );
            Push (  nodo, pAux, pFirstTemp, pLastTemp );//põe na fila auxiliar
            Pop ( pFirst, nodo );
    }
    *pFirst = *pFirstTemp;
    *pLast = *pLastTemp;
    pBuffer = realloc ( pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 ); //Voltando ao tamanho original

    return;
}

/* ====================================================================================== 
LimpaMemoria
    Executa o free() nos nodos que foram criados e, por fim, executa free() no buffer
====================================================================================== */
void LimpaMemoria(){
    pBuffer = realloc ( pBuffer, sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * ) + sizeof ( int ) );

    void **pFirst = pBuffer + sizeof ( int ) * 2;
    void **nodo = pBuffer + sizeof ( int ) * 2 + sizeof ( void* ) * 2;

    Pop (  pFirst, nodo  );
    if ( *nodo == NULL ){
        free ( pBuffer );
        return;
    }

    int *i = pBuffer + sizeof ( int ) * 2 + sizeof ( void * ) * 2 + sizeof ( void * );
    int *contadorContatos = pBuffer + sizeof ( int );

    for ( *i = 0; *i < *contadorContatos; ( *i )++ ){
        free ( *nodo );
        Pop ( pFirst, nodo );
    }

    free ( pBuffer );

    return;
}

/* ====================================================================================== 
Menu
    Mostra na tela as opções do menu e valida se o input do usuário é um número válido;
    Retorna um ponteiro para dentro do Buffer, que representa a escolha do usuário;
====================================================================================== */
int *Menu ( )
{
    int *escolha = pBuffer;
	do {
		printf ( "\n-- MENU:\n" );
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

/* ====================================================================================== 
Pop
    Recebe a cabeça da lista (pFirst) e um ponteiro para o nodo que está no Buffer;
    Como trata-se de uma Heap, os nós só podem ser retirados do início da lista;
    Nodo recebe o primeiro nodo e o segundo (se existir) passa a ser o primeiro;
====================================================================================== */
void Pop ( void **pFirst, void **nodo ){ //vai retornar o nodo do início da fila

    if( *pFirst == NULL ){
        *nodo = NULL;
        return;
    }
    *nodo = *pFirst;

    if ( * ( void ** )( ( *pFirst ) + 79 ) != NULL ){
        * pFirst = * ( void ** )( ( *pFirst ) + 79 );
        * ( void** )( ( *nodo ) + 79 ) = NULL;
        * ( void** )( ( *pFirst ) + 87 ) = NULL;

        return;
    } else {
        *pFirst = NULL;
        void **pLast = pBuffer + sizeof ( int ) * 2 + sizeof ( void* ); 
        *pLast = NULL;
    }

    return;
}

/* ====================================================================================== 
Push
    Recebe o nodo que será adicionado à Heap, o ponteiro auxiliar que percorrerá a Heap,
    pFirst (o primeiro nodo da lista) e pLast (o último nodo da lista);
    Como é uma Heap com ordem ela busca de trás para frente qual será o espaço que o novo
    nodo ocupará, dependendo da ordem lexical;
====================================================================================== */
void Push ( void **nodo, void **pAux, void **pFirst, void **pLast ){
    if ( *pFirst == NULL ){
        *pFirst = *nodo;
        *pLast = *nodo;
        return;
    }
    *pAux = *pLast;
    if ( * ( void ** )( ( *pAux ) + 87 ) == NULL && strcmp ( ( * ( char ** )nodo ), ( * ( char ** )pAux ) ) < 0 ){
        * ( void ** )( ( *nodo ) + 79 ) = *pAux;
        * ( void ** )( ( *pAux ) + 87 ) = *nodo;
        *pFirst = *nodo;

        return;
    } else if ( * ( void ** )( ( *pAux ) + 87 ) == NULL && strcmp( ( * ( char ** )nodo ), ( * ( char ** )pAux ) ) >= 0 ){
        * ( void ** )( ( *pAux ) + 79 ) = *nodo;
        * ( void ** )( ( *nodo ) + 87 ) = *pAux;
        *pLast = *nodo;

        return;
    }//if

    while( strcmp ( ( * ( char ** )nodo ), ( * ( char ** )pAux ) ) < 0 && * ( void ** )( ( * ( char ** )pAux ) + 87 )!= NULL ){
        *pAux = * ( void ** )( ( * ( char ** )pAux ) + 87 );
    }//while

    if ( strcmp ( ( *( char ** )nodo ), ( *( char ** )pAux ) ) < 0 ){//inserir no início
        * ( void ** )( ( *nodo ) + 79 ) = *pAux;//nodo.next = pAux
        * ( void ** )( ( *pAux ) + 87 ) = *nodo;//pAux.prev = nodo
        *pFirst = *nodo;//pFirst = nodo

        return;
    } else if ( * ( void ** )( ( * ( char** )pAux ) + 79 ) == NULL ){//inserir no final
        *( void ** )( ( *pAux ) + 79 ) = *nodo;//pAux.next = nodo
        *( void ** )( ( *nodo ) + 87 ) = *pAux;//nodo.prev = pAux
        *pLast = *nodo;//pLast = nodo

        return;
    } else { //inserir no meio
        * ( void ** )( ( *nodo ) + 79 ) = * ( void ** )( ( *( char** )pAux ) + 79 );//nodo.next = pAux.next
        * ( void ** )( ( *nodo ) + 87 ) = *pAux;//nodo.prev = pAux
        * ( void ** )( ( *pAux ) + 79 ) = *nodo;//pAux.next = nodo
        * ( void  ** )( * ( void ** )( ( *nodo ) + 79 ) + 87 )= *nodo;//nodo.next->prev = nodo

        return;
    }//if 

    
    return;
}

/* ====================================================================================== 
CriaNodo
    Recebe o nome, email e idade do contato;
    Cria um espaço no Buffer para o ponteiro nodo, que recebe uma área de memória com o
    tamanho de 95 bytes;
    Esta área de memória representa um nodo da Lista duplamente encadeada;
====================================================================================== */
void CriaNodo ( char *nome, char *email, unsigned short int *idade ){

    void **nodo = pBuffer + sizeof ( int ) * 2 + sizeof ( void* ) * 2; 

    *nodo = calloc ( 1, MAX_NOME + MAX_MAIL + sizeof( unsigned short int ) + sizeof ( void * ) + sizeof ( void * ) );
    strcpy ( *( ( char **)( nodo)) , nome);
    strcpy ( * (  ( char** ) ( nodo ) ) + 51, email );

    * ( unsigned short int * )( * ( ( char ** )( nodo ) ) + 77 ) = *idade;
    * ( void ** )( * ( ( char ** )( nodo ) ) + 79 ) = NULL;
    * ( void ** )( * ( ( char ** )( nodo ) ) + 87 ) = NULL;
    return;
}

/* ====================================================================================== 
LeString
    Usada para ler o input do usuário e armazenar no buffer o nome e o email do contato;
    Ela usa a posição do parâmetro no buffer para saber se o que vai ser lido é nome ou email.
    Algo necessário visto que são strings com os limites de caracteres distintos
====================================================================================== */
void LeString ( char *string ){

    if ( string ==  ( pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) ) ){ //testa se a string passada é nome
        pBuffer = realloc (pBuffer, sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) + sizeof ( int ) + sizeof ( char ) + sizeof ( int )); //alocando para o contador do loop, para getchar() e para o tamanho
        string = ( pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) );
    } else {
        pBuffer = realloc (pBuffer, sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) + sizeof ( int ) + sizeof ( char ) + sizeof ( int )); //alocando para o contador do loop, para getchar() e para o tamanho
        string = ( pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME);
    }//if

    int *i = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) ;//alocando i depois de `idade`;
    *i = 0;

    char *c = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) + sizeof ( int ); //alocando c depois de `i`
    *c = getchar ( );

    int *tamanho = pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) + MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) + sizeof ( int ) + sizeof ( char );

    if ( string ==  ( pBuffer + sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) ) ){ //verifica se a string passada é nome ou email
        *tamanho = MAX_NOME;
    } else {
        *tamanho = MAX_MAIL;
    }//if

    while ( *c != '\n' && *i < *tamanho ){
        
        * ( string + (*i) ) = *c; 
        (*i)++;
        *c = getchar ( );

    }//while
    * ( string + *i ) = '\0';
    pBuffer = realloc(pBuffer, sizeof ( int ) * 2 + sizeof (void *) * 2 + sizeof (void *) + sizeof(void *) +  MAX_NOME + MAX_MAIL + sizeof ( unsigned short int ) );
    return;
}