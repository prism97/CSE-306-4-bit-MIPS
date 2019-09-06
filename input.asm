addi $t1, $t1, 5
sll $zero, $t1, 2
srl $zero, $t1, 2
addi $t0, $t0, 3
subi $sp, $sp, 25
sw $t0, 0($sp)
lw $t1, 0($sp)
subi $t1, $t1, 1
sw $t1, 50($zero)
lw $t2, 50($zero)
add $t3, $t0, $t2
subi $sp, $sp, 1
sw $t1, 4($sp)
nor $t1, $t3, $t3
ori $t4, $t4, 5
add $t1, $t4, $t3
sub $t4, $t1, $t3
beq $t1, $t4, 2
bneq $t1, $t4, 2
lw $t3, 15($zero)
add $t1, $t1, $t2
j 2