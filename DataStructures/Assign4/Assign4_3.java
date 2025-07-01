package DataStructures.Assign4;

public class Assign4_3 {
    public static void main(String[] args) {
        int[] arr = new int[100];
        int[] count = new int[20];
        int index = 0;
        
        for(int i = 0; i< 100; i++){
            arr[i] = (int) (Math.random() * 20)+1;
            System.out.print(arr[i] + ", ");
            count[arr[i]-1]++;
        }
        System.out.println("\n\n");
        for(int i = 0; i<20; i++){
            System.out.print(count[i] + ", ");
        }
        System.out.println("\n\n");

        for(int i = 0; i<20; i++){
            while(count[i] > 0){
                arr[index] = i+1;
                System.out.print(arr[index] +  ", ");
                index++;
                count[i]--;
            }
        }
    }
}
