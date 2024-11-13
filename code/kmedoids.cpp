#include "kmedoids.h"

// Constructora
kmedoids::kmedoids(const vecDdimension& data, int n, int d, int k, int maxIters) 
{
    this->n = n;
    this->d = d;
    this->k = k;
    this->data = data;
    this->maxIters = maxIters;
    this->actuPoints = true;
    this->itera = 0;
    this->pointXcluster = vector<int>(n);
}

// Función para calcular la distancia euclidiana entre dos puntos 
double kmedoids::calculateDistance(const vector<double>& p1, const vector<double>& p2) 
{
    double calc = 0;
    for (int i = 0; i < d; ++i) {
        calc += (p1[i] - p2[i])*(p1[i] - p2[i]);
    }
    return sqrt(calc);
}

double kmedoids::distance_between_points(int a, int b, vecDdimension &distMedoids) 
{
    if (distMedoids[a][b] != -1) return distMedoids[a][b];
    double distance = calculateDistance(this->data[a], this->data[b]);
    distMedoids[a][b] = distMedoids[b][a] = distance;
    return distance; 
}

// Función para asignar cada punto al cluster del medoide más cercano
void kmedoids::assignClusters(vecDdimension &distMedoids) 
{
    for (int i = 0; i < this->n; ++i) {
        double minDistance = MAX_LIMIT;
        int clusterIndex = -1;

        double distance = 0; 
        // Asignacion al cluster mas cercano
        for (int k = 0; k < this->k; ++k) {
            distance = distance_between_points(i, this->medoids[k], distMedoids);
            if (distance < minDistance) {
                minDistance = distance;
                clusterIndex = k;
            }
        }
        
        if (this->pointXcluster[i] != clusterIndex) this->actuPoints = true;
        // Asignacion al k-cluster
        this->pointXcluster[i] = clusterIndex;
    }
}


// Función para actualizar los medoides de cada clúster
void kmedoids::updateMedoids(vecDdimension &distMedoids) 
{
    // Subdividimos entre clusters, todos los que corresponden al k-cluster actual
    vector<vector<int>> clusterPoints(this->k);

    for (int i = 0; i < this->n; ++i) {
        clusterPoints[this->pointXcluster[i]].push_back(i);
    }

    for (int k = 0; k < this->k; ++k) {
        // Encontrar el punto mas representativo del cluster (medoide)
        double minTotalDistance = MAX_LIMIT;
        int newMedoid = this->medoids[k];

        for (int i = 0; i < clusterPoints[k].size(); ++i) {
            double totalDistance = 0.0;
            for (int j = 0; j < clusterPoints[k].size(); ++j) {
                double distance = distance_between_points(clusterPoints[k][i], clusterPoints[k][j], distMedoids);
                totalDistance += distance;
            }
            if (totalDistance < minTotalDistance) {
                minTotalDistance = totalDistance;
                newMedoid = clusterPoints[k][i];
            }
        }
        //Actualizacion del medoide
        this->medoids[k] = newMedoid;
    }
}


// Algoritmo de k-medoids
void kmedoids::kMedoids(vecDdimension &distMedoids) 
{   
    
    // Inicializar medoides aleatorios
    for (int i = 0; i < k; ++i) {
        int randomIndex = rand() % this->n;
        this->medoids.push_back(randomIndex);
    }

    //Por cada iteracion del for, reorganizamos todos los puntos del dataset en un cluster 
    int iter;

    for (iter = 0; iter < this->maxIters and this->actuPoints; ++iter) {

        // Control para saber si han cambiado respecto a la iter. anterior
        this->actuPoints = false;

        // Asignar cada punto al clúster del medoide más cercano
        assignClusters(distMedoids);

        // Actualizar medoides
        updateMedoids(distMedoids);
        this->itera = iter;
    }
}

// Funcion para pintar los resultados del k-medoid
void kmedoids::print_results() 
{
    /* 
    cout << "Medoides:\n";
    vecDdimension medoids = kmedoids::getMedoids();
    for (const vector<double>& medoid : medoids) {
        cout << "(" << medoid[0]; 

        for (int ki = 1; ki < medoid.size(); ++ki) 
            cout <<  ", " << medoid[ki]; 
    
        cout << ")" << endl;
    }
    cout << "Etiquetas de los clusters:\n";
    for (int label : this->pointXcluster) {
        cout << label << " ";
    }
    cout << endl; 
    */
    cout << "Iterationes:" << this->itera << endl;
}

// Funcion que devuelve el vector de clusters asociados a cada punto
vector<int> kmedoids::getClusters() {
    return this->pointXcluster;
}

vecDdimension kmedoids::getMedoids() {
    vecDdimension medoids (k, vector<double>(d));
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < d; ++j)
        medoids[i][j] = this->data[this->medoids[i]][j];
    }
    return medoids;
}