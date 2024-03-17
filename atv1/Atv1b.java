import java.io.FileWriter;
import java.io.IOException;
import java.util.Random;

public class Atv1b {
    private static final int SIZE = 100;
    private static final int NUM_VECTORS = 1024;
    private static final int REPET = 1024;

    public static void insertSort(int[] vector, int n) {
        for (int i = 1; i < n; i++) {
            int chave = vector[i];
            int j = i - 1;

            while (j >= 0 && vector[j] > chave) {
                vector[j + 1] = vector[j--];
            }
            vector[j + 1] = chave;
        }
    }

    public static void randomVectorInt(int[] vector, int n) {
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            vector[i] = rand.nextInt(1000);  // Números aleatórios entre 0 e 999
        }
    }

    public static void main(String[] args) {
        int qtd = REPET;
        long start, end;
        double cpu_time_used;

        try {
            FileWriter arquivo = new FileWriter("temposEmJava.txt");

            while (qtd-- != 0) {
                int numVectors = NUM_VECTORS;
                start = System.nanoTime();

                while (numVectors-- != 0) {
                    int[] vector = new int[SIZE];
                    randomVectorInt(vector, SIZE);
                    insertSort(vector, SIZE);
                }

                end = System.nanoTime();
                cpu_time_used = (double) (end - start) / 1_000_000_000; // Convertendo para segundos

                arquivo.write(cpu_time_used + "\n");
            }

            arquivo.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
