
#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char**argv) {
  cv::Mat imagemFundo, imagem;
  cv::Vec3b imgFundo, img;

  imagem = cv::imread(argv[1], cv::IMREAD_COLOR);
  
  //linhas e colunas da imagem
  int linhas = imagem.rows;
  int colunas = imagem.cols;

  if (imagem.empty()) {
    std::cout << "a imagem não foi carregada corretamente, tente novamente" << std::endl;
    return -1;
  }

  //imagem escondida
  imagemFundo = cv::Mat::zeros(imagem.rows, imagem.cols, CV_8UC3);

  //   int valorEsteganografia = 1;
  //   for (int i = 0; i < linhas; i++) {
  //     for (int j = 0; j < colunas; j++) {
  //       img = imagem.at<cv::Vec3b>(i, j);
  //       imgFundo[2] = img[2] << (8-valorEsteganografia);
  //       imgFundo[1] = img[1] << (8-valorEsteganografia);
  //       imgFundo[0] = img[0] << (8-valorEsteganografia);
  //       imagemFundo.at<cv::Vec3b>(i, j) = imgFundo;
  //     }
  //   }

  //   int valorEsteganografia = 2;
  //   for (int i = 0; i < linhas; i++) {
  //     for (int j = 0; j < colunas; j++) {
  //       img = imagem.at<cv::Vec3b>(i, j);
  //       imgFundo[2] = img[2] << (8-valorEsteganografia);
  //       imgFundo[1] = img[1] << (8-valorEsteganografia);
  //       imgFundo[0] = img[0] << (8-valorEsteganografia);
  //       imagemFundo.at<cv::Vec3b>(i, j) = imgFundo;
  //     }
  //   }

  //subtrair 3 camadas da imagem foi o melhor número que encontrei
  int valorEsteganografia = 3;
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      //subtrai valorEsteganografia bits de cor da imagem original para encontrar outra
      img = imagem.at<cv::Vec3b>(i, j);
      imgFundo[2] = img[2] << (8-valorEsteganografia);
      imgFundo[1] = img[1] << (8-valorEsteganografia);
      imgFundo[0] = img[0] << (8-valorEsteganografia);
      imagemFundo.at<cv::Vec3b>(i, j) = imgFundo;
    }
  }

  imwrite("imagem_escondida.png", imagemFundo);

  cv::imshow("imagem original", imagem);
  cv::imshow("imagem escondida (-3 bits)", imagemFundo);
  cv::waitKey();

  return 0;
}