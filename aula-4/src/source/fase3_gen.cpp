#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char *argv[]) {
    // Read the video file
    std::string video_file = argv[1];
    cv::VideoCapture video(video_file);
    if (!video.isOpened()) {
        std::cout << "Error opening video file" << std::endl;
        return -1;
    }

    // Read the image file
    std::string image_file = argv[2];
    cv::Mat image = cv::imread(image_file);
    if (image.empty()) {
        std::cout << "Error opening image file" << std::endl;
        return -1;
    }

    // Define the template matching method
    int match_method = cv::TM_CCOEFF_NORMED;

    // Create a video writer to save the output video
    std::string output_file = argv[3];
    cv::VideoWriter output_video(output_file, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(video.get(cv::CAP_PROP_FRAME_WIDTH), video.get(cv::CAP_PROP_FRAME_HEIGHT)));

    // Process each frame of the video
    cv::Mat frame;
    double total_fps = 0;
    int frame_count = 0;
    while (video.read(frame)) {
        // Start the timer
        double start = cv::getTickCount();

        // Perform template matching
        cv::Mat result;
        cv::matchTemplate(frame, image, result, match_method);

        // Normalize the result
        cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

        // Find the best match location
        cv::Point min_loc, max_loc;
        double min_val, max_val;
        cv::minMaxLoc(result, &min_val, &max_val, &min_loc, &max_loc);

        // Draw a rectangle around the best match
        cv::rectangle(frame, max_loc, cv::Point(max_loc.x + image.cols, max_loc.y + image.rows), cv::Scalar(0, 255, 0), 2);

        // Write the frame to the output video
        output_video.write(frame);

        // Calculate the FPS rate
        double end = cv::getTickCount();
        double fps = cv::getTickFrequency() / (end - start);
        total_fps += fps;
        frame_count++;
    }

    // Release the video writer and video capture objects
    output_video.release();
    video.release();

    // Print the average FPS rate
    double average_fps = total_fps / frame_count;
    std::cout << "Average FPS: " << average_fps << std::endl;

    return 0;
}
