#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;

int main () {
    // Load the image into memory, create a copy that we'll draw on
    Mat original = imread("image.png");
    Mat annotated_original;
    original.copyTo(annotated_original);

    // Determine whether any given pixel is on the strip or not based on intensity
    Mat is_strip;
    inRange(original, Scalar(25, 25, 25), Scalar(255, 255, 255), is_strip);

    // Perform a dilate operation on the result - grow the sizes of pixels
    Mat structuring_element = getStructuringElement(MORPH_RECT, Size(5, 5));
    Mat dilate_result;
    dilate(is_strip, dilate_result, structuring_element);
    
    // Use the canny edge detector to find image edges
    Mat canny_result;
    Canny(dilate_result, canny_result, 128, 128);

    // Find contours using OpenCV's algorithm
    std::vector<std::vector<Point>> contours;
    findContours(canny_result, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Find the largest rectangle
    Rect largest_rectangle;
    for (auto& contour : contours) {
        Rect current_rect = boundingRect(contour);
        if (current_rect.area() > largest_rectangle.area()) {
            largest_rectangle = current_rect;
        }
    }

    // Draw on the annotated_original image
    drawContours(annotated_original, contours, -1, Scalar(0, 0, 255));
    imwrite("Contours.png", annotated_original);
    rectangle(annotated_original, largest_rectangle, Scalar(0, 255, 0), 2);

    imshow("Is strip", is_strip);
    imshow("Dilate", dilate_result);
    imshow("Canny", canny_result);
    imshow("Annotated", annotated_original);

    imwrite("is_strip.png", is_strip);
    imwrite("dilate.png", dilate_result);
    imwrite("canny.png", canny_result);
    imwrite("annotated.png", annotated_original);
    while (waitKey(0) != 'q');
}
