#include "randIndex.h"

// Constructora 
randIndex::randIndex(const vector<int>& kmeans, const vector<int>& kmedoids) 
{
    this->n = kmeans.size();
    for (int i = 1; i <= n; i++) {
        this->partitionU.insert(make_pair(i, kmeans[i-1]));
        this->partitionV.insert(make_pair(i, kmedoids[i-1]));
    }
    this->table = createTable();
    this->RI = executeIndex();
}

// Creacion de la tabla de contingencia
map<pair<int, int>, int> randIndex::createTable() 
{
    map<pair<int, int>, int> T;
    for (const auto& punto : partitionU) {
        int cluster1 = punto.second;
        int cluster2 = partitionV.at(punto.first);
        T[{cluster1, cluster2}]++;
    }
    return T;
}

// Ejecucion de la evaluacion externa del cluster
double randIndex::executeIndex() 
{
    // 1r terme: n combinatoria 2
    double nC2 = double(n*(n - 1))/2.0;

    // 2n terme: Σ n_ij² de la tabla de contingencia
    double Snij2 = 0;
    map<int, int> Srow, Scol;
    for (const auto& cell : table) {
        int n_ij = cell.second;

        Snij2 += n_ij * n_ij;
        Srow[cell.first.first] += n_ij;
        Scol[cell.first.second] += n_ij;
    }
     
    // 3r terme: Σ de la fila ni² y la columna nj²
    double Sr2 = 0, Sc2 = 0;
    for (const auto& row : Srow) {
        Sr2 += row.second*row.second;
    }
    for (const auto& col : Scol) {
        Sc2 += col.second*col.second;
    }

    // Cálculo del Rand Index
    double A = nC2 + Snij2 - 0.5 * (Sr2 + Sc2);
    return A / nC2;
}

// Devuelve el valor del indice de Rand
double randIndex::getIndexValue() {
    return this->RI;
}
