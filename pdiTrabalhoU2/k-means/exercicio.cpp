#include <cstdlib>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
  int nRodadas = 1;
  int clusters = 12
  
  char filename[50];

  cv::Mat centers;
  cv::Mat labels;
  cv::Mat img = cv::imread(argv[1], cv::IMREAD_COLOR);
  int size = img.cols*img.rows;
  cv::Mat samples(size, 3, CV_32F);

  for (int n = 0; n < 10; n++) {
    for (int y = 0; y < img.rows; y++) {
      for (int x = 0; x < img.cols; x++) {
        for (int z = 0; z < 3; z++) {
          samples.at<float>(y + x * img.rows, z) = img.at<cv::Vec3b>(y, x)[z];
        }
      }
    }

    cv::kmeans(samples, clusters, labels, cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT, 10000, 0.0001), nRodadas, cv::KMEANS_RANDOM_CENTERS, centers);

    cv::Mat labeled(img.size(), img.type());
    for (int y = 0; y < img.rows; y++) {
      for (int x = 0; x < img.cols; x++) {
        int index = labels.at<int>(y + x * img.rows, 0);
        labeled.at<cv::Vec3b>(y, x)[0] = (uchar)centers.at<float>(index, 0);
        labeled.at<cv::Vec3b>(y, x)[1] = (uchar)centers.at<float>(index, 1);
        labeled.at<cv::Vec3b>(y, x)[2] = (uchar)centers.at<float>(index, 2);
      }
    }
    sprintf(filename, "%.d-imagem.png", n+1);
    
    cv::imwrite(filename, labeled);

  }
  cv::waitKey();
}