# EfficientSearchEngine
Perform efficient searches by ranges with regular mesh type data structure.

This data structure allows:
* Find the points closest to a given one in coordinates in the plane or space.
+ Know if a point belongs or not to a region.
- Given an area or region of the plane, obtain the points it contains.

The program manages a system of products, customers and orders for distribution.
For this reason a regular mesh data structure is used, as seen in the image.

![alt text](https://i.imgur.com/EarCeGL.png "Example of regular mesh.")

The program reads two csv files, "clientes.csv" and "pharma.csv". With this structure

| NIF        | Clave      | Nombre           | Dirección          | Latitud   | Longitud    |
| ---------- |:----------:| ----------------:| ------------------:| ---------:| -----------:|
| 10982609X  | pU7Pqqk    | Marlie Klassmann | 1133 Blaine Place  | -0,789275 | 113,921327  |
| 92139205N  | ipbb9sHKa  | Caria MacIlwrick | 0 Mosinee Place    | 33,436645 | -112,036451 |
| 34536319T  | 4pUF1OcsIG | Lauren Cootes    | 854 Dunning Trail  | 3,6196125 | 98,5089455  |


| Codigo Nacional | Nombre Presentación         | PVP     |
| --------------- |:---------------------------:| -------:|
| 700013          | AAS 100MG 20 COMPRIMIDOS    | $1600   |
| 728196          | ABILIFY 10MG 28 COMPRIMIDOS | $135,51 |
| 743229          | ADVENTAN CREMA tubo de 60 g | $10,04  |

These files are parsed to other data structures, where products are stored in a hash table created by me.

The process followed is:
1. Establish the initial number of zones with any number of rows and columns (10 rows and 20 columns, in this case).
```c++
PharmaDron pharmaDron("pharma1.csv", "clientes_v2.csv", -9.274f, 35.867f, 3.282f, 43.273f, 20, 10);
```

```c++
PharmaDron::PharmaDron(std::string rutaProductos, std::string rutaClientes, float xMin,float yMin, float xMax, float yMax, int nDivX, int nDivY) {
    accesoUTM = new MallaRegular<Cliente*>(xMin, yMin, xMax, yMax, nDivX, nDivY);
}
```
2. We assign the first free drone the nearby area in Segovia and show how many deliveries have been made.
```c++
Dron Segovia(456, UTM(40.9424893, -4.1089545));
pharmaDron.ingresaDron(Segovia);

int numRepartos = pharmaDron.llevarPedidosZona(pharmaDron.getDronDisponible(), Segovia.getUTM(), 0.25);
```
3. Check the maximum load for rows and columns and readjust the table to be similar.
```c++
pharmaDron.definirNumeroZonas(10, 10);
```
4. With this new configuration, assign the second drone the delivery in the Madrid area.
```c++
numRepartos = pharmaDron.llevarPedidosZona(pharmaDron.getDronDisponible(), Madrid.getUTM(), 0.35);
```
5. Adjust the size in rows and columns so that the maximum number of customers per cell does not exceed 50.
```c++
pharmaDron.definirNumeroZonas(15, 20);    
```
6. Finally, with the third drone, assign it the cast in the Jaén area.
```c++
numRepartos = pharmaDron.llevarPedidosZona(pharmaDron.getDronDisponible(), Jaen.getUTM(), 0.3);
```

# Final Result

![alt text](https://i.imgur.com/Bcdbj9tl.jpg "Parser.")

![alt text](https://i.imgur.com/YNpmZmym.png "run screenshot.")
