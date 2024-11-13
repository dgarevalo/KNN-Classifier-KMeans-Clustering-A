#include "generator.hh"

generator::generator(int k, int d, int npoints)
{
    this->k = k;
    this->d = d;
    this->npoints = npoints;
    centroids.resize(k);
    srand(time(nullptr));
}

void generator::generateClusters(double radi) 
{
    for (int i = 0; i < k; ++i) {
        centroids[i].resize(d);
        for (int u = 0; u < d; ++u) {
            centroids[i][u] = static_cast<double>(rand()) / RAND_MAX;
        }

        // Punts al voltant dels centroides
        for (int j = 0; j < npoints; ++j) {
            vector<double> point(d);
            for (int u = 0; u < d; ++u) {
                double angle = 2 * M_PI * static_cast<double>(rand()) / RAND_MAX;
                double rcalc = radi * sqrt(static_cast<double>(rand()) / RAND_MAX);
                point[u] = centroids[i][u] + rcalc * cos(angle);
            }
            etiquetes.push_back(i);
            data.push_back(point);
        }
    }
}

void generator::printData()
{
    // Data
    cout << "Dataset" << endl;
    for (int i = 0; i < data.size(); ++i) {
        cout << "(";
        for (int j = 0; j < d; ++j) {
            cout << data[i][j];
            if (j < d-1) {
                cout << ", ";
            }
        }
        cout << ")" << endl;
    }
    cout << endl;
    
    // Groundtruth
    cout << "Groundtruth" << endl;
    for (int i = 0; i < etiquetes.size(); ++i) {
        cout << etiquetes[i] << endl;
    }
}

vector<vector<double>> generator::getPunts()
{
    return data;
}

vector<int> generator::getEtiquetes()
{
    return etiquetes;
}
