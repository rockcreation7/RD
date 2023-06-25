#include <iostream>
#include <vector>
#include <chrono>

std::vector<int> fibonacci(int n) {
    std::vector<int> sequence;
    int a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        sequence.push_back(a);
        int temp = a;
        a = b;
        b = temp + b;
    }
    return sequence;
}

int main() {
    int n = 1000000; // Number of Fibonacci numbers to generate

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> fibSequence = fibonacci(n);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    for (int num : fibSequence) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    double elapsedMilliseconds = duration.count() / 100000.0;
    std::cout << "Execution time: " << elapsedMilliseconds << " milliseconds" << std::endl;

    return 0;
}

// g++ fibonacci.cpp -o fibonacci
// ./fibonacci