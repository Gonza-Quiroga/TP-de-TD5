import random

n = 100
m = 100

with open('./input/cuadradas/ejemplo_GRANDE.txt', 'w') as e: #ponemos donde guardaremos la matriz de 100x100
    e.write(f"{n} {m}\n") #ponemos las dimensiones al principio de del .txt

    for i in range(n): #generamos las 100 filas
        fila = [f"{random.randint(1, 19) * 0.5:.1f}" for _ in range(m)]
        e.write("  ".join(fila) + "\n")