addi $t1, $t1, 2
sw $t1, 100($zero)
addi $t0, $t0, 3
sw $t1, 0($sp)
sw $t0, 4($sp)
subi $sp, $sp, 4
sw $t0, 4($sp)
lw $t3, 0($sp)
sub $t3, $t3, $zero
