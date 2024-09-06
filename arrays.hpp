#ifndef _TARRAYS_T_
#define _TARRAYS_T_

#include <iostream>

// Descripción: Agrega el elemento e al final de arr incrementando su longitud len.
template <typename T>
int add(T arr[],int& len,T e)
{
   arr[len++] = e;
   return len -1;
}

// Descripción: Inserta el elemento e en la posición p del array arr. Desplaza los
// elementos ubicados a partir de p+1 e incrementa la longitud len.
template <typename T>
void insert(T arr[],int& len,T e,int p)
{
   for (int i=len; i>p; i--)
   {
      arr[i] = arr[i-1];
   }

   arr[p] = e;
   len++;
}

// Descripción: Remueve el elemento ubicado en la posición p del array arr. Desplaza
// ubicados a partir de p y decrementa la longitud len.
template <typename T>
T remove(T arr[],int& len,int p)
{
   T ret = arr[p];
   for (int i = p+1; i<len; i++)
   {
      arr[i-1] = arr[i];
   }
   len--;
   return ret;
}

// Descripción: Retorna la posición de la primera ocurrencia de k dentro de arr o un valor
// negativo si arr no contiene a k.
template <typename T, typename K>
int find(T arr[],int len,K k,int cmpTK(T,K))
{
   int ret = -1;
   int comparacion = -2;

   for (int i = 0; i < len && comparacion != 0; i++)
   {
      if (cmpTK (arr[i], k) == 0)
      {
         ret = i;
      }
   }

   return ret;
}

// Descripción: Inserta e dentro de arr según el criterio de precedencia que establece
// cmpTT, y retorna la posición donde dicho elemento quedó insertado. El array arr debe
// estar ordenado o vacío.
template <typename T>
int orderedInsert(T arr[],int& len,T e,int cmpTT(T,T))
{
   int pos = 0;
   while (pos< len && cmpTT (arr[pos],e) < 0)
   {
      pos++;
   }

   insert (arr,len,e,pos);

   return pos;
}

//Descripción: Ordena arr según el criterio de precedencia que establece cmpTT.
template <typename T>
void sort(T arr[],int len,int cmpTT(T,T))
{
   for (int i = 0; i < len - 1; i++)
   {
      for (int j = 0; j < len - i - 1; j++)
      {
         if (cmpTT (arr[j], arr[j+1]) > 0)
         {
            T temp = arr [j];
            arr[j] = arr[j + 1];
            arr [j+1] = temp;
         }
      }
   }

   return;
}


#endif
