#include<set>
#include<vector>
#include <string>

class Graph {
	vector<vector<int>> ma;
	int dim;
	int indexOf(set<string> cities, string x) {
		int i = -1;
		for (auto it = cities.begin(); it != cities.end(); ++it) {
			++i;
			if (*it == x) return i;
		}
	}
	string stringOf(set<string> cities, int j) {
		int i = -1;
		for (auto it = cities.begin(); it != cities.end(); ++it) {
			++i;
			if (i == j) return *it;
		}
	}
public:
	/*initializeaza matricea de adiacenta*/
	Graph(int dim) {
		this->dim = dim;
		vector<int> x;
		for (int i = 0; i < dim; ++i)
			x.push_back(0);
		for (int j = 0; j < dim; ++j) 
			ma.push_back(x);
		
	}
	void addEdge(set<string> cities,string x,string y) {
		ma[indexOf(cities, x)][indexOf(cities, y)] = 1;
		ma[indexOf(cities, y)][indexOf(cities, x)] = 1;
	}

	/*afisarea lanturilor cu noduri distince*/
	void getPath(set<string> cities) {
		vector<int> viz;
		for (int i = 0; i < dim; ++i)
			viz.push_back(0);
		
		bool existZero = true;
		while (existZero) {
			for (int i = 0; i < dim; ++i) {
				if (viz[i] == 0) {
					viz[i] = 1;
					cout << "\t" << stringOf(cities, i);
					bool sw = true;
					while (sw) {
						bool changeOfCity = true;
						for (int j = i + 1; j < dim; ++j)
							if (viz[j] == 0 && ma[i][j] == 1) {
								cout << " -> " << stringOf(cities, j);
								viz[j] = 1;
								i = j;
								changeOfCity = false;
							}
						if (changeOfCity) {
							sw = false; cout << endl;
						}
					}
				}
			}
			//verificam daca mai exista orase nevizitate
			existZero = false;
			for (int i = 0; i < dim && !existZero; ++i)
				if (viz[i] == 0) existZero = true;
		}
	}
};