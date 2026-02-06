//
// Created by alice on 06.02.2026.
//
#include <iostream>
#include <random>

const std::string TARGET = "methinksitislikeaweasel";
const size_t STRING_LENGTH = 23;
const double MUTATION_PROBABILITY = 0.05;
const int COPIES_COUNT = 100;
std::random_device rd;
std::default_random_engine engine(rd());

char generate_random_letter() {
    std::uniform_int_distribution<int> letter_dist(0, 25);
    int random_index = letter_dist(engine);
    return static_cast<char>('a' + random_index);
}

std::string generate_initial_string() {
    std::string result;
    for (size_t i = 0; i < STRING_LENGTH; i++) {
        result += generate_random_letter();
    }
    return result;
}

std::string mutate_string(const std::string &original) {
    std::string mutant = original;
    std::uniform_real_distribution<double> prob_dist(0.0, 1.0);
    for (size_t i = 0; i < STRING_LENGTH; i++) {
        double percent = prob_dist(engine);
        if (percent < MUTATION_PROBABILITY) {
            mutant[i] = generate_random_letter();
        }
    }
    return mutant;
}

int calculate_differences(const std::string &str) {
    int differ_count = 0;
    for (size_t i = 0; i < STRING_LENGTH; i++) {
        if (TARGET[i] != str[i]) {
            differ_count += 1;
        }
    }
    return differ_count;
}

int main() {
    std::string current = generate_initial_string();
    int iteration = 0;
    bool target_found = false;

    while (!target_found) {
        iteration += 1;

        std::cout << "Итерация " << iteration << ": "
                  << current << " (расхождение: "
                  << calculate_differences(current) << ")" << std::endl;

        std::string best_mutant = current;
        int best_fitness = calculate_differences(current);

        for (int copy = 0; copy < COPIES_COUNT; ++copy) {
            std::string mutant = mutate_string(current);

            int fitness = calculate_differences(mutant);

            if (fitness == 0) {
                std::cout << "Целевая строка найдена: " << TARGET << std::endl;
                target_found = true;
                break;
            }

            if (fitness < best_fitness) {
                best_mutant = mutant;
                best_fitness = fitness;
            }
        }

        if (!target_found) {
            current = best_mutant;
        }
    }

    std::cout << "Потребовалось итераций: " << iteration << std::endl;

    return 0;
}
