#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;

class generator {
	public:
        generator(int k, int d, int npoints);
        void generateClusters(double radi);
        vector<vector<double>> getPunts();
        vector<int> getEtiquetes();
        void printData();
		
	private:
		int k, d;
        int npoints;
        vector<vector<double>> centroids;
        vector<vector<double>> data;
        vector<int> etiquetes;
};

