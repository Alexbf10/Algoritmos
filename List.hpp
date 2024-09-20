#ifndef _TLIST_TAD_
#define _TLIST_TAD_

#include <iostream>

#include "../../funciones/lists.hpp"

using namespace std;

template<typename T>
struct List
{
   Node<T>* p;
   int cantElementos;
   Node<T>* iteracion;
};

//Descripción: Función de inicialización.
template<typename T>
List<T> list()
{
   List<T> lst;

   lst.p = NULL;
   lst.cantElementos = 0;
   lst.iteracion = lst.p;

   return lst;
}

//Descripción: Agrega un elemento al final de la lista.
template<typename T>
T* listAdd(List<T>& lst,T e)
{
   lst.cantElementos++;
   Node<T>* aux = add (lst.p, e);
   T* aux2 = &(aux->info);

   return aux2;
}

//Descripción: Agrega el elemento e al inicio de la lista.
template<typename T>
T* listAddFirst(List<T>& lst,T e)
{
   lst.cantElementos++;
   return addFirst (lst.p, e);
}

//Descripción: Remueve el elemento que concuerde con k según la función cmpTK.
template<typename T,typename K>
T listRemove(List<T>& lst,K k,int cmpTK(T,K))
{
   T t;
   lst.cantElementos--;
   t = remove (lst.p,k,cmpTK);
   return t;
}

//Descripción: Desenlaza y libera el primer nodo de la lista enlazada, retornando el valor
//del elemento que contenía.
template<typename T>
T listRemoveFirst(List<T>& lst)
{
   T t;
   lst.cantElementos--;
   t = removeFirst (lst.p);
   return t;
}

//Descripción: Retorna la dirección del primer
//elemento concordante con k según cmpTK.
template<typename T,typename K>
T* listFind(List<T> lst,K k,int cmpTK(T,K))
{
   return find (lst.p, k, cmpTK);
}

//Descripción: Indica si la lista está vacía o tiene elementos.
template<typename T>
bool listIsEmpty(List<T> lst)
{
   return isEmpty (lst.p);
}

//Descripción: Indica cuántos elementos tiene la lista.
template<typename T>
int listSize(List<T> lst)
{
   return lst.cantElementos;
}

//Descripción: Libera la memoria que ocupa la lista.
template<typename T>
void listFree(List<T>& lst)
{
   lst.cantElementos = 0;
   free (lst.p);
}

//Descripción: Descubre el elemento t en la lista lst.
template<typename T>
T* listDiscover(List<T>& lst,T t,int cmpTT)
{
   return NULL;
}

//Descripción: Inserta un elemento según el orden que establece cmpTT. La lista debe
//estar ordenada (según cmpTT) o vacía.
template<typename T>
T* listOrderedInsert(List<T>& lst,T t,int cmpTT(T,T))
{
   lst.cantElementos++;
   return orderedInsert (lst.p, t, cmpTT);
}

//Descripción: Ordena la lista según el criterio que establece cmpTT.
template<typename T>
void listSort(List<T>& lst,int cmpTT(T,T))
{
   sort (lst.p, cmpTT);
}

//Descripción: Prepara la lista para iterarla.
template<typename T>
void listReset(List<T>& lst)
{
   lst.iteracion = lst.p;
}

//Descripción: Indica si quedan más elementos para seguir iterando la lista.
template<typename T>
bool listHasNext(List<T> lst)
{
   bool respuesta = false;
   if (lst.iteracion != NULL)
   {
      respuesta = true;
   }

   return respuesta;
}

//Descripción: Retorna la dirección del siguiente elemento de la lista en la iteración.
template<typename T>
T* listNext(List<T>& lst)
{
   T* t = &(lst.iteracion->info);
   lst.iteracion = lst.iteracion->sig;
   return t;
}

//Descripción: Retorna la dirección del siguiente elemento de la lista en la iteración.
template<typename T>
T* listNext(List<T>& lst,bool& endOfList)
{
   T* t;
   t = listNext (lst);
   endOfList = listHasNext (lst);
   return t;
}

#endif
