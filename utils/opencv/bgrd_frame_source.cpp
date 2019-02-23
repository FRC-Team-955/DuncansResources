#include <bgrd_frame_source.hpp>

BGRDFrame BGRDFrame::operator()(cv::Rect roi) {
    return BGRDFrame(this->bgr(roi), this->depth(roi));
}

//TODO: Check whether n_pix is out of range first
BGRDFrame BGRDFrame::reduce_width(int n_pix) {
    if (this->bgr.empty() || this->depth.empty()) return BGRDFrame(cv::Mat(), cv::Mat());
    cv::Rect new_roi (n_pix, 0, this->bgr.cols - (n_pix * 2), this->bgr.rows);
    return (*this)(new_roi);
}

BGRDFrameSource::~BGRDFrameSource() {}
