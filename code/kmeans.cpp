#include "kmeans.h"

kmeans::kmeans(){

}

vector<vector<double>> kmeans::kMeans(vector<vector<double>>& data, vector<vector<int>>& assigDadesClustersFinal, vector<int>& Cluster_Punts, int k, int n, int d) {
	//inicialitzacio de centroides amb dimensions aleatories entre 0 i 1
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> distribution(0, 1);
	vector<vector<double>> centroides(k, (vector<double>(d))), centroides_ant(k, (vector<double>(d, -1)));
	for (int l = 0; l < k; ++l) {
		for (int j = 0; j < d; ++j) {
			centroides[l][j] = distribution(gen);
		}
	}

	//vector<vector<int>> assigDadesClustersFinal;
	//entrem al bucle de reorganitzar clusters i centroides fins que el centroides siguin estables
	int iteracions = 0;
	bool iguals = false;
	while (not iguals) {
		iguals = true;
		centroides_ant = centroides;

		//assignem les diferents dades al cluster amb centroide m�s proper
		vector<vector<int>> assigDadesClusters(k);
		// serveix per poder assignar el punt
		vector<int> clsuter_assignat_a_punt(n);

		assignar_dades_cluster(assigDadesClusters, clsuter_assignat_a_punt, n,  k, d, data, centroides);

		//recalculem els centroides
		recalcular_centroides(k, d, assigDadesClusters, data, centroides);

		//comprovem si els centroides han cambiat de posicio
		for (int l = 0; l < k and iguals; ++l) {
			for (int j = 0; j < d and iguals; ++j) {
				if (centroides[l][j] != centroides_ant[l][j]) iguals = false;
			}
		}

		assigDadesClustersFinal = assigDadesClusters;
		Cluster_Punts = clsuter_assignat_a_punt;
		++iteracions;

	}

	/* for (int l = 0; l < k; ++l) {
		cout << "El centroide " << l << " acaba amb les dimensions --> ";
		for (int j = 0; j < d; ++j) {
			cout << centroides[l][j] << " ";
		}
		cout << endl;
	} */
	cout <<	"Iteraciones: " << iteracions << endl;
	return centroides;
}

vector<vector<double>> kmeans::kMeansPP(vector<vector<double>>& data, vector<vector<int>>& assigDadesClustersFinal, vector<int>& Cluster_Punts,int k, int n, int d) {
	//inicialitzacio de centroides amb dimensions aleatories entre 0 i 1
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> distribution(0, n);
	vector<vector<double>> centroides(k, (vector<double>(d))), centroides_ant(k, (vector<double>(d, -1)));
	for (int l = 0; l < k; ++l) {
		for (int j = 0; j < d; ++j) {
			int i = distribution(gen);
			centroides[l][j] = data[i][j];
		}
	}


	//vector<vector<int>> assigDadesClustersFinal;
	//entrem al bucle de reorganitzar clusters i centroides fins que el centroides siguin estables
	int iteracions = 0;
	bool iguals = false;
	while (not iguals) {
		iguals = true;
		centroides_ant = centroides;

		//assignem les diferents dades al cluster amb centroide m�s proper
		vector<vector<int>> assigDadesClusters(k);
		// serveix per poder assignar el punt
		vector<int> clsuter_assignat_a_punt(n);

		assignar_dades_cluster(assigDadesClusters, clsuter_assignat_a_punt, n, k, d, data, centroides);

		//recalculem els centroides
		recalcular_centroides(k, d, assigDadesClusters, data, centroides);

		//comprovem si els centroides han cambiat de posicio
		for (int l = 0; l < k and iguals; ++l) {
			for (int j = 0; j < d and iguals; ++j) {
				if (centroides[l][j] != centroides_ant[l][j]) iguals = false;
			}
		}

		assigDadesClustersFinal = assigDadesClusters;
		Cluster_Punts = clsuter_assignat_a_punt;
		
	}
	
	for (int l = 0; l < k; ++l) {
		cout << "El centroide " << l << " acaba amb les dimensions --> ";
		for (int j = 0; j < d; ++j) {
			cout << centroides[l][j] << " ";
		}
		cout << endl;
	}

	return centroides;
}

void kmeans::recalcular_centroides(int k, int d, vector<vector<int>>& assigDadesClusters, vector<vector<double>>& data, vector<vector<double>>& centroides) {

	for (int l = 0; l < k; ++l) {
		for (int j = 0; j < d; ++j) {
			double suma = 0.0;
			int size = assigDadesClusters[l].size();
			for (int i = 0; i < size; ++i) {
				suma += data[assigDadesClusters[l][i]][j];
			}
			if (size != 0) centroides[l][j] = suma / double(size);
		}
	}

}

void kmeans::assignar_dades_cluster(vector<vector<int>>& assigDadesClusters, vector<int>& clsuter_assignat_a_punt, int n, int k, int d, vector<vector<double>>& data, vector<vector<double>>& centroides) {
	
	for (int i = 0; i < n; ++i) {
		double distMin = -1.0;
		int centroideSeleccionat = -1;
		for (int l = 0; l < k; ++l) {
			double novaDist = distanciaEuclidiana(i, centroides[l], data, d);
			if (distMin == -1 or novaDist < distMin) {
				distMin = novaDist;
				centroideSeleccionat = l;
			}
		}
		assigDadesClusters[centroideSeleccionat].push_back(i);
		clsuter_assignat_a_punt[i] = centroideSeleccionat;
	}
}

double kmeans::distanciaEuclidiana(int i, vector<double> dimCentroide, vector<vector<double>>& data, int d) {
	double distancia = 0;
	for (int j = 0; j < d; ++j) {
		distancia += pow(data[i][j] - dimCentroide[j], 2);
	}
	return sqrt(distancia);
}

void kmeans::print_results(const vector<vector<int> >& assignacio) {
	for (int i = 0; i < assignacio.size(); ++i) {
		cout << "Cluster " << i << ": ";
		for (int j = 0; j < assignacio[i].size(); ++j) {
			cout << assignacio[i][j] << " ";
		}
		cout << endl << endl << endl << endl;
	}
	cout << endl;
}