 #!/bin/bash

rm time.csv
g++ -std=c++11 -o main main.cpp -lpthread 

for i in {1..10}
 do
    for k in 100 1000 2000 3000 4000 5000 6000 7000 8000 9000 10000 11000 12000 13000 14000 15000 16000 17000 18000 19000 20000
        do
            ./main 1000 $k test
        done
done
