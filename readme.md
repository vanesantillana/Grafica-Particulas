## Particulas
Proyecto teorico de Grafica Computacional

### Compilar
El siguiente comando para compilar
```
gcc particulas.cpp `pkg-config opencv --libs --cflags` -o foo -lstdc++ -lglut -lGLU -lGL -lm
```
Para la prueba de particulas
```
gcc libstdc++.so.6 -o foo particulasPrueba.cpp -lglut -lGLU -lGL -lm
```

### Tareas
* Obtener posicion del Puntero
* Crear particula con su clase
* Generar varias particulas a partir del click del puntero