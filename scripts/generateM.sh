# !/bin/bash

snRNA="$1"
methyl="$2"
TFA="$3"
expression="$4"
output="$5"

echo $snRNA
echo $methyl
echo $TFA
echo $expression
echo $output

if [ ! -d $output ]
then
		mkdir -p $output
		chmod 777 $output
fi

ls $output

if [ -s "$methyl" ]
then
	echo "in 0st if"
	paste <(awk '{print $1}' $methyl | awk -F. '{print $1}') <(awk '{$1="";print}' $methyl) > temp2 && mv temp2 $methyl
fi

if [ -s "$snRNA"  ] && [ -s "$TFA" ] && [ -s "$methyl" ]
then
	header="$(paste <(awk '{print $1,$2}' $expression | head -1) <(head -1 $snRNA | awk 'NR==1{$1="";print}') <(awk 'NR==1{$1="";print}' $methyl) <(awk 'NR==1{$1="";print}' $TFA))"
	tokens=(${TFA//// })
	fileName=${tokens[${#tokens[@]}-1]}
	fileNameTokens=(${fileName//_/ })
	shortFileName=${fileNameTokens[0]}'_'${fileNameTokens[1]}'_'${fileNameTokens[2]}'_'${fileNameTokens[3]}
	echo $shortFileName
	cat <(echo $header) <(join <(awk 'NR > 1 {print $1,$2}' $expression | sort -V) <(awk 'NR > 1' $snRNA | sort -V) | join -  <(awk 'NR > 1' $methyl | sort -V) | join -  <(awk 'NR > 1' $TFA | sort -V)) | sed 's/ /\t/g' > $output"/"$shortFileName'_'$tfaType'_'$(date "+%Y.%m.%d_%H.%M.%S")'.txt'
	#cat <(echo $header) <(join <(awk 'NR > 1' $snRNA | sort -V) <(awk 'NR > 1' $methyl | sort -V) | join -  <(awk 'NR > 1' $TFA | sort -V) | join -  <(awk 'NR > 1 {print $1,$10}' $expression | sort -V)) | awk 'BEGIN {OFS=FS=" ";} {temp=$NF; $NF = ""; sub(",$", ""); print temp, $0}' > $shortFileName'_M_'$(date "+%Y.%m.%d_%H.%M.%S")'.txt'
elif [ -s "$snRNA" ] && [ -s "$TFA" ]
then
	header="$(paste <(awk '{print $1,$2}' $expression | head -1) <(head -1 $snRNA | awk 'NR==1{$1="";print}') <(awk 'NR==1{$1="";print}' $TFA))"
	tokens=(${TFA//// })
	fileName=${tokens[${#tokens[@]}-1]}
	fileNameTokens=(${fileName//_/ })
	shortFileName=${fileNameTokens[0]}'_'${fileNameTokens[1]}'_'${fileNameTokens[2]}'_'${fileNameTokens[3]}
	echo $shortFileName
	cat <(echo $header) <(join <(awk 'NR > 1 {print $1,$2}' $expression | sort -V) <(awk 'NR > 1' $snRNA | sort -V) | join -  <(awk 'NR > 1' $TFA | sort -V)) | sed 's/ /\t/g' > $output"/"$shortFileName'_'$tfaType'_'$(date "+%Y.%m.%d_%H.%M.%S")'.txt'

elif [ -s "$snRNA"  ] && [ -s "$methyl" ]
then
	header="$(paste <(awk '{print $1,$2}' $expression | head -1) <(head -1 $snRNA | awk 'NR==1{$1="";print}') <(awk 'NR==1{$1="";print}' $methyl) )"
	tokens=(${methyl//// })
	fileName=${tokens[${#tokens[@]}-1]}
	fileNameTokens=(${fileName//_/ })
	shortFileName=${fileNameTokens[0]}'_'${fileNameTokens[1]}'_'${fileNameTokens[2]}'_'${fileNameTokens[3]}
	echo $shortFileName
	cat <(echo $header) <(join <(awk 'NR > 1 {print $1,$2}' $expression | sort -V) <(awk 'NR > 1' $snRNA | sort -V) | join -  <(awk 'NR > 1' $methyl | sort -V) ) | sed 's/ /\t/g' > $output"/"$shortFileName'_'$tfaType'_'$(date "+%Y.%m.%d_%H.%M.%S")'.txt'
elif [ -s "$TFA" ] && [ -s "$methyl" ]
then
	header="$(paste <(awk '{print $1,$2}' $expression | head -1) <(awk 'NR==1{$1="";print}' $methyl) <(awk 'NR==1{$1="";print}' $TFA))"
	tokens=(${TFA//// })
	fileName=${tokens[${#tokens[@]}-1]}
	fileNameTokens=(${fileName//_/ })
	shortFileName=${fileNameTokens[0]}'_'${fileNameTokens[1]}'_'${fileNameTokens[2]}'_'${fileNameTokens[3]}
	echo $shortFileName
	cat <(echo $header) <(join <(awk 'NR > 1 {print $1,$2}' $expression | sort -V) <(awk 'NR > 1' $methyl | sort -V) | join -  <(awk 'NR > 1' $TFA | sort -V) ) | sed 's/ /\t/g' > $output"/"$shortFileName'_'$tfaType'_'$(date "+%Y.%m.%d_%H.%M.%S")'.txt'
elif [ -f "$snRNA" ]
then
	header="$(paste <(awk '{print $1,$2}' $expression | head -1) <(awk 'NR==1{$1="";print}' $snRNA))"
	tokens=(${snRNA//// })
	fileName=${tokens[${#tokens[@]}-1]}
	fileNameTokens=(${fileName//_/ })
	shortFileName=${fileNameTokens[0]}'_'${fileNameTokens[1]}'_'${fileNameTokens[2]}'_'${fileNameTokens[3]}
	cat <(echo $header) <(join <(awk 'NR > 1 {print $1,$2}' $expression | sort -V) <(awk 'NR > 1' $snRNA | sort -V) ) | sed 's/ /\t/g' > $output"/"$shortFileName'_'$tfaType'_'$(date "+%Y.%m.%d_%H.%M.%S")'.txt'
elif [ -f "$TFA" ]
then
	header="$(paste <(awk '{print $1,$2}' $expression | head -1) <(awk 'NR==1{$1="";print}' $TFA))"
	tokens=(${TFA//// })
	fileName=${tokens[${#tokens[@]}-1]}
	fileNameTokens=(${fileName//_/ })
	shortFileName=${fileNameTokens[0]}'_'${fileNameTokens[1]}'_'${fileNameTokens[3]}
	cat <(echo $header) <(join <(awk 'NR > 1 {print $1,$2}' $expression | sort -V) <(awk 'NR > 1' $TFA | sort -V) ) | sed 's/ /\t/g' > $output"/"$shortFileName'.txt'
else
	header="$(paste <(awk '{print $1,$2}' $expression | head -1) <(awk 'NR==1{$1="";print}' $methyl))"
	tokens=(${methyl//// })
	fileName=${tokens[${#tokens[@]}-1]}
	fileNameTokens=(${fileName//_/ })
	shortFileName=${fileNameTokens[0]}'_'${fileNameTokens[1]}'_'${fileNameTokens[2]}'_'${fileNameTokens[3]}
	cat <(echo $header) <(join <(awk 'NR > 1 {print $1,$2}' $expression | sort -V) <(awk 'NR > 1' $methyl | sort -V) ) | sed 's/ /\t/g' > $output"/"$shortFileName'_'$tfaType'_'$(date "+%Y.%m.%d_%H.%M.%S")'.txt'
fi
