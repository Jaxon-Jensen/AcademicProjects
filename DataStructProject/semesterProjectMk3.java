package DataStructProject;
public class semesterProjectMk3 {// #22 generate parentheses
    public static void main(String[] args){
        long start;
        long end;
        for(int n = 1; n<20; n++){
        start = System.nanoTime();
        boolean valid = true;
        //int n = 5; 
        int sum = 0;
        long counted = 0;
        long max = 0, temp = 0, count = 1;
        long current = (int) Math.pow(2,n) - 1;
        String Scurrent;
        //String out;
        
        
        for(int i = 2*n-2; i>=0; i-=2){
            max += Math.pow(2,i);
        }
        /*for(int i = 0; i < n; i++){
            System.out.print("(");
        }
        for(int i = 0; i < n; i++){
            System.out.print(")");
        }*/
        //System.out.println();
        while(current < max){
            counted++;
            temp = (current | (current-1)) + 1;
            current = temp | ((((temp & ~temp+1) / (current & ~current+1)) >>> 1) - 1);
            Scurrent = Long.toString(current,2);
            if(Scurrent.charAt(Scurrent.length()-1) != '0'){
                sum = (2*n)-Scurrent.length();
                valid = true;
                for(int j = 0; j<Scurrent.length(); j++){
                    if(Scurrent.charAt(j) == '0'){
                        sum++;
                    } else {
                        sum--;
                    }
                    if(sum<0){
                        valid = false;
                        break;
                    }
                }
                if(valid){
                    count++;

                    /*for(int i = 0; i < 2*n-Scurrent.length(); i++)
                    System.out.print("(");
                    out = Scurrent.replaceAll("0","(");
                    out = out.replaceAll("1", ")");
                    System.out.println(out);*/
                }
            }
        }
        System.out.println("\n" + n);
        System.out.println("count: "+count + "     counted: " + counted);
        end = System.nanoTime();
        System.out.println("Seconds: " + (end-start)/1000000000.0);
    }
    }
}
