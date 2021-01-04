#include <iostream>
#include <vector>

int64_t fibonacci_slow(int64_t n) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fibonacci_slow(n - 1) + fibonacci_slow(n - 2);
    }
}

int64_t fibonacci_memo(int64_t n, std::vector<int64_t>& memo) {
    if (n <= 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else if (memo[n] > 0) {
        return memo[n];
    }

    memo[n] = fibonacci_memo(n - 1, memo) + fibonacci_memo(n - 2, memo);
    return memo[n];
}

int64_t fibonacci_fast(int64_t n) {
    int64_t v1 = 0;
    int64_t v2 = n <= 0 ? 0 : 1;
    for (int64_t i = 1; i < n; i++) {
        int64_t sum = v1 + v2;
        v1 = v2;
        v2 = sum;
    }
    return v2;
}

int main() {
    int64_t n = 50;
    for (int64_t i = 0; i < n; i++) {
        std::cout << fibonacci_fast(i) << " ";
    }
    std::cout << std::endl;

    std::vector<int64_t> memo(n + 1);
    for (int64_t i = 0; i < n; i++) {
        std::cout << fibonacci_memo(i, memo) << " ";
    }
    std::cout << std::endl;

    for (int64_t i = 0; i < n; i++) {
        std::cout << fibonacci_slow(i) << " ";
    }
    std::cout << std::endl;
    return 0;
}
