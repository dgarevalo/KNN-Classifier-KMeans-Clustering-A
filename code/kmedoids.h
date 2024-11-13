#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <chrono>
#include "dataset.h"
using namespace std;

typedef vector< vector<double> > vecDdimension;

class kmedoids{
    public:
        kmedoids(const vecDdimension& data, int n, int d, int k, int maxIters);
        // Función para calcular la distancia euclidiana entre dos puntos
        double calculateDistance(const vector<double>& p1, const vector<double>& p2);
        // Función para comprobar y calcular la distancia entre dos puntos
        double distance_between_points(int a, int b, vecDdimension &distMedoids);
        // Función para asignar cada punto al clúster del medoide más cercano
        void assignClusters(vecDdimension &distMedoids);
        // Función para actualizar los medoides de cada clúster
        void updateMedoids(vecDdimension &distMedoids);
        // Algoritmo de k-medoids
        void kMedoids(vecDdimension& distMedoids);
        // Funcion para pintar los resultados del k-medoid
        void print_results();
        // Funcion que devuelve el vector de clusters asociados a cada punto
        vector<int> getClusters();
        // Funcion que devuelve las dimensiones del medoid
        vecDdimension getMedoids();
    
    private:
        int d;
        int k, n;
        int itera;
        int maxIters;
        bool actuPoints;
        vecDdimension data;
        vector<int> medoids;
        vector<int> pointXcluster; // El cluster asociado a cada punto

        const int MAX_LIMIT = numeric_limits<int>::max(); 

};
