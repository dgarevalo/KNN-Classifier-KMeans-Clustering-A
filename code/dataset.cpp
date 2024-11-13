#include "dataset.h"

dataset::dataset() {
}

int dataset::llegirReadme(string readmeEscollit) {
	//obrim l'archiu
	ifstream archiuReadme(readmeEscollit);

	//control d'errors
	if (!archiuReadme.is_open()) {
		return 1;
	}

	string line;
	//per cada linia del readme
	for (int i = 0; i < 4; ++i) {
		getline(archiuReadme, line);
		stringstream ss(line);
		vector<string> row;

		//separem les paraules
		string value;
		while(getline(ss, value, ' ')){
			row.push_back(value);
		}
		//per cada una de les linies comprobem el valor de l'ultima paraula (n, d, k i etiqueta)
		if (i == 0) n = stoi(row[row.size() - 1]);
		if(i == 1) d = stoi(row[row.size() - 1]);
		if (i == 2) {
			string valor = row[row.size() - 1];
			if (valor[valor.size()-1] ==  '?') k = -1;
			else k = stoi(row[row.size() - 1]);
		}
		if (i == 3) {
			if (row[row.size() - 1][0] == 'S') etiqueta = true;
			else etiqueta = false;
		}
	}
	//tanquem l'archiu
	archiuReadme.close();
	return 0;
}

// Función para reemplazar todas las comas por puntos en un string.
void dataset::replaceCommaWithDot(string &s) {
	for (int i = 0; i < s.length(); ++i)
		if (s[i] == ',') s[i] = '.';		
}

vector<string> dataset::split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

int dataset::llegirDataset(string datasetEscollit) {
	//obrim l'archiu
	ifstream archiuDataset(datasetEscollit);

	//control d'errrors
	if (!archiuDataset.is_open()) {
		return 1;
	}
	
	string line;
	int instanciesLlegides = 0;
	//pre cada linea del dataset

	double maxim = numeric_limits<double>::min();
	double minim = numeric_limits<double>::max();
	vector<pair<double, double>> maxim_minims_per_dimensio(d,{maxim,minim});

	while (getline(archiuDataset, line) and instanciesLlegides < n) {
		instanciesLlegides++;
		
		stringstream ss(line);
		vector<double> row;
		replaceCommaWithDot(line); // Convertir comas en puntos para el formato de punto flotante
		vector<string> stringNumbers = split(line, ';');
		int d_etiqueta = d;

		if (etiqueta) d_etiqueta++;

		
		for (int i = 0; i < d_etiqueta; ++i) {
			double newNumber = stod(stringNumbers[i]);
			if (etiqueta and i == d) {
				etiquetes.push_back(newNumber);
			}
			else {
				if (maxim_minims_per_dimensio[i].first < newNumber) {
					maxim_minims_per_dimensio[i].first = newNumber;
				}
				if (maxim_minims_per_dimensio[i].second > newNumber) {
					maxim_minims_per_dimensio[i].second = newNumber;
				}
				row.push_back(newNumber); // Convertir y almacenar cada número como double
			}
			
		}
		//afegim la linia a la matriu
		this->data.push_back(row);
		
	}
	
	normalitzar(maxim_minims_per_dimensio);
	return 0;

}

void dataset::normalitzar(vector<pair<double, double>>& maxims_i_minims) {

	for(int punt = 0; punt < n; ++punt){
		for (int dimensio = 0; dimensio < d; ++dimensio) {
			double operant = data[punt][dimensio] - maxims_i_minims[dimensio].second;
			double divisor = maxims_i_minims[dimensio].first - maxims_i_minims[dimensio].second;
			data[punt][dimensio] = operant / divisor;

			//cout << data[punt][dimensio] << ' ';
		}
		//cout << endl;
	}
}

int dataset::getK() {
	return k;
}

int dataset::getD() {
	return d;
}

int dataset::getN() {
	return n;
}

double dataset::getMin() {
	return min;
}

double dataset::getMax() {
	return max;
}

bool dataset::getEtiqueta() {
	return etiqueta;
}

vector<vector<double> > dataset::getData() {
	return data;
} 

vector<int> dataset::getEtiquetes() {
	return etiquetes;
}