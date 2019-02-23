#pragma once

#include <opencv2/core.hpp>

struct BGRDFrame {
    cv::Mat bgr;
    cv::Mat depth;
    
    //TODO: Add assert that the images are the same size
    BGRDFrame(cv::Mat bgr, cv::Mat depth) : bgr(bgr), depth(depth) {}

    BGRDFrame operator()(cv::Rect roi);
    BGRDFrame reduce_width(int n_pix);
};

class BGRDFrameSource {
    public: 
        virtual BGRDFrame next() = 0;
        virtual ~BGRDFrameSource();
};
