.name "Test - sti "
.comment ""

ld %1, r1
ld %2, r2
ld %160, r3
ld %4, r4
ld 1, r5
ld -100, r6

# REG, REG, REG avec valeurs directes dans 2eme et 3eme arg
test_1:
sti r1, r2, r3

# REG, REG, REG avec valeurs indirectes dans 2eme et 3eme arg
test_2:
sti r1, r5, r6

# REG, DIR, REG avec valeur directe dans 3eme arg
test_3:
sti r2, %500, r1

# REG, DIR, REG avec valeur indirecte dans 3eme arg
test_4:
sti r2, %400, r5

# REG, IND, REG avec valeur directe dans 2eme arg
test_5:
sti r4, 10, r1

# REG, IND, REG avec valeur indirecte dans 2eme arg
test_6:
sti r4, 10, r6

# REG, REG, DIR avec valeur directe dans 2eme arg
test_7:
sti r1, r1, %250

# REG, REG, DIR avec valeur indirecte dans 2eme arg
test_8:
sti r1, r5, %50

# REG, DIR, DIR
test_9:
sti r2, %150, %50

# REG, IND, DIR
test_10:
sti r3, -1000, %50
