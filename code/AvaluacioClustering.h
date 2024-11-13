#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>
#include <limits>
using namespace std;

class AvaluacioClustering
{

	public:
		AvaluacioClustering();
		//vector<vector<double>> silhouette(vector<vector<int>>& cluster, vector<vector<double>>& data, int k, int n, int d);
		vector<vector<double>> silhouette_Optimitzada(vector<vector<int>>& cluster, vector<vector<double>>& data, vector<vector<double>>& centroides, int k, int n, int d);
		vector<vector<double>> silhouette_Optimitzada_Kmediods(vector<vector<int>>& cluster, vector<vector<double>>& data, vector<vector<double>>& centroides, int k, int n, int d);
		double distanciaEuclidiana(int Punt_Base, int Punt_distant, vector<vector<double>>& data, vector<vector<double>>& centroides, int d);
		void printResultat(vector<vector<double>> siluetes);
};

