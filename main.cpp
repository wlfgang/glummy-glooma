#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
    std::cout << cv::getBuildInformation() << std::endl;

    if (argc != 2) {
        std::cerr << "Usage: glummy-glooma <video_file>" << std::endl;
        exit(1);
    }

    cv::VideoCapture videoCapture;
    if (!videoCapture.open(argv[1])) {
        std::cerr << "Cannot open input file: " << argv[1];
        exit(1);
    }

    // grab the first frame and write it out to show it's working
    cv::Mat image;
    videoCapture >> image;
    std::cout << "Image dimensions: " << image.cols << "x" << image.rows << std::endl;
    cv::imwrite("first_frame.png", image);
    videoCapture.release();

    return 0;
}
