int numDifferentIntegers(char *word) {
    int intCounter = 0; 
    char **intList = (char **) calloc(1, sizeof(*intList));
    //intList[0] = (char *) calloc(1, sizeof(char));

    for(int i = 0; word[i] != '\0'; i++){ //substituir letra por espaço
        if(word[i] < 48 || word[i] > 57){
            word[i] = ' ';
        }
    }

    printf("palavra sem letra: %s\n", word);
    for ( int i = 0; word[i] != '\0'; i++ ) {//descartando os zeros à esquerda

        if ( (word[i] < '0' || word[i] > '9') && word[i+1] == '0' && ( word[i+2] >= '0' && word[i+2] <= '9') ) {
            word[i+1] = ' ';
        } else if (i == 0 && word[i] == '0' && ( word[i+1] >= '0' && word[i+1] <= '9' ) ) {
            word[i] = ' ';
        }
    }
    printf("palavra sem 0 a esquerda: %s\n", word);
    for ( int i = 0; word[i] != '\0'; i++ ) { //armazenando cada inteiro
        if ( word[i] >= '0' && word[i] <= '9' ) {
            intList =  realloc( intList, ( intCounter + 1 ) * sizeof( *intList ) );//aloca espaço para a palavra a ser preenchida
            intList[intCounter] = ( char * ) calloc( 1, sizeof ( char ) );// tive que adicionar pq o valgrind reclama se o valor não é inicializado em NULL
            int letter = 0;
            intCounter++;
            while ( word[i] != ' ' && word[i] != '\0'){
                intList[intCounter - 1] = realloc ( intList[intCounter-1], ( letter + 1 ) * sizeof ( char ) );//aloca espaço para a letra a ser preenchida;
                intList[intCounter - 1][letter] = word[i];
                i++;
                letter++;
            }
            intList[intCounter - 1] = realloc ( intList[intCounter - 1], ( letter + 1 ) * sizeof ( char ) );
            intList[intCounter - 1][letter] = '\0';
            i--;//garante que, se o while parar por encontrar o '\0', o for() também pare de ser executado
        }
    }

    for ( int i = 0; i < intCounter; i++ ) { //Retirando os números repetidos do somatório
        for ( int j = i + 1; j < intCounter; j++){
            if ( strcmp ( intList[i], intList[j] ) == 0 ) {
                intList[i] = realloc ( intList[i], sizeof(char) );
                intList[i][0] = '\0';
                j = intCounter;
            }
        }
    }
    int returning = 0;
    for ( int i = 0; i < intCounter; i++ ) {
        if ( intList[i][0] != '\0' )
            returning++;
        free ( intList[i] );
    }
    free ( intList );

    return returning;
}