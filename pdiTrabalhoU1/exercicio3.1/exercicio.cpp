#include <iostream>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>

int main(int argc, char** argv) {
  std::stringstream ss_img1, ss_yml1;
  std::stringstream ss_img2, ss_yml2;
  cv::Mat img1, img2, diferenca;

  ss_yml1 << "1_senoide.yml";
  img1 = cv::Mat::zeros(256, 256, CV_32FC1);

  ss_yml2 << "2_senoide.yml";
  img2 = cv::Mat::zeros(256, 256, CV_32FC1);

  cv::FileStorage file1(ss_yml1.str(), cv::FileStorage::WRITE);
  cv::FileStorage file2(ss_yml2.str(), cv::FileStorage::WRITE);

  float amplitude = 127.0;
  float jwt = (16*M_PI)/256;
  float deslocamento = 128;

  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 256; j++) {
      img2.at<float>(i,j) = ((amplitude*sin((jwt*j)/2))+deslocamento);
      img1.at<float>(i,j) = ((amplitude*sin((jwt*j)))+deslocamento);
    }
  }

  file1 << "mat" << img1;
  file2 << "mat" << img2;
  
  file1.release();
  file2.release();

  cv::normalize(img1, img1, 0, 255, cv::NORM_MINMAX);
  cv::normalize(img2, img2, 0, 255, cv::NORM_MINMAX);
  img1.convertTo(img1, CV_8U);
  img2.convertTo(img2, CV_8U);
  ss_img1 << "1_senoide.png";
  ss_img2 << "2_senoide.png";
  cv::imwrite(ss_img1.str(), img1);
  cv::imwrite(ss_img2.str(), img2);

  file1.open(ss_yml1.str(), cv::FileStorage::READ);
  file1["mat"] >> img1;
  file2.open(ss_yml2.str(), cv::FileStorage::READ);
  file2["mat"] >> img2;
  
  cv::normalize(img1, img1, 0, 255, cv::NORM_MINMAX);
  img1.convertTo(img1, CV_8U);

  cv::normalize(img2, img2, 0, 255, cv::NORM_MINMAX);
  img2.convertTo(img2, CV_8U);

  diferenca = cv::Mat::zeros(256, 256, CV_8U);

  for (int i = 0; i < 256; i++) {
    for (int j = 0; j < 256; j++) {
      if (img1.at<uchar>(i, j) > img2.at<uchar>(i, j)) {
        diferenca.at<uchar>(i, j) = img1.at<uchar>(i, j) - img2.at<uchar>(i, j);
      } else {
        diferenca.at<uchar>(i, j) = img2.at<uchar>(i, j) - img1.at<uchar>(i, j);
      }
    }
  }
  cv::imwrite("diferenca.png", diferenca);
  
  cv::imshow("senoide 1", img1);
  cv::imshow("senoide 2", img2);
  cv::imshow("diferença entre as senoides", diferenca);
  cv::waitKey();

  return 0;
}