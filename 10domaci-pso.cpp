#include <vector>
#include <random>
#include <cmath>
#include <iostream>
#include <iomanip>

#define NUM_AGENTS 50
#define VECTOR_SIZE 6
#define W 0.729
#define C1 1.494
#define C2 1.494

void printVector(const std::vector<double>& agent);
void printPopulation();
bool endRun();
double f(const std::vector<double>& agent);

std::vector<std::vector<double>> agents(NUM_AGENTS);
std::vector<std::vector<double>> agents_v(NUM_AGENTS);
std::vector<std::vector<double>> agents_best(NUM_AGENTS);
std::vector<double> global_best;

const double dots[6][3] = {
	{1,4,0} ,{3,2,0},{2,7,1},{6,3,3},{7,6,5},{5,7,4}
};


int main() {
	
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_real_distribution<double> disXYZ(0.0, 10.0);
	std::uniform_real_distribution<double> dis1(0, 1.0);

	// Inicijalizacija agenta
	for (int iter = 0; iter < NUM_AGENTS; iter++) {

		// Generisanje pozicije agenta	
		for (int i = 0; i < VECTOR_SIZE; i++) agents[iter].push_back(disXYZ(gen));

		// Postavljanje pbest za agenta 
		for (int i = 0; i < VECTOR_SIZE;i++) agents_best[iter].push_back(disXYZ(gen));

		// Provera za gbest
		if (iter == 0 || f(agents_best[iter]) < f(global_best)) {
			global_best = agents_best[iter];
		}

		// Generisanje pocetne brzine
		for (int i = 0;i < VECTOR_SIZE;i++) agents_v[iter].push_back(0);
	}

	//printPopulation();

	int cnt = 0;
	while (true) {

		for (int iter = 0; iter < NUM_AGENTS; iter++) {

			// racunanje Vn
			for (int i = 0; i < VECTOR_SIZE;i++) {
				double tmp1 = W * agents_v[iter][i];
				double tmp2 = C1 * dis1(gen) * (agents_best[iter][i] - agents[iter][i]);
				double tmp3 = C2 * dis1(gen) * (global_best[i] - agents[iter][i]);
				agents_v[iter][i] = tmp1 + tmp2 + tmp3;
				agents_v[iter][i] = (agents_v[iter][i] > 1.0) ? 1.0 : agents_v[iter][i];
				agents_v[iter][i] = (agents_v[iter][i] < -1.0) ? -1.0 : agents_v[iter][i];
				
			}

			// racunanje Xn
			for (int i = 0; i < VECTOR_SIZE;i++) {
				agents[iter][i] = agents[iter][i] + agents_v[iter][i];
			}

			double fnew = f(agents[iter]); // Nova izracunata vrednost
			double pbest = f(agents_best[iter]); // Najbolja vrednost za agenta
			double gbest = f(global_best); // Globalna najbolja vrednost

			if (fnew < pbest) {
				agents_best[iter] = agents[iter];
			}
			// azuriranje gbest
			if (fnew < gbest) {
				global_best = agents[iter];
				//std::cout << fnew << std::endl;
				//printVector(global_best);
			}
		}

		if (endRun())
			break;
	}
	//printPopulation();

	std::cout << std::fixed << std::setprecision(15) << f(global_best) << std::endl;
	printVector(global_best);
	

	return 0;
}


