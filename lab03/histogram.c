/**
 * Histograma secuencial y paralelo con OpenMP
 * siguiendo la metodología de Foster.
 *
 * Etapas de Foster:
 *  1. Partición: dividir el problema en tareas independientes.
 *  2. Comunicación: definir qué datos deben compartir los hilos.
 *  3. Aglomeración: combinar tareas dependientes en unidades más grandes.
 *  4. Mapeo: asignar las tareas a hilos/procesos de forma balanceada.
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h> 

/**
 * Determina a qué bin pertenece un valor dado.
 */
int find_bin(double value, double *bin_edges, int bin_count) {
    for (int i = 0; i < bin_count; i++) {
        if (value < bin_edges[i]) return i;
    }
    return bin_count - 1;
}

/**
 * ============================
 * VERSIÓN SECUENCIAL
 * ============================
 * Recorre todos los datos y actualiza los contadores globales.
 */
void histogram_serial(double *data, int n, int bin_count,
                      double min_val, double max_val, int *bin_counts) {
    double *bin_edges = malloc(bin_count * sizeof(double));
    double step = (max_val - min_val) / bin_count;

    // Inicializar límites de bins y contadores
    for (int i = 0; i < bin_count; i++) {
        bin_edges[i] = min_val + (i + 1) * step;
        bin_counts[i] = 0;
    }

    // Procesamiento secuencial
    for (int i = 0; i < n; i++) {
        int b = find_bin(data[i], bin_edges, bin_count);
        bin_counts[b]++;
    }

    free(bin_edges);
}

/**
 * ============================
 * VERSIÓN PARALELA (OpenMP)
 * ============================
 * Aplicando Foster:
 *  - Partición: se divide el bucle entre hilos con #pragma omp for.
 *  - Comunicación: mínima, solo al sumar resultados locales.
 *  - Aglomeración: (find_bin + incremento) se combinan en la misma iteración.
 *  - Mapeo: OpenMP asigna bloques de datos a hilos automáticamente.
 */
void histogram_parallel(double *data, int n, int bin_count,
                        double min_val, double max_val, int *bin_counts) {
    double *bin_edges = malloc(bin_count * sizeof(double));
    double step = (max_val - min_val) / bin_count;

    // Inicializar límites de bins y contadores
    for (int i = 0; i < bin_count; i++) {
        bin_edges[i] = min_val + (i + 1) * step;
        bin_counts[i] = 0;
    }

    #pragma omp parallel
    {
        // Cada hilo mantiene un histograma local
        int *loc_bin_counts = calloc(bin_count, sizeof(int));

        // === ETAPA 1: PARTICIÓN ===
        // OpenMP divide el bucle entre hilos
        #pragma omp for
        for (int i = 0; i < n; i++) {
            int b = find_bin(data[i], bin_edges, bin_count);

            // === ETAPA 3: AGLOMERACIÓN ===
            // Tarea compuesta: calcular bin + actualizar contador local
            loc_bin_counts[b]++;
        }

        // === ETAPA 2 + 4: COMUNICACIÓN + MAPEO ===
        // Cada hilo suma sus resultados locales al histograma global
        #pragma omp critical
        {
            for (int i = 0; i < bin_count; i++) {
                bin_counts[i] += loc_bin_counts[i];
            }
        }
        free(loc_bin_counts);
    }

    free(bin_edges);
}

int main(int argc, char *argv[]) {
    int n = 10000000;    // número de datos
    int bin_count = 10; // número de bins
    double *data = malloc(n * sizeof(double));

    // Generar datos aleatorios en rango [0,5]
    for (int i = 0; i < n; i++) {
        data[i] = ((double) rand() / RAND_MAX) * 5.0;
    }

    int *bin_counts = calloc(bin_count, sizeof(int));

    if (argc > 1 && strcmp(argv[1], "parallel") == 0) {
        // Ejecutar versión paralela
        histogram_parallel(data, n, bin_count, 0.0, 5.0, bin_counts);
        printf("Histograma paralelo (OpenMP):\n");
    } else {
        // Ejecutar versión secuencial
        histogram_serial(data, n, bin_count, 0.0, 5.0, bin_counts);
        printf("Histograma secuencial:\n");
    }

    for (int i = 0; i < bin_count; i++) {
        printf("Bin %d: %d\n", i, bin_counts[i]);
    }

    free(data);
    free(bin_counts);
    return 0;
}
