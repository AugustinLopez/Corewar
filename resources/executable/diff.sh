echo  "OUR   : \\c"
../../asm $1.s
hexdump -C $1.cor > OUR_DUMP
rm $1.cor
echo  "THEIR : \\c"
./asm $1.s
hexdump -C $1.cor > THEIR_DUMP
rm $1.cor
diff OUR_DUMP THEIR_DUMP
rm OUR_DUMP THEIR_DUMP
