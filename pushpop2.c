// create a stack for push, pop and peek actions

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_INT 10

typedef struct {
	int arr[MAX_INT];
	int top;
} Stack;

void build(Stack *stack) {
	stack->top = -1;
} 

bool isEmpty(Stack *stack) {
	return stack->top == -1;
}

bool isFull(Stack *stack) {
	return stack->top >= MAX_INT - 1;
}

void push(Stack *stack, int value) {
	if (isFull(stack)) { printf("Stack overflow!\n"); }
	++stack->top;
	stack->arr[stack->top] = value;
	printf("We pushed %d in the array stack\n",value);
}

void pop(Stack *stack) {
	if (isEmpty(stack)) { printf("Stack underflow!\n"); }
	int popped = stack->arr[stack->top];
	stack->top--;
	printf("We removed %d out of the array stack\n",popped);
}

void peek(Stack *stack) {
	if (isEmpty(stack)) { printf("The stack is empty!\n"); }
	int top_value = stack->arr[stack->top];
	printf("The element at the top of the stack is %d\n", top_value);
}

void main() {
Stack *stack;
build(stack);
push(stack, 2);
peek(stack);
push(stack, 3);
peek(stack);
push(stack, 5);
peek(stack);
push(stack, 8);
peek(stack);

while (!isEmpty(stack)) {
peek(stack);
pop(stack);
}

free(stack);

}