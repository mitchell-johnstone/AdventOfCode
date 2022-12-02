# page=$(curl https://adventofcode/2022/day/$1 | grep ">Source<" -A 3 | cut -d '>' -f 3  | head -n2 | tail -n1)
input=$(curl https://adventofcode.com/2022/day/$1/input)
echo $input > day$1.input
touch day$1.1.cpp
touch day$1.2.cpp
