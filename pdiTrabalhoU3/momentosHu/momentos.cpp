#include <iostream>
#include <vector>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
	int tamanho, xyPessoa[2];
	double huMomentsPessoa[7], huMomentsTrecho[7];
	double erro = 1000;

	cv::Mat trechoImagem, multidao = cv::imread(argv[1], IMREAD_GRAYSCALE), pessoa = cv::imread(argv[2], IMREAD_GRAYSCALE);
  cv::Moments momentsTrecho;

	// Verificar se as imagens foram carregadas corretamente
	if (pessoa.empty() || multidao.empty()) {
		cout << "Erro ao carregar as imagens" << endl;
		return -1;
	}

	cv::resize(pessoa, pessoa, Size(pessoa.cols / 6, pessoa.rows / 6), INTER_LINEAR);
	cv::resize(multidao, multidao, Size(multidao.cols / 6, multidao.rows / 6), INTER_LINEAR);

	cv::Moments momentsPessoa = cv::moments(pessoa, false);
	cv::HuMoments(momentsPessoa, huMomentsPessoa);

	for (int i = 0; i < 7; i++) {
    huMomentsPessoa[i] = -1 * std::copysign(1.0, huMomentsPessoa[i]) * log10(abs(huMomentsPessoa[i]));
  }

	tamanho = pessoa.cols;

	for (int i = 0; i < (multidao.cols - tamanho); i++) {
		for (int j = 0; j < (multidao.rows - tamanho); j++) {
			cv::Rect rect(i, j, tamanho, tamanho);
			trechoImagem = multidao(rect);
			momentsTrecho = cv::moments(trechoImagem, false);
			cv::HuMoments(momentsTrecho, huMomentsTrecho);
			for (int k = 0; k < 7; k++) {
				huMomentsTrecho[k] = -1 * std::copysign(1.0, huMomentsTrecho[k]) * log10(abs(huMomentsTrecho[k]));
			}
			
      double result = 0;
      for (int i = 0; i < 7; i++) {
        result += abs(huMomentsPessoa[i] - huMomentsTrecho[i]);
      }

      if (result < erro) {
				erro = result;
				xyPessoa[0] = i;
				xyPessoa[1] = j;
			}
		}
	}

	for (int i = xyPessoa[0]; i < (xyPessoa[0] + tamanho); i++) {
		for (int j = xyPessoa[1]; j < (xyPessoa[1] + tamanho); j++) {
			if (i == xyPessoa[0] || i == xyPessoa[0] + tamanho - 1) {
				multidao.at<uchar>(i, j) = 0;
			}
			if (j == xyPessoa[1] || j == xyPessoa[1] + tamanho - 1) {
				multidao.at<uchar>(i, j) = 0;
			}
		}
	}

	std::cout << " (x, y) = (" << xyPessoa[0] << ", " << xyPessoa[1] << ")" <<std::endl;
	cv::imwrite("multidao.png", multidao);
  cv::imwrite("pessoa.png", pessoa);
	cv::imshow("janela", multidao);
  cv::imshow("pessoa", pessoa);
	cv::waitKey(0);

	return 0;
}