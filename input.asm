addi $t0, $zero, 5
add $t1, $zero, $t0
bneq $t0, $t1, 1
j 5
j 0
sll $t0, $t0, 2 
srl $t0, $t0, 2
beq $t0, $t1, 1
j 0
or $t2, $t0, $t1
ori $t2, $t2, 0
andi $t2, $t2, -1
and $t2, $t0, $t1
subi $t2, $t2, 5
sub $t2, $t1, $t2
bneq $t2, $zero, 1
j 0 
sw $t1, 100($t0)
lw $t2, 100($t0)
beq $t2, $t1, 1
j 0
nor $t0, $t0, $t0
and $t2, $t1, $t0
addi $t4, $zero, 120
addi $t3, $zero, -120
sw $t4, 0($sp)
addi $sp, $sp, -1
sw $t3, 0($sp)
addi $sp, $sp, -1
lw $t1, 1($sp)
lw $t2, 2($sp)
beq $t1, $t1, -32
