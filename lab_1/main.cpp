#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>

boost::multiprecision::uint1024_t Fibonacci_a(size_t limit) {
    boost::multiprecision::uint1024_t result = 0;
    std::pair<boost::multiprecision::uint1024_t, boost::multiprecision::uint1024_t> container;

    container.first = 0;
    container.second = 1;

    for (size_t i = 2; i <= limit; i++) {
        boost::multiprecision::uint1024_t temp = container.first + container.second;
        container.first = container.second;
        container.second = temp;
    }

    result = container.second;

    return result;
}

boost::multiprecision::uint1024_t Fibonacci_b(size_t limit) {

    boost::multiprecision::uint1024_t result = 0;
    boost::multiprecision::uint1024_t f[limit + 1];
    f[0] = 0;
    f[1] = 1;
    for (size_t i = 2; i <= limit; i++)
        f[i] = f[i - 1] + f[i - 2];

    result = f[limit];

    return result;
}

boost::multiprecision::uint1024_t Fibonacci_c(size_t limit) {
    return static_cast<boost::multiprecision::uint1024_t>((pow((1 + sqrt(5)) / 2, limit) - pow((1 - sqrt(5)) / 2, limit)) / sqrt(5));
}

boost::multiprecision::uint1024_t Fibonacci_d(size_t limit) {
    boost::multiprecision::uint1024_t a = 0, b = 1, result = 0, row;

    while (limit >= 2) {
        result = a + b;
        a = b;
        b = result;
        limit--;
    }

    return result;
}

boost::multiprecision::uint1024_t Fibonacci_e(size_t limit) {
    if ((limit == 0) || (limit == 1)) {
        return limit;
    } else {
        return Fibonacci_e(limit - 1) + Fibonacci_e(limit - 2);
    }
}

boost::multiprecision::uint1024_t Fibonacci_f(size_t limit) {
    std::vector<size_t> temp{0, 1};
    while (temp.size() <= limit) {
        auto end = temp.size();
        temp.push_back(temp[end - 1] + temp[end - 2]);
    }
    return temp[limit];
}

void display_timed(std::function<boost::multiprecision::uint1024_t(size_t)> f, size_t limit) {
    clock_t start = clock();

    std::cout << f(limit) << '\t';
    double timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << std::fixed << std::setprecision(6) << timer << std::endl;
}

int main() {
    size_t arr1[] = {5, 7, 10, 12, 15, 17, 20, 22, 25, 27, 30, 32, 35, 37, 40, 42, 45};
    size_t arr2[] = {501, 631, 794, 1000, 1259, 1585, 1995, 2512, 3162, 3981, 5012, 6310, 7943, 10000, 12589, 15849};

    std::vector<std::function<boost::multiprecision::uint1024_t(size_t)>> Fibonacci_calc_functions = {
            Fibonacci_a,
            Fibonacci_b,
            // Fibonacci_c,
            Fibonacci_d,
            Fibonacci_f};

    for (auto&& i : Fibonacci_calc_functions) {
        for (auto&& limit : arr2) {
            std::cout << "f(" << limit << ") = ";
            display_timed(i, limit);
        }

        std::cout << std::endl;
    }

    for (auto&& limit : arr1) {
        std::cout << "f(" << limit << ") = ";
        display_timed(Fibonacci_e, limit);
    }
    return 0;
}