#include <cmath>
#include <iomanip>
#include <iostream>

double fact(double digit) {
    double result = 1;
    for (int i = digit; i > 1; i--) {
        result *= i;
    }
    return result;
}

// Chudnovsky algorithm
double calc_pi_1() {
    clock_t start = clock();

    double pi = 0.0;
    int precision = 10;
    for (int k = 0; k <= precision; k++) {
        pi += (pow(-1, k) * fact((6 * k)) * (13591409 + 545140134 * k)) / (fact(3 * k) * pow(fact(k), 3) * pow(640320, (3 * k + 1.5)));
    }
    pi = 1.0 / (12 * pi);

    double timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << std::fixed << std::setprecision(6) << timer << std::setprecision(80) << std::fixed << std::endl;

    return pi;
}

// Leibniz algorithm
double calc_pi_2() {
    clock_t start = clock();

    double pi = 0.0;
    int sign = 1;

    for (int i = 0; i < 100000; i++) {
        pi += sign * 4.0 / (2 * i + 1);
        sign *= -1;
    }

    double timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << std::fixed << std::setprecision(6) << timer << std::setprecision(80) << std::fixed << std::endl;

    return pi;
}

// Bailey-Borwein-Plouffe algorithm
double calc_pi_3() {
    clock_t start = clock();

    double pi = 0.0;

    for (int k = 0; k < 100000; ++k) {
        double numerator = 1.0 / pow(16, k);
        double term1 = 4.0 / (8 * k + 1);
        double term2 = 2.0 / (8 * k + 4);
        double term3 = 1.0 / (8 * k + 5);
        double term4 = 1.0 / (8 * k + 6);

        pi += numerator * (term1 - term2 - term3 - term4);
    }

    double timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << std::fixed << std::setprecision(6) << timer << std::setprecision(80) << std::fixed << std::endl;

    return pi;
}

int main() {
    std::cout << std::endl
              << "Method 1:\n"
              << calc_pi_1() << std::endl
              << std::endl
              << "Method 2:\n"
              << calc_pi_2() << std::endl
              << std::endl
              << "Method 3:\n"
              << calc_pi_3() << std::endl
              << std::endl
              << "C++ Defined Pi:\n"
              << M_PI << std::endl
              << std::endl;
}