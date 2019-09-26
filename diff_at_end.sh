#Executer avec la boucle de la fonction corewar dans le main.
#Supprimer l'affichage des couleurs, des process et des joueurs

OUR=0
THEIR=0
DIFF=0
if [ "$#" -ne "2" ]
then
	echo "Usage : ./diff_at_end.sh champion1.cor champion2.cor"
	exit
fi
./corewar $1 $2 > OUR
echo "...OUR created..."
./resources/corewar $1 $2 > THEIR
echo "...THEIR created..."
if diff OUR THEIR > /dev/null; then
	echo "No diff at end"
	rm OUR THEIR
else
	echo "!!! Diff at end !!!"
	echo "OUR is on top, THEIR is on the bottom"
	diff OUR THEIR
	rm OUR THEIR
	exit
fi
