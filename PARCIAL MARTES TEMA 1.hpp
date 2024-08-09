
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

/*Se ingresa por teclado un conjunto de palabras separadas entre sí por [ENTER]. El ingreso de datos finalizará con la palabra "FIN"
(que no forma parte del conjunto). Se pide grabarlas en un archivo de registros (PALABRAS.dat) donde cada registro debe contener una
de las palabras ingresadas y el número de orden en que se ingresó. Los registros deben estar ordenados ascendentemente según la
cantidad de letras 'A' (sin discriminar entre mayúsculas y minúsculas) de las palabras que contienen.*/

struct Palabras
{
   string palabras;
   int cont;
};

int cmpPalabrasA (string palabra1, string palabra2)
{
   palabra1 = toUpperCase (palabra1);
   palabra2 = toUpperCase (palabra2);
   int uno = charCount (palabra1, 'A');
   int dos = charCount (palabra2, 'A');
   return uno - dos;
}

int main()
{
   // Creo una coleccion vacia
   Coll<string> memoria = coll<string> ();

   // Se ingresa las palabras por teclado
   string palabra = "";
   cout << "Ingresar palabra, al finalizar poner 'FIN': " << endl;
   cin >> palabra;

   // itero las palabras ingresadas hasta que se ponga "FIN"
   while (palabra != "FIN")
   {
      //
      palabra = palabra + "-" + intToString (collSize<string> (memoria) + 1);
      collAdd <string> (memoria, palabra, stringToString);
      cin >> palabra;
   }

   // Ordeno la coleccion
   collSort <string> (memoria, cmpPalabrasA, stringToString, stringToString);

   // Obtengo las palabras
   collReset <string> (memoria);
   FILE* f = fopen ("PALABRAS.dat", "w+b");
   while (collHasNext<string> (memoria))
   {
      string s = collNext <string> (memoria,stringToString);
      cout << s << endl;
      write (f,s);
   }

   fclose (f);
   return 0;
}

#endif
