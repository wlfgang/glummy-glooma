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

    auto numFrames = static_cast<size_t>(videoCapture.get(cv::CAP_PROP_FRAME_COUNT));
    std::cout << "Number of frames: " << numFrames << std::endl;

    // grab the first frame and write it out to show it's working
    cv::Mat image;
    videoCapture >> image;
    std::cout << "Image dimensions: " << image.cols << "x" << image.rows << std::endl;
    cv::imwrite("first_frame.png", image);

    for (size_t i = 1; i < numFrames; i++) {
        auto frame = static_cast<size_t>(videoCapture.get(cv::CAP_PROP_POS_FRAMES));
        std::cout << "Reading frame " << frame << "..." << std::endl;

        if (!videoCapture.read(image) || image.empty()) {
            std::cout << "Error reading frame " << frame << std::endl;
        }
    }

    videoCapture.release();

    return 0;
}
