bool lemonadeChange(int* bills, int billsSize) {
    
    int store[3] = {0,0,0}; //respectivamente 5$, 10$, 20$

    for(int i = 0; i < billsSize; i++){
        if(bills[i] == 5){
            store[0]++;

        } else if (bills[i] == 10) {
            if (store[0] == 0){
                return false;
            }
            store[0]--;
            store[1]++;

        } else {
            if (store[0] == 0){
                return false;
            } else if (store[1] == 0){
                if (store[0] < 3){
                    return false;
                }
                store[0] = store[0] - 3;
                store[2]++;
            } else {
                store[0]--;
                store[1]--;
                store[2]++;
            }
        }
     }
    return true;
}
