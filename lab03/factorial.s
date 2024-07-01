.globl factorial

.data
n: .word 3

.text
main:
    la t0, n
    lw a0, 0(t0) # a0 = n = 8
    jal ra, factorial

    addi a1, a0, 0 # return value in a0
    addi a0, x0, 1 # print return value
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    addi t0, x0, 1
    beq a0, t0, exit
    addi sp, sp, -8
    sw a0, 0(sp)
    sw ra, 4(sp)
    addi a0, a0, -1 # fun(n-1)
    jal factorial
    mv t1, a0 # return value
    lw a0, 0(sp)
    lw ra, 4(sp)
    addi sp, sp, 8
    mul a0, a0, t1
    jr ra
    
exit:
    addi a0, x0, 1
    jr ra
    
