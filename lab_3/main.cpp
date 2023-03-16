#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>

static bool c[100001];

void Algorithm_1(int32_t n) {
    c[1] = false;
    int32_t i = 2;
    while (i <= n) {
        if (c[i] == true) {
            int32_t j = 2 * i;
            while (j <= n) {
                c[j] = false;
                j = j + i;
            }
        }
        i++;
    }
}

void Algorithm_2(int32_t n) {
    c[1] = false;
    int32_t i = 2;
    while (i <= n) {
        int32_t j = 2 * i;
        while (j <= n) {
            c[j] = false;
            j = j + i;
        }
        i++;
    }
}

void Algorithm_3(int32_t n) {
    c[1] = false;
    int32_t i = 2;
    while (i <= n) {
        if (c[i] == true) {
            int32_t j = i + 1;
            while (j <= n) {
                if (j % i == 0) {
                    c[j] = false;
                }
                j++;
            }
        }
        i++;
    }
}

void Algorithm_4(int32_t n) {
    c[1] = false;
    int32_t i = 2;
    while (i <= n) {
        int32_t j = 1;
        while (j < i) {
            if (i % j == 0) {
                c[i] = false;
            }
            j++;
        }
        i++;
    }
}

void Algorithm_5(int32_t n) {
    c[1] = false;
    int32_t i = 2;
    while (i <= n) {
        int32_t j = 2;
        while (j <= sqrt(i)) {
            if (i % j == 0) {
                c[i] = false;
            }
            j++;
        }
        i++;
    }
}

void display_timed(std::function<void(int32_t)> f, int32_t limit) {
    clock_t start = clock();

    f(limit);
    double timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << std::fixed << std::setprecision(6) << timer << std::endl;
}

int main() {
    std::vector<std::function<void(int32_t)>> Fibonacci_calc_functions = {
            Algorithm_1,
            Algorithm_2,
            Algorithm_3,
            Algorithm_4,
            Algorithm_5};

    uint16_t algo_nr(1);
    for (auto&& i : Fibonacci_calc_functions) {
        uint32_t elem_c(10);
        std::cout << "Algorithm_" << (algo_nr++) << std::endl;
        while (elem_c <= 100000) {
            std::cout << "f(" << elem_c << ") = \t";
            display_timed(i, elem_c);
            elem_c *= 10;
        }

        std::cout << std::endl;
    }
    return 0;
}