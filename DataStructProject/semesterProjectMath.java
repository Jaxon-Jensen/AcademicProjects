package DataStructProject;

public class semesterProjectMath {
    public static void main(String[] args){
        int n = 6; // How many 1s and 0s
        int total = 0; // Number of values.
        int[] arr = new int[n-1]; // Array to store calculated values for the main sequence.
        int[][] temp = new int[n-2][n-3]; // 2D array to store intermediate calculations for nested sequences.

        // Array to hold powers of 2 up to (2*n)-1.
        int[] pow = new int[(2*n)-1];
        for(int i = 0; i < (2*n)-1; i++) {
            pow[i] = (int) Math.pow(2, i); // Calculate 2^i and store it in pow array.
        }

        // Initialize the first element in arr to a value derived from powers of 2, then print it.
        arr[0] = pow[n] - 1;
        System.out.println(Integer.toString(arr[0], 2) + "  " + arr[0] + "    ");
        total++;

        // Modify arr[0] by adding another power of 2, then print it.
        arr[0] += pow[n - 1];
        System.out.print(Integer.toString(arr[0], 2) + "  " + arr[0] + "    ");
        total++;

        // Populate remaining elements of arr based on the preceding element.
        for(int i = 1; i < n-1; i++) {
            arr[i] = arr[i-1] + pow[n-1-i];
            System.out.print(Integer.toString(arr[i], 2) + "  " + arr[i] + "    ");
            total++;
        }
        System.out.println();

        // Nested loop for modifying and printing elements in arr and temp with specific calculations.
        for(int j = 0; j < n-2; j++) {
            System.out.println();

            // Modify arr elements by adding increasing powers of 2 in each iteration.
            for(int i = 0; i < n-1; i++) {
                arr[i] += pow[n + j];
                System.out.print(Integer.toString(arr[i], 2) + "  " + arr[i] + "    ");
                total++;
            }

            if(n == 3) { return; } // Special case for n = 3, exits the method early.

            // First column of temp initialized based on arr and powers of 2.
            System.out.print("\n                 ");
            for(int i = 0; i < n-2; i++) {
                temp[i][0] = arr[i+1] + pow[n-1];
                System.out.print(Integer.toString(temp[i][0], 2) + "  " + temp[i][0] + "    ");
                total++;
            }

            // Nested structure for handling multiple columns in temp, depending on numCol and count.
            System.out.print("\n                                   ");
            if(j >= 0) {
                int numCol = n-3;
                int count = 1;
                while(numCol > 1) {
                    for(int i = 0; i < temp.length - count; i++) {
                        temp[i+count][count] = temp[i+count][count-1] + pow[n-1-count];
                        System.out.print(Integer.toString(temp[i+count][count], 2) + "  " + temp[i+count][count] + "    ");
                        total++;
                    }
                    System.out.print("\n                                                      ");
                    count++;
                    numCol--;
                }
            }

            // Nested update on temp for each row in the matrix.
            for(int s = 1; s < j+1 && s < n-3; s++) {
                System.out.print("\n                 ");
                for(int i = 0; i < n-2; i++) {
                    temp[i][0] += pow[n-1+s];
                    System.out.print(Integer.toString(temp[i][0], 2) + "  " + temp[i][0] + "    ");
                    total++;
                }
                System.out.print("\n                                   ");

                // Loop to manage updates across multiple columns in temp.
                if(j > 0) {
                    int numCol = n-3;
                    int count = 1;
                    while(numCol > 1) {
                        for(int i = 0; i < temp.length - count; i++) {
                            temp[i+count][count] += pow[n-1+s];
                            System.out.print(Integer.toString(temp[i+count][count], 2) + "  " + temp[i+count][count] + "    ");
                            total++;
                        }
                        System.out.print("\n                                                      ");
                        count++;
                        numCol--;
                    }
                }
            }
            System.out.print("\n");
        }

        // Print the total number of values processed.
        System.out.println(total);
    }
}
