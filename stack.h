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

#ifndef stack_h
#define stack_h

typedef struct stack stack;

/**
 @typedef
 Prototipo de funcion para eliminar de memoria el objeto que se guarda dentro del stack.
 
 @param object Puntero al objecto guardado.
 */
typedef void (*stack_release_object_callback) (void *object);

/**
 Crea un puntero de tipo Stack e inicializa sus variables.
 
 @return Puntero al nuevo Stack.
 */
extern stack *stack_create (stack_release_object_callback release);

/**
 Crea un puntero de tipo Stack e inicializa sus variables.
 
 @return Puntero al nuevo Stack.
 */
extern stack *stack_create_empty (void);


/**
 Inserta un elemento en la parte superior del Stack.
 
 Complejidad: O(1)
 
 @param stack Puntero al Stack.
 @param data Puntero al dato que quiere ser insertado en el Stack.
 */
extern void stack_push (stack *stack, const void *data);

/**
 Elimina el elemento en la parte superior del Stack,
 si la funcion release esta activa, esta eliminara de la memoria
 del puntero al dato guardado y retornara NULL,
 en caso contrario retornara el puntero al dato.
 
 Complejidad: O(1)
 
 @param stack Puntero al Stack.
 @return Puntero al objeto en la parte superior del Stack.
 */
extern void *stack_pop (stack *stack);

/**
 Retorna el elemento de la parte superior del Stack sin eliminarlo del Stack.
 
 Complejidad: O(1)
 
 @param stack Puntero al Stack.
 @return Puntero al objeto en la parte superior del Stack.
 */
extern void *stack_top (stack *stack);

/**
 Devuelve la cantidad de elementos en el Stack.
 
 Complejidad: O(1)
 
 @param stack Puntero al Stack.
 @return La cantitdad de elementos en el stack.
 */
extern long stack_size (stack *stack);

/**
 Prueba si el Stack está vacía.
 
 Complejidad: O(1)
 
 @param stack Puntero al Stack.
 @return 1 (true) si y solo si el Stack no contiene elementos; 0 (false) lo contrario.
 */
extern int stack_empty (stack *stack);

/**
 Elimina todo los elementos del stack, si se encuetra la funcion release
 activa, eliminara los datos de la memoria.
 
 Complejidad: O(n)
 
 @param stack Puntero a puntero de Stack.
 */
extern void stack_release (stack **stack);

#endif /* stack_h */
