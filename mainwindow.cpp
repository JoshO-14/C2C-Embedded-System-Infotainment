#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <wiringPi.h>
#include <QDebug>


#define HEADLIGHT_PIN 4
#define INTERIOR_PIN 17
#define HORN_BUTTON_PIN 27

#define BRIGHT_LED1 5
#define BRIGHT_LED2 13

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      headlightsOn(false),
      interiorLightsOn(false)
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
    connect(ui->sliderBrightness, &QSlider::valueChanged, this, &MainWindow::brightnessChanged);

    // Audio
    connect(ui->sliderVolume, &QSlider::valueChanged, this, &MainWindow::volumeChanged);

    //Horn
    connect(ui->btnHorn, &QPushButton::pressed, this, &MainWindow::hornPressed);
    connect(ui->btnHorn, &QPushButton::released, this, &MainWindow::hornReleased);

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
    wiringPiSetupGpio();

    pinMode(HEADLIGHT_PIN, OUTPUT);
    pinMode(INTERIOR_PIN, OUTPUT);
    pinMode(HORN_BUTTON_PIN, OUTPUT);

    pinMode(BRIGHT_LED1, OUTPUT);
    pinMode(BRIGHT_LED2, OUTPUT);

    qDebug() << "GPIO Setup Complete";   
}

void MainWindow::setHeadlights(bool state)
{
    digitalWrite(HEADLIGHT_PIN, state ? HIGH : LOW);
    qDebug() << "Headlights:" << state;
}

void MainWindow::setInteriorLights(bool state)
{
    digitalWrite(INTERIOR_PIN, state ? HIGH : LOW);
    qDebug() << "Interior Lights:" << state;
}

void MainWindow::hornPressed()
{
    digitalWrite(HORN_BUTTON_PIN, HIGH);
    qDebug() << "HORN!";
}

void MainWindow::hornReleased()
{
    digitalWrite(HORN_BUTTON_PIN, LOW);
}

void MainWindow::setBrightness(int level)
{
    qDebug() << "Brightness Level:" << level;

    int leds = level / 33;

    digitalWrite(BRIGHT_LED1, leds >= 1);
    digitalWrite(BRIGHT_LED2, leds >= 2);
}

void MainWindow::setVolume(int level)
{
    qDebug() << "Volume Level:" << level;
}
