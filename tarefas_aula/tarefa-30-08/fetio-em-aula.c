int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {

    int mostProf = -1;
    int maxProfit = 0;

    for (int i = 0; i < workerSize; i++ ){
        for(int j = 0; j < difficultySize; j++){
            if (difficulty[j] <= worker[i]){
                if(mostProf == -1){
                    mostProf = j;
                }else if(profit[j] > profit[mostProf]){
                    mostProf = j;
                }
            }
        }
        if (mostProf != -1){
        maxProfit += profit[mostProf];
        }
        mostProf = -1;
    }

    return maxProfit;
}


