
#ifndef _MAIN
#define _MAIN

#include <iostream>
#include "biblioteca/funciones/strings.hpp"
#include "biblioteca/funciones/tokens.hpp"
#include "biblioteca/funciones/files.hpp"
#include "biblioteca/tads/parte2/Array.hpp"
#include "biblioteca/tads/parte2/Map.hpp"
#include "biblioteca/tads/parte2/List.hpp"
#include "biblioteca/tads/parte2/Stack.hpp"
#include "biblioteca/tads/parte2/Queue.hpp"
#include "biblioteca/tads/parte1/Coll.hpp"
#include "biblioteca/tads/parte1/MultidimColl.hpp"
#include "principal.hpp"
using namespace std;

/*Se dispone del archivo de registros PALABRAS. dat, donde cada registro contiene una palabra de hasta 15 caracteres.
 * Se pide mostrar las palabras del archivo ordenadas decrecientemente según la cantidad de vocales que contienen,
 * indicando también en qué posición aparecieron en el archivo. No se debe discriminar entre mayúsculas y minúsculas.
 * Por ejemplo: AMANECER tiene 4 vocales. 2 'A' y 2 'E'. Las palabras del archivo no tienen tilde.
Para leer desde utilice la siguiente función:*/

string leerPalabra (FILE* f)
{
   char buff[15];
   fread (buff, 1, 15, f) ;
   return buff;
}

int countVocal (string v)
{
   v = toUpperCase (v);
   int count = 0;
   count += charCount (v,'A');
   count += charCount (v,'E');
   count += charCount (v,'I');
   count += charCount (v,'O');
   count += charCount (v,'U');
   return count;
}

int cmpVocales (string vocal1, string vocal2)
{
   int vocalUno = countVocal(vocal1);
   int vocalDos = countVocal(vocal2);
   return vocalDos - vocalUno;
}

int main()
{
   // abro el archivo y agrego las palabras en la coleccion
   FILE* f = fopen ("PALABRAS.dat", "r+b");
   Coll<string> memoria = coll<string> ();
   while (!feof (f))
   {
      int pos = ftell (f);
      string s = intToString (pos) + "-" + leerPalabra (f);
      collAdd <string> (memoria, s, stringToString);
   }

   // ordeno la colleccion
   collSort <string> (memoria, cmpVocales,stringToString,stringToString);

   // muestro la coleccion por consola
   collReset <string> (memoria);
   while (collHasNext<string> (memoria))
   {
      string s = collNext <string> (memoria,stringToString);
      cout << s << endl;
   }

   fclose (f);
   return 0;
}

#endif
