gcc -g -std=c11 -Wall -o bin/main src/*.c -lm
# ./bin/main ../instances/SET1_2-3/T3-100-2-3.ophs ../out/SET1_2-3/T3-100-2-3.ophsout 1000 3 3 0 1 1
./bin/main ../instances/SET5_15-4/100-200-15-4.ophs ../out/SET5_15-4/100-200-15-4.ophsout 1 3 3 0 0 1
# cd .. && python3 visualize.py SET1_2-3/T3-100-2-3 0 && cd algorithm
cd ..
python3 visualize.py SET5_15-4/100-200-15-4 0
cd algorithm
rm bin/*
