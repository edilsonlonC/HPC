#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <thread>

using namespace std;

class Jacobi
{
private:
    vector<double> stmp;
    vector<double> u;
    vector<double> f;
    vector<double> utmp;

public:
    Jacobi(int n)
    {
        double h = 1.0 / n;
        this->u.resize((n + 1) * sizeof(double), 0);
        this->f.resize((n + 1) * sizeof(double));

        utmp.resize((n + 1) * sizeof(double));
        for (int i = 0; i <= n; ++i)
            this->f[i] = i * h;
    }

    ~Jacobi()
    {
        this->u.clear();
        this->f.clear();
        this->utmp.clear();
    }

    void write_solution(int n, const char *fname)
    {
        int i;
        double h = 1.0 / n;
        FILE *fp = fopen(fname, "w+");
        for (i = 0; i <= n; ++i)
            fprintf(fp, "%g %g\n", i * h, this->u[i]);
        fclose(fp);
    }

    static void threading(vector<double> &utmp, vector<double> &u, vector<double> &f, double h2, int n)
    {
        for (int i = 1; i < n; ++i)
            utmp[i] = (u[i - 1] + u[i + 1] + h2 * f[i]) / 2;

        /* Old data in utmp; new data in u */
        for (int i = 1; i < n; ++i)
            u[i] = (utmp[i - 1] + utmp[i + 1] + h2 * f[i]) / 2;
    }

    void jacobi(int nsteps, int n)
    {
        double h = 1.0 / n;
        double h2 = h * h;

        this->utmp[0] = this->u[0];
        this->utmp[n] = this->u[n];

        vector<thread> th;

        for (int sweep = 0; sweep < nsteps; sweep += 2)
        {
            //th.push_back(thread(threading, ref(this->utmp), ref(this->u), ref(this->f), h2, n));
            this->threading(this->utmp,this->u,this->f,h2,n);
        }
        for (int i = 0; i < th.size(); i++)
        {
            th[i].join();
        }
    }
};