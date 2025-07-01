package DataStructures.Assign2;

public class Assign2_4 {
    public static void main(String[] args){    
        String tree="{1,#,2,3}";
        String numberOnly= tree.replaceAll("[#]", "");
        for(int i = 0; i<numberOnly.length()-1; i++){
            if(numberOnly.charAt(i) == ',' && numberOnly.charAt(i+1) == ','){
                numberOnly = numberOnly.substring(0, i) + numberOnly.substring(i+1);
                i--;
            }
        }
        numberOnly = numberOnly.substring(1, numberOnly.length()-1);
        numberOnly = numberOnly.replaceAll("[,]","][");
        System.out.println("[[" + numberOnly + "]]");
    }
}