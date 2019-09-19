.name "Test3 - binary"
.comment ""

test_1:
ld %1, r2
ld %1, r3
and %2, -5, r4
st r4, 100
zjmp %100
