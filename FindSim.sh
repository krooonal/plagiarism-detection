if [ $# -lt 2 ]
then
	echo "$0 : You must give/supply two programs"
	exit 1
fi

find $1 -name "* *" -type f | rename 's/ /_/g'

#Extracting file names
n1=`echo $1 | awk -F'/' '{print $NF}'`
n2=`echo $2 | awk -F'/' '{print $NF}'`

#echo "removing comments"
sh removeComments1.sh $1 > p$n1
sh removeComments1.sh $2 > p$n2

#Tokenizing
./lexer < p$n1 > t$n1.txt
./lexer < p$n2 > t$n2.txt

#Comparing
if [ $# -eq 3 ]
then
	./compare t$n1.txt t$n2.txt $3
else
	./compare t$n1.txt t$n2.txt
fi

rm t$n1.txt t$n2.txt p$n1 p$n2
echo "*** CHEATING IS A CHOICE NOT A MISTAKE ***"
