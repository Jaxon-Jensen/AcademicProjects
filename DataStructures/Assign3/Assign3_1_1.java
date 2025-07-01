public class Assign3_1_1 {
    public static void main(String[] args){
        int[] table = new int[10];
        
        table = insertHash(69, table);
        table = insertHash(48, table);
        table = insertHash(139, table);
        table = insertHash(648, table);
        table = insertHash(109, table);
        table = insertHash(75, table);

        for(int i = 0; i<9; i++){
            System.out.print(table[i] + ", ");
        }
        System.out.println(table[9]);
    }
    public static int[] insertHash(int x, int[] table){
        int i = 0;
        while(i<10){
            if(table[(x+(i*i))%10] == 0){
                table[(x+(i*i))%10] = x;
                break;
            }
            i++;
        }
        return table;
    }
}
