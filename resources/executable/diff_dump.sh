# Bebug script to compare the output of the two vm from DUMP_START and for each DUMP_STEP after that.
# There should be no diff.

if ((("$#" < 4 )) || (( "$#" > 6 )))
then
	echo "Usage: sh diff_dump.sh [DUMP_STEP] [DUMP_START] [champion1.cor] [champion2.cor] ... (up to four champions)"
	exit
fi

OUR_DUMP=0
THEIR_DUMP=0
i=$2
while [ $i -lt 10000000 ]
do
	../../corewar -dump $i $3 $4 $5 $6 > OUR_DUMP
	./corewar -d $i $3 $4 $5 $6 > THEIR_DUMP
	if diff OUR_DUMP THEIR_DUMP > /dev/null; then
		echo "No diff, dump is |$i|"
	else
		echo "\nDiff at dump |$i| !"
		echo "OUR_DUMP is on top, THEIR_DUMP is on bottom\n"
		diff OUR_DUMP THEIR_DUMP
		rm OUR_DUMP THEIR_DUMP
		exit
	fi
	i=$((i + $1))
done
rm OUR_DUMP THEIR_DUMP
