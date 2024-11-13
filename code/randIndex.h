#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;
typedef unordered_map<int, int> UnordMap;

class randIndex {
    public:
        // Constructora 
        randIndex(const vector<int>& kmeans, const vector<int>& kmedoids);
        // Funcion para la creacion de la tabla de contingencia
        map<pair<int, int>, int> createTable();
        // Funcion para la ejecucion de la evaluacion externa del cluster
        double executeIndex();
        // Funcion que devuelve el valor del indice de Rand
        double getIndexValue();
    
    private:
        double n, RI;
        UnordMap partitionU, partitionV;  
        map<pair<int, int>, int> table;
};