#include "FuerzaBruta.h"

void encontrarSeamFuerzaBruta_Aux(const std::vector<std::vector<double>>& energia, int fila_actual, int col_actual, double energia_acumulada, std::vector<int>& costura_actual, double& mejor_energia, std::vector<int>& mejor_costura) {
    int n = energia.size();
    int m = energia[0].size();

    //1 procesamos el paso actual
    energia_acumulada += energia[fila_actual][col_actual];
    costura_actual.push_back(col_actual);

    //2 caso base: ¿llegamos al fondo de la imagen?
    if(fila_actual == n-1){//el indice de la ultima fila es n-1
        if(energia_acumulada < mejor_energia){ //si nuestro nuevo camino es mejor, guardamos el nuevo record
            mejor_energia = energia_acumulada;
            mejor_costura = costura_actual;
        }

        costura_actual.pop_back(); //limpiamos el ultimo paso, para que puede probar distintos caminos sin acumular pasos extra
        return; 
    }
    else{// 3 exploracmos los 3 caminos posibles hacia la fila de abajo, teniendo cuidado con los bordes
        if(col_actual == 0){ //si esta al principio de la fila
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual+1, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
        }
        else if(col_actual == m-1){ //si esta al final de la fila
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual-1, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
        }

        else{ //si no esta ni al final ni al principio de la fila
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual-1, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual+1, energia_acumulada, costura_actual, mejor_energia, mejor_costura);
        }  
    }
    costura_actual.pop_back();
}

std::vector<int> encontrarSeamFuerzaBruta(const std::vector<std::vector<double>>& energia) {
    if(energia.empty() == true){
        return{};
    }

    std::vector<int> mejor_costura = {};
    std::vector<int> costura_actual = {};
    double mejor_energia = 500000000; //ponemos un numero muy alto para asegurarnos que el primer mejor camino sea si o si menor

    for(int i = 0; i < energia[0].size(); i++){ //¿Desde qué píxel de la primera fila arrancamos a caminar? Arrancamos desde todos porque queremos hacer fuerza bruta
        encontrarSeamFuerzaBruta_Aux(energia, 0, i, 0.0, costura_actual, mejor_energia, mejor_costura);
    }

    return mejor_costura;
}

    
