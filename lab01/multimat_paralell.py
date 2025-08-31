import numpy as np
import time
from multiprocessing import Pool, cpu_count

# Tamaño de la matriz
N = 1000
A = np.random.rand(N, N)
B = np.random.rand(N, N)

def compute_row(i):
    """Calcular una fila de la matriz resultado"""
    row = np.zeros(N)
    for j in range(N):
        for k in range(N):
            row[j] += A[i][k] * B[k][j]
    return row

if __name__ == "__main__":
    start = time.time()

    with Pool(cpu_count()) as p:
        C = p.map(compute_row, range(N))

    end = time.time()
    print(f"Tiempo Python paralelo: {end - start:.3f} segundos")
