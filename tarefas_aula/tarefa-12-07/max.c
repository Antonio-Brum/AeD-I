#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct stack{
    char *letters;
    char *top;
    int counter;
}stack_t;


int maximumGain(char* s, int x, int y);
char *buscaAb(stack_t *stack, char *s, int *xCounter);
char *buscaBa(stack_t *stack, char *s, int *yCounter);
void Reset(stack_t *stack);
void Push(stack_t *stack, char letter);
void Pop(stack_t *stack);
bool Empty(stack_t *stack);
void Clear(stack_t *stack);
char Top(stack_t *stack); //retorna topo da stack

int maximumGain(char* s, int x, int y) {
    if (strlen(s) == 1){
        return 0;
    }

    int xCounter = 0, yCounter = 0; 
    char *temp, *newS;

    stack_t stack;
    Reset(&stack);
    
    if (x > y) { //procura AB
        newS = buscaAb(&stack, s, &xCounter);
        Clear(&stack);
        temp = buscaBa(&stack, newS, &yCounter);
        free(newS);
        free(temp);

    } else if (x < y) {//procura BA
        newS = buscaBa(&stack, s, &yCounter);
        Clear(&stack);
        temp = buscaAb(&stack, newS, &xCounter);
        free(newS);
        free(temp);
    } 
    Clear(&stack);
    return xCounter*x + yCounter*y;

}

char * buscaAb(stack_t *stack, char *s, int *xCounter){
    int sSize = strlen(s); 
    char *newS = (char *) calloc(1, sSize); 
    int newSCounter = 0; //serve para saber o tamanho da nova string para fazer um realloc ao final

    for(int i = 0; s[i] != '\0'; i++){
        if (s[i] == 'b'){
            if (Top(stack) == 'a'){
                *xCounter = *xCounter+1;
                Pop(stack); //retira o 'a' que estava na pilha
                newSCounter--;
                newS[newSCounter] = '0'; //bota um '0' onde estava o 'a'
                //não empilha o b
            } else {
                Push(stack, s[i]);//Se acha um 'b', mas n tem um 'a' antes, apenas empilha 'b'
                newS[newSCounter] = s[i];
                newSCounter++;
            }
        } else {
            Push(stack, s[i]);
            newS[newSCounter] = s[i];
            newSCounter++;

        }
    }
    newS = (char *) realloc(newS, newSCounter + 1);
    newS[newSCounter] = '\0';
    return newS;
}

char *buscaBa(stack_t *stack, char *s, int *yCounter){
    int sSize = strlen(s); 
    char *newS = (char *) calloc(1, sSize); //vai ser a nova String, após a retirada dos ab's
    int newSCounter = 0; //serve para saber o tamanho da nova string para fazer um realloc ao final

    for(int i = 0; s[i] != '\0'; i++){
        if (s[i] == 'a'){
            if (Top(stack) == 'b'){
                *yCounter = *yCounter+1;
                Pop(stack); //retira o 'b' que estava na pilha
                newSCounter--;
                newS[newSCounter] = '0'; //bota um '0' onde estava o 'a'
                //não empilha o a
            } else {
                Push(stack, s[i]);//Se acha um 'a', mas n tem um 'b' antes, apenas empilha 'a'
                newS[newSCounter] = s[i];
                newSCounter++;
            }
        } else {
            Push(stack, s[i]);
            newS[newSCounter] = s[i];
            newSCounter++;
        }
    }
    newS = (char *) realloc(newS, newSCounter+1);
    newS[newSCounter] = '\0';
    return newS;
}


void Reset(stack_t *stack){
    stack->letters = NULL;
    stack->top = NULL;
    stack->counter = 0;
    return;
}

void Push(stack_t *stack, char letter){
    if(Empty(stack)){
        stack->letters = (char *) calloc(1, sizeof(char));
        stack->letters[0] = letter;
        stack->top = &stack->letters[stack->counter];
        stack->counter=1;
        return;
    }

    stack->letters = (char *) realloc(stack->letters, sizeof(char) * (stack->counter + 1));
    stack->letters[stack->counter] = letter;
    stack->top = &stack->letters[stack->counter];
    stack->counter++;
    return;
}
void Pop(stack_t *stack){
    if(Empty(stack)){
        return;
    } 
    if(stack->counter == 1){
        Clear(stack);
        return;
    } 

    stack->letters = (char *) realloc(stack->letters, sizeof(char) * (stack->counter - 1));
    stack->counter--;
    stack->top = &stack->letters[stack->counter-1];

    return;
}

bool Empty(stack_t *stack){
    return stack->top == NULL;
}

void Clear(stack_t *stack){
    if (Empty(stack)){
        return;
    }

    free(stack->letters);
    Reset(stack);

    return;
}

char Top(stack_t *stack){
    if(Empty(stack)){
        return '0';
    }

    return *stack->top;
}
