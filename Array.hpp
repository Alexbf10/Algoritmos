#ifndef _TARR_TAD_
#define _TARR_TAD_

#include <iostream>
#include <stdlib.h>
#include "../../funciones/arrays.hpp"

using namespace std;

template<typename T>
struct Array
{
   T* array;
   int length;
};

// Descripción: Inicializa un array cuya capacidad inicial será establecida por defecto.
// La longitud del array será 0, y se incrementará a medida que se agreguen o inserten
// nuevos elementos.
template<typename T>
Array<T> array()
{
   Array<T> ret;
   ret.array = new T[100];
   ret.length = 0;

   return ret;
}

// Descripción: Agrega t al final de a incrementando, de ser necesario, su capacidad.
// Retorna la posición del arr donde quedó ubicado el elemento t.
template<typename T>
int arrayAdd(Array<T>& a,T t)
{
   add (a.array,a.length,t);
   return (a.length);
}

// Descripción: Retorna la dirección del elemento de a ubicado en la posición p.
template<typename T>
T* arrayGet(Array<T> a,int p)
{
   T* pos = &(a.array[p]);
   return pos;
}

// Descripción: Asigna el elemento t en la posición p del array a.
template<typename T>
void arraySet(Array<T>& a,int p,T t)
{
   a.array[p] = t;
}

// Descripción: Inserta t en la posición p del array a.
template<typename T>
void arrayInsert(Array<T>& a,T t,int p)
{
   insert (a.array,a.length,t,p);
}

// Descripción: Retorna la longitud actual del array.
template<typename T>
int arraySize(Array<T> a)
{

   return a.length;
}

// Descripción: Remove el elemento de a ubicado en la posición p.
template<typename T>
T arrayRemove(Array<T>& a,int p)
{
   T t;
   t = remove (a.array,a.length,p);
   return t;
}

//Descripción: Remueve todos los elemento de a dejándolo vacío, con longitud 0.
template<typename T>
void arrayRemoveAll(Array<T>& a)
{
   delete a.array;
   a.array = new T[100];
   a.length = 0;
}

// Descripción: Retorna la posición que k ocupa dentro de a,
// según la función de comparación cmpTK, o un valor negativo si a no contiene a k.
template<typename T,typename K>
int arrayFind(Array<T> a,K k,int cmpTK(T,K))
{
   int pos = find (a.array,a.length,k,cmpTK);
   return pos;
}

// Descripción: Inserta t en a según el criterio de precedencia que establece cmpTT.
template<typename T>
int arrayOrderedInsert(Array<T>& a,T t,int cmpTT(T,T))
{
   int pos = orderedInsert (a.array,a.length,t,cmpTT);
   return pos;
}

// Descripción: Descubre (busca, y si no encuentra lo agrega) al elemento t en el array a.
template<typename T>
T* arrayDiscover(Array<T>& a,T t,int cmpTT(T,T))
{
   // Lo busco
   int pos = find (a.array,a.length,t,cmpTT);

   // Si no esta, lo agrego
   if (pos<0)
   {
      add (a.array,length,t);
   }

   //retorno su direccion
   return (arrayGet(a, pos));
}

//Descripción: Ordena el array a según establece cmpTT.
template<typename T>
void arraySort(Array<T>& a,int cmpTT(T,T))
{
   sort (a.array,a.length,cmpTT);
}

#endif
