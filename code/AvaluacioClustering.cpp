#include "AvaluacioClustering.h"

AvaluacioClustering::AvaluacioClustering() {

}

/*vector<vector<double>> AvaluacioClustering::silhouette(vector<vector<int>>& cluster, vector<vector<double>>& data, int k, int n, int d) {
	vector<vector<double>> SiluetaPerPunt(k);
	// Per cada cluster
	for (int Cluster_1 = 0; Cluster_1 < k; ++Cluster_1) {
		// si el cluster nomes te nomes un elemet la seva silueta es 0
		if (cluster[Cluster_1].size() == 1) {
			SiluetaPerPunt[Cluster_1].push_back(0.0);
		}
		//per cada punt del cluster 
		else {
			for (int PuntsPerCluster_1 = 0; PuntsPerCluster_1 < cluster[Cluster_1].size(); ++PuntsPerCluster_1) {

				// agafem el punt del cluster i-essim
				int Punt_Base = cluster[Cluster_1][PuntsPerCluster_1];
				double suma = 0.0;
				// Calcul de la distancia mitjana de un punt a tots els altres del mateix cluster
				for (int PuntsPerCluster_2 = 0; PuntsPerCluster_2 < cluster[Cluster_1].size(); ++PuntsPerCluster_2) {
					int Punt_distant = cluster[Cluster_1][PuntsPerCluster_2];
					if (Punt_Base != Punt_distant) {
						suma += distanciaEuclidiana(Punt_Base, Punt_distant, data, d);
					}
				}

				double Distancia_Mitjana = suma / cluster[Cluster_1].size();
				double Minim = numeric_limits<double>::max();
				// ara em de calcular la mitjana entre tots els punts de cluster diferent, i el punt base
				// cluster per cluster i ens cadarem la mitjana mes petita
				for (int Cluster_2 = 0; Cluster_2 < k; ++Cluster_2) {
					if (Cluster_1 != Cluster_2) {
						suma = 0.0;
						// Per totes els punts del cluster diferent el punt base
						for (int PuntsPerCluster_2 = 0; PuntsPerCluster_2 < cluster[Cluster_2].size(); ++PuntsPerCluster_2) {
							int punt_diferent_cluster = cluster[Cluster_2][PuntsPerCluster_2];
							suma += distanciaEuclidiana(Punt_Base, punt_diferent_cluster, data, d);

						}

						double Distancia_mitjana_ClusterDiferent = suma / cluster[Cluster_2].size();
						if (Distancia_mitjana_ClusterDiferent < Minim) {
							Minim = Distancia_mitjana_ClusterDiferent;
						}


					}
				}
				//cout << "Cluster " << Cluster_1 << ":" << ' '  << Minim << ' ' << Distancia_Mitjana << endl;
				double silueta = ((Minim - Distancia_Mitjana) / max(Distancia_Mitjana, Minim));
				SiluetaPerPunt[Cluster_1].push_back(silueta);
			}
		}
	}
	return SiluetaPerPunt;
}
*/

vector<vector<double>> AvaluacioClustering::silhouette_Optimitzada(vector<vector<int>>& cluster, vector<vector<double>>& data, vector<vector<double>>& centroides, int k, int n, int d) {

	vector<vector<double>> SiluetaPerPunt(k);

	for (int Cluster_1 = 0; Cluster_1 < k; ++Cluster_1) {
		for (int PuntPerCluster = 0; PuntPerCluster < cluster[Cluster_1].size(); ++PuntPerCluster) {

			int Punt_Base = cluster[Cluster_1][PuntPerCluster];
			double Distancia_Punt_Centroide = distanciaEuclidiana(Punt_Base, Cluster_1, data, centroides, d);

			double Minim = numeric_limits<double>::max();
			for (int cluster_2 = 0; cluster_2 < k; ++cluster_2) {
				if (Cluster_1 != cluster_2) {
					
					double distancia_Centroide_Ex = distanciaEuclidiana(Punt_Base, cluster_2, data, centroides, d);
					if (Minim > distancia_Centroide_Ex) {
						Minim = distancia_Centroide_Ex;
					}
				}
			}

			double silueta = (Minim - Distancia_Punt_Centroide) / (max(Distancia_Punt_Centroide, Minim));
			SiluetaPerPunt[Cluster_1].push_back(silueta);

		}
	}

	return SiluetaPerPunt;

}

vector<vector<double>> AvaluacioClustering::silhouette_Optimitzada_Kmediods(vector<vector<int>>& cluster, vector<vector<double>>& data, vector<vector<double>>& centroides, int k, int n, int d) {

	vector<vector<double>> SiluetaPerPunt(k);

	for (int Cluster_1 = 0; Cluster_1 < k; ++Cluster_1) {
		for (int PuntPerCluster = 0; PuntPerCluster < cluster[Cluster_1].size(); ++PuntPerCluster) {

			int Punt_Base = cluster[Cluster_1][PuntPerCluster];
			double Distancia_Punt_Centroide = distanciaEuclidiana(Punt_Base, Cluster_1, data, centroides, d);

			double Minim = numeric_limits<double>::max();
			for (int cluster_2 = 0; cluster_2 < k; ++cluster_2) {
				if (Cluster_1 != cluster_2) {

					double distancia_Centroide_Ex = distanciaEuclidiana(Punt_Base, cluster_2, data, centroides, d);
					if (Minim > distancia_Centroide_Ex) {
						Minim = distancia_Centroide_Ex;
					}
				}
			}

			double silueta = double(1 - (Distancia_Punt_Centroide/Minim));
			SiluetaPerPunt[Cluster_1].push_back(silueta);

		}
	}
	return SiluetaPerPunt;
}

double AvaluacioClustering::distanciaEuclidiana(int Punt_Base, int Punt_distant, vector<vector<double>>& data, vector<vector<double>>& centroides, int d) {
	double distancia = 0;
	for (int j = 0; j < d; ++j) {
		distancia += pow(data[Punt_Base][j] - centroides[Punt_distant][j], 2);
	}
	return sqrt(distancia);
}

void AvaluacioClustering::printResultat(vector<vector<double>> siluetes) {
	for (int i = 0; i < siluetes.size(); ++i) {
		cout << "Cluster " << i << ": ";
		for (int j = 0; j < siluetes[i].size(); ++j) {
			cout << siluetes[i][j] << ' ';
		}
		cout << endl;
	}
}