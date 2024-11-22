#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 读取输入图片
    cv::Mat input = cv::imread("../images/input/20211815921.jpg");

    std::vector<std::vector<cv::Point>> contours;
    // 应用阈值操作
    // cv::cvtColor(input, output, cv::COLOR_BGR2HSV);
    cv::Mat red_mask;
    cv::inRange(input, cv::Scalar(0, 0, 150), cv::Scalar(100, 100, 255), red_mask);
    cv::findContours(red_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    cv::Mat output = input.clone();
    cv::Scalar contourColor(0, 255, 0);

    for (size_t i = 0; i < contours.size(); i++) {
        // 绘制轮廓的实际形状
        cv::drawContours(output, contours, (int)i, contourColor, 2);
    }

    // 保存结果图片
    cv::imwrite("../images/output/output.jpg", output);

    std::cout << "图片处理完成，已保存到 ../images/output/output.jpg" << std::endl;

    return 0;
}
