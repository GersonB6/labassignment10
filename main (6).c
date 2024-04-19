#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node
typedef struct TrieNode {
    struct TrieNode *children[26]; // 26 letters of the alphabet
    int count;                     // To store the count of the word
} TrieNode;

// Creates a new trie node
TrieNode *createNode() {
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    for (int i = 0; i < 26; i++) {
        node->children[i] = NULL;
    }
    node->count = 0;
    return node;
}

// Inserts a word into the trie
void insert(TrieNode *root, char *word) {
    TrieNode *current = root;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    // Mark the end of the word and increment the count
    current->count++;
}

// Counts the occurrences of a word in the trie
int numberOfOccurrences(TrieNode *root, char *word) {
    TrieNode *current = root;
    int len = strlen(word);

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            return 0; // Word not found
        }
        current = current->children[index];
    }
    return current->count;
}

// Deallocates the trie
void deallocateTrie(TrieNode *root) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < 26; i++) {
        if (root->children[i] != NULL) {
            deallocateTrie(root->children[i]);
        }
    }
    free(root);
}

// Reads the dictionary file and populates the words array
int readDictionary(char *filename, char **pInWords) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    int count = 0;
    char word[256];

    while (fscanf(file, "%s", word) != EOF) {
        pInWords[count] = strdup(word);
        count++;
    }

    fclose(file);
    return count;
}

int main(void) {
    char *inWords[256];

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);

    for (int i = 0; i < numWords; ++i) {
        printf("%s\n", inWords[i]);
    }

    TrieNode *root = createNode();
    for (int i = 0; i < numWords; i++) {
        insert(root, inWords[i]);
    }

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(root, pWords[i]));
    }

    deallocateTrie(root);

    return 0;
}
