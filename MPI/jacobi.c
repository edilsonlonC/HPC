#include <stdio.h>
#include <math.h>
#include "mpi.h"

/* 
Créditos de la implementación:
Nos basamos en el tutorial propuesto por la pagina: 
https://www.mcs.anl.gov/research/projects/mpi/tutorial/mpiexmpl/src/jacobi/C/main.html
*/


/* Este ejemplo maneja una malla de 12 x 12, solo en 4 procesos. */
#define maxn 12


int main( argc, argv )

// Entero al número de argumentos
int argc;

// Puntero al vector de argumentos
char **argv;

// Main
{
    int        rank, value, size, errcnt, toterr, i, j, itcnt;
    int        i_first, i_last;
    MPI_Status status;
    double     diffnorm, gdiffnorm;
    double     xlocal[(12/4)+2][12]; // 5*12
    double     xnew[(12/3)+2][12];   // 6*12

    MPI_Init( &argc, &argv );

	// Determina el rango (identificador) del proceso que lo llama dentro del comunicador seleccionado.
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );

	// Determina el tamaño del comunicador seleccionado, es decir, el número de procesos que están actualmente asociados a este.
    MPI_Comm_size( MPI_COMM_WORLD, &size );

	// Numero de procesos
    if (size != 4) MPI_Abort( MPI_COMM_WORLD, 1 );

    i_first = 1;
    i_last  = maxn/size;

    if (rank == 0)        i_first++;
    if (rank == size - 1) i_last--;

    /* Se llenan los datos como especifica xlocal */
    for (i=1; i<=maxn/size; i++) {
		for (j=0; j<maxn; j++) {
			xlocal[i][j] = rank;
		}
	}

    for (j=0; j<maxn; j++) {
		xlocal[i_first-1][j] = -1;
		xlocal[i_last+1][j] = -1;
    }

    itcnt = 0;
    do {

		/* Enviar a menos que esté en la parte superior, luego recibir desde abajo */

		if (rank < size - 1){
			MPI_Send( 
				xlocal[maxn/size], 
				maxn, 
				MPI_DOUBLE, 
				rank + 1, 
				0, 
				MPI_COMM_WORLD 
				);
		}

		if (rank > 0){
			MPI_Recv( 
				xlocal[0], 
				maxn, 
				MPI_DOUBLE, 
				rank - 1, 
				0, 
				MPI_COMM_WORLD, 
				&status 
				);
		}


		/* Enviar a menos que esté en la parte inferior */

		if (rank > 0) {
			MPI_Send( 
				xlocal[1], 
				maxn, 
				MPI_DOUBLE, 
				rank - 1, 1, 
				MPI_COMM_WORLD 
				);
		}

		if (rank < size - 1) {
			MPI_Recv( 
				xlocal[maxn/size+1], 
				maxn, MPI_DOUBLE, 
				rank + 1, 
				1, 
				MPI_COMM_WORLD, 
				&status 
				);
		}
			
		
		/* Calcular nuevos valores (pero no en el límite) */

		itcnt ++;
		diffnorm = 0.0;

		for (i=i_first; i<=i_last; i++) {
			for (j=1; j<maxn-1; j++) {
				xnew[i][j] = (xlocal[i][j+1] + xlocal[i][j-1] +
							xlocal[i+1][j] + xlocal[i-1][j]) / 4.0;
				diffnorm += (xnew[i][j] - xlocal[i][j]) * 
							(xnew[i][j] - xlocal[i][j]);
			}
		}

		/* Solo transfiere los puntos interiores */

		for (i=i_first; i<=i_last; i++) {
			for (j=1; j<maxn-1; j++) {
				xlocal[i][j] = xnew[i][j];
			}
		}

		/* All reduce para todos los procesos */

		MPI_Allreduce( 
			&diffnorm, 
			&gdiffnorm, 
			1, 
			MPI_DOUBLE, 
			MPI_SUM,
			MPI_COMM_WORLD 
			);

		gdiffnorm = sqrt( gdiffnorm );

		if (rank == 0) {
			printf( "At iteration %d, diff is %e\n", itcnt, gdiffnorm );
		}
		
    } while (gdiffnorm > 1.0e-2 && itcnt < 100);

    MPI_Finalize( );
    return 0;
}