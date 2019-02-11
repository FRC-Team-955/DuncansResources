#pragma once

#include <librealsense2/rs.hpp>
#include <bgrd_frame_source.hpp>
#include <opencv2/core.hpp>

class RealSenseBGRDFrameSource : public BGRDFrameSource {
    public:
        RealSenseBGRDFrameSource(cv::Size size, int fps);
        BGRDFrame next();
        float get_depth_scale();

    private:
        float depth_scaling_factor;
        cv::Size image_size;
		rs2::pipeline pipe;
		rs2::align align;
};
