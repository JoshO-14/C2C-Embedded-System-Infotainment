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
    void brightnessChanged(int value);

    // Audio
    void volumeChanged(int value);

    // Horn
    void hornPressed();
    void hornReleased();
    void checkHornButton();

private:
    Ui::MainWindow *ui;

    bool headlightsOn;
    bool interiorLightsOn;

    void setupGPIO();

    // GPIO control (implement later)
    void setHeadlights(bool state);
    void setInteriorLights(bool state);
    void setBrightness(int level);
    void setVolume(int level);
};

#endif // MAINWINDOW_H
