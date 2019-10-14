#!/bin/zsh

remove=1

test_file_error () {
	echo "Test Numero : $i"
	echo "\033[33mOur ASM\033[0m"
	name=${fichier%.s}
	name+=.cor
	$EXEC/asm $fichier
	if [ -e $name ]; then fail="KO"; else fail=""; fi
	if [ $remove -eq 1 ]; then rm -f $name; fi
	echo "\033[33mProvided ASM\033[0m"
	./asm_r $fichier
	if [ $remove -eq 1 ]; then rm -f $name; fi
	if [ "$fail" != "" ];
	then
		printf "%-70s\033[31mKO\033[00m\n";
	else
		printf "%-70s\033[32mOK\033[00m\n";
	fi;
	echo
}

test_file_valid () {
	echo "Test Numero : $i"
	name=${fichier%.s}
	name+=.cor
	$EXEC/asm $fichier > /dev/null
	if [ -e $name ]; then hexdump -C $name > ours; fi
	if [ $remove -eq 1 ]; then rm -f $name; fi
	./asm_r $fichier > /dev/null
	hexdump -C $name > real
	if [ $remove -eq 1 ]; then rm -f $name; fi
	DIFF=$(diff -N ours real)
	if [ "$DIFF" != "" ]
	then
		mkdir -p error_test 2> /dev/null || true
		dif="error_test/valid$i.diff"
		diff -N -y ours real > $dif
		if [ -e ours ]; then mv ours error_test/"valid$i-ours"; fi
		mv real error_test/"valid$i-real"
		echo "Création du fichier $dif\033[00m"
		printf "%-70s\033[31mKO\033[00m\n\n" $fichier
	else
		rm -Rf ours real
		printf "%-70s\033[32mOK\033[00m\n\n" $fichier
	fi
}

test_file_perso () {
	echo "Test Numero : $i"
	echo "\033[33mOur ASM\033[0m"
	$EXEC/asm $fichier
	name=${fichier%.s}
	name+=.cor
	if [ -e $name ]; then hexdump -C $name > ours; fi
	if [ $remove -eq 1 ]; then rm -f $name; fi
	echo "\033[33mProvided ASM\033[0m"
	./asm_r $fichier
	if [ -e $name ]; then hexdump -C $name > real; fi
	if [ $remove -eq 1 ]; then rm -f $name; fi
	if [ -e ours -o -e real ]; then DIFF=$(diff -N ours real); else DIFF=""; fi
	if [ "$DIFF" != "" ]
	then
		mkdir -p error_test 2> /dev/null || true
		dif="error_test/perso$i.diff"
		diff -N -y ours real > $dif
		if [ -e ours ]; then mv ours error_test/"perso$i-ours"; fi
		if [ -e real ]; then mv real error_test/"perso$i-real"; fi
		echo "Creating diff file: $dif\033[00m"
		printf "%-70s\033[31mKO\033[00m\n\n" $fichier
	else
		rm -Rf ours real
		printf "%-70s\033[32mOK\033[00m\n\n" $fichier
	fi
}

rm -Rf ./error_test
clear
read -e -p 'Executables path : ' EXEC
clear
while :
do
	clear
	echo " ---------------------------------"
	echo "| 1.Test_Error 2.Test_Valid |\n
		| 3.Your_file 4.Your_folder |\n
		| 5.Change_path 0.Exit |" | column -t
	echo " ---------------------------------"
	read INPUT
	case $INPUT in
		1)
			clear
			i=1
			for fichier in ./tests_asm/error/*.s
			do
				test_file_error
				i=$((i+1))
			done
			read -p "Press return to continue..." ;;
		2)
			clear
			i=1
			for fichier in ./tests_asm/valid/*.s
			do
				test_file_valid
				i=$((i+1))
			done
			read -p "Press return to continue..." ;;
		3)
			clear
			i=0
			read -p "File to test: " -e fichier
			test_file_perso
			read -p "Press return to continue..." ;;
		4)
			clear
			i=1
			read -p "Directory to test: " -e DIR
			DIR+=/*.s
			clear
			for fichier in $DIR
			do
				test_file_perso
				i=$((i+1))
			done
			read -p "Press return to continue..." ;;
		5)
			clear
			echo "Current path: $EXEC"
			read -e -p 'New path : ' EXEC ;;
		0)
			break ;;
	esac
done
clear
