#use bash instead of sh
if [ $# -lt 1 ]
then
	echo "$0 : You must give/supply one directory name"
	exit 1
fi

if [ $# -ne 1 ]
then
	SIMTHRES=$2
else
	SIMTHRES=0.7
fi
echo "Threshold " $SIMTHRES

find $1 -name "* *" -type f | rename 's/ /_/g'

echo -n "" > dlist.txt
for f in $1/*;do if [[ -d $f  ]]; then echo $f >> dlist.txt;fi; done;
dirarray=( `cat dlist.txt | tr '\n' ' '`)
echo ${#dirarray[@]}

N=${#dirarray[@]}
#echo $N
#generating tokens for all assignments
for (( i = 0; i<N ; i++ ))
do
	#listing all .c and .h files in list.txt
	find ${dirarray[$i]} -type f | sed 's/ /\\ /g' | xargs ls -ldt | awk -F' ' '{print $9}' | grep .c$ > list.txt
	find ${dirarray[$i]} -type f | xargs ls -ldt | awk -F' ' '{print $9}' | grep .h$ >> list.txt
	status=$?
	if [[ $status -eq 0 ]]
	then
		filearray=( `cat list.txt | tr '\n' ' '`)
		M=${#filearray[@]}
	
		#retriving directory name
		n1=`echo ${dirarray[$i]} | awk -F'/' '{print $NF}'`
		echo -n "" > t#$n1.txt
	
		for (( j = 0; j<M ; j++ ))
		do
			sh removeComments1.sh ${filearray[$j]} > p$n1
			./lexer < p$n1 >> t#$n1.txt
		
		done
		rm p$n1
		#echo "tokenization done for " $n1
	else
		echo "$status error for" ${dirarray[$i]}
	fi
done

echo "comparision starting"
for (( i = 0; i<N ; i++ ))
do
	n1=`echo ${dirarray[$i]} | awk -F'/' '{print $NF}'`
	for (( j = i + 1; j<N ; j++ ))
	do
		n2=`echo ${dirarray[$j]} | awk -F'/' '{print $NF}'`
		./compare t#$n1.txt t#$n2.txt $SIMTHRES
	done
done
rm t#*.txt
rm dlist.txt
rm list.txt

echo "*** CHEATING IS A CHOICE NOT A MISTAKE ***"
