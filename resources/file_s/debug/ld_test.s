.name "Test 1 - Carry"
.comment ""

# ld %0: carry == 1 (if register is valid)
# not 0: carry == 0
begin:
#fork %17
ld 100, r2
st r2, 50
#fork %-18
st r1, 95

wall:
live %0
live %0
live %0
live %0
live %0
live %0
live %0
live %0
live %0
live %0

#end:
#zjmp %-53


lld -2047, r3
lld 2052, r4
st r3, 300
st r4, 320
