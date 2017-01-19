//declarition of class topology
#ifndef _TOPOLOGY_HPP
#define _TOPOLOGY_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <limits>
#include <cstring>
#include <fstream>
#include <sstream>
#include "EasyBMP_1.06/EasyBMP.h"

using namespace std;

class Topology{
public:
	vector<float> theta; // store nodes angle velues for dynamic ring.
	vector<vector<float> > nodes;//store coordinates for crescent moon.

	//2-dimentional vector to keep neighbors for each node
	vector<vector<int> > list;
	
	vector<vector<float> > chart; //keep distance from node to node. 
	vector<float> distance_sum;//distance of sum recording 50 cycles

	Topology(int N, int k, int r);
	Topology(int N, int k);
	Topology(int N, int k, char type);
	void cycle(int N, int k);
	void filelist(int N, int k, string type, int iteration);
	void calculate_dos(int r);
	void filedos(int N, int k, string type);
	void ringplot(int N, int k,int r, int maxr, string type, int iteration);
	void BRtreeplot(int N, int k, string type, int iteration);
	void moonplot(int N, int k, int r, string type, int iteration);

private:
	vector<int> random;//store randomly generated node sequence.

	float ring_distance(float theta1, float theta2);
	int BRtree_distance(int a, int b);
	float moon_distance(float x1, float y1, float x2, float y2, int i , int j, int N);
	void dsort(vector<int> nodes, vector<float> dvec, int target, int k);
	string ntos(int a);
	void line(int x1, int y1, int const x2, int const y2, BMP& img);
	int level(int i);
};

#endif