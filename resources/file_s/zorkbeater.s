.name "zorkbeater"
.comment "having a fight with zork"

start:
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0
st r1, 6
live %0

work:
ld %50331648, r4       #03 00 00 00
ld %1879375874, r5     #70 05 00 02
ld %445, r6            #jumper
ld %1879310785, r10
ld %1879376317, r11
st r4, 449
st r10, 445
st r4, 444
st r11, 440
fork %:looplive
st r1, 6
live %0
fork %:kroz
ld %83887619 ,r5       #50 00 06 03
ld %0, r16
zjmp %221

kroz:
ld %1879375874, r5     #70 05 00 02
ld %0, r16
zjmp %200

looplive:
sti r1, %:live, %1
ld %0, r16

live: 
live %1
zjmp%:live
