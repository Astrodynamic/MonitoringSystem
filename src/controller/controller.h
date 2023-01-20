#ifndef CONTROLER_H
#define CONTROLER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

class Controller : public QMainWindow {
  Q_OBJECT

 public:
  Controller(QWidget *parent = nullptr);
  ~Controller();

 private:
  Ui::View *ui;
};
#endif  // CONTROLER_H
