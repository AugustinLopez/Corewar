.name "Test4 - ldi"
.comment ""

ld 8, r1
ld %-10, r2
ld 7, r3

#					CAS REG REG REG
# 					OK avec DIR et IND dans registres
#test_1:
#ldi r1, r2, r3
#st r3, 150
#zjmp %300

#					CAS IND __ REG
# 					OK avec DIR et IND dans registres
#test_2:
ldi 10, r1, r3
#ldi 0, r2, r3
st r3, 2
st r2, 10
zjmp %300

#					CAS DIR __ REG
# 					
#test_2:
#ldi 10, r2, r3
#ldi 10, 20, r3
#st r3, 150
#zjmp %300
