## Particulas
Proyecto teorico de Grafica Computacional

### Compilar

Para probar ejemplo1 y ejemplo2 de particulas.
```
gcc libstdc++.so.6 -o foo ejemplo1.cpp -lglut -lGLU -lGL -lm
```
El siguiente comando para compilar la prueba, pero aun no bota nada.
```
gcc particulas.cpp `pkg-config opencv --libs --cflags` -o foo -lstdc++ -lglut -lGLU -lGL -lm
```

### Tareas
* Obtener posicion del Puntero
* Crear particula con su clase
* Generar varias particulas a partir del click del puntero

### Repos de ayuda
* https://github.com/sotoea/2D-Particle-System  --> Ejemplo 1
* https://github.com/krlgrgn/OpenGL-Particles  --> Ejemplo 2
* https://github.com/usmanshaahid/ParticleSystem
* https://gist.github.com/thaenor/4d9531cc9a7d1c34b998 -->lluvia

