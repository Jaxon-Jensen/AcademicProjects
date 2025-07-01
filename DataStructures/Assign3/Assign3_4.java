import java.util.Arrays;

public class Assign3_4{
    public static void main(String[] args){
        int[] inputArr = {8,12,9,7,22,3,26,14,11,15,22};
        minHeap(inputArr);
    }
    public static void minHeap(int[] arr){
        int temp;
        for(int i = 0; i<arr.length; i++){
            for(int j = 0; j<arr.length-i-1; j++){
                if(arr[j]>arr[j+1]){
                    temp = arr[j+1];
                    arr[j+1] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        System.out.println(Arrays.toString(arr));
    }
}