#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Create a vector of integers
    std::vector<int> numbers = {5, 3, 8, 1, 2};

    // Print the original vector
    std::cout << "Original numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    // Sort the vector in ascending order
    std::sort(numbers.begin(), numbers.end());

    // Print the sorted vector
    std::cout << "Sorted numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Find the maximum element in the vector
    auto maxElement = *std::max_element(numbers.begin(), numbers.end());
    std::cout << "Maximum element: " << maxElement << std::endl;
    // Find the minimum element in the vector
    auto minElement = *std::min_element(numbers.begin(), numbers.end());
    std::cout << "Minimum element: " << minElement << std::endl;
    return 0;
}