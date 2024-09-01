#include <stdio.h>

void Merge ( int *difLeft, int *profLeft, int difLeftSize, int *difRight, int *profRight, int difRightSize, int *dif, int *prof );
void Sort_r ( int *dif, int *prof, int difSize );
int MaxProfitAssignment ( int *difficulty, int difficultySize, int *profit, int profitSize, int *worker, int workerSize );

/*
====================
main

    Cria o caso para teste e chama a função que calcula o resultado
====================
*/
int main (  ) {
    int difficulty [ ] = { 4, 8, 6, 10, 2 };
    int difficultySize = sizeof ( difficulty ) / sizeof ( difficulty [ 0 ] );
    int profit [ ] = { 20, 40, 30, 50, 10 };
    int profitSize = sizeof ( profit ) / sizeof ( profit [ 0 ] );
    int worker [ ] = { 6, 4, 11, 5 };
    int workerSize = sizeof ( worker ) / sizeof ( worker [ 0 ] );

    int maxProfit = MaxProfitAssignment ( difficulty, difficultySize, profit, profitSize, worker, workerSize );
    printf ( "Maximum profit: %d\n", maxProfit );

    return 0;
}

/*
====================
Merge

    Função chamada por Sort_r();
    Compara os números entre os arrays da esquerda e da direita e 'monta' um novo array em ordem crescente;
    Para que se possa ordenar a dificuldade do trabalho é preciso modificar o vetor de `profit` para que a relação se mantenha;
====================
*/
void Merge ( int *difLeft, int *profLeft, int difLeftSize, int *difRight, int *profRight, int difRightSize, int *dif, int *prof ){
    int i = 0;
    int j = 0;
    int k = 0;

    while ( i < difLeftSize && j < difRightSize ){

        if  (  difLeft [ i ] <= difRight [ j ]  ) {
            dif [ k ] = difLeft [ i ];
            prof [ k ] = profLeft [ i ];
            i++;
        } else {
            dif [ k ] = difRight [ j ];
            prof [ k ] = profRight [ j ];
            j++;
        }
        k++;
    }

    while  ( j < difRightSize ){
        dif [ k ] = difRight [ j ];
        prof [ k ] = profRight [ j ];
        j++;
        k++;
    }

    while  ( i < difLeftSize ){
        dif [ k ] = difLeft [ i ];
        prof [ k ] = profLeft [ i ];
        i++;
        k++;
    }
}


/*
====================
Sort_r

    Recebe dois arrays;
    Para que se possa ordenar a dificuldade do trabalho é preciso modificar o vetor de `profit` para que a relação se mantenha;
    Função recursiva que separa um array em esquerda e direita, partindo do meio deste array;
    Após separar o array a função chama merge() para que este array seja ordenado;
====================
*/
void Sort_r  ( int *dif, int *prof, int difSize ){
    if  ( difSize <= 1 ){
        return;
    }
    int mid =  ( int ) difSize / 2;

    int difLeft [ mid ];
    int difRight [ difSize - mid ];
    int profLeft [ mid ];
    int profRight [ difSize - mid ];

    int i = 0;
    int j = 0;

    for ( i; i < difSize; i++ ){
        if ( i >= mid ){
            difRight [ j ] = dif [ i ];
            profRight [ j ] = prof [ i ];
            j++;
        } else {
            difLeft [ i ] = dif [ i ];
            profLeft [ i ] = prof [ i ];  
        }
    }

    Sort_r ( difLeft, profLeft, mid );
    Sort_r ( difRight, profRight, difSize - mid );
    Merge ( difLeft, profLeft, mid, difRight, profRight, difSize - mid, dif, prof );

    return;
}

/*
====================
MaxProfitAssignment

    Recebe os 3 arrays da main();
    Ordena `workers` e `difficulty`, em ordem crescente, chamando Sort_r();
    Busca pelo trabalho j mais lucrativo para o trabalhador i;
====================
*/
int MaxProfitAssignment ( int *difficulty, int difficultySize, int *profit, int profitSize, int *worker, int workerSize ) {

    Sort_r ( difficulty, profit, difficultySize );
    Sort_r ( worker, worker, workerSize );

    int mostProf = -1;
    int maxProfit = 0;
    int j;
    for  ( int i = 0; i < workerSize; i++  ){
        if ( mostProf != -1 ){
            j = mostProf;
        } else {
            j = 0;
        }
        for ( j; j < difficultySize; j++ ){
            if  ( difficulty [ j ] <= worker [ i ] ){
                if ( mostProf == -1 ){
                    mostProf = j;
                } else if ( profit [ j ] > profit [ mostProf ] ){
                    mostProf = j;
                }
            } else {
                j = difficultySize + 1;
            }
        }
        if  ( mostProf != -1 ){
        maxProfit += profit [ mostProf ];
        }

    }

    return maxProfit;
   
}
