
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

char* strings_xor(char* s, char* t) {
    int length = strlen(s);
    char* result = (char*) malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++) {
        if (s[i] == t[i]) {
            result[i] = '0';
        } else {
            result[i] = '1';
        }
    }
    result[length] = '\0';  // Add null terminator
    return result;
}

int main() {
    char s[10000];
    char t[10000];
    scanf("%s", s);
    scanf("%s", t);
    char* result = strings_xor(s, t);
    printf("%s\n", result);
    free(result);
    return 0;
}
