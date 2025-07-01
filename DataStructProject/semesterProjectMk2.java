package DataStructProject;
public class semesterProjectMk2 {
    public static void main(String[] args){
        for(int n = 3; n<17; n++){
            //int n = 16;
            long timeStart = System.nanoTime(); 
            int upperBound = 0;
            for(int i = 2*n-2; i>=0; i-=2){
                upperBound += Math.pow(2,i);
            }
            int lowerBound = (int) (Math.pow(2,n))-1;
            int total = 0;
            String num;
            int count;
            int counted = 0;
            boolean valid;

            for(int i = lowerBound; i<= upperBound; i+=2){
                counted++;
                valid = true;
                num = Integer.toString(i,2);
                count = (2*n)-num.length();
                for(int j = 0; j<num.length(); j++){
                    if(num.charAt(j) == '0'){
                        count++;
                    } else {
                        count--;
                    }
                    if(count<0){
                        valid = false;
                        break;
                    }
                }
                if(valid && count == 0){
                    //System.out.println(num + "  " + i);
                    total++;
                }
            }
            System.out.println("\n\n" + total);
            System.out.println("counted: " + counted);
            long timeEnd = System.nanoTime();
            System.out.println(n);
            System.out.println(((double)(timeEnd-timeStart)) /1000000000);
        }
    }
}
