# Multiplicación de Matrices Secuencial y Concurrente 

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
La implementación secuencial recibe como parámetros el número de columnas para generar dos matrices aleatorias cuadradas y luego recorrerlas para multiplicarlas y generar una nueva matriz resultante. A diferencia de la implementación concurrente, además de crear matrices cuadradas, crea un vector de hilos con este mismo número para realizar las tareas de forma concurrente de manera que los núcleos del computador lo permitan. 
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

![Results](https://raw.githubusercontent.com/edilsonlonC/HPC/master/matrix-mult/assets/results_algorithm.png) 

## Conclusiones :blue_book:
<p align="justify">
La multiplicación de matrices de manera secuencial, es una buena solución para matrices pequeñas, y resulta ser mas eficiente que la solución concurrente en estos casos, pero cuando la matriz empieza a crecer y supera las 1000 columnas; hay una notable diferencia de tiempos, donde la solución concurrente resulta ser mas eficiente.
</p>
<p align="justify">
Al momento de realizar la ejecución del algoritmo concurrente, la máquina donde se realizó la prueba, quedó inoperativa. Esto es debido a que se están utilizando todos los recursos de la máquina, es decir los 4 núcleos que contiene el procesador. Mientras que durante la ejecución del algoritmo secuencial, se podían realizar tareas en segundo plano.
</p>

## Contribuciones :busts_in_silhouette:

*Realizada por:* \
*[Edilson Londoño Castañeda](https://github.com/edilsonlonC)* \
*[Sebastian Velez Montoya](https://github.com/sebasttianvelez)*
