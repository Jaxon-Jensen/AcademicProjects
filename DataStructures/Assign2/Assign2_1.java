package DataStructures.Assign2;
public class Assign2_1{
    public static void main(String[] args){
        int[] arr = {1,2,3,3,4,5,10};
        int left = 0;
        int right = arr.length - 1;
        int mid = (int)(left + right)/2;
        int target = 3;
        while(left != right){
            
            if(arr[mid] == target){
                while(arr[mid] == arr[mid-1]){
                    mid--;
                }
                System.out.println("index = " + mid);
                return;
            } else if (arr[mid] > target){
                right = mid;
                mid = (int)((left + right)/2);
            } else {
                left = mid;
                mid = (int)((left + right)/2);
            }
            System.out.println(arr[mid] + "\n");
        }
        System.out.println("index = -1");
    }
}
    