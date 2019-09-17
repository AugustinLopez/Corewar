.name "Smelly cheese"
.comment "Do you know what a 6-pool is ?"

tremplin:
ld %151106560, r2
ld %57672705, r3
ld %151107840, r4

carry:
ld %0, r7

jump:
zjmp %511

padding:
zjmp %508
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
live %0

second_jump:
zjmp %118

second_wall:
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
live %0
live %0
live %0

third_jump:
st r4, 511
st r3, 504
st r2, 504
zjmp %494
