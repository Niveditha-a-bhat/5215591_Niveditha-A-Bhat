#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* highestValuePalindrome(char* s, int n, int k) {
    int changes_needed = 0;
    int* changed = (int*)calloc(n, sizeof(int));
    char* str = (char*)malloc((n + 1) * sizeof(char));
    strcpy(str, s);
    
    // Calculate minimum changes needed to make palindrome
    for (int i = 0; i < n / 2; i++) {
        if (str[i] != str[n - 1 - i]) {
            changes_needed++;
        }
    }
    
    if (changes_needed > k) {
        free(changed);
        free(str);
        return "-1";
    }
    
    int remaining_changes = k;
    // First pass: make it a palindrome
    for (int i = 0; i < n / 2; i++) {
        int j = n - 1 - i;
        if (str[i] != str[j]) {
            if (str[i] > str[j]) {
                str[j] = str[i];
                changed[j] = 1;
            } else {
                str[i] = str[j];
                changed[i] = 1;
            }
            remaining_changes--;
        }
    }
    
    // Second pass: maximize the value
    for (int i = 0; i < n / 2 && remaining_changes > 0; i++) {
        int j = n - 1 - i;
        if (str[i] != '9') {
            if (changed[i] || changed[j]) {
                // This pair was changed in the first pass, so we can upgrade to 9 with one change
                if (remaining_changes >= 1) {
                    str[i] = '9';
                    str[j] = '9';
                    remaining_changes--;
                }
            } else {
                // This pair was not changed in the first pass, so we need two changes to upgrade both to 9
                if (remaining_changes >= 2) {
                    str[i] = '9';
                    str[j] = '9';
                    remaining_changes -= 2;
                }
            }
        }
    }
    
    // If n is odd and there are remaining changes, upgrade the center to '9'
    if (n % 2 == 1 && remaining_changes > 0) {
        int mid = n / 2;
        if (str[mid] != '9') {
            str[mid] = '9';
            remaining_changes--;
        }
    }
    
    free(changed);
    return str;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    char* s = (char*)malloc((n + 1) * sizeof(char));
    scanf("%s", s);
    char* result = highestValuePalindrome(s, n, k);
    printf("%s\n", result);
    free(s);
    return 0;
}