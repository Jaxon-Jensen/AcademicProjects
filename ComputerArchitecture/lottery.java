package ComputerArchitecture;
import java.util.Random;
import java.util.Scanner;
import java.util.Arrays;
public class lottery {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int temp;
        int[] input = {0,0,0,0,0,0,0};
        int[] generated = {0,0,0,0,0,0};
        String trash;
        for(int i = 1; i<=7; i++){
            System.out.printf("Input number %d: ", i);
            try{   
                temp = sc.nextInt();
            } catch(Exception e){
                System.out.println("Invalid try again\n");
                i--;
                trash = sc.nextLine();
                continue;
            }
            if(temp>0 && temp < 45){
                input[i-1] = temp;
            } else {
                System.out.println("Invalid try again");
                i--;
            }
        }

        
        int drawings;
        while(true){
            System.out.print("How many drawings: ");
            try{   
                drawings = sc.nextInt();
            } catch(Exception e){
                System.out.println("Invalid\n");
                continue;
            }
            if(drawings > 0 && drawings < 101){
                break;
            } else {
                System.out.println("Invalid\n");
            }
        }

        System.out.println("Drawing started");
        int cnt = 0;
        for(int i = 1; i<= drawings; i++){
            generate(generated, 6);
            System.out.printf("Drawing %d: [", i);
            for(int j : generated){
                System.out.print(j + " ,");
            }
            System.out.print("]: ");
            sort(generated,6);
            if(drawing(input, generated) == 1){
                cnt ++;
            }
        }
        System.out.printf("You won %d games!", cnt);
        sc.close();
    }



    public static int drawing(int[] input, int[] generated){
        int temp;
        int cnt = 0;
        boolean[] matches = {false,false,false,false,false,false,false};
        for(int i = 0; i < 7; i++){
            temp = find(generated, input[i], 6);
            if(temp != -1){
                matches[i] = true;
                cnt++;
            }
        }
        if(cnt>0){
            System.out.print("Matching [");
            for(int i = 0; i< 7; i++){
                if(matches[i]){
                    System.out.print(input[i] + " ");
                }
            }
            System.out.print("]");
            if(matches[6]){
                System.out.printf(" and bounus [%d]. ",input[6]);
                cnt++;
            }
        } else {
            System.out.println("No matching numbers. Lose");
            return 0;
        }
        if(cnt>6){
            System.out.println("All matches. 1st prize");
            return 1;
        }
        if(cnt>5 && matches[6]){
            System.out.println("2nd prize");
            return 1;
        }
        if(cnt>5){
            System.out.println("3rd prize");
            return 1;
        }
        if(cnt>4){
            System.out.println("4th prize");
            return 1;
        }
        if(cnt>3){
            System.out.println("5th prize");
            return 1;
        }

        System.out.println(" Lose. ");
        return 0;
    }

    public static void sort(int[] generated, int cnt){
        Arrays.sort(generated);
    }

    public static void generate(int[] generated, int cnt){
        Random rand = new Random();
        int temp;
        for(int i = 0; i < cnt; i++){
            temp = rand.nextInt(45)+1;
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