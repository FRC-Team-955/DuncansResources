#include <fifo_median.hpp>

// Construct a new FifoMedian with the specified max length
FifoMedian::FifoMedian(size_t max_length) {
    this->fifo_max_length = max_length;
}

// Insert new data into the FifoMedian
void FifoMedian::insert_data(float data) {
    // Push new data onto the FIFO
    fifo.push_front(data);

    // If the amount of data is larger than that we allow, throw it out
    if (fifo.size() > fifo_max_length)
        fifo.pop_back(); // Pop data off of the FIFO
}

// Calculate the median of the data currently in the FIFO
// (This implementation _could_ be faster, it's just not necessary)
float FifoMedian::calculate_median() {
    // In the event that there is no data, return 0
    if (fifo.size() == 0)
        return 0.0;

    // Create a copy of the FIFO so that our sort preserves the original order of
    // the array
    std::deque<float> fifo_copy(fifo);

    // Sort the copied array
    std::sort(fifo_copy.begin(), fifo_copy.end());

    // Approximate the middle index of the array, in the case of an even
    // number of elements it will be the 'right' element
    size_t middle = fifo_copy.size() / 2;

    // Bitwise mask to determine if the FIFO size is odd or even.
    if (fifo_copy.size() & 1) {
        // If the number of elements in the FIFO is odd, just return the middle
        // element
        return fifo_copy[middle];
    } else {
        // Otherwise if it is even, average the 'left' and 'right' elements
        return (fifo_copy[middle] + fifo_copy[middle - 1]) / 2.0;
    }
}
