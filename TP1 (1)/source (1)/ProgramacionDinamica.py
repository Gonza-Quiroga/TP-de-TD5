def minimo(a, b, c):
    if a <= b and a <= c:
        return a
    elif b <= a and b <= c:
        return b
    else:
        return c

def encontrarSeamPD_Aux(energia, fila, col, memo):
    n = len(energia)
    m = len(energia[0])

    # Caso base 1: ya lo calculamos
    if memo[fila][col] != -1.0:
        return memo[fila][col]

    # Caso base 2: llegamos al final
    if fila == n - 1:
        memo[fila][col] = energia[fila][col]
        return memo[fila][col]

    # exploracion
    costo_izq = 500000000000.0
    costo_centro = 50000000000.0
    costo_der = 5000000000.0

    if col == 0: # si esta al principio de la fila
        costo_centro = encontrarSeamPD_Aux(energia, fila+1, col, memo)
        costo_der = encontrarSeamPD_Aux(energia, fila+1, col+1, memo)
    
    elif col == m - 1: # si esta al final de la fila
        costo_centro = encontrarSeamPD_Aux(energia, fila+1, col, memo)
        costo_izq = encontrarSeamPD_Aux(energia, fila+1, col-1, memo)
    
    else: # si no esta ni al final ni al principio de la fila
        costo_centro = encontrarSeamPD_Aux(energia, fila+1, col, memo)
        costo_izq = encontrarSeamPD_Aux(energia, fila+1, col-1, memo)
        costo_der = encontrarSeamPD_Aux(energia, fila+1, col+1, memo)

    memo[fila][col] = energia[fila][col] + minimo(costo_izq, costo_centro, costo_der)
    return memo[fila][col]

def encontrarSeamPD(energia):
    if not energia:
        return []

    n = len(energia)
    m = len(energia[0])
    # Inicializamos memo con -1.0
    memo = [[-1.0 for _ in range(m)] for _ in range(n)]

    best_energia_total = 5000000000000.0
    best_col_inicio = 0

    for i in range(m):
        costo_desde_este_inicio = encontrarSeamPD_Aux(energia, 0, i, memo)
        if costo_desde_este_inicio < best_energia_total:
            best_energia_total = costo_desde_este_inicio
            best_col_inicio = i

    mejor_costura = [0] * n
    mejor_costura[0] = best_col_inicio
    col_actual = best_col_inicio

    for fila in range(n - 1):
        # Miramos los 3 posibles pasos en la siguiente fila (fila + 1)
        min_costo = 50000000000000.0
        mejor_siguiente_col = col_actual

        # ¿Puedo ir a la izquierda? ¿Es más barato?
        if col_actual > 0 and memo[fila + 1][col_actual - 1] < min_costo:
            min_costo = memo[fila + 1][col_actual - 1]
            mejor_siguiente_col = col_actual - 1
        
        # ¿El centro es más barato?
        if memo[fila + 1][col_actual] < min_costo:
            min_costo = memo[fila + 1][col_actual]
            mejor_siguiente_col = col_actual
        
        # ¿Puedo ir a la derecha? ¿Es más barato?
        if col_actual < m - 1 and memo[fila + 1][col_actual + 1] < min_costo:
            min_costo = memo[fila + 1][col_actual + 1]
            mejor_siguiente_col = col_actual + 1

        # Damos el paso
        col_actual = mejor_siguiente_col
        mejor_costura[fila + 1] = col_actual # Guardamos la columna en nuestro vector final

    return mejor_costura