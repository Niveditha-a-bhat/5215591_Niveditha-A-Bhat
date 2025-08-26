#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 100000

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

void push(Stack* s, int value) {
    s->data[++s->top] = value;
}

int pop(Stack* s) {
    return s->data[s->top--];
}

int peek(Stack* s) {
    return s->data[s->top];
}

int isEmpty(Stack* s) {
    return s->top == -1;
}

int main() {
    int q;
    scanf("%d", &q);
    
    Stack stack1, stack2;
    stack1.top = -1;
    stack2.top = -1;
    
    for (int i = 0; i < q; i++) {
        int type;
        scanf("%d", &type);
        
        if (type == 1) {
            int x;
            scanf("%d", &x);
            push(&stack1, x);
        } else if (type == 2) {
            if (isEmpty(&stack2)) {
                while (!isEmpty(&stack1)) {
                    push(&stack2, pop(&stack1));
                }
            }
            pop(&stack2);
        } else if (type == 3) {
            if (isEmpty(&stack2)) {
                while (!isEmpty(&stack1)) {
                    push(&stack2, pop(&stack1));
                }
            }
            printf("%d\n", peek(&stack2));
        }
    }
    
    return 0;
}