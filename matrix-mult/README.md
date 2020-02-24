# Multiplicación de Matrices Secuencial y Concurrente

*Realizada por:* \
*[Sebastian Velez Montoya](https://github.com/sebasttianvelez)* \
*[Sebastian Velez Montoya](https://github.com/sebasttianvelez)*

```bash
git clone https://github.com/edilsonlonC/HPC
```

## Definiciones
La multiplicación de matrices tiene como característica recorrer un arreglo de dos dimensiones, donde la complejidad es O(n³). El código está estructurado en dos implementaciones: Una de manera secuencial y la otra de manera concurrente usando hilos. 

## Caracteristicas del Algoritmo

La implementación secuencial recibe como parámetros el número de columnas para generar dos matrices aleatorias cuadradas y luego recorrerlas para multiplicarlas y generar una nueva matriz resultante. A diferencia de la implementación concurrente, además de crear matrices cuadradas, crea un vector de hilos con este mismo número para realizar las tareas de forma concurrente de manera que los núcleos del computador lo permitan. 

Los tiempos reales de cpu se están calculando durante el proceso donde se efectúan operaciones aritméticas recorriendo cada matriz.

## Características del PC

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


