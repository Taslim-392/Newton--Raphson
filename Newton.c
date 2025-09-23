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
// Modified Newton-Raphson with performance tracking
int modifiedNewton(double x0, int choice, double* final_root, int* iterations, double* time_taken) {
    clock_t start = clock();
    *iterations = 0;
    
    for (int i=1; i<=MAX_IT; i++) {
        (*iterations)++;
        double fx = f(x0, choice);
        double dfx = df(x0, choice);
        double d2fx = d2f(x0, choice);
        double denom = dfx*dfx - fx*d2fx;
        
        if (fabs(denom) < EPS) {
            clock_t end = clock();
            *time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
            return 0; // Failed - denominator too small
        }
        
        double x1 = x0 - (fx*dfx)/denom;
        
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
// Function to compare both methods
void compareMethods(double x0, int choice, const char* function_name) {
    printf("\n=== Comparing Methods for %s ===\n", function_name);
    
    double root1, root2;
    int iter1, iter2;
    double time1, time2;
    int success1, success2;
    
    // Test Classical Newton-Raphson
    success1 = newtonRaphson(x0, choice, &root1, &iter1, &time1);
    
    // Test Modified Newton-Raphson
    success2 = modifiedNewton(x0, choice, &root2, &iter2, &time2);
    
    // Print results
    printf("\nClassical Newton-Raphson:\n");
    printf("Status: %s\n", success1 ? "Converged" : "Failed");
    if (success1) printf("Root: %.6f\n", root1);
    printf("Iterations: %d\n", iter1);
    printf("Time taken: %.6f seconds\n", time1);
    printf("Final f(x): %.6e\n", f(success1 ? root1 : x0, choice));
    
    printf("\nModified Newton-Raphson:\n");
    printf("Status: %s\n", success2 ? "Converged" : "Failed");
    if (success2) printf("Root: %.6f\n", root2);
    printf("Iterations: %d\n", iter2);
    printf("Time taken: %.6f seconds\n", time2);
    printf("Final f(x): %.6e\n", f(success2 ? root2 : x0, choice));
    
    // Comparison analysis
    printf("\n=== Comparison Analysis ===\n");
    if (success1 && success2) {
        printf("Both methods converged to similar roots: %s\n", 
               fabs(root1 - root2) < EPS ? "Yes" : "No");
        printf("Speedup factor: %.2fx\n", time1 / time2);
        printf("Iteration reduction: %.1f%%\n", 
               (1.0 - (double)iter2/iter1) * 100);
    }
    
    printf("Stability: %s\n", 
           (success1 && success2) ? "Both stable" :
           (success1) ? "Classical more stable" :
           (success2) ? "Modified more stable" : "Both unstable");
    
    printf("\n");
}
