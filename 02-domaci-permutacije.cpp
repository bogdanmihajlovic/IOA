#include <iostream>
#include <algorithm>

const int NA = 4;
const int NB = 12;

void findMinPath(int);

double holes[12][2] = { {2.7, 33.1}, {2.7, 56.8}, {9.1, 40.3}, {9.1, 52.8},
	{15.1, 49.6}, {15.3, 37.8}, {21.5, 45.8}, {22.9, 32.7}, {33.4, 60.5}, {28.4, 31.7},
	{34.7, 26.4}, {45.7, 25.1}
};


double l2Norma(double x1, double y1, double x2, double y2){
	double x = x1 - x2; 
	double y = y1 - y2;
	double dist;

	dist = x*x + y*y;       
	dist = sqrt(dist);

	return dist;
}

void copyPath(double** path1, double** path2, int size) {
	for (int i = 0; i < size; i++) {
		path2[i][0] = path1[i][0];
		path2[i][1] = path1[i][1];
	}
}

int main() {
	std::cout << "Prvih 8 tacaka\n";
	findMinPath(8);
	std::cout << "\nPrvih 12 tacaka\n";
	findMinPath(12);
	return 0;
}

void findMinPath(int size) {
	int permu[12] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

	int num = 0;
	double minDistance = 9999999.9;
	int minPath[12] = { 0 };

	do {

		double distance = 0;
		for (int i = 0; i < size - 1; i++) {
			int hole1 = permu[i];
			int hole2 = permu[i + 1];

			distance += l2Norma(holes[hole1][0], holes[hole1][1], holes[hole2][0], holes[hole2][1]);
			if (distance > minDistance)
				break;
		}
		if (distance < minDistance) {
			minDistance = distance;
			std::copy(permu, permu + size, minPath);
		}

	}while (std::next_permutation(permu, permu + size));
	
	for (int i = 0; i < size; i++) {
		std::cout << minPath[i] + 1 << " ";
	}
	std::cout << std::endl << minDistance;

}
