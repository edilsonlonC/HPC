#!/bin/bash

# Command for compile c++ threads and run 
compile='compile' # compile file 
run='run' # run file 
auto='auto'
clean='clean'
#if you use both can compile and run
args=("$@")

auto_exec(){
	for i in {1..10}
	do
		for k in 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 1500 2000 2500 3000
			do
			./"$1" $k
			done
	done
}

echo " ${args[0]} ${args[1]} ${args[2]} ${args[3]}"

if [ "${args[0]}" == "$compile" ] &&  [ "${args[1]}" == "$run" ] && [ "${args[2]}" == "$auto" ] && [ "${args[3]}" == "$clean" ];
then
	rm time.csv
	g++ -std=c++11 -o ${args[4]} ${args[4]}.cpp -lpthread
	auto_exec ${args[4]}

elif [ "${args[0]}" == "$compile" ] &&  [ "${args[1]}" == "$run" ] && [ "${args[2]}" == "$auto" ];
then
	
	g++ -std=c++11 -o ${args[3]} ${args[3]}.cpp -lpthread

	auto_exec ${args[3]}

elif [ "${args[0]}" == "$compile" ] &&  [ "${args[1]}" == "$run" ]; 
then
	 g++ -std=c++11 -o ${args[2]} ${args[2]}.cpp -lpthread
	./${args[@]:2:10}

elif [ "$1" == "$run" ];
then
	./${args[@]:1:10}
elif [ "$1" == "$compile" ];
then
	g++ -std=c++11 -o ${args[1]} ${args[1]}.cpp -lpthread

else 
	echo "revisa los comandos de entrada"

fi
