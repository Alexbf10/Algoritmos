#ifndef _TQUEUE_TAD_
#define _TQUEUE_TAD_

#include <iostream>
#include "../../funciones/lists.hpp"

using namespace std;

template<typename T>
struct Queue
{
   Node<T>* p;
   Node<T>* q;
   int cantElementos;
};

//Descripción: Crea una cola vacía.
template<typename T>
Queue<T> queue()
{
   Queue<T> q;
   q.p = NULL;
   q.q = NULL;
   q.cantElementos = 0;
   return q;
}

//Descripción: Encola el elemento e.
template<typename T>
T* queueEnqueue(Queue<T>& q,T e)
{
   q.cantElementos++;
   return enqueue (q.p,q.q,e);
}

//Descripción: Desencola un elemento.
template<typename T>
T queueDequeue(Queue<T>& q)
{
   q.cantElementos--;
   T t;
   t = dequeue (q.p,q.q);
   return t;
}

//Descripción: Retorna true o false según la cola tenga elementos o no.
template<typename T>
bool queueIsEmpty(Queue<T> q)
{
   return isEmpty (q.p);
}

//Descripción: Retorna la cantidad de elementos que tiene la cola.
template<typename T>
int queueSize(Queue<T> q)
{
   return q.cantElementos;;
}

#endif
