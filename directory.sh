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

ls $1/*.c > list.txt
filearray=( `cat list.txt | tr '\n' ' '`)

N=${#filearray[@]}
echo $N " files"
for(( i = 0; i<N ; i++ ))
do
	#Extracting file names
	n1=`echo ${filearray[$i]} | awk -F'/' '{print $NF}'`
	#Removing Comments and preprocessing
	sh removeComments1.sh ${filearray[$i]} > p$n1
	#Tokenizing
	./lexer < p$n1 > t#$n1.txt
	rm p$n1
done

for (( i = 0; i<N ; i++ ))
do
	n1=`echo ${filearray[$i]} | awk -F'/' '{print $NF}'`
	
	for (( j = 0; j<N ; j++ ))
	do
		if [ $i -eq $j ]
		then
			continue
		fi
		
		#Extracting file names
		n2=`echo ${filearray[$j]} | awk -F'/' '{print $NF}'`
		#Comparing
		./compare t#$n1.txt t#$n2.txt $SIMTHRES
	done
done

rm t#*.txt
rm list.txt

echo "*** CHEATING IS A CHOICE NOT A MISTAKE ***"
