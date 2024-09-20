#ifndef _TLIST_T_
#define _TLIST_T_

#include <iostream>
#include <stdio.h>

template <typename T>
struct Node
{
   T info;
   Node<T>* sig;
};

//Descripción: Agrega el elemento e al final de la lista direccionada por p.
template <typename T>
Node<T>* add(Node<T>*& p,T e)
{
   Node<T>* nuevo = new Node<T>(e, NULL);

   if (p != NULL)
   {
      Node<T>* aux = p;
      while (aux->sig != NULL)
      {
         aux = aux->sig;
      }

      aux->sig = nuevo;
   }
   else
   {
      p = nuevo;
   }

   return p;
}

//Descripción: Agrega el elemento e al inicio de la lista direccionada por p.
template <typename T>
Node<T>* addFirst(Node<T>*& p,T e)
{
   //creo el nuevo primer nodo
   Node<T>* nuevo = new Node<T>(e,p);
   // conecto nuevo con la lista y redirecciono a p
   p = nuevo;
   return p;
}

//Descripción: Remueve la primera ocurrencia del elemento concordante con cmpTK.
template <typename T, typename K>
T remove(Node<T>*& p,K k,int cmpTK(T,K))
{
   T t;
   Node<T>* aux = p;
   Node<T>* aux2;

   //busco elemento y el anterior
   while (cmpTK(aux->info,k) != 0)
   {
      aux2 = aux;
      aux = aux->sig;
   }

   //se lo saltea en la lista
   aux2->sig = aux->sig;

   //le hago return, y delete
   t = aux->info;
   delete aux;

   return t;
}

//Descripción: Remueve el primer elemento de la lista direccionada por p.
template <typename T>
T removeFirst(Node<T>*& p)
{
   T t;
   Node<T>* aux = p->sig;

   //delete el primer nodo
   t = p->info;
   delete p;

   //reasigno p
   p = aux;

   return t;
}

//Descripción: Retorna la dirección del nodo que contiene la primera ocurrencia de k,
//según cmpTK, o NULL si ningún elemento concuerda con dicha clave de búsqueda.
template <typename T, typename K>
Node<T>* find(Node<T>* p,K k,int cmpTK(T,K))
{
   Node<T>* aux = p;

   //busco el nodo
   while (cmpTK (aux->info, k) != 0 && aux != NULL)
   {
      aux = aux->sig;
   }
   return aux;
}

//Descripción: Inserta el elemento e en la lista direccionada por p según el criterio que
//establece la función cmpTT. La lista debe estar vacía u ordenada según cmpTT.
template <typename T>
Node<T>* orderedInsert(Node<T>*& p,T e,int cmpTT(T,T))
{
   Node<T>* aux = p;
   Node<T>* aux2 = NULL;
   Node<T>* nuevo = new Node<T>(e, NULL);

   if (p != NULL)
   {
      //busco el nodo
      while (aux != NULL && cmpTT (aux->info, e) < 0)
      {
         aux2 = aux;
         aux = aux->sig;
      }

      if (aux2 != NULL)
      {
         aux2->sig = nuevo;
      }
      else
      {
         p = nuevo;
      }
      nuevo->sig = aux;
   }
   else
   {
      p = nuevo;
   }

   return nuevo;
}

//Descripción: Busca en la lista direccionada por p la primera ocurrencia de e, y retorna
//la dirección del nodo que lo contiene. Si e no existe en la lista entonces lo insertar en
//orden, según el criterio establecido por cmpTT, y retorna la dirección del nodo
//insertado. Asigna true o false a enc según e fue encontrado o insertado.
template <typename T>
Node<T>* searchAndInsert(Node<T>*& p,T e,bool& enc,int cmpTT(T,T))
{
   Node<T>* aux = p;
   enc = false;

   //busco el nodo
   while (aux != NULL && cmpTT (aux->info, e) != 0)
   {
      aux = aux->sig;
   }

   if (aux != NULL && cmpTT (aux->info, e) == 0)
   {
      enc = true;
   }
   else
   {
      //si no lo encuentro, lo agrego
      aux = add (p,e);
   }

   return aux;
}

//Descripción: Ordena la lista direccionada por p según el criterio que establece la
//función de comparación cmpTT.
template <typename T>
void sort(Node<T>*& p,int cmpTT(T,T))
{
   //creo los datos a usar
   Node<T>* aux = p; //nodo actual
   Node<T>* siguiente = p->sig; //nodo siguiente
   Node<T>* anterior = p; //nodo anterior
   Node<T>* acomodar;
   bool cambio = true;

   //mientras halla cambios, reviso
   while (cambio)
   {
      cambio = false;

      while (siguiente != NULL)
      {
         //si cmp dice cambio
         if (cmpTT (aux->info, siguiente->info) > 0)
         {
            if (aux == p)
            {
               //si cambio el primero, cambia p
               p = siguiente;
            }

            //permuto
            anterior->sig = siguiente;
            aux->sig = siguiente->sig;
            siguiente->sig = aux;
            cambio = true;

            //reacomodo para que aux siga siendo donde estoy parado
            //y siguiente sea el siguiente
            acomodar = siguiente;
            siguiente = aux;
            aux = acomodar;
         }

         anterior = aux;
         aux = aux->sig;
         siguiente = siguiente->sig;
      }

      //reinicio valores
      aux = p;
      siguiente = p->sig;
   }
}

//Descripción: Indica si la lista direccionada por p tiene o no elemento.
template <typename T>
bool isEmpty(Node<T>* p)
{
   bool respuesta = false;
   if (p==NULL)
   {
      respuesta = true;
   }
   return respuesta;
}

//Descripción: Libera la memoria que utiliza lista direccionada por p. Asigna NULL a p.
template <typename T>
void free(Node<T>*& p)
{
   Node<T>* aux = p;

   while (p != NULL)
   {
      p = p-> sig;
      delete aux;
      aux = p;
   }
}

//Descripción: Inserta un nodo conteniendo a e al inicio de la lista direccionada por p.
template <typename T>
Node<T>* push(Node<T>*& p,T e)
{
   Node<T>* aux;
   aux = addFirst (p,e);
   return aux;
}

//Descripción: Remueve el primer nodo de la lista direccionada por p.
template <typename T> T pop(Node<T>*& p)
{
   T t;
   t = removeFirst (p);
   return t;
}

//Descripción: Agrega el elemento e al final la lista direccionada por q.
template <typename T>
Node<T>* enqueue(Node<T>*& p,Node<T>*& q,T e)
{
   Node<T>* aux = new Node<T>();
   aux = add (p,e);
   q = aux;
   return aux;
}

//Descripción: Agrega el elemento e al final la lista circular direccionada por q.
template <typename T>
Node<T>* enqueue(Node<T>*& q,T e)
{
   return NULL;
}

//Descripción: Remueve el primer nodo de la lista direccionada por p.
template <typename T>
T dequeue(Node<T>*& p, Node<T>*& q)
{
   T t;
   t = removeFirst (p);
   return t;
}

//Descripción: Remueve el primer nodo de la lista circular direccionada por q.
template <typename T>
T dequeue(Node<T>*& q)
{
   T t;
   return t;
}

#endif
