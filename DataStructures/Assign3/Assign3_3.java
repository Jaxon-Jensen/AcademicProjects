public class Assign3_3 {
    public static void main(String[] args){
        int[] arr = {11,2,7,15};
        int target = 9;
        sumToTarget(target, arr);
    }
    public static void sumToTarget(int target, int[] arr){
        int[] table = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
        int j = 0;
        for(int i = 0; i< arr.length; i++){
            j = 0;
            while(j<10){    
                if(table[(arr[i]+(j*j))%10] == -1){
                    table[(arr[i]+(j*j))%10] = i;
                    break;
                }
                j++;
            }
            if(table[target-arr[i]%10] != -1){
                if(arr[i] + arr[table[target-arr[i]%10]] == target){
                    System.out.print("[" + table[target-arr[i]%10] + ",");
                    System.out.println(i + "]");
                    return;
                }
            }
        }
        System.out.println("[-1,-1]");
        return;
    }
}
