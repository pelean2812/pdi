#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  cv::Mat str, image, d1, dil1, erode1, d2, dil2, erode2, d3, dil3, erode3, d4, dil4, erode4, d5, dil5, erode5;

  d1 = cv::imread("./digitos-1.png", cv::IMREAD_UNCHANGED);
  d2 = cv::imread("./digitos-2.png", cv::IMREAD_UNCHANGED);
  d3 = cv::imread("./digitos-3.png", cv::IMREAD_UNCHANGED);
  d4 = cv::imread("./digitos-4.png", cv::IMREAD_UNCHANGED);
  d5 = cv::imread("./digitos-5.png", cv::IMREAD_UNCHANGED);

  if(d1.empty() || d2.empty() || 
    d3.empty() || d4.empty() || 
    d5.empty()) {
    std::cout << "Erro ao carregar as imagens" << std::endl;
    return -1;
  }else{
    cv::bitwise_not(d1, d1);
    cv::bitwise_not(d2, d2);
    cv::bitwise_not(d3, d3);
    cv::bitwise_not(d4, d4);
    cv::bitwise_not(d5, d5);

    // elemento estruturante
    str = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 15));

    //aplicação da operação de fechamento morfológico: primeiro dilatar e depois erodir
    cv::dilate(d1, dil1, str);
    cv::dilate(d2, dil2, str);
    cv::dilate(d3, dil3, str);
    cv::dilate(d4, dil4, str);
    cv::dilate(d5, dil5, str);

    cv::erode(dil1, erode1, str);
    cv::erode(dil2, erode2, str);
    cv::erode(dil3, erode3, str);
    cv::erode(dil4, erode4, str);
    cv::erode(dil5, erode5, str);

    cv::bitwise_not(erode1, erode1);
    cv::bitwise_not(erode2, erode2);
    cv::bitwise_not(erode3, erode3);
    cv::bitwise_not(erode4, erode4);
    cv::bitwise_not(erode5, erode5);

    cv::imwrite("close1.png", erode1);
    cv::imwrite("close2.png", erode2);
    cv::imwrite("close3.png", erode3);
    cv::imwrite("close4.png", erode4);
    cv::imwrite("close5.png", erode5);
  }

  cv::waitKey();
  return 0;
}