#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::experimental::filesystem;

int main()
{
    fs::path img_path{"C:/Dev/projects/ml-with-c++/data/bot.jpg"};
    cv::Mat img;

    if(fs::exists(img_path))
    {
        img = cv::imread(img_path.string());
    }
    else
    {
       std::cerr << "File path " << img_path << " is invalid\n";
    }

    if(img.empty())
    {
        const int width = 512;
        img = cv::Mat(width, width, CV_32FC3);
        img = cv::Scalar(255, 255, 255);
        cv::rectangle(img, {width / 4, width / 4}, {width / 2, width / 2}, cv::Scalar(0, 0, 0), -1);
    }

    cv::namedWindow("Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Image", img);
    cv::waitKey(0);

    cv::resize(img, img, {img.cols / 2, img.rows / 2}, 0, 0, cv::INTER_AREA);
    cv::imshow("Image", img);
    cv::waitKey(0);

    cv::resize(img, img, {}, 1.5, 1.5, cv::INTER_CUBIC);
    cv::imshow("Image", img);
    cv::waitKey(0);

    img = img(cv::Rect(0, 0, img.cols / 2, img.rows / 2));
    cv::imshow("Image", img);
    cv::waitKey(0);

    cv::Mat transMat = (cv::Mat_<double>(2, 3) << 1, 0, -50, 0, 1, -50);
    cv::warpAffine(img, img, transMat, {img.cols, img.rows});
    cv::imshow("Image", img);
    cv::waitKey(0);

    auto rotm = cv::getRotationMatrix2D({static_cast<float>(img.cols / 2), static_cast<float>(img.rows / 2)}, 45, 1);
    cv::warpAffine(img, img, rotm, {img.cols, img.rows});
    cv::imshow("Image", img);
    cv::waitKey(0);

    int top = 50;
    int bottom = 20;
    int left = 150;
    int right = 5;
    cv::copyMakeBorder(img, img, top, bottom, left, right, cv::BORDER_CONSTANT | cv::BORDER_ISOLATED,
                       cv::Scalar(255, 0, 0));
    cv::imshow("Image", img);
    cv::waitKey(0);

    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    cv::imshow("Image", img);
    cv::waitKey(0);

    cv::cvtColor(img, img, cv::COLOR_RGB2GRAY);
    std::cout << "Grayscale image channels " << img.channels() << std::endl;
    cv::imshow("Image", img);
    cv::waitKey(0);

    img.convertTo(img, CV_8UC1, 255);
    cv::imshow("Image", img);
    cv::waitKey(0);

    img = cv::Mat(512, 512, CV_32FC3);
    img = cv::Scalar(255, 255, 255);
    cv::Mat bgr[3];
    cv::split(img, bgr);
    cv::Mat ordered_channels;
    cv::vconcat(bgr[2], bgr[1], ordered_channels);
    cv::vconcat(ordered_channels, bgr[0], ordered_channels);

    std::cout << "Memory layout is continuous " << ordered_channels.isContinuous()
              << std::endl;

    return 0;
}
