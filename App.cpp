#include "App.h"

int App::run()
{
  get_app_state();
  
  if (calibration)
  {
    model_calibrate(model);
  }
  
  return 0;
}

App::App()
{
  condicao = "cal";
  calibration = true;
  arq_modelo = "trained_model.xml";
  dt = 1.0f;
}

App::App(int argc, char* argv[])
{
  App();
  if (argc > 1)
  {
    condicao = std::string(argv[1]);
    if (condicao.compare("use") == 0)
    {
      if (argc < 3)
      {
        show_usage(argv[0]);
        exit(1);
      }
      arq_modelo = argv[2];
    }
    else if (condicao.compare("cal") == 0) calibration = true;
    else 
    {
      show_usage(argv[0]);
      exit(1);
    }
  }
}

void App::show_usage(std::string app_name)
{
  std::cout << "Uso:\n" << app_name << " [condição] [arq_modelo] [dt]" << std::endl;
  std::cout << "condição:   'cal' para calibrar ou 'use' para utilizar modelo calibrado 'arq_modelo'" << std::endl;
  std::cout << "            OBS: se condição for 'use' deve-se especificar o arq_model" << std::endl;
  std::cout << "dt      :   intervalo de tempo (em segundos) entre predições" << std::endl;
}

void App::get_app_state()
{
  using namespace std;
  cout << "Método de utilização:\t";
  if (condicao.compare("cal") == 0)
  {
    cout << "Calibração" << endl;
  }
  else
  {
    cout << "Predição\nArquivo do modelo:\t" << arq_modelo << endl;
  }
  cout << "Tempo de atualização:\t" << dt << endl;
}

void App::model_calibrate(Model model)
{
  std::string output_dir;
  // Capturando da webcam
  int camera_device = 0;
  cv::VideoCapture capture;
  capture.open(camera_device);

  if (! capture.isOpened())
  {
    std::cerr << "Erro ao capturar video\n";
    return;
  }

  // calculando FPS
  time_t start, end;
  int num_frames = 0;
  cv::Mat frame;

  // sequencia de nome dos arquivos de saida
  int seq_arq = 0;

  // loop principal
  while (capture.read(frame))
  {
    if (seq_arq == 0)
    {
      std::cout << "Olhe para CIMA\nPresione ENTER para continuar...";
      std::cin.ignore(); std::cin.clear();
      output_dir = "data/cima";
    } 
    if (seq_arq == 60)
    {
      std::cout << "Olhe para BAIXO\nPresione ENTER para continuar...";
      std::cin.ignore();
      output_dir = "data/baixo";
    } 
    if (seq_arq == 120)
    {
      std::cout << "Olhe para ESQUERDA\nPresione ENTER para continuar...";
      std::cin.ignore();
      output_dir = "data/esq";
    } 
    if (seq_arq == 180)
    {
      std::cout << "Olhe para DIREITA\nPresione ENTER para continuar...";
      std::cin.ignore();
      output_dir = "data/dir";
    }
    if (seq_arq == 240)
    {
      std::cout << "Imagens necessárias ao treinamento capturadas" << std::endl;
      break;
    }

    num_frames++;
    time(&start);

    if(frame.empty())
    {
      std::cout << "Erro ao capturar frame -- Break!\n";
      break;
    }
    // Aplica o classificador ao frame corrente
    //detectAndDisplay(frame);

    cv::Mat olhos[2];
    model.detectAndReturnEyes(frame, olhos);

    // aplica filtro nas matrizes dos olhos
    if (model.eyes.size() > 0)
    {
      // por enquanto, considera apenas 1 olho
      
      // normaliza o tamanho (60x60)
      cv::Mat rs_olho(cv::Size(60,60), olhos[0].type());
      cv::resize(olhos[0],rs_olho, rs_olho.size());

      // calcula a media de intensidade
      cv::Scalar avg = cv::mean(rs_olho);

      // aplica o threshold
      cv::Mat bw_olho(cv::Size(60,60), rs_olho.type());
      cv::threshold(rs_olho, bw_olho, *avg.val, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C);
      seq_arq++;

      // imprime a media (DEBUG)
      //std::cout << *avg.val << std::endl;
      
      // mostra imagem final (DEBUG)
      cv::imshow("1", bw_olho);

      // salva imagens para treinamento de direção
      std::string output_file = std::to_string(seq_arq);
      std::cout << "olho_" << output_file << ".png" << std::endl;
      
      // grava figura em preto e branco
      //if(!cv::imwrite(output_dir+"/olho_"+output_file+".png", bw_olho))

      // grava figura em preto tons de cinza
      if(!cv::imwrite(output_dir+"/olho_"+output_file+".png", rs_olho))
      {
        std::cout << output_dir+"/olho_"+output_file+".png" << std::endl;
        std::cout << "Erro ao salvar arquivo de imagem" << std::endl;
      }
    }

    // Sai caso tecla ESC seja pressionada
    if(cv::waitKey(1) == 27) break;

     // mostra FPS
    time(&end);
    double sec = difftime(end, start);
    if (sec >= 1.0f)
    {
      std::cout << "FPS: "    << num_frames;
      std::cout << "\t# olhos: " << eyes.size() << std::endl;
      num_frames = 0;
    }
  }

}
