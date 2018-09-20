all:
	g++ -std=c++14 -Wall ./src/main.cpp -o ./bin/SimAnneal

clean:
	rm -f ./bin/SimAnneal