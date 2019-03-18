#include <fifo_median.hpp>
#include <stdio.h>
#include <vector>

int main() {
    // Create a new FifoMedian filter with a maximum capacity of 5 elements
    FifoMedian fifo = FifoMedian(5);

    // Test dataset
    std::vector<float> test_data{0.0, 1.0, 5.0, 2.0, 3.0, 6.0, 9.0};

    // For each item in the test dataset, add it to the median filter and
    // calculate the median
    printf("%.f\n", fifo.calculate_median());
    for (auto &test_data_point : test_data) {

        // "Insert" data into the median filter. Throws out old data past 5
        // elements.
        fifo.insert_data(test_data_point);

        // Find the median value and print it
        printf("%.2f\n", fifo.calculate_median());
    }
}
