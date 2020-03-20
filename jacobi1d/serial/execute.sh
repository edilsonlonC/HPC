 #!/bin/bash

rm time.csv
g++ -std=c++11 -o main main.cpp -lpthread 

for i in {1..10}
 do
    for k in 10 20 30 40 50 60 70 80 90 100 200 300 400 500 600 700 800 900 1000 1500 2000 2500 3000 3500 4000 4500 5000 6000 7000 15000
        do
            ./main 1000 $k test
        done
done
