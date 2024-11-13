#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>
using namespace std;

class kmeans {
    public:
        kmeans();

        vector<vector<double>> kMeans(vector<vector<double>>& data, vector<vector<int>>& assigDadesClustersFinal, vector<int>& Cluster_Punts, int k, int n, int d);
        vector<vector<double>> kMeansPP(vector<vector<double>>& data, vector<vector<int>>& assigDadesClustersFinal, vector<int>& Cluster_Punts, int k, int n, int d);
        void recalcular_centroides(int k, int d, vector<vector<int>>& assigDadesClusters, vector<vector<double>>& data, vector<vector<double>>& centroides);
        void assignar_dades_cluster(vector<vector<int>>& assigDadesClusters, vector<int>& clsuter_assignat_a_punt, int n, int k, int d, vector<vector<double>>& data, vector<vector<double>>& centroides);
        double distanciaEuclidiana(int i, vector<double> dimCentroide, vector<vector<double>>& data, int d);
        void print_results(const vector<vector<int> >& assignacio);
};