#pragma once

#include <algorithm>
#include <deque>
#include <stdio.h>

class FifoMedian {
    private:
        // First In First Out array
        std::deque<float> fifo;

        // Maximum length we allow the array to reach
        size_t fifo_max_length;

    public:
        FifoMedian(size_t max_length);
        void insert_data(float data);
        float calculate_median();
};
