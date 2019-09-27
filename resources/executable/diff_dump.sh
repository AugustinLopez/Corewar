#Executer avec la boucle de la fonction corewar dans le main.
#Supprimer l'affichage des couleurs, des process et des joueurs

OUR=0
THEIR=0
DIFF=0
i=$2 ##Carrefull 0 won't work here
#if [ "$#" -ne "5" ]
#then
#	echo "Usage : ./diff_dump.sh dump_step_value dump_start_value champion1.cor champion2.cor"
#	exit
#fi
while [ $i -lt 100000 ]
do
	./corewar -dump $i $3 $4 $5 $6> OUR
	./resources/corewar -d $i $3 $4 $5 $6 > THEIR
	if diff OUR THEIR > /dev/null; then
		echo "No diff, dump $i"
	else
		echo "!!! Diff at dump $i !!!"
		echo "OUR is on top, THEIR is on the bottom"
		diff OUR THEIR
		exit
	fi
	rm OUR THEIR
	i=$((i + $1))
done
