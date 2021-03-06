#include "edge_filter.h"

void Edge_Filter_rgb(cv::Mat& src_img, cv::Mat& dst_img) {
	cv::Mat channel[3];
	cv::split(src_img, channel);

	cv::Mat filtered_img[3];
	int i;
	for (i = 0; i < 3; ++i) {
		filtered_img[i] = cv::Mat(channel[i].rows, channel[i].cols, CV_8UC1);
		Edge_Filter_rgb_Processing(channel[i], filtered_img[i]);
	}

	dst_img = cv::max(max(filtered_img[0], filtered_img[1]), filtered_img[2]);
}

void Edge_Filter_rgb_Processing(cv::Mat& src_img, cv::Mat& dst_img) {
	cv::Mat height_img = cv::Mat(src_img.rows, src_img.cols, CV_8UC1);
	cv::Mat width_img = cv::Mat(src_img.rows, src_img.cols, CV_8UC1);
	cv::Mat total_img = cv::Mat(src_img.rows, src_img.cols, CV_8UC1);

	int array_y[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };
	int array_x[3][3] = { { 1,0,-1 },{ 2,0,-2 },{ 1,0,-1 } };

	Filter(src_img, height_img, array_y);
	Filter(src_img, width_img, array_x);
	Total(height_img, width_img, total_img);

	total_img.copyTo(dst_img);
}

void Edge_Filter(cv::Mat& src_img, cv::Mat& dst_img) {
	cv::Mat gray_img = cv::Mat(src_img.rows, src_img.cols, CV_8U);
	cvtColor(src_img, gray_img, CV_BGR2GRAY);

	cv::Mat height_img = cv::Mat(gray_img.rows, gray_img.cols, CV_8UC1);
	cv::Mat width_img = cv::Mat(gray_img.rows, gray_img.cols, CV_8UC1);
	cv::Mat total_img = cv::Mat(gray_img.rows, gray_img.cols, CV_8UC1);

	int array_y[3][3] = { { 1,2,1 },{ 0,0,0 },{ -1,-2,-1 } };
	int array_x[3][3] = { { 1,0,-1 },{ 2,0,-2 },{ 1,0,-1 } };

	Filter(gray_img, height_img, array_y);
	Filter(gray_img, width_img, array_x);
	Total(height_img, width_img, total_img);

	total_img.copyTo(dst_img);
}

void Filter(cv::Mat& src, cv::Mat& dst, const int kernel[3][3]) {
	int sum = 0;
	for (int y = 1; y < src.rows - 1; ++y) {
		for (int x = 1; x < src.cols - 1; ++x) {
			for (int c = 0; c < src.channels(); ++c) {
				sum = 0;
				for (int i = -1; i <= 1; ++i) {
					for (int j = -1; j <= 1; ++j) {
						sum += static_cast<int>(src.data[(y + i)*src.step + (x + j) * src.elemSize() + c]) * kernel[i + 1][j + 1];
					}
				}
				dst.data[y*dst.step + x * dst.elemSize() + c] = static_cast<uchar>(abs(sum));
			}
		}
	}
}

void Total(cv::Mat& src1, cv::Mat& src2, cv::Mat& dst) {
	double intensity = 0;
	for (int y = 0; y < src1.rows; ++y) {
		for (int x = 0; x < src1.cols; ++x) {
			for (int c = 0; c < src1.channels(); ++c) {
				intensity = sqrt(pow(static_cast<int>(src1.data[y*src1.step + x * src1.elemSize() + c]), 2) + pow(static_cast<int>(src2.data[y*src2.step + x * src2.elemSize() + c]), 2));
				if (intensity > 255) {
					intensity = 255;
				}
				dst.data[y*dst.step + x*dst.elemSize() + c] = static_cast<uchar>(static_cast<int>(intensity));
			}
		}
	}
}