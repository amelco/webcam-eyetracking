#include "Model.h"
#include <filesystem>

Model::Model()
{
  face_cascade_name = "haarcascade_frontalface_alt.xml";
  eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
  output_dir = "data/";
  std::filesystem::create_directory("datasss");
  
  // Carregando os cascades
  if (!face_cascade.load(face_cascade_name))
  {
    std::cerr << "Erro carregando face cascade\n";
    return;
  };
  if (!eyes_cascade.load(eyes_cascade_name))
  {
    std::cerr << "Erro carregando eyes cascade\n";
    return;
  };
}

Model::~Model() {}

void Model::train_model(std::string img_dir)
{

}

void Model::load_model(std::string arq_model)
{

}

int  Model::predict(std::string arq_imagem)
{
  return 0;
}


/* 
 * Retorna lista cv::Mat com 2 elementos contendo 0, 1 ou 2 olhos detectados
 * Entrada: 
 *    img: matriz com a imagem da webcam
 * Saída:
 *    olho: matriz 2 elementos com imagem dos olhos
 */
void Model::detectAndReturnEyes(cv::Mat img, cv::Mat* olho)
{
  cv::Mat frame_gray;
  cv::Mat faceROI;
  std::vector<cv::Rect> faces;
  std::vector<cv::Rect> eyes;

  cv::cvtColor(img, frame_gray, cv::COLOR_BGR2GRAY);
  cv::equalizeHist(frame_gray, frame_gray);

  face_cascade.detectMultiScale(frame_gray, faces);
  if (faces.size() > 0)
  {
    faceROI = frame_gray(faces[0]);
    eyes_cascade.detectMultiScale(faceROI, eyes);
    if (eyes.size() > 0)
    {
      olho[0] = faceROI(eyes[0]);
      if (eyes.size() == 2) olho[1] = faceROI(eyes[1]);
    }
  }
}
