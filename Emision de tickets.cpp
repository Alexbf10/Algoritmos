#ifndef _MAIN
#define _MAIN

#include
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

Coll subirProductos ()
{
Coll ret = coll ();
FILE* f = fopen ("PRODUCTOS.dat","r+b");

Producto p = read (f);
while (!feof (f))
{
RProducto rp = rProducto (p,0);
collAdd (ret,rp,rProductoToString);
p = read (f);
}

fclose (f);
return ret;
}

Coll subirRubros ()
{
Coll ret = coll ();

FILE* f = fopen ("RUBROS.dat", "r+b");
Rubro r = read (f);
while (!feof (f))
{
collAdd (ret, r, rubroToString);
r = read (f);
}

fclose (f);
return ret;
}

int leerCliente ()
{
int id;
cout<< "Ingresar el id.cliente: "<< endl;
cin >> id;

return id;
}

int leerNroTKInicial ()
{
int nro;
cout << "Ingresar Nro.cliente: " << endl;
cin >> nro;
return nro;
}

Par leerPar ()
{
cout << "Ingresar id.producto y cantidad: " << endl;
return {};
}

int cmpRProductoId (RProducto rp, int id)
{
return rp.p.idProd-id;
}

void procesarParPunto1 (Coll& ticket, Par par, Coll cProd)
{
//busco el producto
int pos = collFind <RProducto, int> (cProd, par.idPro, cmpRProductoId, rProductoFromString);
RProducto elmProd = collGetAt (cProd, pos, rProductoFromString);

//descubro en ticket
int pos = collFind <RProducto, int> (cProd, par.idPro, cmpRProductoId, rProductoFromString);
if (pos < 0)
{
RProducto x = rProducto(elmProd.p,0);
pos = collAdd (ticket, x, rProductoToString);
}
RProducto elmProd2 = collGetAt (ticket, pos, rProductoFromString);
elmProd2.acum+= par.cant;
collSetAt (ticket, elmProd2, pos, rProductoToString);
}

int cmpRProductos (RProducto a, RProducto b)
{
string aDesc = a.p.descr;
string bDesc = b.p.descr;

return cmpString (aDesc, bDesc);
}

int cmpRubroId (Rubro r, int id)
{
return r.idRub-id;
}

int cmpRRubroId (RRubro rr, int id)
{
return rr.r.idRub-id;
}

//muestro resultados por subconjunto
void mostrarResultadosPunto1 (Coll ticket, Coll cRub, int& nroTKInicial)
{
cout << nroTKInicial << endl;
nroTKInicial++;

Coll cDtoxRub = coll ();

//ordeno ticket
collSort (ticket, cmpRProductos, rProductoFromString, rProductoToString);

double totalAPagar = 0;

//itero ticket
collReset (ticket);
while (collHasNext (ticket))
{
RProducto it = collNext (ticket, rProductoFromString);

  //parte 1 del ticket
  string descripcionProducto = it.p.descr;
  double precio = it.p.precio;

  //busco el rubro
  int pos = collFind <Rubro, int> (cRub, it.p.idRub, cmpRubroId, rubroFromString);
  Rubro elmRub = collGetAt <Rubro> (cRub, pos, rubroFromString);

  double dto = elmRub.promo;
  double conDto = precio-(precio*dto);
  int cantidad = it.acum;
  double total = conDto*cantidad;

  cout << descripcionProducto << precio << dto << conDto << cantidad << total << endl;

  totalAPagar += total;

  //parte 2 del ticket


  pos = collFind <RRubro, int> (cDtoxRub,it.p.idRub,cmpRRubroId,rRubroFromString);
  if (pos < 0)
  {
     RRubro y = rRubro (elmRub,0);
     pos = collAdd <RRubro> (cDtoxRub,y,rRubroToString);
  }
  RRubro elmRRub = collGetAt <RRubro>(cDtoxRub,pos,rRubroFromString);
  elmRRub.acum+=precio*dto*cantidad;
  collSetAt<RRubro> (cDtoxRub, elmRRub, pos, rRubroToString);
}

cout << totalAPagar << endl;

double totalAPagarRubro = 0;
collReset (cDtoxRub);
while (collHasNext (cDtoxRub))
{
RRubro it2 = collNext (cDtoxRub,rRubroFromString);
string descripcionRubro = it2.r.descr;
double totalRubro = it2.acum;

  cout << descripcionRubro << totalRubro << endl;

  totalAPagarRubro += totalRubro;
}

cout << totalAPagarRubro << endl;
}

int cmpCantProd (RProducto a, RProducto b)
{
return a.acum-b.acum;
}

void procesarParPunto2 (Par par, Coll& cProd)
{
int pos = collFind (cProd, par.idPro, cmpRProductoId, rProductoFromString);
RProducto elmRProd = collGetAt (cProd, pos, rProductoFromString);
elmRProd.acum+=par.cant;
collSetAt (cProd,elmRProd,pos,rProductoToString);
}

//muestro resultados generales
void mostrarResultadosPunto2 (Coll cProd)
{
collSort (cProd,cmpCantProd,rProductoFromString,rProductoToString);

int i = 0;

collReset (cProd);
while (collHasNext (cProd) && i<10)
{
RProducto it3 = collNext (cProd, rProductoFromString);

  if (it3.acum == 0)
  {
     break;
  }

  string descProd = it3.p.descr;
  cout << descProd << it3.acum << endl;

  i++;
}
}

int main()
{
//subimos archivos a memoria
Coll cProd = subirProductos ();
Coll cRub = subirRubros ();

int nroTKInicial = leerNroTKInicial ();

//leo el cliente
int idCli = leerCliente ();

while (idCli != 0)
{
//buffer para el ticket
Coll ticket = Coll ();

  Par par = leerPar ();

  while (par.idPro != 0)
  {
     //proceso el par
     procesarParPunto1 (ticket,par,cProd);

     //
     procesarParPunto2 (par,cProd);

     par = leerPar ();
  }


  mostrarResultadosPunto1 (ticket,cRub, nroTKInicial);

  idCli = leerCliente ();
}

mostrarResultadosPunto2 (cProd);

return 0;
}

#endif
