CC = g++
CCARGS = -O2 -Wall -Wshadow -std=gnu++1z -march=native
GENERATOR_LIST = \
	house.exe \
	house_extreme.exe \
	storm \
	game \
	molecule \
	road.exe

all: $(GENERATOR_LIST)

clean:
	rm -f $(GENERATOR_LIST)

%.exe: %.cpp
	$(CC) $^ $(CCARGS) -o $@

house: house.exe house_extreme.exe
	$(info Hi, I'm actually house.exe and house_extreme.exe.)

run_house: house.exe house_extreme.exe
	./house.exe random 2 1 0xFF32ADEA 1
	./house.exe random 2 1 0xADEAFF32 2
	./house_extreme.exe 2 1000 514 > 1_0003_extreme_514.in
	./house_extreme.exe 2 1000 7122 > 1_0004_extreme_7122.in
	./house_extreme.exe 2 1000 9527 > 1_0005_extreme_9527.in
	./house_extreme.exe 2 1000 48763 > 1_0006_extreme_48763.in
	./house.exe random 100 2 0xFF32ADEA 7
	./house.exe random 100 2 0xADEAFF32 8
	./house_extreme.exe 100 1000 114514 > 2_0009_extreme_114514.in
	./house.exe random 100000 3 0xFF32ADEA 10
	./house.exe random 100000 3 0xADEAFF32 11
	./house_extreme.exe 100000 1000 948794 > 3_0012_extreme_948794.in

storm: storm.py
	echo ""

run_storm: storm.py
	python3 storm.py

game: game.cc game_sp.py
	$(CC) game.cc $(CCARGS) -o game

run_game: game
	./game
	python3 game_sp.py

molecule: molecule.py
	echo ""

run_molecule: molecule.py
	python3 molecule.py

road: road.exe
	$(info road.exe)

run_road: road
	./road.exe pure_random 10 30 10 1 1 seed=1 > 1_001_random.in
	./road.exe pure_random 100 300 300 1 1 seed=1 > 1_002_random.in
	./road.exe pure_random 100 300 300 1 1 seed=2 > 1_003_random.in
	./road.exe kruskal 100 300 300 1 1 40 1 -1 -1 -1 -1 -1 -1 150 seed=1 > 1_004_random.in
	./road.exe kruskal 100 300 300 1 1 20 1 -1 -1 -1 -1 -1 -1 100 seed=1 > 1_005_random.in
	./road.exe kruskal 100 300 300 1 1 60 1 -1 -1 -1 -1 -1 -1 200 seed=1 > 1_006_random.in
	./road.exe kruskal 100 300 300 1 1 10 3 1 1 -1 -1 -1 -1 10 seed=1 > 1_007_random.in
	./road.exe kruskal 100 300 300 1 1 90 1 -1 -1 -1 -1 1 1 290 seed=1 > 1_008_random.in
	./road.exe kruskal 100 300 300 1 1 90 1 -1 -1 -1 -1 2 1 290 seed=1 > 1_009_random.in
	./road.exe pure_random 100 101 300 1 1 seed=2 > 1_010_random.in
	./road.exe pure_random 87 514 486 1 10000 seed=1 > 2_001_random.in
	./road.exe pure_random 500 1000 1000 1 1000000000 seed=1 > 2_002_random.in
	./road.exe pure_random 500 1000 1000 1 1000000000 seed=2 > 2_003_random.in
	./road.exe kruskal 500 1000 1000 1 1000000000 200 1 -1 -1 -1 -1 -1 -1 100 seed=1 > 2_004_random.in
	./road.exe kruskal 500 1000 1000 1 1000000000 60 3 -1 -1 -1 -1 -1 -1 50 seed=1 > 2_005_random.in
	./road.exe kruskal 500 1000 1000 1 1000000000 300 1 -1 -1 -1 -1 -1 -1 800 seed=1 > 2_006_random.in
	./road.exe kruskal 500 1000 1000 1 1000000000 1 3 -1 -1 -1 -1 -1 -1 0 seed=1 > 2_007_random.in
	./road.exe kruskal 500 1000 1000 1 1000000000 1 3 -1 -1 2 10 -1 -1 0 seed=1 > 2_008_random.in
	./road.exe kruskal 500 1000 1000 1 1000000000 3 3 1 2 1 5 -1 -1 10 seed=1 > 2_009_random.in
	./road.exe kruskal 500 1000 1000 7122 8787 200 1 -1 -1 -1 -1 1 2 50 seed=1 > 2_010_random.in
	./road.exe kruskal 500 1000 1000 999999995 1000000000 200 1 -1 -1 -1 -1 -1 -1 100 seed=1 > 2_011_random.in
	./road.exe pure_random 777 2222 66666 1 1000000 seed=1 > 3_001_random.in
	./road.exe pure_random 1000 3000 500000 1 1000000000 seed=1 > 3_002_random.in
	./road.exe pure_random 1000 3000 500000 1 1000000000 seed=2 > 3_003_random.in
	./road.exe kruskal 1000 3000 500000 1 1000000000 400 1 -1 -1 -1 -1 -1 -1 150 seed=1 > 3_004_random.in
	./road.exe kruskal 1000 3000 500000 1 1000000000 80 3 -1 -1 -1 -1 -1 -1 100 seed=1 > 3_005_random.in
	./road.exe kruskal 1000 3000 500000 1 1000000000 600 1 -1 -1 -1 -1 -1 -1 400000 seed=1 > 3_006_random.in
	./road.exe kruskal 1000 3000 500000 1 1000000000 1 3 -1 -1 -1 -1 -1 -1 0 seed=1 > 3_007_random.in
	./road.exe kruskal 1000 3000 500000 1 1000000000 1 3 -1 -1 2 10 -1 -1 0 seed=1 > 3_008_random.in
	./road.exe kruskal 1000 3000 500000 1 1000000000 3 3 1 2 1 5 -1 -1 10 seed=1 > 3_009_random.in
	./road.exe kruskal 1000 3000 500000 7122 8787 600 1 -1 -1 -1 -1 1 2 450000 seed=1 > 3_010_random.in
	./road.exe kruskal 1000 3000 500000 1 1000000000 1 3 -1 -1 -1 -1 -1 -1 0 seed=2 > 3_011_random.in
	./road.exe kruskal 1000 3000 500000 1 1000000000 1 3 -1 -1 -1 -1 -1 -1 0 seed=3 > 3_012_random.in
	./road.exe kruskal 1000 3000 500000 999999995 1000000000 400 1 -1 -1 -1 -1 -1 -1 150 seed=1 > 3_013_random.in
	./road.exe pure_random 656 87878 64646 456456 987987987 seed=1 > 4_001_random.in
	./road.exe pure_random 1000 500000 500000 1 1000000000 seed=1 > 4_002_random.in
	./road.exe pure_random 1000 500000 500000 1 1000000000 seed=2 > 4_003_random.in
	./road.exe kruskal 1000 500000 500000 1 1000000000 400 1 -1 -1 -1 -1 -1 -1 150 seed=1 > 4_004_random.in
	./road.exe kruskal 1000 500000 500000 1 1000000000 80 3 -1 -1 -1 -1 -1 -1 100 seed=1 > 4_005_random.in
	./road.exe kruskal 1000 500000 500000 1 1000000000 600 1 -1 -1 -1 -1 -1 -1 400000 seed=1 > 4_006_random.in
	./road.exe kruskal 1000 500000 500000 1 1000000000 1 3 -1 -1 -1 -1 -1 -1 0 seed=1 > 4_007_random.in
	./road.exe kruskal 1000 500000 500000 1 1000000000 1 3 -1 -1 2 10 -1 -1 0 seed=1 > 4_008_random.in
	./road.exe kruskal 1000 500000 500000 1 1000000000 3 3 1 2 1 5 -1 -1 10 seed=1 > 4_009_random.in
	./road.exe kruskal 1000 500000 500000 7122 8787 600 1 -1 -1 -1 -1 1 2 450000 seed=1 > 4_010_random.in
	./road.exe kruskal 1000 500000 500000 1 1000000000 1 3 -1 -1 -1 -1 -1 -1 0 seed=2 > 4_011_random.in
	./road.exe kruskal 1000 500000 500000 1 1000000000 1 3 -1 -1 -1 -1 -1 -1 0 seed=3 > 4_012_random.in
	./road.exe pure_random 1000 500000 500000 1 1000000000 seed=3 > 4_013_random.in
	./road.exe kruskal 1000 500000 500000 1 1000000000 5 3 -1 -1 2 1 -1 -1 0 seed=1 > 4_014_random.in
	./road.exe kruskal 1000 500000 500000 999999995 1000000000 400 1 -1 -1 -1 -1 -1 -1 150 seed=1 > 4_015_random.in
