.name "Test aff"
.comment ""

test_1:
ld 0, r2
st r2, 100
live %0
zjmp %100

# Should show Lol and not jump cause 
ld %76, r3
ld %111, r4
ld %108, r5
aff r3
# to slow display for zaz vm : fork %100
aff r4
# to slow display for zaz vm : fork %100
aff r5
zjmp %100

# Should jump cause carry value is 1
aff r2
zjmp %100
