#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QTimer>
#include <QString>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  this->IMG_SIZE = 500;
  this->FRAME_COUNT = 1;
  this->isRunning = true; // set opposite value of what you want
  on_runButton_clicked( ); // toggles value of [isRunning]

  this->gravSim = new GravSim( );
  gravSim->AddStaticCube(1.0e9, 6, 1e26);
  QImage img = gravSim->ToQImage(IMG_SIZE, IMG_SIZE);
  ui->imgLabel->setPixmap(QPixmap::fromImage(img));

  Next( );
} // MainWindow

MainWindow::~MainWindow( ) {
  delete ui;
} // ~MainWindow

void MainWindow::Next( ) {
  double imgScale = double(ui->scaleBox->value( )) * 1.0e-11;

  if (this->isRunning == false) {
    QImage img = gravSim->ToQImage(IMG_SIZE, double(IMG_SIZE) * imgScale);
    ui->imgLabel->setPixmap(QPixmap::fromImage(img));

    QString infStr = "\n";
    infStr += "Sim step...........: " + QString::number(gravSim->stepCounter, 'E', 2) + "\n";
    infStr += "Sim time...........: " + QString::number(double(gravSim->totTime), 'E', 2) + "s";
    ui->infoLabel->setText(infStr);

    QTimer::singleShot(10, this, SLOT(Next( )));
    return;
  } // if

  time_t t0 = clock( );
  double dt = ui->dtBox->value( );
  int nSteps = ui->stepsBox->value( );
  bool rotCube = ui->rotCheck->isChecked( );
  double rotSpeed = double(ui->rotSpeed->value( )) * 1e-8;

  for (int i = 0; i < nSteps; i++) {
    gravSim->NextStep(dt);

    if (rotCube)
      gravSim->RotateStaticParticles(rotSpeed * dt);
  } // for

  double DT = double(clock( ) - t0) / CLOCKS_PER_SEC;
  double freq = double(nSteps) / DT;
  freq = int(freq);

  QString infStr = "\n";
  infStr += "Sim step...........: " + QString::number(gravSim->stepCounter, 'E', 2) + "\n";
  infStr += "Steps per second...: " + QString::number(freq, 'E', 2) + "Hz\n";
  infStr += "Sim time...........: " + QString::number(double(gravSim->totTime), 'E', 2) + "s";
  ui->infoLabel->setText(infStr);

  // CREATE IMAGE
  QImage img = gravSim->ToQImage(IMG_SIZE, double(IMG_SIZE) * imgScale);
  ui->imgLabel->setPixmap(QPixmap::fromImage(img));

  // SAVE IMAGE AS FRAME
  if (ui->animCheck->isChecked( )) {
    QString frameStr = QString::number(FRAME_COUNT);
    while (frameStr.length( ) < 3)
      frameStr = "0" + frameStr;

    QString str = "/Users/fmarsman/Dropbox/Qt_Projects/GravitySim/frames/zframe_";
    str += frameStr;
    str += ".png";

    auto active_window = qApp->activeWindow( );
    if (active_window) { // could be null if your app doesn't have focus
      QPixmap pixmap(active_window->size( ));
      active_window->render(&pixmap);
      QImage image = pixmap.toImage( );
      bool success = image.save(str, "png");
      qDebug( ) << "SImage size!" << image.width( ) << "sucess = " << success << "name = " << str;
    } // if

    //bool success = img.save(str, "png");
    //qDebug( ) << "SImage size!" << img.width( ) << "sucess = " << success << "name = " << str;
    this->FRAME_COUNT++;

    ui->statusBar->showMessage("FRAME: " + QString::number(FRAME_COUNT));
  } // if

  QTimer::singleShot(10, this, SLOT(Next( )));
} // Next


// starts or pauses simulation
void MainWindow::on_runButton_clicked( ) {
  if (isRunning) {
    isRunning = false;
    ui->runButton->setText("Start sim");
  } // if
  else {
    isRunning = true;
    ui->runButton->setText("Pause sim");
  } // else
} // on_runButton_clicked




