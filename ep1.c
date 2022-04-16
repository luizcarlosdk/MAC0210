#include <stdio.h>
#include <complex.h>
#include <math.h>

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

    for (i=0; i =! 100; i++) {
        x1 = g1(x1);
        x2 = g2(x2);
        x3 = g3(x3);
    }

    printf("A primeira raiz é: %lf", x1);
    printf("A segunda raiz é: %lf", x2);
    printf("A terceira raiz é: %lf", x3);

}