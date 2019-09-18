.name "Test 1 - Carry"
.comment ""

# ld %0: carry == 1 (if register is valid)
# not 0: carry == 0
begin:
fork %21
aff r1
aff r1
ld 100, r2
st r2, 50
fork %-18
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

end:
zjmp %-53
