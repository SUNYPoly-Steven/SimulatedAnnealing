SRC = ./src/main.cpp ./src/Annealing.cpp

all:
	g++ -std=c++14 -Wall $(SRC) -o ./bin/SimAnneal

clean:
	rm -f ./bin/SimAnneal