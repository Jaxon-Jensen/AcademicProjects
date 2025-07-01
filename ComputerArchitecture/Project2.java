package ComputerArchitecture;
import java.util.Random;
import java.util.Scanner;
public class Project2 {
    public static void main(String[] args) {
        int[] arr = {0,0,0};
        generate(arr, 3);
        for(int i: arr){
            System.out.print(i);
        }
        System.out.println("");
        Scanner sc = new Scanner(System.in);
        String in;
        int[] guess = {-1,-1,-1};
        int temp;
        boolean badInput = false;
        while(true){
            System.out.print("Enter guess (Ex. 815): ");
            in = sc.nextLine();

            if(in.length() != 3){
                System.out.println("Enter 3 numbers\n");
                continue;
            }
            badInput = false;
            for(int i = 0; i < 3; i++){
                temp = Character.getNumericValue(in.charAt(i));
                if(temp == 0){
                    System.out.println("Enter only 1-9\n");
                    badInput = true;
                    break;
                }
                if(find(arr, temp, i) != -1){
                    System.out.println("Cannot have duplicate numbers\n");
                    badInput = true;
                    break;
                }
                guess[i] = temp;
            }
            if(badInput){
                continue;
            }

            int balls = findBalls(arr, guess);
            int strikes = findStrikes(arr, guess);
            if(strikes == 3){
                System.out.printf("\nGood Job! Do you want to play again (Y/N)? ");
                String ans = sc.nextLine();
                if(ans.toUpperCase().charAt(0) == 'Y'){
                    System.out.println("\n");
                    main(args);
                    sc.close();
                    return;
                } else {
                    break;
                }
            }
            if(strikes != 0){
                System.out.printf("%d strike(s) ", strikes);
            }
            if(balls != 0){
                System.out.printf("%d ball(s) ", balls);
            }
            if(balls == 0 && strikes == 0){
                System.out.print("Out");
            }
            System.out.println("\n\n");
        }
        sc.close();
    }

    public static int findStrikes(int[] generated, int[] input){
        int cnt = 0;
        for(int i = 0; i < 3; i++){
            if(find(generated, input[i], 3) == i){
                cnt++;
            }
        }
        return cnt;
    }

    public static int findBalls(int[] generated, int[] input){
        int cnt = 0;
        int index;
        for(int i = 0; i < 3; i++){
            index = find(generated, input[i], 3);
            if(index != -1 && index != i){
                cnt++;
            }
        }
        return cnt;
    }

    public static void generate(int[] generated, int cnt){
        Random rand = new Random();
        int temp;
        for(int i = 0; i < cnt; i++){
            temp = rand.nextInt(9)+1;
            if(find(generated,temp,i) == -1){
                generated[i] = temp;
            } else {
                i--;
            }
        }
    }

    public static int find(int[] arr, int num, int cnt){
        for(int i = 0; i< cnt; i++){
            if(arr[i] == num){
                return i;
            }
        }
        return -1;
    }
}