#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#define ARRAY_SIZE 100000

static uint16_t x = 0x15, y = 0xE5, z = 0xB5;

inline uint16_t fast_rand() {
    x ^= x << 0x10;
    x ^= x >> 0x5;
    x ^= x << 0x1;

    uint16_t t(x);
    x = y;
    y = z;
    z = t ^ x ^ y;

    return z;
}

inline void swap(uint16_t& arr, uint16_t& b) {
    uint16_t t = arr;
    arr = b;
    b = t;
}

inline int32_t partition(uint16_t (&arr)[ARRAY_SIZE], int32_t low, const int32_t high) {
    int32_t pivot(arr[high]);

    for (int32_t j = low + 1; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[low], arr[j]);
            low++;
        }
    }

    swap(arr[low], arr[high]);

    return low;
}

inline void merge(uint16_t (&arr)[ARRAY_SIZE], const int32_t left, const int32_t mid, const int32_t right) {
    const int32_t sub_1(mid - left + 1);
    const int32_t sub_2(right - mid);

    int32_t* left_arr(new int32_t[sub_1]);
    int32_t* right_arr(new int32_t[sub_2]);

    for (int32_t i = 0; i < sub_1; i++)
        left_arr[i] = arr[left + i];
    for (int32_t j = 0; j < sub_2; j++)
        right_arr[j] = arr[mid + j + 1];

    int32_t ind_sub_1(0);
    int32_t ind_sub_2(0);
    int32_t ind_merged(left);

    while (ind_sub_1 < sub_1 && ind_sub_2 < sub_2) {
        if (left_arr[ind_sub_1] <= right_arr[ind_sub_2]) {
            arr[ind_merged] = left_arr[ind_sub_1];
            ind_sub_1++;
        } else {
            arr[ind_merged] = right_arr[ind_sub_2];
            ind_sub_2++;
        }

        ind_merged++;
    }

    while (ind_sub_1 < sub_1) {
        arr[ind_merged] = left_arr[ind_sub_1];
        ind_sub_1++;
        ind_merged++;
    }

    while (ind_sub_2 < sub_2) {
        arr[ind_merged] = right_arr[ind_sub_2];
        ind_sub_2++;
        ind_merged++;
    }
}

inline void to_heap(uint16_t (&arr)[ARRAY_SIZE], const int32_t high, const int32_t index) {
    int32_t largest(index);
    int32_t l(2 * index + 1);
    int32_t r(2 * index + 2);

    if (l < high && arr[l] > arr[largest])
        largest = l;

    if (r < high && arr[r] > arr[largest])
        largest = r;

    if (largest != index) {
        swap(arr[index], arr[largest]);
        to_heap(arr, high, largest);
    }
}

inline void q_sort(uint16_t (&arr)[ARRAY_SIZE], const int32_t low, const int32_t high) {
    if (low < high) {
        int32_t pi(partition(arr, low, high));
        q_sort(arr, low, pi - 1);
        q_sort(arr, pi + 1, high);
    }
}

inline void m_sort_low(uint16_t (&arr)[ARRAY_SIZE], const int32_t low, const int32_t high) {
    if (low == high)
        return;

    int32_t half = (low + high) / 2;
    m_sort_low(arr, low, half);
    m_sort_low(arr, half + 1, high);

    int32_t b[high - low + 1];
    int32_t count(0);
    int32_t left(low);
    int32_t right(half + 1);

    while (left <= half && right <= high) {
        if (arr[left] < arr[right]) {
            b[count] = arr[left];
            left++;
        } else {
            b[count] = arr[right];
            right++;
        }
        count++;
    }
    if (right > high) {
        while (left <= half) {
            b[count++] = arr[left++];
        }
    }
    if (left > half) {
        while (right <= high) {
            b[count++] = arr[right++];
        }
    }

    count = 0;
    for (int32_t j(low); j <= high; arr[j++] = b[count++]) {}
}

inline void m_sort_high(uint16_t (&arr)[ARRAY_SIZE], const int32_t low, const int32_t high) {
    if (low >= high)
        return;

    int32_t mid(low + (high - low) / 2);
    m_sort_high(arr, low, mid);
    m_sort_high(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

inline void m_sort(uint16_t (&arr)[ARRAY_SIZE], const int32_t low, const int32_t high) {
#if arr_size <= 600000
    m_sort_low(arr, low, high);
#else
    m_sort_high(arr, low, high);
#endif
}

inline void h_sort(uint16_t (&arr)[ARRAY_SIZE], const int32_t low, const int32_t high) {
    for (int32_t i = high / 2 - 1; i >= low; i--)
        to_heap(arr, high, i);

    for (int32_t i = high - 1; i > low; i--) {
        swap(arr[0], arr[i]);
        to_heap(arr, i, 0);
    }
}

void i_sort(uint16_t (&arr)[ARRAY_SIZE], const int32_t low, const int32_t high) {
    for (int32_t i = low + 1; i < high; i++) {
        int32_t key = arr[i], j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j -= 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    // generate array using pseudo-random algo. (always the array will be same)
    uint16_t arr[ARRAY_SIZE];

    for (int32_t i = 0; i < ARRAY_SIZE; *(arr + i++) = fast_rand()) {}

    // set timer 
    clock_t start = clock();

    // q_sort(arr, 0, ARRAY_SIZE);
    // m_sort(arr, 0, ARRAY_SIZE);
    // h_sort(arr, 0, ARRAY_SIZE);
    // i_sort(arr, 0, ARRAY_SIZE);
    std::sort(std::begin(arr), std::end(arr));

    double timer = static_cast<double>(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Time taken: " << std::fixed << std::setprecision(6) << timer << std::endl;
     
    // for (int32_t i = 0; i < ARRAY_SIZE; printf("%d ", *(arr + i++))) {}

    return 0;
}
