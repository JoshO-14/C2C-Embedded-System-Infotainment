#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      headlightsOn(false),
      interiorLightsOn(false),
      fuelLightsOn(false)

{
    ui->setupUi(this);

    setupGPIO();

    // Navigation
    connect(ui->btnHome, &QPushButton::clicked, this, &MainWindow::showHome);
    connect(ui->btnLights, &QPushButton::clicked, this, &MainWindow::showLights);
    connect(ui->btnAudio, &QPushButton::clicked, this, &MainWindow::showAudio);

    // Lights
    connect(ui->btnHeadlights, &QPushButton::clicked, this, &MainWindow::toggleHeadlights);
    connect(ui->btnInteriorLights, &QPushButton::clicked, this, &MainWindow::toggleInteriorLights);
    connect(ui->btnFuelLights, &QPushButton::clicked, this, &MainWindow::toggleFuelLights);
    connect(ui->sliderBrightness, &QSlider::valueChanged, this, &MainWindow::brightnessChanged);

    // Audio
    connect(ui->sliderVolume, &QSlider::valueChanged, this, &MainWindow::volumeChanged);

    showHome();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Navigation
void MainWindow::showHome()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::showLights()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::showAudio()
{
    ui->stackedWidget->setCurrentIndex(2);
}

// Lights
void MainWindow::toggleHeadlights()
{
    headlightsOn = !headlightsOn;
    setHeadlights(headlightsOn);
    ui->btnHeadlights->setText(headlightsOn ? "Headlights ON" : "Headlights OFF");
}

void MainWindow::toggleInteriorLights()
{
    interiorLightsOn = !interiorLightsOn;
    setInteriorLights(interiorLightsOn);
    ui->btnInteriorLights->setText(interiorLightsOn ? "Interior ON" : "Interior OFF");
}

void MainWindow::toggleFuelLights()
{
    fuelLightsOn = !fuelLightsOn;
    setFuelLights(fuelLightsOn);
    ui->btnFuelLights->setText(fuelLightsOn ? "Fuel Light ON" : "Fuel Light OFF");
}

void MainWindow::brightnessChanged(int value)
{
    ui->labelBrightnessValue->setText("Brightness Level: " + QString::number(value));
    setBrightness(value);
}

// Audio
void MainWindow::volumeChanged(int value)
{
    ui->labelVolumeValue->setText("Volume Level: " + QString::number(value));
    setVolume(value);
}

// GPIO (Implement Later)
void MainWindow::setupGPIO()
{
    qDebug() << "GPIO Setup Complete";
}

void MainWindow::setHeadlights(bool state)
{
    qDebug() << "Headlights:" << state;
}

void MainWindow::setInteriorLights(bool state)
{
    qDebug() << "Interior Lights:" << state;
}

void MainWindow::setFuelLights(bool state)
{
    qDebug() << "Fuel Lights:" << state;
}

void MainWindow::setBrightness(int level)
{
    qDebug() << "Brightness Level:" << level;
}

void MainWindow::setVolume(int level)
{
    qDebug() << "Volume Level:" << level;
}
