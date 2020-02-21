#!/bin/bash

# Command for compile c++ threads and run 
compile='compile' # compile file 
run='run' # run file 
#if you use both can compile and run
args=("$@")

for i in "$@";
do
	file="$i"
done

if [ "${args[0]}" == "$compile" ] &&  [ "${args[1]}" == "$run" ]; 
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
