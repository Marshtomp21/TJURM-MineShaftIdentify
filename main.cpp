#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <algorithm>

// 计算两点之间的距离
double distance(const cv::Point2f& p1, const cv::Point2f& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

// 计算三角形的面积
double triangleArea(const std::vector<cv::Point2f>& triangle) {
    return std::abs(triangle[0].x * (triangle[1].y - triangle[2].y) +
                    triangle[1].x * (triangle[2].y - triangle[0].y) +
                    triangle[2].x * (triangle[0].y - triangle[1].y)) / 2.0;
}

// 计算两条直线的夹角
double angleBetweenLines(const cv::Point2f& p1, const cv::Point2f& p2, const cv::Point2f& p3, const cv::Point2f& p4) {
    double dx1 = p2.x - p1.x;
    double dy1 = p2.y - p1.y;
    double dx2 = p4.x - p3.x;
    double dy2 = p4.y - p3.y;
    double dotProduct = dx1 * dx2 + dy1 * dy2;
    double magnitude1 = std::sqrt(dx1 * dx1 + dy1 * dy1);
    double magnitude2 = std::sqrt(dx2 * dx2 + dy2 * dy2);
    return std::acos(dotProduct / (magnitude1 * magnitude2));
}

// 用绿线连接四个点
void drawShape(cv::Mat& image, std::vector<cv::Point2f>& points) {
    // 按顺时针顺序排序点
    cv::Point2f center(0, 0);
    for (const auto& point : points) {
        center += point;
    }
    center *= (1.0 / points.size());

    std::sort(points.begin(), points.end(), [&center](const cv::Point2f& a, const cv::Point2f& b) {
        double angleA = std::atan2(a.y - center.y, a.x - center.x);
        double angleB = std::atan2(b.y - center.y, b.x - center.x);
        return angleA < angleB;
    });

    for (int i = 0; i < 4; i++) {
        cv::line(image, points[i], points[(i + 1) % 4], cv::Scalar(0, 255, 0), 2);
    }
}

int main(int argc, char** argv) {
    // 检查命令行参数
    if (argc != 2) {
        std::cerr << "用法: " << argv[0] << " <输入图片文件名>" << std::endl;
        return -1;
    }

    // 读取命令行输入的文件名
    std::string input_filename = argv[1];
    std::string input_path = "../images/input/" + input_filename;

    // 读取输入图片
    cv::Mat input = cv::imread(input_path);
    if (input.empty()) {
        std::cerr << "无法读取图片: " << input_path << std::endl;
        return -1;
    }

    // 高斯模糊
    cv::Mat blurred;
    cv::GaussianBlur(input, blurred, cv::Size(5, 5), 0);

    // 转换到HSV颜色空间
    cv::Mat hsv;
    cv::cvtColor(blurred, hsv, cv::COLOR_BGR2HSV);

    // 创建红色掩码
    cv::Mat red_mask1, red_mask2, red_mask;
    cv::inRange(hsv, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), red_mask1);
    cv::inRange(hsv, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), red_mask2);
    cv::bitwise_or(red_mask1, red_mask2, red_mask);

    // 二值化
    cv::threshold(red_mask, red_mask, 64, 255, cv::THRESH_BINARY); 

    // 形态学操作（腐蚀和膨胀）
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::morphologyEx(red_mask, red_mask, cv::MORPH_CLOSE, kernel);

    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(red_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 绘制每个轮廓的最小外接三角形并标出张角最大的点
    cv::Mat output = input.clone();
    cv::Scalar triangleColor(0, 255, 0);
    cv::Scalar maxAnglePointColor(255, 255, 255);
    cv::Scalar rightTopPointColor(255, 0, 0);

    cv::Point2f maxXMinusXPoint(-1, -1);
    double maxXMinusXValue = -std::numeric_limits<double>::infinity();

    std::vector<std::pair<std::vector<cv::Point2f>, double>> triangles;

    for (const auto& contour : contours) {
        std::vector<cv::Point2f> triangle;
        cv::minEnclosingTriangle(contour, triangle);

        // 计算三角形面积
        double area = triangleArea(triangle);
        triangles.push_back({triangle, area});
    }

    // 如果外接三角形等于7个，去掉面积最小的两个
    if (triangles.size() == 7 || triangles.size() == 6) {
        std::sort(triangles.begin(), triangles.end(), [](const std::pair<std::vector<cv::Point2f>, double>& a, const std::pair<std::vector<cv::Point2f>, double>& b) {
            return a.second < b.second;
        });
        triangles.erase(triangles.begin(), triangles.begin() + 2);
    }

    std::vector<cv::Point2f> whitePoints;

    for (const auto& triangle : triangles) {
        // 绘制最小外接三角形
        // for (size_t i = 0; i < 3; i++) {
        //    cv::line(output, triangle.first[i], triangle.first[(i + 1) % 3], triangleColor, 2);
        //}

        // 找到张角最大的点
        double maxOppositeSideLength = 0;
        cv::Point2f maxAnglePoint;
        for (size_t i = 0; i < 3; i++) {
            double oppositeSideLength = distance(triangle.first[(i + 1) % 3], triangle.first[(i + 2) % 3]);
            if (oppositeSideLength > maxOppositeSideLength) {
                maxOppositeSideLength = oppositeSideLength;
                maxAnglePoint = triangle.first[i];
            }
        }

        // 用白点标出张角最大的点
        cv::circle(output, maxAnglePoint, 5, maxAnglePointColor, -1);
        whitePoints.push_back(maxAnglePoint);

        // 更新 y - x 值最大的点
        double xMinusXValue = maxAnglePoint.x - maxAnglePoint.y;
        if (xMinusXValue > maxXMinusXValue) {
            maxXMinusXValue = xMinusXValue;
            maxXMinusXPoint = maxAnglePoint;
        }
    }

    // 用蓝点标出 y - x 值最大的点
    if (maxXMinusXPoint.x != -1) {
        cv::circle(output, maxXMinusXPoint, 5, rightTopPointColor, -1);
    }

    // 找到四个点形成夹角最接近平行的两条直线
    std::vector<cv::Point2f> selectedPoints;
    double minAngleDifference = std::numeric_limits<double>::infinity();

    for (size_t i = 0; i < whitePoints.size(); i++) {
        for (size_t j = i + 1; j < whitePoints.size(); j++) {
            for (size_t k = j + 1; k < whitePoints.size(); k++) {
                for (size_t l = k + 1; l < whitePoints.size(); l++) {
                    std::vector<cv::Point2f> points = { whitePoints[i], whitePoints[j], whitePoints[k], whitePoints[l] };
                    // 检查所有可能的两条线段组合
                    double angle1 = angleBetweenLines(points[0], points[1], points[2], points[3]);
                    double angle2 = angleBetweenLines(points[0], points[2], points[1], points[3]);
                    double angle3 = angleBetweenLines(points[0], points[3], points[1], points[2]);
                    double minCurrentAngleDifference = std::min({std::abs(angle1), std::abs(angle2), std::abs(angle3)});
                    if (minCurrentAngleDifference < minAngleDifference) {
                        minAngleDifference = minCurrentAngleDifference;
                        selectedPoints = points;
                    }
                }
            }
        }
    }

    if (!selectedPoints.empty()) {
        drawShape(output, selectedPoints);
    }

    // 排除这四个maxAnglePoint
    std::vector<cv::Point2f> remainingPoints;
    for (const auto& point : whitePoints) {
        if (std::find(selectedPoints.begin(), selectedPoints.end(), point) == selectedPoints.end()) {
            remainingPoints.push_back(point);
        }
    }

    // 对于剩下的一个maxAnglePoint所在的最小外接三角形，用白点标出其另外的两个顶点
    if (!remainingPoints.empty()) {
        for (const auto& triangle : triangles) {
            if (std::find(triangle.first.begin(), triangle.first.end(), remainingPoints[0]) != triangle.first.end()) {
                for (const auto& point : triangle.first) {
                    if (point != remainingPoints[0]) {
                        cv::circle(output, point, 5, maxAnglePointColor, -1);
                    }
                }
                break;
            }
        }
    }

    // 生成输出文件名
    std::string output_filename = "output-" + input_filename;
    std::string output_path = "../images/output/" + output_filename;

    // 保存结果图片
    cv::imwrite(output_path, output);

    return 0;
}