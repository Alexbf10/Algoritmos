
#ifndef _TMAP_TAD_
#define _TMAP_TAD_

#include <iostream>
#include "Array.hpp"

using namespace std;

template<typename K,typename V>
struct Map
{
   Array<K> keys;
   Array<V> values;
   int iteracionK;
   int iteracionV;
};

// Descripción: Inicializa un map.
template<typename K,typename V>
Map<K,V> map()
{
   Map<K,V> m;
   m.keys = array<K>();
   m.values = array<V>();
   m.iteracionK = 0;
   m.iteracionV = 0;
   return m;
}

template<typename K>
int cmpKK (K a, K b)
{
   int resultado;

   if (a>b)
   {
      resultado = 1;
   }
   else if (a<b)
   {
      resultado = -1;
   }
   else if (a==b)
   {
      resultado = 0;
   }
   return resultado;
}
// Descripción: Retorna la dirección de memoria del valor asociado
// a la clave k o NULL si m no contiene ningún valor asociado a dicha clave.
template<typename K,typename V>
V* mapGet(Map<K,V> m,K k)
{
   int pos = arrayFind<K,K> (m.keys,k, cmpKK);
   return arrayGet<V>(m.values,pos);
} //xd

// Descripción: Agrega al map m el elemento v asociado a la clave k.
// Si existía una entrada vinculada a k se debe reemplazar el valor anterior por v.
template<typename K,typename V>
V* mapPut(Map<K,V>& m,K k,V v)
{
   V* value;
   int pos = arrayFind<K,K> (m.keys,k,cmpKK);

   if (pos<0)
   {
      arrayAdd<K> (m.keys,k);
      pos = arrayAdd<V> (m.values,v);
      value = arrayGet<V> (m.values, pos);
   }
   else if (pos>=0)
   {
      V* value = arrayGet<V> (m.values,pos);
      *value = v;
   }

   return value;
} //xd

// Descripción: Verifica si m contiene a k.
template<typename K,typename V>
bool mapContains(Map<K,V> m,K k)
{
   bool respuesta;
   int pos = arrayFind <K,K> (m.keys,k,cmpKK);
   if (pos>=0)
   {
      respuesta = true;
   }
   else
   {
      respuesta = false;
   }

   return respuesta;
}// xd

//Descripción: Elimina de m la entrada identificada con la clave k.
template<typename K,typename V>
V mapRemove(Map<K,V>& m,K k)
{
   V v;
   int pos = arrayFind<K,K> (m.keys,k,cmpKK);
   v = arrayRemove<V> (m.values,pos);
   arrayRemove<K> (m.keys,pos);
   return v;
}

// Descripción: Elimina todas las entradas del map m.
template<typename K,typename V>
void mapRemoveAll(Map<K,V>& m)
{
   arrayRemoveAll<V> (m.values);
   arrayRemoveAll<K> (m.keys);
   m.iteracionV = 0;
   m.iteracionK = 0;
}

// Descripción: Retorna la cantidad actual de entradas que tiene m.
template<typename K,typename V>
int mapSize(Map<K,V> m)
{
   int cant = arraySize<V> (m.values);
   return cant;
}

// Descripción: Indica si quedan más elementos para continuar iterando el map.
template<typename K,typename V>
bool mapHasNext(Map<K,V> m)
{
   bool respuesta;
   if (m.keys.length>=(m.iteracionK+1) && m.values.length>=(m.iteracionV+1))
   {
      respuesta = true;
   }
   else
   {
      respuesta = false;
   }
   return respuesta;
}

//Descripción: Permite iterar sobre las claves del map. Esta función es mutuamente
//excluyente respecto de mapNextValue.
template<typename K,typename V>
K mapNextKey(Map<K,V>& m)
{
   K k;
   k = m.keys.array[m.iteracionK++];
   return k;
} // xd

// Descripción: Permite iterar sobre los valores que contiene el map.
// Esta función es mutuamente excluyente despecto de mapNextKey.
template<typename K,typename V>
V* mapNextValue(Map<K,V>& m)
{
   V* v;
   v = arrayGet<V> (m.values,m.iteracionV++);
   return v;
} // xd

// Descripción: Prepara el map para comenzar una nueva iteración.
template<typename K,typename V>
void mapReset(Map<K,V>& m)
{
   m.iteracionV = 0;
   m.iteracionK = 0;
}

// Descripción: Descubre (busca, y si no encuentre agrega)
// una entrada {k,v} en el map m.
template<typename K,typename V>
V* mapDiscover(Map<K,V>& m,K k,V v)
{
   // Lo busco
   int pos = arrayFind<K> (m.keys,k,cmpKK);

   // Si no esta lo agrego
   if (pos<0)
   {
      pos = arrayAdd<K> (m.keys,k);
      arrayAdd<V> (m.values,v);
   }

   //Lo vuelvo int* y lo devuelvo
   return (arrayGet<V>(m.values,pos));
}

// Descripción: Ordena el map aplicando sobre sus claves
// el criterio que establece cmpKK.
template<typename K,typename V>
void mapSortByKeys(Map<K,V>& m,int cmpKK(K,K))
{
   bool cambio = true;

   while (cambio)
   {
      cambio = false;

      for (int i = 0; i<mapSize(m);i++)
      {
         if (cmpKK(m.keys.arr[i],m.keys.arr[i+1])>0)
         {
            K k = m.keys.arr[i];
            m.keys.arr[i] = m.keys.arr[i+1];
            m.keys.arr[i+1] = k;

            V v = m.values.arr[i];
            m.values.arr[i] = m.values[i+1];
            m.values.arr[i+1] = v;

            cambio = true;
         }
      }
   }
} // xd

int cmpVV(int a, int b)
{
   int resultado;

   if (a>b)
   {
      resultado = 1;
   }
   else if (a<b)
   {
      resultado = -1;
   }
   else if (a==b)
   {
      resultado = 0;
   }
   return resultado;
}

// Descripción: Ordena el map aplicando sobre sus values
// el criterio que establece cmpVV.
template<typename K, typename V>
void mapSortByValues(Map<K, V>& m, int cmpVV(V, V)) {
    bool cambio = true;

    // Recorre mientras haya cambios en la pasada anterior.
    while (cambio) {
        cambio = false;

        // Asegúrate de no acceder fuera de los límites, recorriendo hasta el penúltimo elemento.
        for (int i = 0; i < mapSize(m) - 1; i++) {
            // Compara los valores usando la función cmpVV.
            if (cmpVV(m.values.array[i], m.values.array[i + 1]) > 0) {
                // Intercambia las llaves usando una variable temporal.
                K tempKey = m.keys.array[i];
                m.keys.array[i] = m.keys.array[i + 1];
                m.keys.array[i + 1] = tempKey;

                // Intercambia los valores usando una variable temporal.
                V tempValue = m.values.array[i];
                m.values.array[i] = m.values.array[i + 1];
                m.values.array[i + 1] = tempValue;

                cambio = true; // Marca que hubo un cambio para continuar iterando.
            }
        }
    }
}

#endif
