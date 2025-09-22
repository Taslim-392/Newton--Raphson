#include <stdio.h>
#include <math.h>
#include <time.h>

#define EPS 1e-6
#define MAX_IT 100

// Example 1: Well-behaved f(x) = x^2 -5*x+1
// Example 2: Ill-conditioned f(x) = x^3 - 2x + 2
// Function definitions
double f(double x, int choice) {
    switch(choice) {
        case 1:
            return x*x - 5*x + 1;
        default:
            return x*x*x - 2*x + 2;
    }
}

double df(double x, int choice) {
    switch(choice) {
        case 1:
            return 2*x - 5;
        default:
            return 3*x*x - 2;
    }
}
double d2f(double x, int choice) {
    switch(choice) {
        case 1:
            return 2;
        default:
            return 6 * x;
    }
}

// Classical Newton-Raphson with performance tracking
int newtonRaphson(double x0, int choice, double* final_root, int* iterations, double* time_taken) {
    clock_t start = clock();
    *iterations = 0;

    for (int i=1; i<=MAX_IT; i++) {
        (*iterations)++;
        double fx = f(x0, choice);
        double dfx = df(x0, choice);

        if (fabs(dfx) < EPS) {
            clock_t end = clock();
            *time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
            return 0; // Failed - derivative too small
        }

        double x1 = x0 - fx/dfx;

        if (fabs(x1 - x0) < EPS) {
            *final_root = x1;
            clock_t end = clock();
            *time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
            return 1; // Success
        }

        x0 = x1;
    }

    clock_t end = clock();
    *time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    return 0; // Failed - max iterations reached
}

