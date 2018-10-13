import java.util.Random;
import java.util.Scanner;


public class Main {
    public static int[][] Densify(int[][] matrix) {
        int height = matrix.length;
        int width = matrix[0].length;

        boolean[] keepRows = new boolean[height];
        boolean[] keepCols = new boolean[width];

        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                if(matrix[i][j] != 0) {
                    keepRows[i] = true;
                    keepCols[j] = true;
                }
            }
        }

        int src_row = 0;
        int dst_row = 0;

        while(src_row < height && dst_row < height) {
            if(keepRows[src_row]) {
                if(src_row != dst_row) {
                    for (int j = 0; j < width; ++j) {
                        matrix[dst_row][j] = matrix[src_row][j];
                    }
                }
                src_row++;
                dst_row++;
            } else {
                src_row++;
            }
        }

        for(boolean k : keepRows) {
            if(!k) {
                height--;
            }
        }

        int src_col = 0;
        int dst_col = 0;

        while(src_col < width && dst_col < width) {
            if(keepCols[src_col]) {
                if(src_col != dst_col) {
                    for (int i = 0; i < height; ++i) {
                        matrix[i][dst_col] = matrix[i][src_col];
                    }
                }
                src_col++;
                dst_col++;
            } else {
                src_col++;
            }
        }

        for(boolean k : keepCols) {
            if(!k) {
                width--;
            }
        }

        int[][] newMatrix = new int[height][width];
        for(int i = 0; i < height; ++i) {
            for(int j = 0; j < width; ++j) {
                newMatrix[i][j] = matrix[i][j];
            }
        }

        return newMatrix;

    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("enter the matrix dimension N");
        int n = scanner.nextInt();
        scanner.close();

        int[][] matrix = new int[n][n];

        Random random = new Random();
        for(int i = 0; i < matrix.length; ++i){
            for(int j=0;j<matrix[i].length;++j){
                if(random.nextDouble() < 2.0 / n) {
                    matrix[i][j] = (int) (-n - 1 + random.nextDouble() * (2 * n + 2));
                } else {
                    matrix[i][j] = 0;
                }
            }
        }

        System.out.println("sparse matrix:");

        for(int i = 0; i < matrix.length; ++i) {
            for(int j = 0; j < matrix[i].length; ++j) {
                System.out.printf("%3d ", matrix[i][j]);
            }
            System.out.println();
        }

        matrix = Densify(matrix);

        System.out.println("dense matrix:");

        for(int i = 0; i < matrix.length; ++i) {
            for(int j = 0; j < matrix[i].length; ++j) {
                System.out.printf("%3d ", matrix[i][j]);
            }
            System.out.println();
        }

    }
}
