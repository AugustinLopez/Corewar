if ((("$#" < 2 )) || (( "$#" > 4 )))
then
	echo "Usage: sh diff_at_end.sh [champion1.cor] [champion2.cor] ... (up to four champions)"
	exit
fi

OUR_DUMP=0
THEIR_DUMP=0
../../corewar $1 $2 > OUR_DUMP
echo "...OUR_DUMP created..."
./corewar $1 $2 > THEIR_DUMP
echo "...THEIR_DUMP created..."
if diff OUR_DUMP THEIR_DUMP > /dev/null; then
	echo "No diff at the end."
	rm OUR_DUMP THEIR_DUMP
else
	echo "Diff at the end !"
	echo "OUR_DUMP is on top, THEIR_DUMP is on bottom\n"
	diff OUR_DUMP THEIR_DUMP
	rm OUR_DUMP THEIR_DUMP
	exit
fi
