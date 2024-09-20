#ifndef _TSTACK_TAD_
#define _TSTACK_TAD_

#include <iostream>
#include "../../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Stack
{
   Node<T>* p;
   int cantElementos;
};

//Descripción: Crea una pila vacía.
template<typename T>
Stack<T> stack()
{
   Stack<T> st;
   st.p = NULL;
   st.cantElementos = 0;
   return st;
}

//Descripción: Apila el elemento e.
template<typename T>
T* stackPush(Stack<T>& st,T e)
{
   st.cantElementos++;
   return push (st.p, e);
}

//Descripción: Desapila un elemento.
template<typename T>
T stackPop(Stack<T>& st)
{
   st.cantElementos--;
   T t;
   t = removeFirst (st.p)
   return t;
}

//Descripción: Retorna true o false según la pila tenga elementos o no.
template<typename T>
bool stackIsEmpty(Stack<T> st)
{
   return isEmpty (st.p);
}

//Descripción: Retorna la cantidad de elementos que tiene la pila.
template<typename T>
int stackSize(Stack<T> st)
{
   return st.cantElementos;
}

#endif
