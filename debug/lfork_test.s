.name "Test 3 - Fork"
.comment ""

# ld %0: carry == 1 (if register is valid)
# not 0: carry == 0
begin:
ld %0, r2
lfork %1024
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
