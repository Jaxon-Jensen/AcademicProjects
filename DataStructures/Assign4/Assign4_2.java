package DataStructures.Assign4;

public class Assign4_2 {
    public static void main(String[] args) {
        int[] arr1 = {1,2,5};
        int[] arr2 = {3,4};
        int[] arrOut = new int[5];
        int iOne = 0, iTwo = 0;
        
        for(int i = 0; i<arr1.length + arr2.length; i++){
            if(iOne >= arr1.length){
                for(int j = iTwo; j<arr2.length; j++){
                    arrOut[i] = arr2[j];
                    i++;
                }
            } else if(iTwo >= arr2.length){
                for(int j = iOne; j<arr1.length; j++){
                    arrOut[i] = arr1[j];
                    i++;
                }
            } else {
                if(arr1[iOne] < arr2[iTwo]){
                    arrOut[i] = arr1[iOne];
                    iOne++;
                } else {
                    arrOut[i] = arr2[iTwo];
                    iTwo++;
                }
            }
        }
        for(int i = 0; i< arrOut.length; i++){
            System.out.print(arrOut[i] + ", ");
        }
    }
}
