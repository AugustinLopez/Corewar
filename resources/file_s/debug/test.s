.name "Testing"
.comment ""

# ld %0: carry == 1 (if register is valid)
# not 0: carry == 0
lfork %250
#live %0
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
add r1, r2, r3
or r1, r2, r3
or r1, r2, r3
st r1, 6
live %0
#st r1, 200
#st r1, 300
#lfork %0
#lldi r1, r2, r3
#lldi r1, r2, r3
#lldi r1, r2, r3
#lldi r1, r2, r3
#lldi r1, r2, r3
#lldi r1, r2, r3
#lldi r1, r2, r3
#lldi r1, r2, r3
#lldi r1, r2, r3
#lldi r1, r2, r3
#add r1, r2, r3
#or r1, r2, r3
#st r1, 200
#st r1, 300
