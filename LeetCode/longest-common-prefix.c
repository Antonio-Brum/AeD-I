char* longestCommonPrefix(char** strs, int strsSize) {
    if(isCharacter(strs, strsSize)){

        int reaTam = 1; //Define o tamanho do realloc
        char *comum = (char *)malloc(sizeof(char));
        comum[0] = '\0';
        char *temp = (char *)malloc(sizeof(char));
        int keep = 1;
        int i;

        for(i = 0; strs[0][i] != '\0' && keep == 1; i++){
            temp[i] = strs[0][i];
            for(int j = 1; j < strsSize ;j++){
                if(strs[j][i] == strs[0][i]){
                    temp[i] = strs[0][i];
                }
                else{
                    temp[i] = '\0';
                    break;
                }
            }
            if (temp[i] == '\0'){
                keep = 0;
                reaTam++;
                comum =(char *)realloc(comum, reaTam * sizeof(char));
                comum[i] = '\0';
            }else {
                comum[i] = temp[i];
                reaTam++;
                comum = (char *)realloc(comum, reaTam * sizeof(char));
                comum[i+1]='\0';
                temp = (char *)realloc(temp, reaTam * sizeof(char));
            }
        }   
        free (temp);
        return comum;
    }else
        return "";
}

int isCharacter(char** strs, int strsSize){//Testa se não recebe string vazia
    int vazio = 0;
    for(int i = 0; i != strsSize; i++){
        if(strs[i][0] != '\0'){
            vazio = 1;
        }
    }
    return vazio;
}
