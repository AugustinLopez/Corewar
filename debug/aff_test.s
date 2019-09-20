.name "Test aff"
.comment ""

test_1:
# Should show Lol and not jump cause carry value is 0
ld %76, r3
ld %111, r4
ld %108, r5
aff r3
# to slow display for zaz ===> vm : fork %100
aff r4
# to slow display for zaz ===> vm : fork %100
aff r5
zjmp %100

test_2:
# Should not jump cause carry value is 0, aff don't modify carry
ld 0, r2
aff r2
zjmp %100

test_3:
# Should jump cause carry value is 1, add modify carry to 1
add r6, r6, r6
zjmp %1000
