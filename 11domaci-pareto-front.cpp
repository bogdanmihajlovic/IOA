#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <fstream>

#define NUMS_S 1000000
#define VECTOR_SIZE 3
const double pi = 3.14159265358979323846;

double H(double a, double b, double S) {
	double z0 = b / 2.0 + 1e-2;
	double N = b * std::sqrt(pi/(4*S));
	double tmp1 = (z0 + (b / 2.0));
	double tmp2 = (z0 - (b / 2.0));
	double cost = tmp1 / std::sqrt(a * a + tmp1 * tmp1) - tmp2 / std::sqrt(a*a + tmp2*tmp2);
	cost = cost * (N / (2.0 * b));
	return cost;
}

double R(double a, double b, double S) {
	double N = b * std::sqrt(pi / (4 * S));
	double cost = N * ((2 * pi * a) / ((58.0*1e6) * S));
	return cost;
}

int main() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> disA(1e-2, 5e-2);
	std::uniform_real_distribution<double> disB(0.1, 0.4);
	std::uniform_real_distribution<double> disS(0.5e-6, 3e-6);

	std::vector<std::vector<double>> dots(NUMS_S);

	std::ofstream AllDots("all.txt");
	std::ofstream ParetoDots("pareto.txt");

	// Generisanje tacaka
	for (int iter = 0; iter < NUMS_S; iter++) {
		dots[iter].push_back(disA(gen));
		dots[iter].push_back(disB(gen));
		dots[iter].push_back(disS(gen));
	}

	std::vector<std::vector<double>> dotsCost(NUMS_S);
	
	// Racunanje vrednosti
	for (int iter = 0; iter < NUMS_S; iter++) {
		double h_value = H(dots[iter][0], dots[iter][1], dots[iter][2]);
		double r_value = R(dots[iter][0], dots[iter][1], dots[iter][2]);

		dotsCost[iter].push_back(h_value);
		dotsCost[iter].push_back(r_value);

		AllDots << h_value << " " << r_value << "\n";
	}

	std::vector<std::vector<double>> pareto;
	int cnt = 0;
	for (int i = 0; i < NUMS_S; i++) {
		bool flag = true;
		double h1 = dotsCost[i][0];
		double r1 = dotsCost[i][1];
		for (int j = 0; j < NUMS_S; j++) {
			double h2 = dotsCost[j][0];
			double r2 = dotsCost[j][1];

			
			if ((h1 <= h2 && r1 >= r2) && (h1 < h2 || r1 < r2)) {
				flag = false;
				break;
			}
		}

		if (flag) {
			cnt++;
			std::vector<double> tmp = { h1, r1 };
			ParetoDots << h1 << " " << r1 << "\n";
			//std::cout << "H: " << h1 << " R: " << r1 << "\n";
			pareto.push_back(tmp);
		}
	}
	std::cout << cnt;




	// 3 2
	// 3 1

	//std::cout << "Pareto optimalni su:\n";

	//for (const auto& elem : pareto) {
	//	std::cout << "H: " << elem[0] << " S: " << elem[1] << "\n";
	//}
	

	return 0;
}