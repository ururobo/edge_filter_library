#pragma once

#include <iostream>
#include <opencv2\opencv.hpp>

void Edge_Filter_rgb(cv::Mat& src_img, cv::Mat& dst_img);
void Edge_Filter_rgb_Processing(cv::Mat& src_img, cv::Mat& dst_img);
void Edge_Filter(cv::Mat& src_img, cv::Mat& dst_img);
void Filter(cv::Mat& src, cv::Mat& dst, const int kernel[3][3]);
void Total(cv::Mat& src1, cv::Mat& src2, cv::Mat& dst);