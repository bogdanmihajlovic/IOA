#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>

#define N 24
#define SIZE_POPULATION 60
#define F 0.8
#define CR 0.8

#define Xp1 0
#define Yp1 1
#define Xp2 2
#define Yp2 3
#define A1 4 
#define A2 5

double s[N] = { -0.09940112332480822, -0.09570265063923192, -0.07782620994584906,
	-0.044595775065571636, -0.008470411838648773, -0.0013292572938769093,
	-0.01402876134848341, 0.0011785680597112547, -0.0016096599564817682,
	-0.03141072397571561, -0.05773121434057853, -0.07098734083487862,
	-0.07421256224434619, -0.09674779542915338, -0.13216942328836218,
	-0.18406033359301877, -0.24214426775005213, -0.25978279767024376,
	-0.2186443973931424, -0.3289283483195699, -0.4205252223787085,
	-0.32130499477499636, -0.205134242990832, -0.13760381018149595 };

double xpos[N] = { -15, -10, -5, 0, 5, 10, 15, 15, 15, 15, 15, 15, 15, 10, 5, 0, -5, -10, -15,  -15, -15, -15, -15, -15 };
double ypos[N] = { -15, -15, -15, -15, -15, -15, -15, -10, -5, 0, 5, 10,  15, 15, 15, 15, 15, 15, 15, 10, 5, 0, -5, -10 };

double f(const std::vector<double>& x) {
	double calc = 0;
	for (int i = 0; i < N; i++) {
		double temp1 = x[A1] / std::sqrt(
			(xpos[i] - x[Xp1]) * (xpos[i] - x[Xp1]) + 
			(ypos[i] - x[Yp1]) * (ypos[i] - x[Yp1])
			);

		double temp2 = x[A2] / std::sqrt(
			(xpos[i] - x[Xp2]) * (xpos[i] - x[Xp2]) +
			(ypos[i] - x[Yp2]) * (ypos[i] - x[Yp2])
		);
		double temp = (temp1 + temp2 - s[i]) * (temp1 + temp2 - s[i]);

		calc += temp;
	}

	if(x[A1] < -15 || x[A1] > 15 || x[A2] < -15 || x[A2] > 15 || 
			x[Xp1] < -15 || x[Xp1] > 15 || x[Xp2] < -15 || x[Xp2] > 15 ||
			x[Yp1] < -15 || x[Yp1] > 15 || x[Yp2] < -15 || x[Yp2] > 15)
			calc += 1000;
	return calc;
}

std::vector<double> calculateZ(const std::vector<double>& xa, const std::vector<double>& xb, const std::vector<double>& xc) {
	
	if (xa.size() == xb.size() && xb.size() == xc.size()) {
		
		std::vector<double> z(xa.size());
		for (int i = 0; i < xb.size(); i++) {
			z[i] = xa[i] + F*(xb[i] - xc[i]);
		}

		return z;
	}
	else {
		throw std::invalid_argument("Vektori nisu iste duzine.");
	}
}
std::vector<double> calculateY(const std::vector<double>& x, const std::vector<double>& z) {
	std::vector<double> y(x.size());

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis1(0, 5);
	int R = dis1(gen);
	std::uniform_real_distribution<double> dis(0.0, 1.0);


	for (int i = 0; i < x.size(); i++) {
		double r = dis(gen);
		if (r < 0.8 || i == R) {
			y[i] = z[i];
		}
		else {
			y[i] = x[i];
		}
	}
	return y;
}

void printVector(const std::vector<double>& v) {
	std::cout << std::setprecision(15);
	for (const auto& elem : v) {
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}


int main() {

	std::vector<std::vector<double>> population(SIZE_POPULATION);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis1(-15.0, 15.0);

	for (int iter = 0; iter < SIZE_POPULATION; iter++) {
		for (int i = 0; i < 6; i++) {
			population[iter].push_back(dis1(gen));
		}
	}

	std::uniform_int_distribution<int> dis2(0, SIZE_POPULATION - 1);
	double minF = 9999.99;
	std::vector<double> minVector(6);
	while (true) {
		for (int iter = 0; iter < SIZE_POPULATION; iter++) {
			int indexa;
			do {
				indexa = dis2(gen);
			} while (indexa == iter);

			int indexb;
			do {
				indexb = dis2(gen);
			} while (indexa == indexb || indexb == iter);

			int indexc;
			do {
				indexc = dis2(gen);
			} while (indexc == indexb || indexc == indexa || indexc == iter);

			std::vector<double> x = population[iter];
			std::vector<double> xa = population[indexa];
			std::vector<double> xb = population[indexb];
			std::vector<double> xc = population[indexc];

			std::vector<double> z = calculateZ(xa, xb, xc);
			std::vector<double> y = calculateY(x, z);

			double fx = f(x);
			double fy = f(y);

			if (fy < fx) {
				population[iter] = y;
			}

			if (f(population[iter]) < minF) {
				minF = f(population[iter]);
				minVector = population[iter];
			}
			if (minF < 1e-14) {
				std::cout << minF << std::endl;
				printVector(minVector);
				std::cout << f(minVector) << std::endl;
				return 0;
			}
		}

	}

	

	return 0;
}