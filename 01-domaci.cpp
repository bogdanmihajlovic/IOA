#include <iostream>
#include <complex>

int const MAX_PRICE = 777;
int const MIN_PRICE = 1;
int const K = 1000000;

using namespace std;

long long exampleA(FILE* out) {
	long long int attemps = 0;

	for (int i1 = MIN_PRICE; i1 < MAX_PRICE; i1++) {
		for (int i2 = MIN_PRICE; i2 < MAX_PRICE; i2++) {
			for (int i3 = MIN_PRICE; i3 < MAX_PRICE; i3++) {
				for (int i4 = MIN_PRICE; i4 < MAX_PRICE; i4++) {
					attemps++;
					int sum = i1 + i2 + i3 + i4;
					int mul = i1 * i2 * i3 * i4;

					if (sum == MAX_PRICE && mul == MAX_PRICE * K) {
						printf("%d %d %d %d mul = %d\n", i1, i2, i3, i4, mul);
						fprintf_s(out, "Primer pod a: %d %d %d %d, broj iteracija ", i1, i2, i3, i4);
						return attemps;
					}
				}
			}
		}
	}

	return attemps;
}

int exampleB(FILE* out) {
	int attemps = 0;

	for (int i1 = MIN_PRICE; i1 < MAX_PRICE; i1++) {
		for (int i2 = MIN_PRICE; i2 < MAX_PRICE; i2++) {
			for (int i3 = MIN_PRICE; i3 < MAX_PRICE; i3++) {
				attemps++;
				int i4 = MAX_PRICE - (i1 + i2 + i3);
				int sum = i1 + i2 + i3 + i4;
				int mul = (i1 * i2 * i3 * i4);
				if (mul == MAX_PRICE * K) {
					printf("%d %d %d %d mul = %d\n", i1, i2, i3, i4, mul);
					fprintf_s(out, "%d %d %d %d", i1, i2, i3, i4);
					return attemps;
				}
			}
		}
	}

	return attemps;
}

int main() {

	FILE* out;
	fopen_s(&out, "OutFile.txt", "w+");

	long long int attempsA = exampleA(out);
	int attempsB = exampleB(out);

	cout << "Primer pod a, broj pokusaja = " << attempsA << endl;
	cout << "Primer pod b, broj pokusaja = " << attempsB << endl;


	return 0;
}
