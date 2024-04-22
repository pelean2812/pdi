#include <iostream>
#include <opencv2/opencv.hpp>

int main(int, char**) {
  // Carregar a imagem original
    cv::Mat image = cv::imread("ru.png");

    if (image.empty()) {
        std::cout << "não abriu a foto do RU" << std::endl;
        return -1;
    }

    cv::imshow("janta do ru", image);

    //pega a largura da imagem
    int largura = image.cols;
    //pega a altura da imagem
    int altura = image.rows;

    //imagem do canto superior esquerdo
    cv::Mat superiorEsquerdo = image(cv::Rect(0, 0, largura / 2, altura / 2));
    //imagem do canto superior direito
    cv::Mat superiorDireito = image(cv::Rect(largura / 2, 0, largura / 2, altura / 2));
    //imagem do canto inferior direito
    cv::Mat inferiorDireito = image(cv::Rect(largura / 2, altura / 2, largura / 2, altura / 2));
    //imagem do canto inferior esquerdo
    cv::Mat inferiorEsquerdo = image(cv::Rect(0, altura / 2, largura / 2, altura / 2));
    
    //nova imagem do tamanho da imagem original
    cv::Mat imgModificada(altura, largura, image.type());

    //a parte superior esquerda da imagem vai para o canto inferior direito da imagem modificada
    superiorEsquerdo.copyTo(imgModificada(cv::Rect(largura / 2, altura / 2, largura / 2, altura / 2)));
    //a parte superior direita da imagem vai para o canto inferior esquerdo da imagem modificada
    superiorDireito.copyTo(imgModificada(cv::Rect(0, altura / 2, largura / 2, altura / 2)));
    //a parte inferior direita da imagem vai para o canto superior esquerdo da imagem modificada
    inferiorDireito.copyTo(imgModificada(cv::Rect(0, 0, largura / 2, altura / 2)));
    //a parte inferior esquerda da imagem vai para o canto superior direito da imagem modificada
    inferiorEsquerdo.copyTo(imgModificada(cv::Rect(largura / 2, 0, largura / 2, altura / 2)));

    // Mostrar a imagem imgModificadaante
    cv::imshow("janta do ru modificada", imgModificada);
    cv::waitKey(0);

    return 0;
}