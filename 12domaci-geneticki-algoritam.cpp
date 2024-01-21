#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

#define SIZE_POPULATION 15000
#define VECTOR_SIZE 31
#define SELECTION_SIZE 3000
#define N_GEN 50

std::vector<int> x0 = { 1,0,1,0,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,1,1,1,0,0,1,1 };

int f(const std::vector<int>& x) {
    int sum = 0;
    int zero_counter = 0;
    for (int k = 0; k < VECTOR_SIZE;k++) {
        if (x[k] == 0) zero_counter++;

        int cros_same = 0;
        int cros_diff = 0;

        int auto_same = 0;
        int auto_diff = 0;

        for (int i = 0, r = k;i < VECTOR_SIZE;i++, r = (r + 1) % VECTOR_SIZE) {

            if (x0[i] == x[r]) cros_same++;
            else cros_diff++;

            if (x[i] == x[r]) auto_same++;
            else auto_diff++;
        }

        int cros_res = cros_same - cros_diff;
        int auto_res = auto_same - auto_diff;

        if (cros_res > -4 && cros_res < 6) sum += cros_res;
        else sum += 1000; // Penali

        if (k == 0) continue;

        if (auto_res > -18 && auto_res < 12) sum += auto_res;
        else sum += 1000; // Penali

    }

    if (!(zero_counter == 15 || zero_counter == 16))
        sum += 500; // Penali

    return sum;
}

unsigned int bitvector_to_decimal(const std::vector<int>& arr) {
    unsigned int decimal = 0;
    for (int i = 0; i < 31; i++) decimal = (decimal << 1) | arr[i];
    return decimal;
}

std::vector<int> random_vector() {
    std::vector<int> arr(VECTOR_SIZE);
    // broj jedinica u nizu 15 ili 6
    int nums_of_1 = (rand() % 2 == 0) ? 15 : 16;

    for (int i = 0; i < nums_of_1;i++) {
        arr[i] = 1;
    }
    std::random_shuffle(arr.begin(), arr.end());
    return arr;
}




int main() {

    srand((unsigned int)time(NULL));
    std::pair<int, std::vector<int>> population[SIZE_POPULATION];

    for (int n = 0; n < 20;n++) {

        // Generisanje pocetne populacije
        for (int iter = 0; iter < SIZE_POPULATION; iter++) {
            std::vector<int> arr = random_vector();
            population[iter] = std::make_pair(f(arr), arr);
        }

        // Najbolje resenje
        std::vector<int> best_vector = population[0].second;
        int best_f = population[0].first;

        for (int generation = 0; generation < N_GEN;generation++) {

            std::sort(std::begin(population), std::end(population));

            if (population[0].first < best_f) {
                best_f = population[0].first;
                best_vector = population[0].second;
            }

            std::pair<int, std::vector<int>> new_population[SIZE_POPULATION];

            // Kopiranje selektovanih
            for (int iter = 0;iter < SELECTION_SIZE;iter++) {
                new_population[iter] = std::make_pair(population[iter].first, population[iter].second);
            }


            // Pravljenje nove generacije
            for (int new_population_counter = SELECTION_SIZE; new_population_counter < SIZE_POPULATION;new_population_counter += 2) {
                // Selekcija roditelja
                int a;
                int b;
                do {
                    a = rand() % SELECTION_SIZE;
                    b = rand() % SELECTION_SIZE;
                } while (a == b);


                std::vector<int> parent1 = population[a].second;
                std::vector<int> parent2 = population[b].second;

                std::vector<int> child1(VECTOR_SIZE);
                std::vector<int> child2(VECTOR_SIZE);

                int p = rand() % VECTOR_SIZE;

                // Ukrstanje bitova
                for (int pos = 0; pos < VECTOR_SIZE;pos++) {
                    if (pos < p) {
                        child1[pos] = parent1[pos];
                        child2[pos] = parent2[pos];
                    }
                    else {
                        child1[pos] = parent2[pos];
                        child2[pos] = parent1[pos];
                    }
                }

                new_population[new_population_counter] = std::make_pair(f(child1), child1);
                new_population[new_population_counter + 1] = std::make_pair(f(child2), child2);
            }

            // Mutacija
            for (int iter = 0; iter < SIZE_POPULATION; iter++) {
                double r = (double)rand() / (double)RAND_MAX * 1.0;
                if (r <= 0.1) {
                    int position = rand() % VECTOR_SIZE;
                    int bit = rand() % 2;
                    new_population[iter].second[position] = bit;
                    new_population[iter].first = f(new_population[iter].second);
                }
            }

            // Kopiranje
            for (int iter = 0; iter < SIZE_POPULATION;iter++) {
                population[iter].first = new_population[iter].first;
                population[iter].second = new_population[iter].second;
                if (population[iter].first < best_f) {
                    best_f = population[iter].first;
                }
            }
        }

        // Ako nema penala
        if (best_f < 500) {
            std::cout << "Vrednost f " << best_f << '\n';
            std::cout << "Vektor: ";
            for (int i = 0;i < VECTOR_SIZE;i++)
                std::cout << best_vector[i] << ", ";

            std::cout << "\nDecimalna vrednost: " << bitvector_to_decimal(best_vector) << '\n';

            std::cout << "--------\n";
        }

    }

    return 0;
}