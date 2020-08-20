#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <opencv4/opencv2/opencv.hpp>

class Model
{
private:
  cv::CascadeClassifier face_cascade;
  cv::CascadeClassifier eyes_cascade;
  std::string face_cascade_name;
  std::string eyes_cascade_name;
  std::string output_dir;

  void detectAndReturnEyes(cv::Mat input, cv::Mat* olho);

public:
  Model();
  ~Model();
  void train_model(std::string img_dir);
  void load_model(std::string arq_model);
  int predict(std::string arq_imagem);

};

#endif // MODEL_H
