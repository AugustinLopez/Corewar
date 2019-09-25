#Executer avec la boucle de la fonction coreward dans le main.
#Supprimer l'affichage des couleurs, des process et des joueurs

OUR=0
THEIR=0
DIFF=0
i=1530 ##Carrefull 0 won't work here
if [ "$#" -ne "4" ]
then
	echo "Usage : ./diff_dump_x dump_test_value last_dump_value champion1.cor champion2.cor"
	exit
fi
while [ $i -lt $2 ]
do
	./corewar -dump $i $3 $4 > OUR
	./resources/corewar -d $i $3 $4 > THEIR
	if diff OUR THEIR > /dev/null; then
		echo " No diff, dump $i"
	else
		echo " !!! Diff at dump $i !!!"
		echo " OUR is on top, THEIR is on the bottom"
		diff OUR THEIR
		exit
	fi
	rm OUR THEIR
	i=$((i + $1))
done
