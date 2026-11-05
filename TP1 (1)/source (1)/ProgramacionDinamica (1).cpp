#include "ProgramacionDinamica.h"

double minimo(double a, double b, double c){
    if(a <= b && a <= c){
        return a;
    }
    else if(b <= a && b <= c){
        return b;
    }
    else{
        return c;
    }
}

double encontrarSeamPD_Aux(const std::vector<std::vector<double>>& energia, int fila, int col, std::vector<std::vector<double>>& memo) {
    int n = energia.size();
    int m = energia[0].size();

    //Caso base 1: ya lo calculamos
    if(memo[fila][col] != -1.0){
        return(memo[fila][col]);
    }

    //Caso base 2: llegamos al final
    if(fila == n-1){
        memo[fila][col] = energia[fila][col];
        return memo[fila][col];
    }

    //exploracion
    double costo_izq = 500000000000.0;
    double costo_centro = 50000000000.0;
    double costo_der = 5000000000.0;

    if(col == 0){ //si esta al principio de la fila
        costo_centro = encontrarSeamPD_Aux(energia, fila+1, col, memo);
        costo_der = encontrarSeamPD_Aux(energia, fila+1, col+1, memo);
    }
    else if(col == m-1){ //si esta al final de la fila
        costo_centro = encontrarSeamPD_Aux(energia, fila+1, col, memo);
        costo_izq = encontrarSeamPD_Aux(energia, fila+1, col-1, memo);
    }

    else{ //si no esta ni al final ni al principio de la fila
        costo_centro = encontrarSeamPD_Aux(energia, fila+1, col, memo);
        costo_izq = encontrarSeamPD_Aux(energia, fila+1, col-1, memo);
        costo_der = encontrarSeamPD_Aux(energia, fila+1, col+1, memo);
    }  

    memo[fila][col] = energia[fila][col] + minimo(costo_izq, costo_centro, costo_der);

    return memo[fila][col];
}

std::vector<int> encontrarSeamPD(const std::vector<std::vector<double>>& energia) {
    if(energia.empty()){
        return{};
    }

    int n = energia.size();
    int m = energia[0].size();
    std::vector<std::vector<double>> memo(n, std::vector<double>(m, -1.0));

    double best_energia_total = 5000000000000.0;
    int best_col_inicio = 0;

    for(int i = 0; i < m; i++){
        double costo_desde_este_inicio = encontrarSeamPD_Aux(energia, 0, i, memo);

        if(costo_desde_este_inicio < best_energia_total){
            best_energia_total = costo_desde_este_inicio;
            best_col_inicio = i;
        }
    }

    std::vector<int> mejor_costura(n);
    mejor_costura[0] = best_col_inicio;
    int col_actual = best_col_inicio;

    for (int fila = 0; fila < n - 1; fila++) {
        // Miramos los 3 posibles pasos en la siguiente fila (fila + 1)
        double min_costo = 500000000.0;
        int mejor_siguiente_col = col_actual;

        // ¿Puedo ir a la izquierda? ¿Es más barato?
        if (col_actual > 0 && memo[fila + 1][col_actual - 1] < min_costo) {
            min_costo = memo[fila + 1][col_actual - 1];
            mejor_siguiente_col = col_actual - 1;
        }
        // ¿El centro es más barato?
        if (memo[fila + 1][col_actual] < min_costo) {
            min_costo = memo[fila + 1][col_actual];
            mejor_siguiente_col = col_actual;
        }
        // ¿Puedo ir a la derecha? ¿Es más barato?
        if (col_actual < m - 1 && memo[fila + 1][col_actual + 1] < min_costo) {
            min_costo = memo[fila + 1][col_actual + 1];
            mejor_siguiente_col = col_actual + 1;
        }

        // Damos el paso
        col_actual = mejor_siguiente_col;
        mejor_costura[fila + 1] = col_actual; // Guardamos la columna en nuestro vector final
    }

    return mejor_costura;    
}

