#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <iostream>

using namespace std;

class dataset {
	public:
		dataset();
		void replaceCommaWithDot(string &s);
		vector<string> split(const string &s, char delimiter);
		int llegirReadme(string readmeEscollit);
		int llegirDataset(string datasetEscollit);
		int getK();
		int getD();
		int getN();
		double getMin();
		double getMax();
		bool getEtiqueta();
		vector<vector<double>> getData();
		vector<int> getEtiquetes();
		void normalitzar(vector<pair<double, double>>& maxims_i_minims);
		
	private:
		int k, d, n;
		double min, max;
		bool etiqueta;
		vector<vector<double>> data;
		vector<int> etiquetes; //nomes utilitzat en cas de que etiqueta == true
};

