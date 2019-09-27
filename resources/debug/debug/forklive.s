.name "Test 1 - Carry"
.comment ""

# ld %0: carry == 1 (if register is valid)
# not 0: carry == 0
begin:
lfork %500
lldi r1, r2, r3
lldi r1, r2, r3
lldi r1, r2, r3
lldi r1, r2, r3
lldi r1, r2, r3
lldi r1, r2, r3
lldi r1, r2, r3
lldi r1, r2, r3
lldi r1, r2, r3
lldi r1, r2, r3
st r1, 1000
st r1, 1000
st r1, 1000
st r1, 1000
st r1, 1000
