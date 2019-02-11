#include <realsense_bgrdfs.hpp>

RealSenseBGRDFrameSource::RealSenseBGRDFrameSource(cv::Size size, int fps) : align(RS2_STREAM_COLOR), image_size(size) {
	rs2::config cfg;
	cfg.enable_stream(RS2_STREAM_DEPTH, size.width, size.height, RS2_FORMAT_Z16, fps);
	cfg.enable_stream(RS2_STREAM_COLOR, size.width, size.height, RS2_FORMAT_BGR8, fps);
	pipe.start(cfg);

	rs2::device dev = pipe.get_active_profile().get_device();
	for (rs2::sensor &sensor : dev.query_sensors()) {
		if (rs2::depth_sensor dpt = sensor.as<rs2::depth_sensor>()) {
			depth_scaling_factor = dpt.get_depth_scale();
			break;
		}
	}
}

BGRDFrame RealSenseBGRDFrameSource::next() {
    //TODO: Minimize allocations?
    auto output_frame = BGRDFrame(cv::Mat(image_size, CV_8UC3), cv::Mat(image_size, CV_16UC1));
	rs2::frameset realsense_frame = align.process(pipe.wait_for_frames());
	memcpy(output_frame.bgr.data, (uchar*)realsense_frame .get_color_frame().get_data(), output_frame.bgr.elemSize() * output_frame.bgr.total());
	memcpy(output_frame.depth.data, (uchar*)realsense_frame .get_depth_frame().get_data(), output_frame.depth.elemSize() * output_frame.depth.total());
    return output_frame;
}

float RealSenseBGRDFrameSource::get_depth_scale() {
    return depth_scaling_factor;
}
