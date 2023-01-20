#include "controller.h"

#include "./ui_view.h"

Controller::Controller(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
}

Controller::~Controller() { delete ui; }
