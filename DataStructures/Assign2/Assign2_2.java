package DataStructures.Assign2;

public class Assign2_2{
    public static void main(String[] args){
        String in = "([)]";
        int i = 0;
        while (i<in.length()-1){
            if(in.charAt(i) == '('){
                if(in.charAt(i+1) != ')'){
                    System.out.println("False");
                    return;
                }
            } else if (in.charAt(i) == '['){
                if(in.charAt(i+1) != ']'){
                    System.out.println("False");
                    return;
                }
            } else if (in.charAt(i) == '{'){
                if(in.charAt(i+1) != '}'){
                    System.out.println("False");
                    return;
                }
            } else {
                System.out.println("False");
            }
            i += 2;
        }
        System.out.println("True");
    }
}
