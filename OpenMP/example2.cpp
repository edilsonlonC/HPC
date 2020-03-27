#include <stdio.h>
#include <omp.h>
#include <chrono>
#include <iostream>

using namespace std;

int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    int x;

    x = 2;
#pragma omp parallel num_threads(2) shared(x)
    {
        if (omp_get_thread_num() == 0)
        {
            x = 5;
        }
        else
        {
            /* Print 1: the following read of x has a race */
            printf("1: Thread# %d: x = %d\n", omp_get_thread_num(), x);
        }

#pragma omp barrier

        if (omp_get_thread_num() == 0)
        {
            /* Print 2 */
            printf("2: Thread# %d: x = %d\n", omp_get_thread_num(), x);
        }
        else
        {
            x++;

            /* Print 3 */
            printf("3: Thread# %d: x = %d\n", omp_get_thread_num(), x);
        }
    }

    end = std::chrono::system_clock::now();
    double time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << endl
         << "time here : " << time << endl;
    return 666;
}