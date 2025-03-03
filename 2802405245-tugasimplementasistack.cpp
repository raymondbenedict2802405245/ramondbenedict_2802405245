#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

char stack[MAX];
char infix[MAX], postfix[MAX];
int top = -1;

void push(char);
char pop();
int isEmpty();
void inToPost();
void print();
int precedence(char);

int precedence(char symbol) {
    switch(symbol) {
        case '^': return 3;
        case '/': case '*': return 2;    
        case '+': case '-': return 1;
        default: return 0;
    }
}

void inToPost() {
    int i, j = 0;
    char symbol, next;
    for (i = 0; i < strlen(infix); i++) {
        symbol = infix[i];
        
        if (symbol == ' ' || symbol == '\t') {
            continue; // Abaikan spasi
        }

        switch(symbol) {
            case '(':
                push(symbol);
                break;
            case ')':
                while (!isEmpty() && (next = pop()) != '(') {
                    postfix[j++] = next;
                }
                break;
            case '+': case '-': case '*': case '/': case '^':
                while (!isEmpty() && precedence(stack[top]) >= precedence(symbol)) {
                    postfix[j++] = pop();
                }
                push(symbol);
                break;
            default:
                postfix[j++] = symbol;
        }
    }

    while (!isEmpty()) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

void print() {
    printf("The equivalent postfix expression is: %s\n", postfix);
}

void push(char c) {
    if (top == MAX - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];  // Perbaikan: Decrement top setelah pop
}

int isEmpty() {
    return (top == -1);
}

int main() {
    printf("Enter the infix expression: ");
    fgets(infix, MAX, stdin);
    
    // Menghapus karakter newline dari fgets
    infix[strcspn(infix, "\n")] = '\0';

    inToPost();
    print();
    
    return 0;
}

