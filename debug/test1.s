.name "Test - Live"
.comment ""

test_1:
st r1, 6
live %0
# Live increase by 1 for the player. The ID of the player is set in the VM

test_2:
st r1, 518
live %0
# live increase by 1 for the player. Because of IDX_MOD
zjmp %100
# st does not modify the carry value. Carry == 0

test_3:
ld 0, r2
# 0 is the position of ld. The loaded value is not 0, carry == 0
st r2, 100
zjmp %100

test_4:
# The loaded value is 0, carry == 1
ld %0, r2
st r2, 100
# st does not modify the carry, so zjmp works.
zjmp %1
live %0

test_5:
# The loaded value is 0, carry == 1
ld 0, r2
st r2, 100
# st does not modify the carry, so zjmp works.
zjmp %100
