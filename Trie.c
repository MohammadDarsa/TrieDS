#include <stdio.h>
#include <stdlib.h>

#define ALPHA_SIZE 26

//Node Definition
typedef struct TrieNode {
    struct TrieNode* children[ALPHA_SIZE];
    int EOW;
} TrieNode;

//Create Node Function
TrieNode* createNode() {
    TrieNode* temp = (TrieNode*)malloc(sizeof(TrieNode));
    for(int i=0; i<ALPHA_SIZE; i++) {
        temp->children[i] = NULL;
    }
    temp->EOW = 0;
    return temp;
}

//Insert Word Function
void insert(TrieNode* root, char* key) {
    TrieNode* current = root;
    for(int i=0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';

        if(!current->children[index])
            current->children[index] = createNode();

        current = current->children[index];
    }

    current->EOW = 1;
}

//Search Word Function
int search(TrieNode* root, char* key) {
    TrieNode* current = root;
    for(int i=0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';
        if(!current->children[index])
            return 0;
        
        current = current->children[index];
    }

    return current && current->EOW;
}

//Is Empty Function
int isEmpty(TrieNode* root) {
    if(!root) return 0;

    for(int i=0; i<ALPHA_SIZE; i++) {
        if(root->children[i]) return 1;
    }

    return 0;
}

//Delete Word Function
TrieNode* deleteWord(TrieNode* root, char* key) {
    if(!root) return NULL;
    if(*key == '\0') {
        if(root->EOW) root->EOW = 0;
        if(isEmpty(root)) {
            free(root);
            root = NULL;
        }

        return root;
    }

    int index = *key - 'a';
    root->children[index] = deleteWord(root->children[index], key+1);

    if(isEmpty(root) && !root->EOW) {
        free(root);
        root = NULL;
    }

    return root;
}

//Test Our Trie
int main() {
    char* names[] = {
        "cat",
        "dog",
        "monke"
    };

    TrieNode* trie = createNode();

    insert(trie, names[0]);
    insert(trie, names[1]);
    insert(trie, names[2]);

    printf("%d means shark is not preset in the trie\n", search(trie, "shark"));
    printf("%d means cat is preset in the trie\n", search(trie, "cat"));
    printf("%d means dogs is not preset in the trie\n", search(trie, "dogs"));

    deleteWord(trie, "cat");
    printf("%d means cat is not preset in the trie after deletion\n", search(trie, "cat"));
    return 0;
}
