#!bash/bin
rm workload_looping.csv
rm workload_80_20.csv
rm workload_random.csv

touch workload_looping.csv
echo RANDOM,LRU,FIFO > workload_looping.csv
touch workload_80_20.csv
echo RANDOM,LRU,FIFO > workload_80_20.csv
touch workload_random.csv
echo RANDOM,LRU,FIFO > workload_random.csv