.data   
i:      .word   0
j:      .word   1
A:      .word   1, 2, 3
B:      .word   4, 5, 6

.text   
    # =============================== #
    # 3.1.
    # if (i < j)
    #   A[i]++;
    # else
    #   B[j]--;
main:   
    lw      $t0,        i                       # put i into $t0
    lw      $t1,        j                       # put j into $t1
    blt     $t0,        $t1,        less        # if less than, go to less
    
    la	    $t2,        B			# load address of B
    sll     $t3,        $t1,        2           # get offset of j
    add     $t2,        $t3,        $t2         # add offset to index to get B[j]
    lw      $t3,        0($t2)                  # load B[j] into $t3
    addi    $t3,        $t3,        -1          # decrement B[j] by 1
    sw      $t3,        0($t2)                  # store value back at B[j]
    j       end

less:   
    la	    $t2,        A			# load address of A
    sll     $t3,        $t0,        2           # get offset of i
    add     $t2,        $t3,        $t2         # add offset to index to get A[i]
    lw      $t3,        0($t2)                  # load A[i] into $t3
    addi    $t3,        $t3,        1           # increment A[i] by 1
    sw      $t3,        0($t2)                  # store value back at A[i]

end:    

.text   
    # =============================== #
    # 3.2.
    # A[i] = A[i+1] + B[3]
main:   
    lw      $t0,        i                       # put i into $t0
    addi    $t2,        $t0,        1           # increment i by 1 and store in $t2

    lw      $t3,        4($s0)                  # load A[i + 1] into $t3
    lw      $t4,        12($s1)                 # load B[3] into register $t3
    add     $t5,        $t3,        $t4         # A[i + 1] + B[3] stored in $t5

    lw      $t5,        0($s0)                  # store result in $t5

.text   
    # =============================== #
    # 3.3.
    # for( int i = 0; A[i] > B[i]; i++ ) {
    #   A[i] += B[i + 1];
    # }
main:   
    lw      $t0,        i                       # put i into $t0
    j       loop                                # jump to loop

loop:   
    lw      $t1,        0($s0)                  # load A[i] into $t1
    lw      $t2,        0($s1)                  # load B[i] into $t2
    bgt     $t1,        $t2,        end         # if $t0 <= $t1 then goto end

    lw      $t3,        4($s1)                  # load B[i + 1] into $t3
    lw      $t4,        0($s0)                  # load A[i] into $t4
    add     $t4,        $t3,        $t4         # A[i] += B[i + 1] into $t4
    sw      $t4,        0($s0)                  # store $t4 back at A[i]

    addi    $t0,        $t0,        1           # i++

    j       loop                                # jump to loop

end:    

    # ============================================================== #
.data   
arr:    .word   1, 2, 3, 4, 5, 6, 7, 8, 9, 10

.text   
    # =============================== #
    # 5.
    # a lot of c code

main:   
    la      $s0,        arr                     # load the address of arr into $s0

    jal     test
    #      assume,     your,       program,        is, done, here,
test:   
    #      write,      your,       instructions,   here,
    jal     findSum
    #      write,      your,       instructions,   here,
    jr      $ra
findSum:
    lw      $v0,        0                       # for returning sum
    li      $t0,        0                       # for the value of i
    li      $t1,        10                      # CONSTANT FOR `size` OF THE ARRAY. :TODO CHANGE THIS LATER
    j       loop
    #      write,      your,       instructions,   here,
    jr      $ra

loop:   
    bge     $t0,        $t1,        loop_end    # check if i >= size

    lw      $t2,        0($s0)                  # load arr[i] into $t2
    add     $v0,        $v0,        $t2         # add arr[i] to sum

    addi    $t0,        $t0,        1           # i++
    addi    $s0,        $s0,        4           # move to the next element in arr

    j       loop                                # loop again

loop_end:
    jr      $ra                                 # jump to $ra

