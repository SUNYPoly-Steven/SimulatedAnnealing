#include "Annealing.h"
#include <cmath>
#include <algorithm>

void gen_path(std::vector<unsigned int>& output, unsigned int mapSize);
float fitness(const std::vector<std::pair<int, int>>& map, const std::vector<unsigned int>& path);
float dist(const std::pair<int, int>* from, const std::pair<int, int>* to);
void step(const std::vector<unsigned int>& src, std::vector<unsigned int>& dest);
float temperature(float currTime);
bool P(float s, float snew, float t);

void Anneal(const std::vector<std::pair<int, int>>& map, int max_iters)
{
	/*
	Simmulated Annealing on TSP:
		Givens:
			- Graph Layout

		Step 1:
			- stocastically pick a path to take (*DONE*)
		Step 2:
			- get the fitness of that path (*DONE*)
		Step 3: 
			- for i < MAX_ITERS (*DONE*)
				- Move to a neighboring state. (*DONE*)
				- get the new states fitness (*DONE*)
				- determine wether to move to the new state with some tempurature function (*DONE*)

	*/
	srand((unsigned) time(NULL));

	//vector if indecies into map
	auto path = std::vector<unsigned int>();
	auto newPath = std::vector<unsigned int>();
	gen_path(path, map.size());

	for (int i = 0; i < max_iters; ++i) {
		step(path, newPath);
		if (P(fitness(map, path), fitness(map, newPath), temperature(i / max_iters)) >= ((float)rand() / (float)RAND_MAX)) {
			path.swap(newPath); //swap to avoid copies
		}
	}
	

}

void gen_path(std::vector<unsigned int>& output, unsigned int mapSize)
{
	auto indecies = std::vector<unsigned int>();
	for (unsigned int i = 0; i < mapSize; ++i) {
		indecies.push_back(i);
	}

	int random = -1;
	while (!indecies.empty()) {
		random = rand() % indecies.size();
		output.push_back(indecies[random]);
		indecies.erase(indecies.begin() + random);
	}
}

float fitness(const std::vector<std::pair<int, int>>& map, const std::vector<unsigned int>& path)
{
	const std::pair<int, int>* lastPoint = &map[path[0]];
	float sum = 0.0f;

	for (unsigned int i = 1; i < path.size(); ++i) {
		sum += dist(lastPoint, &map[path[i]]);
		lastPoint = &map[path[i]];
	}

	sum += dist(lastPoint, &map[path[0]]); //dont forget to go back to the start

	return sum;
}

float dist(const std::pair<int, int>* from, const std::pair<int, int>* to)
{
	return (float) sqrt((to->first - from->first) + (to->second - from->second));
}

void step(const std::vector<unsigned int>& src, std::vector<unsigned int>& dest)
{
	dest = src; //copy src to dest

	int _1st = rand() % src.size(); 
	int _2nd = rand() % (src.size() - _1st);

	std::reverse(dest.begin() + _1st, dest.begin() + _2nd); //reverse the subsection of the dest vector to take the "step" 

}

float temperature(float currTime) {
	return (1 / currTime);
}

bool P(float s, float snew, float t) 
{
	return (snew < s) ? 1 : exp(-(snew - s)/t);
}