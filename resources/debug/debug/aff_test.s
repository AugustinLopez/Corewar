.name "Test aff and the carry modif"
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
# Should not jump because carry value is 0, aff don't modify carry
# Should retrieve the "l" and display it
ld -17, r2
st r2, 500
aff r2
zjmp %100

test_2:
# Should not jump because carry value is 0, aff don't modify carry
# Should retrieve the "o" and display it
ld -40, r2
st r2, 500
aff r2
zjmp %100

test_4:
# Should jump now because add modified carry to 1
add r6, r6, r6
zjmp %1000
