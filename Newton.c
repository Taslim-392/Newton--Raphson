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
