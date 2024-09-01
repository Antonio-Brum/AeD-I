
void Merge(int *difLeft, int *profLeft, int difLeftSize, int *difRight, int *profRight, int difRightSize, int *dif, int *prof){
    int i = 0;
    int j = 0;
    int k = 0;

    while(i < difLeftSize && j < difRightSize){

        if ( difLeft[i] <= difRight[j] ) {
            dif[k] = difLeft[i];
            prof[k] = profLeft[i];
            i++;
        } else {
            dif[k] = difRight[j];
            prof[k] = profRight[j];
            j++;
        }
        k++;
    }

    while (j < difRightSize){
        dif[k] = difRight[j];
        prof[k] = profRight[j];
        j++;
        k++;
    }

    while (i < difLeftSize){
        dif[k] = difLeft[i];
        prof[k] = profLeft[i];
        i++;
        k++;
    }
}



void Sort (int *dif, int *prof, int difSize){
    if (difSize <= 1){
        return;
    }
    int mid = (int)difSize/2;

    int difLeft[mid];
    int difRight[difSize - mid];
    int profLeft[mid];
    int profRight[difSize - mid];

    int i = 0;
    int j = 0;

    for(i; i < difSize; i++){
        if(i >= mid){
            difRight[j] = dif[i];
            profRight[j] = prof[i];
            j++;
        } else {
            difLeft[i] = dif[i];
            profLeft[i] = prof[i];
        }
    }

    Sort(difLeft, profLeft, mid);
    Sort(difRight, profRight, difSize - mid);
    Merge(difLeft, profLeft, mid, difRight, profRight, difSize - mid, dif, prof);

    return;
}

int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {

    Sort(difficulty, profit, difficultySize);
    Sort(worker, worker, workerSize);

    int mostProf = -1;
    int maxProfit = 0;
    int j;
    for (int i = 0; i < workerSize; i++ ){
        if(mostProf != -1){
            j = mostProf;
        } else {
            j = 0;
        }
        for(j; j < difficultySize; j++){
            if (difficulty[j] <= worker[i]){
                if(mostProf == -1){
                    mostProf = j;
                }else if(profit[j] > profit[mostProf]){
                    mostProf = j;
                }
            } else {
                j = difficultySize + 1;
            }
        }
        if (mostProf != -1){
        maxProfit += profit[mostProf];
        }

    }

    return maxProfit;
   
}
