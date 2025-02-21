#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int x;
    tnode *next;
    tnode *prev;
} *head, *tail;

void push_front(int value) {
    struct tnode *node = (tnode*) malloc(sizeof(tnode));
    node->x = value;
    node->prev = NULL;
    
    if (head == NULL) {
        head = tail = node;
        tail->next = NULL;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
}

void push_back(int value) {
    struct tnode *node = (tnode*) malloc(sizeof(tnode));
    node->x = value;
    node->next = NULL;
    
    if (head == NULL) {
        head = tail = node;
        head->prev = NULL;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}

void display_forward() {
    struct tnode *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->x);
        temp = temp->next;
    }
    printf("\n");
}

void display_backward() {
    struct tnode *temp = tail;
    while (temp != NULL) {
        printf("%d ", temp->x);
        temp = temp->prev;
    }
    printf("\n");
}

struct tnode* previous(struct tnode* node) {
    if (node == NULL || node->prev == NULL) {
        return NULL;
    }
    return node->prev;
}

int main() {
    push_front(10);
    push_front(20);
    push_back(30);
    push_back(40);
    
    printf("Double Linked List:\n");
    printf("Forward: ");
    display_forward();
    
    printf("Backward: ");
    display_backward();
    
    struct tnode* temp = tail;
    if (previous(temp) != NULL) {
        printf("Previous of %d is %d\n", temp->x, previous(temp)->x);
    } else {
        printf("No previous node for %d\n", temp->x);
    }
    
    return 0;
}

