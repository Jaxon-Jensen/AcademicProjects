package ComputerArchitecture;

public class test {
    public static void main(String[] args) {
        int i = -1;
        if(i){
            System.out.println("true");
        }
    }
}


/*
li $t0, 0
la $t1, input
li $v0, 1
printInput:
bgt $t0, 6, endPrintInput
lw $a0, ($t1)
syscall
addi $t0, $t0,1
addi $t1, $t1,4
j printInput
endPrintInput:

*/