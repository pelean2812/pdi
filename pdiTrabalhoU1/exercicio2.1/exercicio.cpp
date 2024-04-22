#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**) {
  cv::Mat image;

  image = cv::imread("./luffy.png", cv::IMREAD_COLOR);

  if (!image.data) {
    std::cout << "não abriu a foto do rei dos piratas" << std::endl;
    return -1;
  }
  
  cv::imshow("luffy", image);
  
  int xP1 = 0;
  int yP1 = 0;
  
  //lê as coordernadas do ponto 1 (x primeiro e y depois)
  std::cout << "Digite o x do ponto 1:";
  std::cin >> xP1;
  std::cout << "Digite o y do ponto 1:";
  std::cin >> yP1;
  
  std::cout << "Ponto 1: P1(" << xP1 << "," << yP1 << ")" << std::endl;

  int xP2 = 0;
  int yP2 = 0;

  //lê as coordernadas do ponto 2 (x primeiro e y depois)
  std::cout << "Digite o x do ponto 2:";
  std::cin >> xP2;
  std::cout << "Digite o y do ponto 2:";
  std::cin >> yP2;

  std::cout << "Ponto 2: P1(" << xP2 << "," << yP2 << ")" << std::endl;

  //desde o menor valor do x até o maior valor do x fornecido...
  for (int i = std::min(xP1, xP2); i < std::max(xP1, xP2); i++) {
    //desde o menor valor do y até o maior valor do y fornecido ...
    for (int j = std::min(yP1, yP2); j < std::max(yP1, yP2); j++) {
      //nessas coornedadas, faz o negativo da imagem
      image.at<cv::Vec3b>(i, j)[2] = 255 - image.at<cv::Vec3b>(i, j)[2]; // negativo do vermelho
      image.at<cv::Vec3b>(i, j)[1] = 255 - image.at<cv::Vec3b>(i, j)[1]; // negativo do verde
      image.at<cv::Vec3b>(i, j)[0] = 255 - image.at<cv::Vec3b>(i, j)[0]; // negativo do azul
    }
  }

  cv::imwrite("luffyNegativo.png", image);
  cv::imshow("luffyNegativo", image);
  cv::waitKey();
  return 0;
}