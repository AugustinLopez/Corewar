.name "Test ldi and lldi"
.comment ""

#CAS REG REG REG
# Should expect on line 0x0200 and 0x0240 :
# 54 02 03 04 00 02 03 04 03 00 54 02 03 04

ld %0, r2
ld 16, r3
ldi r2, r3, r4
st r4, 495
live %1

ld %0, r2
ld 528, r3
ldi r2, r3, r4
st r4, 473
live %2

ld %0, r2
ld -550, r3
ldi r2, r3, r4
st r4, 451
live %1

lld %4097, r2
lld %8192, r3
lldi r2, r3, r4
st r4, 476
live %1

ld %0, r2
ld 528, r3
lldi r2, r3, r4
st r4, 454
live %2

ld %0, r2
ld -550, r3
lldi r2, r3, r4
st r4, 432
live %1

#CAS REG DIR REG
# Should expect on line 0x0280 : 64 02 00 01 00 02 00 02 04 00 64 02 00 01
# Should expect on line 0x02c0 : 64 02 00 00 00 02 00 02 04 00 64 02 00 01

ld %0, r2
ld 16, r3
ldi r2, %1, r4
st r4, 458
live %1

ld %0, r2
ld 528, r3
ldi r2, %2, r4
st r4, 435
live %2

ld %0, r2
ld -550, r3
ldi r2, %1, r4
st r4, 412
live %1

lld %4097, r2
lld %8192, r3
lldi r2, %0, r4
st r4, 436
live %1

ld %0, r2
ld 528, r3
lldi r2, %2, r4
st r4, 413
live %2

ld %0, r2
ld -550, r3
lldi r2, %1, r4
st r4, 390
live %1

#CAS IND __ REG
# Should expect on line 0x0300 : 00 00 04 03 00 03 02 04 03 00 54 02 03 04
live %1
live %2
ld %0, r2
ld 16, r3
ldi 3, %0, r4
st r4, 405

live %1
live %2
ld %0, r2
ld 16, r3
ldi 3, r2, r4
st r4, 377

# Here we write the 4 bytes starting frome 0x0201 : 54 02 03 04
live %1
live %89
ld %0, r2
ld 16, r3
## Retrieve the number 89 + 0 => go to pc + 89 and store in r4 the value
ldi -16, r2, r4 
st r4, 349

live %1
live %1656 #312
ld %0, r2
ld 16, r3
## Retrieve the number 1853 + 0 => go to pc + 1853 and store in r4 the value
## Should get the 4 bytes starting at 0x0901
ldi -16, r2, r4
st r4, 370
