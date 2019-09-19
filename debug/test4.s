.name "Test4 - ldi"
.comment ""

test_1:
ld 0, r2
st r2, 100
live %0
zjmp %100
