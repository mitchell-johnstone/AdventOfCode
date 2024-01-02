if [ ! -d AOC$1 ]
then
	mkdir AOC$1
fi

cookie="53616c7465645f5f39b166994a2cc9b810dd30553d3a5ef39e895b19317d03493a4b1fa78321c4fbb6f86b3b0a0cea2294565d791029aca486193ae422cc9a36"

file="AOC$1/input_$2.txt"
if [ ! -f $file ]
then
	curl https://adventofcode.com/$1/day/$2/input --cookie "session=$cookie" > $file
fi

file="AOC$1/sol_$2.cpp"
if [ ! -f $file ]
then
	cp ./sol_temp.cpp $file

	match='main(){'
	insert1="\tifstream inputFile(\".\/AOC$1\/input_$2.txt\");"
	insert2="\t\/\/ifstream inputFile(\".\/AOC$1\/ex_$2.txt\");"

	sed -i "s/$match/$match\n$insert1\n$insert2/" ./AOC$1/sol_$2.cpp
fi

nvim ./AOC$1/sol_$2.cpp ./AOC$1/ex_$2.txt -O +30
