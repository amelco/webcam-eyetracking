#ifndef APP_H
#define APP_H

#include <iostream>
#include "Model.h"

class App
{
private:
  Model model;
  std::string condicao;
  std::string arq_modelo;
  bool calibration;
  float dt;

public:
  App();
  App(int argc, char* argv[]);

  int run();
  void get_app_state();
  void show_usage(std::string);
  void model_calibrate(Model model);

};

#endif // APP_H
