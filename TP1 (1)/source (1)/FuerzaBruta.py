def encontrarSeamFuerzaBruta(energia):
    if not energia:
        return []

    mejor_costura = []
    costura_actual = []
    # Ponemos un numero muy alto para asegurarnos que el primer mejor camino sea si o si menor
    mejor_energia = [500000000.0] 

    # ¿Desde qué píxel de la primera fila arrancamos a caminar? 
    # Arrancamos desde todos porque queremos hacer fuerza bruta
    for i in range(len(energia[0])):
        encontrarSeamFuerzaBruta_Aux(energia, 0, i, 0.0, costura_actual, mejor_energia, mejor_costura)

    return mejor_costura

def encontrarSeamFuerzaBruta_Aux(energia, fila_actual, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura):
    n = len(energia)
    m = len(energia[0])

    # 1 procesamos el paso actual
    energia_acumulada += energia[fila_actual][col_actual]
    costura_actual.append(col_actual)

    # 2 caso base: ¿llegamos al fondo de la imagen?
    if fila_actual == n - 1: # el indice de la ultima fila es n-1
        if energia_acumulada < mejor_energia[0]: # si nuestro nuevo camino es mejor, guardamos el nuevo record
            mejor_energia[0] = energia_acumulada
            mejor_costura[:] = list(costura_actual) # Copiamos el contenido

        # limpiamos el ultimo paso, para que puede probar distintos caminos sin acumular pasos extra
        costura_actual.pop()
        return
    
    else: # 3 exploracmos los 3 caminos posibles hacia la fila de abajo, teniendo cuidado con los bordes
        if col_actual == 0: # si esta al principio de la fila
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual+1, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
        
        elif col_actual == m - 1: # si esta al final de la fila
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual-1, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
        
        else: # si no esta ni al final ni al principio de la fila
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual-1, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
            encontrarSeamFuerzaBruta_Aux(energia, fila_actual+1, col_actual+1, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
    
    costura_actual.pop()