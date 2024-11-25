/* 
Author: Calbee
Last Update: 11/25/2024
TODO List:
1.标注侧边图形
2.学习 PnP 解算，确定矿槽位姿
*/

#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Function: 读取图片
    // TODO: 读取配置文件 or 读取命令行参数？
    cv::Mat input = cv::imread("../images/input/20213047194.jpg");
    if (input.empty()) {
        std::cerr << "无法读取图片" << std::endl;
        return -1;
    }

    // Function: 转换到HSV颜色空间
    cv::Mat hsv;
    cv::cvtColor(input, hsv, cv::COLOR_BGR2HSV);

    // Function: 创建红色掩码
    cv::Mat red_mask1, red_mask2, red_mask;
    cv::inRange(hsv, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), red_mask1);
    cv::inRange(hsv, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), red_mask2);
    cv::bitwise_or(red_mask1, red_mask2, red_mask);

    // Function: 腐蚀膨胀
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(red_mask, red_mask, cv::MORPH_CLOSE, kernel);

    // Function: 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(red_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Function: 查找顶点
    // TODO: 将顶点按顺序标出
    //       右上角特殊点特定识别
    std::vector<cv::Point> vertices;
    for (const auto& contour : contours) {
        for (const auto& point : contour) {
            vertices.push_back(point);
        }
    }

    // Function: 使用凸包找到顶点
    std::vector<cv::Point> hull;
    cv::convexHull(vertices, hull);

    // Function: 如果找到的顶点数大于四个，使用approxPolyDP简化顶点
    if (hull.size() > 4) {
        cv::approxPolyDP(hull, hull, cv::arcLength(hull, true) * 0.02, true);
    }

    // Function: 如果找到的顶点数为四个，连成一个四边形并用绿色标出
    if (hull.size() == 4) {
        cv::Mat output = input.clone();
        cv::Scalar contourColor(0, 255, 0);
        cv::Scalar vertexColor(0, 0, 255);

        // 绘制四边形的绿色边框
        for (size_t i = 0; i < 4; i++) {
            cv::line(output, hull[i], hull[(i + 1) % 4], contourColor, 2);
        }

        // 标注顶点坐标并输出到控制台
        // TODO: 输出至文件
        for (size_t j = 0; j < 4; j++) {
            cv::circle(output, hull[j], 5, vertexColor, -1);
            cv::putText(output, std::to_string(j), hull[j], cv::FONT_HERSHEY_SIMPLEX, 3, vertexColor, 2);
            std::cout << "顶点 " << j << ": (" << hull[j].x << ", " << hull[j].y << ")" << std::endl;
        }

        // 保存结果图片
        cv::imwrite("../images/output/result.jpg", output);
    } else {
        std::cerr << "未找到四个顶点" << std::endl;
    }

    return 0;
}