#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TABLE_SIZE 10

// Struktur untuk chaining
typedef struct Node {
    int key;
    struct Node* next;
} Node;

// Hash table
int hashTable[TABLE_SIZE];
Node* chain[TABLE_SIZE];

// Inisialisasi tabel
void initializeTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = -1; // Untuk linear probing dan rehashing
        chain[i] = NULL;    // Untuk chaining
    }
}

// Fungsi Hash
int midSquare(int key) {
    int squared = key * key;
    return (squared / 10) % TABLE_SIZE;
}

int divisionMethod(int key) {
    return key % TABLE_SIZE;
}

int foldingMethod(int key) {
    int part1 = key / 100, part2 = key % 100;
    return (part1 + part2) % TABLE_SIZE;
}

int digitExtraction(int key) {
    return (key / 10) % TABLE_SIZE;
}

int rotationMethod(int key) {
    return ((key << 1) | (key >> (sizeof(int) * 8 - 1))) % TABLE_SIZE;
}

// Collision Handling: Linear Probing
void insertLinearProbing(int key, int (*hashFunc)(int)) {
    int index = hashFunc(key);
    while (hashTable[index] != -1) {
        index = (index + 1) % TABLE_SIZE;
    }
    hashTable[index] = key;
}

// Collision Handling: Chaining
void insertChaining(int key, int (*hashFunc)(int)) {
    int index = hashFunc(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = chain[index];
    chain[index] = newNode;
}

// Collision Handling: Rehashing
void insertRehashing(int key, int (*hashFunc)(int)) {
    int index = hashFunc(key);
    int step = 7 - (key % 7);
    while (hashTable[index] != -1) {
        index = (index + step) % TABLE_SIZE;
    }
    hashTable[index] = key;
}

// Menampilkan tabel
void displayTable() {
    printf("\nHash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        if (hashTable[i] != -1)
            printf("%d", hashTable[i]);
        Node* temp = chain[i];
        while (temp) {
            printf(" -> %d", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    initializeTable();
    int choice, hashChoice, collisionChoice, key;
    int (*hashFunc)(int) = NULL;
    void (*collisionHandler)(int, int (*)(int)) = NULL;

    printf("Pilih metode hash:\n");
    printf("1. Mid-Square\n2. Division\n3. Folding\n4. Digit Extraction\n5. Rotation\n");
    scanf("%d", &hashChoice);
    
    switch (hashChoice) {
        case 1: hashFunc = midSquare; break;
        case 2: hashFunc = divisionMethod; break;
        case 3: hashFunc = foldingMethod; break;
        case 4: hashFunc = digitExtraction; break;
        case 5: hashFunc = rotationMethod; break;
        default: printf("Pilihan tidak valid!\n"); return 0;
    }

    printf("Pilih metode collision handling:\n");
    printf("1. Linear Probing\n2. Chaining\n3. Rehashing\n");
    scanf("%d", &collisionChoice);
    
    switch (collisionChoice) {
        case 1: collisionHandler = insertLinearProbing; break;
        case 2: collisionHandler = insertChaining; break;
        case 3: collisionHandler = insertRehashing; break;
        default: printf("Pilihan tidak valid!\n"); return 0;
    }
    
    while (1) {
        printf("\n1. Insert\n2. Display\n3. Exit\n");
        scanf("%d", &choice);
        if (choice == 3) break;
        
        switch (choice) {
            case 1:
                printf("Masukkan kunci: ");
                scanf("%d", &key);
                collisionHandler(key, hashFunc);
                break;
            case 2:
                displayTable();
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    }
    return 0;
}

