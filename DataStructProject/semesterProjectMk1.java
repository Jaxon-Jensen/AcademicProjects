package DataStructProject;
public class semesterProjectMk1 {
    public static void main(String[] args){
        for(int n = 3; n<17; n++){
        //int n = 16;
        long timeStart = System.nanoTime(); 
        long total = 0;
        String num;
        long count;
        long counted = 0;
        boolean valid;

        for(long i = 0; i<= Math.pow(2,2*n); i++){
            counted++;
            valid = true;
            num = Long.toString(i,2);
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
