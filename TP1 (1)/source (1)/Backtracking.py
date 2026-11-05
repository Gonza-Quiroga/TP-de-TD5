def encontrarSeamBacktracking(energia):
    if not energia:
        return []

    mejor_costura = []
    costura_actual = []
    # Ponemos un numero muy alto para asegurarnos que el primer mejor camino sea si o si menor
    mejor_energia = [500000000.0] 

    # ¿Desde qué píxel de la primera fila arrancamos a caminar?
    for i in range(len(energia[0])):
        encontrarSeamBacktracking_Aux(energia, 0, i, 0.0, costura_actual, mejor_energia, mejor_costura)

    return mejor_costura

def encontrarSeamBacktracking_Aux(energia, fila_actual, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura):
    n = len(energia)
    m = len(energia[0])

    energia_acumulada += energia[fila_actual][col_actual]
    costura_actual.append(col_actual)

    # si en este punto ya tengo una energia acumulada igual o peor, directamente podo y sigo con otro posible camino
    if energia_acumulada >= mejor_energia[0]:
        costura_actual.pop() # Deshacer antes de volver
        return

    if fila_actual == n - 1: # el indice de la ultima fila es n-1
        # REDUNDANTE, YA LO CHECKEAMOS ANTES
        mejor_energia[0] = energia_acumulada
        mejor_costura[:] = list(costura_actual)

        # limpiamos el ultimo paso
        costura_actual.pop()
        return 
    
    else: # 3 exploracmos los 3 caminos posibles hacia la fila de abajo
        if col_actual == 0:
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual+1, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
        
        elif col_actual == m - 1:
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual-1, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
        
        else:
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual-1, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
            encontrarSeamBacktracking_Aux(energia, fila_actual+1, col_actual+1, energia_acumulada, costura_actual, mejor_energia, mejor_costura)
            
    costura_actual.pop()