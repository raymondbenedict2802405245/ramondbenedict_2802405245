#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int top;
    char items[MAX];
} Stack;

void init(Stack *s) { s->top = -1; }
int isEmpty(Stack *s) { return s->top == -1; }
void push(Stack *s, char c) { s->items[++(s->top)] = c; }
char pop(Stack *s) { return isEmpty(s) ? '\0' : s->items[(s->top)--]; }
char peek(Stack *s) { return isEmpty(s) ? '\0' : s->items[s->top]; }
int precedence(char op) { return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : (op == '^') ? 3 : 0; }
int isOperand(char c) { return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'); }

void infixToPostfix(char *infix, char *postfix) {
    Stack s; init(&s);
    int i, j = 0;
    for (i = 0; infix[i]; i++) {
        char c = infix[i];
        if (isOperand(c)) postfix[j++] = c;
        else if (c == '(') push(&s, c);
        else if (c == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') postfix[j++] = pop(&s);
            pop(&s);
        } else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(c))
                postfix[j++] = pop(&s);
            push(&s, c);
        }
    }
    while (!isEmpty(&s)) postfix[j++] = pop(&s);
    postfix[j] = '\0';
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Masukkan infix: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("postfix: %s\n", postfix);
    return 0;
}

