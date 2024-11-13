#include <iostream>
#include <vector>
#include <chrono>
#include "dataset.h"
#include "kmeans.h"
#include "kmedoids.h"
#include "AvaluacioClustering.h"
#include "randIndex.h"
#include "generator.hh"
using namespace std;

// Función para calcular la distancia euclidiana entre dos puntos 
double calculateDistance(const vector<double>& p1, const vector<double>& p2, int d) 
{
    double calc = 0;
    for (int i = 0; i < d; ++i) {
        calc += (p1[i] - p2[i])*(p1[i] - p2[i]);
    }
    return sqrt(calc);
}

double calculateWCSS(const vecDdimension& data, const vecDdimension& medoids, const vector<int>& clusterLabels) {
    double wcss = 0.0;
	int d = data[0].size();
    for (int i = 0; i < data.size(); ++i) {
        double distance = calculateDistance(data[i], medoids[clusterLabels[i]], d);
        wcss += distance * distance;
    }
    return wcss;
}


int main() {
	//creem vectors dels datasets i els READMEs
	vector<string> datasets = { "Dataset1.csv","Dataset2.csv" ,"Dataset3.csv" ,"Dataset4.csv" ,"Dataset5.csv","Dataset6.csv","Dataset7.csv" };
	vector<string> readmes = { "README-Dataset1.txt", "README-Dataset2.txt", "README-Dataset3.txt", "README-Dataset4.txt", "README-Dataset5.txt", "README-Dataset6.txt", "README-Dataset7.txt" };
	
	//Preguntem quin dataset es vol utilitzar
	cout << "Vols generar un dataset o vols utilitzar un que ja existeix?" << endl;
	cout << "1) Generar dataset nou" << endl;
	cout << "2) Escollir dataset existent" << endl;
	int op; cin >> op;

	int k;													// num. clusters
	int d;													// dimension
	int n;													// num. puntos
	int maxIters = 1000;									// max iters.

	// Lectura del propio dataset con todos sus puntos
	vector<vector<double> > data;
	// Etiquetas de cada punto del dataset (groundtruth)
	vector<int> groundtruth;

	if (op == 1) {
		cout << "Escull el numero de clusters: k = ";
		cin >> k;
		cout << "Escull ara les dimensions dels punts: d = ";
		cin >> d;
		cout << "Ara, quants punts voldràs per cluster? ";
		int npoints; cin >> npoints;
		n = npoints*k;
		cout << "Perfecte! S'acaba de crear un dataset a mida." << endl << endl;
		double radi = 0.01;

		generator GaussianMix = generator(k, d, npoints);
		GaussianMix.generateClusters(radi);
		data = GaussianMix.getPunts();
		groundtruth = GaussianMix.getEtiquetes();
		//GaussianMix.printData();
		//cout << endl << endl << endl;
	}
	else if (op == 2) {
		cout << "Quin dataset vols utilitzar? (1-6)" << endl;
		int numDataSet;
		cin >> numDataSet;
		string dataSetEscollit = datasets[numDataSet - 1];
		string readmeEscollit = readmes[numDataSet - 1];

		// LECTURA DATOS DATASETS (servira para ambos algoritmos)
		dataset datasetActual = dataset();
		if (datasetActual.llegirReadme("datasets/" + readmeEscollit) == 1) {
			cout << "El README no s'ha pogut obrir" << endl;
			return 1;
		}
		if (datasetActual.llegirDataset("datasets/" + dataSetEscollit) == 1) {
			cout << "El dataset no s'ha pogut obrir" << endl;
			return 1;
		}

		k = datasetActual.getK(); 						// num. clusters
		d = datasetActual.getD();						// dimension
		n = datasetActual.getN();						// num. puntos
		maxIters = 1000;								// max iters.

		// Lectura del propio dataset con todos sus puntos
		data = datasetActual.getData();
		// Etiquetas de cada punto del dataset (groundtruth)
		groundtruth = datasetActual.getEtiquetes();
	}

	// START -----------------------------------------------------------
	auto start = std::chrono::high_resolution_clock::now();

	// Clusters asociados a los puntos del kmeans plus plus
	vector<int> assignedKmeansPPClusters;
	// Clusters asociados a los puntos del kmeans
	vector<int> assignedKmeansClusters;
	// Clusters asociados a los puntos del kmedoids
	vector<int> assignedKmedoidsClusters;
	// Matriz de distancias entre puntos de kmedoids
	vecDdimension kmedoidsPointDist(n, vector<double>(n, -1));


	// K-ÓPTIMA -----------------------------------------------------------
	if (k == -1) {
		cout << "Busquem la k optima" << endl;
		cout << "Calcular K en " << endl << "1) K-means" << endl << "2) K-medoids" << endl;
		int inp;
		cin >> inp;

		vector<double> wcssValues;

		for (int k = 2; k <= 15; ++k) { // Comienza desde 2 porque 1 no es útil
			double wcss;
			if (inp == 1) { // K-means
				kmeans KMEANS = kmeans();
				vector<vector<int>> assigDadesClustersFinal;
				vector<vector<double>> centroides;
				centroides = KMEANS.kMeans(data, assigDadesClustersFinal, assignedKmeansClusters, k, n, d);

				wcss = calculateWCSS(data, centroides, assignedKmeansClusters);

			}

			else { // K-medoids
				kmedoids KMEDOIDS = kmedoids(data, n, d, k, maxIters);
				KMEDOIDS.kMedoids(kmedoidsPointDist);

				vector<vector<double>> medoids;
				assignedKmedoidsClusters = KMEDOIDS.getClusters();
				medoids = KMEDOIDS.getMedoids();

				wcss = calculateWCSS(data, medoids, assignedKmedoidsClusters);

			}
			wcssValues.push_back(wcss);

			cout << "k = " << k << " WCSS = " << wcss << endl;
		}
		double wcss_opt_k = wcssValues[0] - (wcssValues[0] - wcssValues[int(wcssValues.size())-1])*0.9;
		//Calula la distancia más pequeña que haya en wcssValues con respecto a wcss_opt_k
		double dist = 1000000;
		int opt_k = 0;
		for (int i = 0; i < int(wcssValues.size()); ++i) {
			if (abs(wcssValues[i] - wcss_opt_k) < dist) {
				dist = abs(wcssValues[i] - wcss_opt_k);
				opt_k = i;
			}
		}
		k = opt_k;
		cout << "La k optima es: " << k << endl;
	}
	

	// ALGORITMO -----------------------------------------------------------
	cout << "Quin algoritme vols utilitzar?" << endl;
	cout << "1) K-means" << endl;
	cout << "2) K-medoids" << endl;
	cout << "3) Find optimal K" << endl;


	int alg; cin >> alg;								
	if (alg == 1) { // k-means
		kmeans KMEANS = kmeans();
		// Avaluació Interna: Average Silhouette
		vector<vector<int>> assigDadesClustersFinal_Kmeans;
		//Vector de los centroides de kmeans
		vector<vector<double>> centroides_kmeans;
		centroides_kmeans = KMEANS.kMeans(data, assigDadesClustersFinal_Kmeans, assignedKmeansClusters,k, n, d);
		KMEANS.print_results(assigDadesClustersFinal_Kmeans);

		// Per calcular la silueta
		vector<vector<int>> assigDadesClustersFinal_KmeansPP;
		//Vector de los centroides de kmeans plus plus
		vector<vector<double>> centroides_kmeansPP;
		centroides_kmeansPP = KMEANS.kMeansPP(data, assigDadesClustersFinal_KmeansPP, assignedKmeansPPClusters, k, n, d);
		KMEANS.print_results(assigDadesClustersFinal_KmeansPP);

		AvaluacioClustering X;
		vector<vector<double>> Siluetes = X.silhouette_Optimitzada(assigDadesClustersFinal_Kmeans,data, centroides_kmeans, k, n, d);
		X.printResultat(Siluetes);

		cout << endl;

		Siluetes = X.silhouette_Optimitzada(assigDadesClustersFinal_KmeansPP,data,centroides_kmeansPP, k, n, d);
		X.printResultat(Siluetes);
		if (groundtruth.size() > 0) {
			randIndex RI = randIndex(groundtruth, assignedKmeansClusters);
			cout << " -> Rand Index: " << RI.getIndexValue() << endl;
		}
	}

	else if (alg == 2){ // k-medoids
		kmedoids KMEDOIDS = kmedoids(data, n, d, k, maxIters);
		KMEDOIDS.kMedoids(kmedoidsPointDist);
		KMEDOIDS.print_results();

		// Avaluació Externa: Rand Index
		assignedKmedoidsClusters = KMEDOIDS.getClusters();
		
		// Avaluació Iterna: Average Silhouette
		vector<vector<int>> Punts_Per_Cluster(k);
		for (int i = 0; i < n; ++i) {
			Punts_Per_Cluster[assignedKmedoidsClusters[i]].push_back(i);
		}
		AvaluacioClustering X;
		vector<vector<double>> centroides = KMEDOIDS.getMedoids();
		vector<vector<double>> Siluetes = X.silhouette_Optimitzada_Kmediods(Punts_Per_Cluster, data, centroides,k, n, d);
		X.printResultat(Siluetes);
		if (groundtruth.size() > 0) {
			randIndex RI = randIndex(groundtruth, assignedKmedoidsClusters);
			cout << " -> Rand Index: " << RI.getIndexValue() << endl;
		}
	}

	else { //Find optimal K
		cout << "Calcular K en " << endl << "1) K-means" << endl << "2) K-medoids" << endl;
		int inp;
		cin >> inp;

		vector<double> wcssValues;
		for (int k = 2; k <= 20; ++k) { // Comienza desde 2 porque 1 no es útil
			double wcss;
			if (inp == 1) { // K-means
				kmeans KMEANS = kmeans();
				vector<vector<int>> assigDadesClustersFinal;
				vector<vector<double>> centroides;
				centroides = KMEANS.kMeans(data, assigDadesClustersFinal, assignedKmeansClusters, k, n, d);

				wcss = calculateWCSS(data, centroides, assignedKmeansClusters);
				if (groundtruth.size() > 0) {
					randIndex RI = randIndex(groundtruth, assignedKmeansClusters);
					cout << " -> Rand Index: " << RI.getIndexValue() << endl;
				}
			}
			
			else { // K-medoids
				kmedoids KMEDOIDS = kmedoids(data, n, d, k, maxIters);
				KMEDOIDS.kMedoids(kmedoidsPointDist);

				vector<vector<double>> medoids;
				assignedKmedoidsClusters = KMEDOIDS.getClusters();
				medoids = KMEDOIDS.getMedoids();			
				
				wcss= calculateWCSS(data, medoids, assignedKmedoidsClusters);
				wcssValues.push_back(wcss);

				if (groundtruth.size() > 0) {
					randIndex RI = randIndex(groundtruth, assignedKmedoidsClusters);
					cout << " -> Rand Index: " << RI.getIndexValue() << endl;
				}
			}

			wcssValues.push_back(wcss);
			cout << "k = " << k << " WCSS = " << wcss << endl;
		}


	}

	// RESULTADOS -----------------------------------------------------------
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end-start;
	cout << "*****" << endl;
	cout << "Tiempo de ejecucion: " << diff.count() << " s\n";
	std::cout << "Duración: " << diff.count() << " segundos" << std::endl;
}
