#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    char *brackets;
    char *top;
    char *base;
    int bound;
}stack_t;

bool isValid(char* s);
void Push(stack_t *stack, char s);
void Pop(stack_t *stack);
void Reset(stack_t *stack);
bool Empty(stack_t *stack);
void Clear(stack_t *stack);

int main(){
      clock_t start_time = clock();

    if(isValid("]")){
        printf("bombou");
    } else {
        printf("não bombou");
    }
  double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
  printf("Done in %f seconds\n", elapsed_time);
    
    return 0;
}
bool isValid(char* s) {
    stack_t stack;
    Reset(&stack);

    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            Push(&stack, s[i]);
        }//if
        if(!Empty(&stack)){
            if(s[i] == ')'){
                if(*stack.top != '('){
                    return false;
                }//if
                Pop(&stack);
            }//if

            if(s[i] == ']'){
                if(*stack.top != '['){
                    return false;
                }
                Pop(&stack);
            }

            if(s[i] == '}'){
                if(*stack.top != '{'){
                    return false;
                }
                Pop(&stack);
            }
        }
    }//for

    if(!Empty(&stack)){
        return false;
    }

    Clear(&stack);
    return true;
}

void Reset(stack_t *stack){
    stack->brackets = NULL;
    stack->top = NULL;
    stack->base = NULL;
    stack->bound = 0;
}

void Push(stack_t *stack, char s){
    if ( Empty(stack) ) {
        stack->brackets = (char *) calloc(1, sizeof(char));
        stack->brackets[0] = s;
        stack->top = &stack->brackets[0];
        stack->base = &stack->brackets[0];
        stack->bound = 1;
        return;
    }//if

    stack->brackets = (char *) realloc(stack->brackets, sizeof(char) * (stack->bound + 1));
    stack->brackets[stack->bound] = s;
    stack->top = &stack->brackets[stack->bound];
    stack->bound++;
}

void Pop(stack_t *stack){
    if (Empty(stack)){
        return;
    }
    if (stack->bound == 1){
        free(stack->brackets);
        Reset(stack);
        printf("Pilha esvaziada");
        return;
    }
    
    stack->brackets = (char *) realloc(stack->brackets, sizeof(char) * (stack->bound - 1));
    stack->bound--;
    stack->top = &stack->brackets[stack->bound - 1];
    return;
}

bool Empty(stack_t *stack){
    return stack->brackets==NULL;
}

void Clear(stack_t *stack){
    if(Empty(stack)){
        return;
    }
    free(stack->brackets);
    return;
}
