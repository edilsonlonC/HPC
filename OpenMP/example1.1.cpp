#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <iostream>

using namespace std;

void simple(int n, float *a, float *b)
{
   int i;

   std::chrono::time_point<std::chrono::system_clock> start, end;
   start = std::chrono::system_clock::now();

   //#pragma omp parallel for
   for (i = 1; i < n; i++) /* i is private by default */
      b[i] = (a[i] + a[i - 1]) / 2.0;

   end = std::chrono::system_clock::now();
   double time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
   cout << endl
        << "time here : " << time << endl;
}

void showArray(int n, float *v)
{

   for (int i = 0; i < n; i++)
      printf(" %f ", v[i]);
   printf("\n");
}

int main()
{
   int n = 1000000;

   float a[n] = {
       1.0,
       1.0,
       1.0,
       1.0,
       1.0,
   };
   float b[n] = {
       2.0,
       2.0,
       2.0,
       2.0,
       2.0,
   };
   //    printf("antes \n");
   //    showArray(n,a);
   //    showArray(n,b);
   simple(n, a, b);
   //    printf("despues\n");
   //    showArray(n,a);
   //    showArray(n,b);

   return 666;
}
