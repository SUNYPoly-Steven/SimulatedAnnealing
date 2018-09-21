#include <iostream>
#include <cstring>
#include <fstream>

#include "Annealing.h"

#define _10e3 1000
#define _10e4 10000
#define _10e5 100000

void printUsage();
void ReadFile(const char* filepath, std::vector<std::pair<int, int>>& map);

int main(int argc, char** argv) {

	argc--;
	argv++;

	if (argc < 1) {
		printUsage();
		exit(EXIT_SUCCESS);
	}

	auto tsp_map = std::vector<std::pair<int, int>>();


	ReadFile(argv[0], tsp_map);
	Anneal(tsp_map, _10e4);
	

	exit(EXIT_SUCCESS);

}

void printUsage() 
{
	std::cout << "./SimAnneal TSP_file" << std::endl;
}

void ReadFile(const char* filepath, std::vector<std::pair<int, int>>& map)
{
	auto file = std::ifstream(filepath);
	if (!file.is_open()) {
		std::cerr << "ERROR: Unable to open file " << filepath << " terminating program." << std::endl;
		exit(EXIT_FAILURE);
	}

	int _1st = -1;
	int _2nd = -1;

	while (!file.eof()) {
		file >> _1st;
		file >> _2nd;
		map.emplace_back(_1st, _2nd);
	}

}