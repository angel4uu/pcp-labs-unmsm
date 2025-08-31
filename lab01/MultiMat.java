public class MultiMat {
    static final int MAX = 500;

    public static void main(String[] args) {
        int[][] a = new int[MAX][MAX];
        int[][] b = new int[MAX][MAX];
        int[][] c = new int[MAX][MAX];

        // Inicialización de las matrices
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                a[i][j] = 0;
                b[i][j] = 100 + i;
            }
            a[i][i] = 1; // matriz identidad
        }

        // Multiplicación de matrices
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                c[i][j] = 0;
                for (int k = 0; k < MAX; k++) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }

        // Impresión de la matriz resultado
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                System.out.printf("%5d ", c[i][j]);
            }
            System.out.println();
        }
    }
}
