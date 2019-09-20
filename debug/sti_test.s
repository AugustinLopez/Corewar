.name "Test - sti"
.comment ""

# WORKS OK
test_1:
ld %10, r1
ld %20, r2
sti r3, r1, r2

# WORKS OK
test_2:
sti r1, 0, %10

# WORKS OK
test_3:
sti r1, %20, %50

# DONT WORK
test_3:
ld 1, r4
ld 2, r5
sti r6, r4, r5
