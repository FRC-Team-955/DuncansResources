#include <bgrd_frame_source.hpp>
#include <realsense_bgrdfs.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <histogram.hpp>

using namespace cv;

int main () {
    // Open a new realsense camera
    auto camera = RealSenseBGRDFrameSource(Size(1920, 1080), 30);

    // Create a new histogram using the aforementioned distances
    auto histogram = Histogram<unsigned short>(100, 4000);

    // Main loop
    while (true) {
        // Capture a new set of frames from the camera
        BGRDFrame frameset = camera.next();

        // Show the frame in color and depth on screen
        imshow("Depth", frameset.depth);
        imshow("Color", frameset.bgr);

        // Create an ROI with which to sample the depth
        auto roi = Rect(0, 0, 50, 50);

        // Create an image containing only the information from within the roi
        Mat roi_image = frameset.depth(roi);

        // Clear histogram and insert the new image into it
        histogram.clear();
        histogram.insert_image(roi_image);

        // Take a percentile from the histogram
        float sample = 
            (float)histogram.take_percentile(0.1) 
            * camera.get_depth_scale();
    }
}