bool endRun() {
	double s1_xavg = 0;
	double s1_yavg = 0;
	double s1_zavg = 0;

	double s2_xavg = 0;
	double s2_yavg = 0;
	double s2_zavg = 0;

	// Pronalazenje centra za S1 i S2
	for (int iter = 0; iter < NUM_AGENTS;iter++) {
		double s1_x = agents[iter][0];
		double s1_y = agents[iter][1];
		double s1_z = agents[iter][2];

		double s2_x = agents[iter][3];
		double s2_y = agents[iter][4];
		double s2_z = agents[iter][5];

		s1_xavg += s1_x;
		s2_xavg += s2_x;

		s1_yavg += s1_y;
		s2_yavg += s2_y;

		s1_zavg += s1_z;
		s2_zavg += s2_z;

	}

	// centar S1
	s1_xavg /= (NUM_AGENTS * 1.0);
	s1_yavg /= (NUM_AGENTS * 1.0);
	s1_zavg /= (NUM_AGENTS * 1.0);

	// centar S2
	s2_xavg /= (NUM_AGENTS * 1.0);
	s2_yavg /= (NUM_AGENTS * 1.0);
	s2_zavg /= (NUM_AGENTS * 1.0);

	double s1_max_distance = 0;
	double s2_max_distance = 0;
	double distance;


	// Najveca udaljenost == R sfere oko svih tacaka
	for (int iter = 0; iter < VECTOR_SIZE;iter++) {
		distance = 0;

		double s1_x = agents[iter][0];
		double s1_y = agents[iter][1];
		double s1_z = agents[iter][2];

		distance += std::sqrt(std::pow(s1_x - s1_xavg, 2) + std::pow(s1_y - s1_yavg, 2) + std::pow(s1_z - s1_zavg, 2));


		if (distance > s1_max_distance) {
			s1_max_distance = distance;
		}

		double s2_x = agents[iter][3];
		double s2_y = agents[iter][4];
		double s2_z = agents[iter][5];

		distance = 0;
		distance += std::sqrt(std::pow(s2_x - s2_xavg, 2) + std::pow(s2_y - s2_yavg, 2) + std::pow(s2_z - s2_zavg, 2));

		if (distance > s2_max_distance) {
			s2_max_distance = distance;
		}
	}

	if (s1_max_distance < 1e-3 && s2_max_distance < 1e-3)
		return true;

	return false;
}

double f(const std::vector<double>& agent) {
	// a - s1
	// b - s1
	// c - s1
 //	double s1_x = agent[0] * 10;
	//double s1_y = agent[1] * 10;
	//double s1_z = agent[2] * 10;

	//double s2_x = agent[3] * 10;
	//double s2_y = agent[4] * 10;
	//double s2_z = agent[5] * 10;

	double s1_x = agent[0];
	double s1_y = agent[1];
	double s1_z = agent[2];

	double s2_x = agent[3];
	double s2_y = agent[4];
	double s2_z = agent[5];
	double distance = 0;
	for (int i = 0; i < VECTOR_SIZE / 2; i++) {
		double dot_x = dots[i][0];
		double dot_y = dots[i][1];
		double dot_z = dots[i][2];

		distance += std::sqrt(std::pow(s1_x - dot_x, 2) + std::pow(s1_y - dot_y, 2) + std::pow(s1_z - dot_z, 2));
	}
	for (int i = VECTOR_SIZE / 2; i < VECTOR_SIZE; i++) {
		double dot_x = dots[i][0];
		double dot_y = dots[i][1];
		double dot_z = dots[i][2];

		distance += std::sqrt(std::pow(s2_x - dot_x, 2) + std::pow(s2_y - dot_y, 2) + std::pow(s2_z - dot_z, 2));
	}
	distance += std::sqrt(std::pow(s2_x - s1_x, 2) + std::pow(s2_y - s1_y, 2) + std::pow(s2_z - s1_z, 2));
	return distance;
}


void printPopulation() {
	for (int iter = 0; iter < NUM_AGENTS;iter++) {
		std::cout << "[";
		for (int i = 0;i < VECTOR_SIZE;i++) {
			std::cout << agents[iter][i];
			if (i == VECTOR_SIZE - 1) std::cout << "]";
			else std::cout << ", ";
		}
		if (iter != NUM_AGENTS - 1) std::cout << ",\n";
		else std::cout << "\n";
	}
}

void printVector(const std::vector<double>& agent) {
	//std::cout << "S1: " << agent[0] * 10 << " " << agent[1]*10 << " " << agent[2] * 10 << std::endl;
	//std::cout << "S2: " << agent[3] * 10 << " " << agent[4] * 10 << " " << agent[5] * 10 << std::endl;
	std::cout << "S1: " << agent[0] << " " << agent[1] << " " << agent[2] << std::endl;
	std::cout << "S2: " << agent[3] << " " << agent[4] << " " << agent[5] << std::endl;
}
