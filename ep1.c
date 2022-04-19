#include <stdio.h>
#include <complex.h>
#include <math.h>
<<<<<<< Updated upstream

double g1(double x) {
    double y = x + (exp(x) - 2* pow(x,2));
    return y;
}

double g2(double x) {
    double y = -sqrt(exp(x)/2);
    return y;
}

double g3(double x) {
    float y = x - (exp(x) - 2*pow(x,2))/(exp(x) - 4*x);
    return y;
}

=======
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "rootStruct.h"

#define MAX_ITER 100
#define REL_TOL 0.001
int maxIter = MAX_ITER;
double relTol = REL_TOL;

double g1(double x) { return x + (exp(x) - 2 * pow(x, 2)); }

double g2(double x) { return -sqrt(exp(x) / 2); }

double g3(double x) { return x - (exp(x) - 2 * pow(x, 2)) / (exp(x) - 4 * x); }

bool hasConverged(double x1, double x2) {
    return fabs(x1 - x2) < relTol * fabs(x1);
}

struct FixedPointResult {
    double result;
    bool exceededIterations;
};

struct FixedPointResult fixedPoint(double x0, double (*f)(double)) {
    double x = f(x0);
    double prevX = x0;
    bool exceededIterations = true;
    for (int i = 0; i < maxIter; i++) {
        prevX = x;
        x = f(x);

        if (isnan(x) || isinf(x)) {
            exceededIterations = false;
            break;
        }

        if (hasConverged(prevX, x)) {
            exceededIterations = false;
            break;
        }
    }

    struct FixedPointResult result = {.result = x,
                                      .exceededIterations = exceededIterations};

    return result;
}

void calculateRoots(struct RootStruct *roots, int rootsLength) {
    for (int i = 0; i < rootsLength; i++) {
        struct FixedPointResult result = fixedPoint(roots[i].x0, roots[i].g);
        if (result.exceededIterations) {
            roots[i].status = IterationsExceeded;
            continue;
        }

        roots[i].result = result.result;
        if (isinf(roots[i].result)) {
            roots[i].status = Overflow;
        } else if (isnan(roots[i].result)) {
            roots[i].status = DivisionByZero;
        } else {
            roots[i].status = Success;
        }
    }
}

>>>>>>> Stashed changes
int main() {
    double x1,x2,x3;
    double root0,root1,root2,i;
    printf("Digite o valor de x0 para a primeira raiz: ");
    scanf("%lf",&root0);
    printf("Digite o valor de x0 para a segunda raiz: ");
    scanf("%lf",&root1);
    printf("Digite o valor de x0 para a terceira raiz: ");
    scanf("%lf",&root2);
    x1 = g1(root0);
    x2 = g2(root1);
    x3 = g3(root2);

    for (i=0; i != 100; i++) {
        x1 = g1(x1);
        x2 = g2(x2);
        x3 = g3(x3);
    }

    printf("A primeira raiz é: %lf", x1);
    printf("A segunda raiz é: %lf", x2);
    printf("A terceira raiz é: %lf", x3);

}
