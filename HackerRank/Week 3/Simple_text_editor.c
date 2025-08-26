#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_OPERATIONS 1000
#define MAX_STRING_LENGTH 1000000

typedef struct {
    char* data;
    int capacity;
    int size;
} Stack;

void push(Stack* stack, const char* str) {
    int len = strlen(str);
    if (stack->size + len + 1 > stack->capacity) {
        stack->capacity = (stack->size + len + 1) * 2;
        stack->data = realloc(stack->data, stack->capacity);
    }
    strcpy(stack->data + stack->size, str);
    stack->size += len;
}

int main() {
    int q;
    scanf("%d", &q);
    
    // Initialize the current string and undo stack
    char* current = malloc(MAX_STRING_LENGTH);
    current[0] = '\0';
    int current_len = 0;
    
    // Stack for undo operations (stores strings)
    char** undo_stack = malloc(MAX_OPERATIONS * sizeof(char*));
    int undo_top = -1;
    
    for (int i = 0; i < q; i++) {
        int op;
        scanf("%d", &op);
        
        if (op == 1) { // Append
            char str[1000000];
            scanf("%s", str);
            
            // Save current state to undo stack
            undo_stack[++undo_top] = malloc(current_len + 1);
            strcpy(undo_stack[undo_top], current);
            
            // Append new string
            strcat(current, str);
            current_len = strlen(current);
        }
        else if (op == 2) { // Delete
            int k;
            scanf("%d", &k);
            
            // Save current state to undo stack
            undo_stack[++undo_top] = malloc(current_len + 1);
            strcpy(undo_stack[undo_top], current);
            
            // Delete last k characters
            current_len -= k;
            current[current_len] = '\0';
        }
        else if (op == 3) { // Print
            int k;
            scanf("%d", &k);
            printf("%c\n", current[k - 1]);
        }
        else if (op == 4) { // Undo
            if (undo_top >= 0) {
                strcpy(current, undo_stack[undo_top]);
                current_len = strlen(current);
                free(undo_stack[undo_top]);
                undo_top--;
            }
        }
    }
    
    // Free memory
    free(current);
    for (int i = 0; i <= undo_top; i++) {
        free(undo_stack[i]);
    }
    free(undo_stack);
    
    return 0;
}