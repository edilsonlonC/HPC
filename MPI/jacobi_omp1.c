
  #include <stdio.h> 
  #include <math.h> 
  #include <stdlib.h> 
 
 /* 
       subroutine jacobi (n,m,dx,dy,alpha,omega,u,f,tol,maxit)
 ******************************************************************
 * Subroutine HelmholtzJ
 * Solves poisson equation on rectangular grid assuming : 
 * (1) Uniform discretization in each direction, and 
 * (2) Dirichlect boundary conditions 
 * 
 * Jacobi method is used in this routine 
 *
 * Input : n,m   Number of grid points in the X/Y directions 
 *         dx,dy Grid spacing in the X/Y directions 
 *         alpha Helmholtz eqn. coefficient 
 *         omega Relaxation factor 
 *         f(n,m) Right hand side function 
 *         u(n,m) Dependent variable/Solution
 *         tol    Tolerance for iterative solver 
 *         maxit  Maximum number of iterations 
 *
 * Output : u(n,m) - Solution 
 *****************************************************************
 */
 void jacobi ( const int n, const int m, double dx, double dy, double alpha, 
 	double omega, double *u, double *f, double tol, int maxit )
 {
   int i,j,k,k_local;
   double error, resid, rsum, ax, ay, b;
   double error_local;
 
 
   double *uold;
 
   /* wegen Array-Kompatibilitaet, werden die Zeilen und Spalten (im Kopf)
 	 getauscht, zB uold[spalten_num][zeilen_num]; bzw. wir tuen so, als ob wir das
 	 gespiegelte Problem loesen wollen */
 
   uold = (double *)malloc(sizeof(double) * n *m);
 
 
 
   ax = 1.0/(dx * dx); /* X-direction coef */
   ay = 1.0/(dy*dy); /* Y_direction coef */
   b = -2.0/(dx*dx)-2.0/(dy*dy) - alpha; /* Central coeff */
 
   error = 10.0 * tol;
 
   k = 1;
   while (k <= maxit && error >; tol) {
 
 	error = 0.0;
 
 	/* copy new solution into old */
 #pragma omp parallel for private(i) 
     for (j=0; j<m; j++)
 	  for (i=0; i<n; i++)
 		uold[i + m*j] = u[i + m*j];
 
 
 	/* compute stencil, residual and update */
 #pragma omp parallel for reduction(+:error) private(i,resid) 
 	for (j=1; j<m-1; j++)
 	  for (i=1; i<n-1; i++){
 		resid =(
 				ax * (uold[i-1 + m*j] + uold[i+1 + m*j])
 				+ ay * (uold[i + m*(j-1)] + uold[i + m*(j+1)])
 				+ b * uold[i + m*j] - f[i + m*j]
 			   ) / b;
 		
 		/* update solution */
 		u[i + m*j] = uold[i + m*j] - omega * resid;
 
 		/* accumulate residual error */
 		error =error + resid*resid;
 
 	  }
 
 	/* error check */
 	k++;
     error = sqrt(error) /(n*m);
 
   } /* while */
   printf("Total Number of Iteratuons %d\n", k);
 
   printf("Residual %.15f\n", error);
free(uold);
} 	
