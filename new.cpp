#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Create a vector of integers
    std::vector<int> numbers = {5, 3, 8, 1, 2};

    // Sort the vector in ascending order
    std::sort(numbers.begin(), numbers.end());

    // Print the sorted vector
    std::cout << "Sorted numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}