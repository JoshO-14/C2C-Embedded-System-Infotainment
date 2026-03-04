#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Navigation
    void showHome();
    void showLights();
    void showAudio();

    // Lights
    void toggleHeadlights();
    void toggleInteriorLights();
    void toggleFuelLights();
    void brightnessChanged(int value);

    // Audio
    void volumeChanged(int value);

private:
    Ui::MainWindow *ui;

    bool headlightsOn;
    bool interiorLightsOn;
    bool fuelLightsOn;

    void setupGPIO();

    // GPIO control (implement later)
    void setHeadlights(bool state);
    void setInteriorLights(bool state);
    void setFuelLights(bool state);
    void setBrightness(int level);
    void setVolume(int level);
};

#endif // MAINWINDOW_H
