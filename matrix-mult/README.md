# Multiplicación de Matrices Serial, con Hilos, Procesos y Transponiendo la matriz

*Clonar Repositorio*

```bash
git clone https://github.com/edilsonlonC/HPC
```

## Definiciones :bulb:
<p align="justify">
La multiplicación de matrices tiene como característica recorrer un arreglo de dos dimensiones, donde la complejidad es O(n³). El código está estructurado en dos implementaciones: Una de manera secuencial y la otra de manera concurrente usando hilos. 
</p>

## Caracteristicas del Algoritmo :mag:

<p align="justify">
La implementación secuencial recibe como parámetros el número de columnas para generar dos matrices aleatorias cuadradas y luego recorrerlas para multiplicarlas y generar una nueva matriz resultante. A diferencia de la implementación concurrente, además de crear matrices cuadradas, crea un vector de hilos con este mismo número para realizar las tareas de forma concurrente de manera que los núcleos del computador lo permitan. Para la implementación con la matriz transpuesta, es similar a la implementación serial.
</p>
<p>
Para la implementación con múltiples procesos, se hace uso de memoria compartida por medio de mmap, la cual evita el uso de semáforos.
</p>
<p align="justify">
Los tiempos reales de cpu se están calculando durante el proceso donde se efectúan operaciones aritméticas recorriendo cada matriz.
</p>


## Características del PC :computer:

#### Procesador: 
* Intel Core i7-4510U CPU @ 2.00GHz 
* 1 physical processor 
* 2 cores 4 threads

#### Sistema Operativo:
* Linux Lite 4.4

#### Memoria RAM:
* 8 GB

#### Tarjeta Madre:
* 1.0 / X455LD (ASUSTeK COMPUTER INC.)

#### Gráficos:
* NVIDIA GEFORCE 820M

#### Almacenamiento:
* 1 TB SATA ST


## Estadísticas :bar_chart:
<p align="center">
  <img width="781" height="476" src="https://raw.githubusercontent.com/edilsonlonC/HPC/master/matrix-mult/assets/results_times.png">
  <img width="641" height="372" src="https://raw.githubusercontent.com/edilsonlonC/HPC/master/matrix-mult/assets/speedup_rate.png">
</p>


## Conclusiones :blue_book:
<p align="justify">
La multiplicación de matrices de manera secuencial, es una buena solución para matrices pequeñas, y resulta ser mas eficiente que la solución concurrente en estos casos, pero cuando la matriz empieza a crecer y supera las 1000 columnas; hay una notable diferencia de tiempos, donde la solución concurrente resulta ser mas eficiente. 
</p>
<p align="justify">
Al momento de realizar la ejecución del algoritmo concurrente, la máquina donde se realizó la prueba, quedó inoperativa. Esto es debido a que se están utilizando todos los recursos de la máquina, es decir los 4 núcleos que contiene el procesador. Mientras que durante la ejecución del algoritmo secuencial, se podían realizar tareas en segundo plano.
</p>
<p>
Cuando se realizó la multiplicación utilizando múltiples procesos, se nota una pequeña mejora con respecto al tiempo de los hilos, pero no es significativa, ya que al investigar un poco sobre la librería pthread, se encuentra el uso de procesos en bajo nivel. Es decir, al final hilos y procesos tendrán el mismo código en máquina. Esta prueba también bloqueó completamente el procesador.
</p>
<p>
Al momento de realizar la multiplicación teniendo en cuenta la transpuesta de la matriz, se obtuvo una sorpresa con respecto al tiempo, ya que al principio el algoritmo parecía mas lento que el serial, pero a medida que se aumentaron las columnas, se muestra una mejora significativa con respecto al serial. Esto se debe al cache line y la forma en que reducen los tiempos para acceder a memoria.
</p>

## Contribuciones :busts_in_silhouette:

*Realizada por:* \
*[Edilson Londoño Castañeda](https://github.com/edilsonlonC)* \
*[Sebastian Velez Montoya](https://github.com/sebasttianvelez)*
