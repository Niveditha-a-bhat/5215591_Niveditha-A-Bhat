#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define ALPHABET_SIZE 10

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
} TrieNode;

TrieNode* createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

bool insertAndCheck(TrieNode *root, const char *word) {
    TrieNode *current = root;
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
        if (current->isEndOfWord) {
            return false;
        }
    }
    current->isEndOfWord = true;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (current->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

void noPrefix(int words_count, char** words) {
    TrieNode *root = createNode();
    for (int i = 0; i < words_count; i++) {
        if (!insertAndCheck(root, words[i])) {
            printf("BAD SET\n%s\n", words[i]);
            return;
        }
    }
    printf("GOOD SET\n");
}

int main() {
    int n;
    scanf("%d", &n);
    getchar(); // to consume the newline after integer input

    char **words = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        words[i] = (char *)malloc(1000000 * sizeof(char)); // max length constraint is 10^6
        scanf("%s", words[i]);
    }

    noPrefix(n, words);

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(words[i]);
    }
    free(words);

    return 0;
}