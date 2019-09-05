addi $t0, $t0, 3
sw $t0, 100($sp)
lw $t1, 100($sp)
subi $t1, $t1, 1
sw $t1, 50($zero)
lw $t2, 50($zero)
add $t3, $t0, $t2