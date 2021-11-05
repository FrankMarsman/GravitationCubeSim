#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "vector2d.h"
#include "gravsim.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  bool isRunning; // true if sim is running
  unsigned int IMG_SIZE; // size of output image
  unsigned int FRAME_COUNT; // for animation

  GravSim * gravSim;
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow( );

private:
  Ui::MainWindow *ui;

public slots:
  void Next( );
private slots:
  void on_runButton_clicked();
};

#endif // MAINWINDOW_H
