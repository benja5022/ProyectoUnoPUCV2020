/**
 MIT License
 
 Copyright (c) 2018 Matias Barrientos.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "stack.h"
#include <stdlib.h>
#include <assert.h>

typedef struct node node;

struct node {
    const void *data;
    node *next;
};

struct stack {
    node *head;
    long count;
    stack_release_object_callback release;
};

static node *
node_init (const void *data) {
    node *new = (node *) malloc (sizeof (node));
    
    assert (new != NULL);
    
    new->data = data;
    new->next = NULL;
    
    return new;
}

stack *
stack_create (stack_release_object_callback release) {
    stack *new = (stack *) malloc (sizeof (stack));
    
    assert (new != NULL);
    
    new->head = NULL;
    new->count = 0;
    new->release = release;
    
    return new;
}

stack *
stack_create_empty () {
    return stack_create (NULL);
}

void
stack_push (stack *stack, const void *data) {
    assert (stack != NULL);
    
    node *new = node_init (data);
    
    if (stack->head != NULL)
        new->next = stack->head;
    
    stack->head = new;
    stack->count += 1;
}

void *
stack_pop (stack *stack) {
    assert (stack != NULL);
    
    if (stack->head == NULL)
        return NULL;
    
    node *aux = stack->head;
    
    void *data = (void *) aux->data;
    
    if (stack->release != NULL) {
        stack->release(data);
        data = NULL;
    }
    
    stack->head = stack->head->next;
    
    free (aux);
    
    stack->count -= 1;
    
    return data;
}

void *
stack_top (stack *stack) {
    assert (stack != NULL);
    
    if (stack->head == NULL)
        return NULL;
    
    return (void *)stack->head->data;
}

long
stack_size (stack *stack) {
    assert (stack != NULL);
    
    if (stack->head == NULL)
        return 0;
    
    return stack->count;
}

int
stack_empty (stack *stack) {
    assert (stack != NULL);
    
    return stack->count == 0;
}

void
stack_release (stack **stack) {
    assert (stack != NULL);
    assert ((*stack) != NULL);
    
    while ((*stack)->head != NULL) {
        stack_pop (*stack);
    }
    
    free(*stack);
    *stack = NULL;
}
