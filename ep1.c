#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

enum Status { Pending, Success, IterationsExceeded, Overflow, DivisionByZero };

struct RootStruct {
    double x0;
    double (*g)(double);
    enum Status status;
    double result;
};

void printResult(int rootIndex, double x, enum Status status) {
    if (status == DivisionByZero) {
        printf("Erro: O cálculo da raiz %d passou por uma divisão por zero.\n",
               rootIndex);
    } else if (status == IterationsExceeded) {
        printf("Erro: O cálculo da raiz %d excedeu o limite de iterações.\n",
               rootIndex);
    } else if (status == Overflow) {
        printf("Erro: No cálculo da raiz %d houve overflow.\n", rootIndex);
        return;
    } else {
        printf("A raiz %d convergiu para %f.\n", rootIndex, x);
    }
}

void askStopParams() {
    char input[128];
    printf("CRITÉRIOS DE PARADA\n"
           "===================\n");
    printf("Qual o número de iterações máximo?\n"
           "(deixe vazio usar o padrão %d)\n",
           maxIter);
    fgets(input, 128, stdin);
    if (input[0] != '\n') {
        maxIter = atoi(input);
    }

    printf("\nQual a constante rtol, para o erro relativo?\n"
           "(deixe vazio para usar o padrão %f)\n",
           relTol);
    fgets(input, 128, stdin);
    if (input[0] != '\n') {
        relTol = strtod(input, NULL);
    }

    printf("\n\n");
}

void askPoints(struct RootStruct *roots, int rootsLength) {
    printf("PONTOS INICIAIS\n"
           "===============\n");

    for (int i = 0; i < rootsLength; i++) {
        printf("Qual o valor do ponto inicial da raiz %d?\n"
               "(deixe vazio para usar o padrão %f)\n",
               i, roots[i].x0);

        char input[128];
        fgets(input, 128, stdin);
        if (input[0] != '\n') {
            roots[i].x0 = strtod(input, NULL);
        }

        printf("\n");
    }
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

void printResults(struct RootStruct *roots, int rootsLength) {
    printf("RESULTADOS\n"
           "==========\n");

    for (int i = 0; i < rootsLength; i++) {
        printResult(i + 1, roots[i].result, roots[i].status);
    }
}

int main() {
    askStopParams();

    struct RootStruct roots[3] = {
        {.x0 = 2, .g = g1}, {.x0 = 3, .g = g2}, {.x0 = 3, .g = g3}};

    askPoints(roots, 3);
    calculateRoots(roots, 3);
    printResults(roots, 3);
}
