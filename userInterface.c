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

void printResults(struct RootStruct *roots, int rootsLength) {
    printf("RESULTADOS\n"
           "==========\n");

    for (int i = 0; i < rootsLength; i++) {
        printResult(i + 1, roots[i].result, roots[i].status);
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
