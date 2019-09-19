.name "Test2 - Operation"
.comment ""

test_1:
ld %1, r2
ld %1, r3
add r2, r3, r4
zjmp %100
add r5, r5, r5
zjmp %100
