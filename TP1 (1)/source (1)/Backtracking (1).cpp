#include "Backtracking.h"

void encontrarSeamBacktracking_Aux(const std::vector<std::vector<double>>& energia, int fila_actual, int col_actual, double energia_acumulada, std::vector<int>& costura_actual, double& mejor_energia, std::vector<int>& mejor_costura) {
    int n = energia.size();
    int m = energia[0].size();

    energia_acumulada += energia[fila_actual][col_actual];
    costura_actual.push_back(col_actual);

    if(energia_acumulada >= mejor_energia){ //si en este punto ya tengo una energia acumulada igual o peor, directamente podo y sigo con otro posible camino
        costura_actual.pop_back(); //Deshacer antes de volver
        return;
    }
    

    if(fila_actual == n-1){//el indice de la ultima fila es n-1
        //if(energia_acumulada < mejor_energia){ //si nuestro nuevo camino es mejor, guardamos el nuevo record <----- REDUNDANTE, YA LO CHECKEAMOS ANTES AL VER SI NUESTRE ENERGIA ACUMULADA ERA IGUAL O MAYOR
            mejor_energia = energia_acumulada;
            mejor_costura = costura_actual;
        //}

        costura_actual.pop_back(); //limpiamos el ultimo paso, para que puede probar distintos caminos sin acumular pasos extra
        return; 
    }

    else{// 3 exploracmos los 3 caminos posibles hacia la fila de abajo, teniendo cuidado con los bordes
        if(col_actual == 0){ //si esta al principio de la fila
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual+1, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
        }
        else if(col_actual == m-1){ //si esta al final de la fila
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual-1, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
        }

        else{ //si no esta ni al final ni al principio de la fila
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual-1, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual+1, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
        }  
    }
    costura_actual.pop_back();
}

std::vector<int> encontrarSeamBacktracking(const std::vector<std::vector<double>>& energia) {
    if(energia.empty()){
        return {};
    }

    std::vector<int> mejor_costura = {};
    std::vector<int> costura_actual = {};
    double mejor_energia = 500000000; //ponemos un numero muy alto para asegurarnos que el primer mejor camino sea si o si menor

     for(int i = 0; i < energia[0].size(); i++){ //¿Desde qué píxel de la primera fila arrancamos a caminar? Arrancamos desde todos porque queremos hacer fuerza bruta
        encontrarSeamBacktracking_Aux(energia, 0, i, 0.0, costura_actual, mejor_energia, mejor_costura);
    }

    return mejor_costura;
}

