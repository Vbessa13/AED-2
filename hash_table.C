#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 100

typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode* table[TABLE_SIZE];
} HashTable;

unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

HashTable* createHashTable() {
    HashTable* ht = (HashTable*) malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
    return ht;
}

void insert(HashTable* ht, int key, int value) {
    unsigned int index = hash(key);
    HashNode* newNode = (HashNode*) malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = ht->table[index];
    ht->table[index] = newNode;
}

int search(HashTable* ht, int key) {
    unsigned int index = hash(key);
    HashNode* current = ht->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void removeNode(HashTable* ht, int key) {
    unsigned int index = hash(key);
    HashNode* current = ht->table[index];
    HashNode* previous = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (previous == NULL) {
                ht->table[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}
