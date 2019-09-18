.name "Test 1 - Carry"
.comment ""

# ld %0: carry == 1 (if register is valid)
# not 0: carry == 0
begin:
ld %0, r2
ld %1, r13
zjmp %53

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
