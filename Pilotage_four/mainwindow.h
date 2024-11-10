#ifndef MAINWINDOW_H
#define MAINWINDOW_H

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startHeating();
    void stopHeating();
    void setPuissance(int value);
    void setConsigne(int value);
    void sampleTemperature();

private:
    Ui::MainWindow *ui;

    // Variables pour la régulation
    double temperature;
    double consigne;
    int puissance;
    int samplingInterval;

    // Timer pour l'échantillonnage de la température
    QTimer *sampleTimer;

    // Graphique
    QChart *chart;
    QLineSeries *series;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QChartView *chartView;

    // Instance du contrôle du four
    ControlFour controlFour;
};

#endif // MAINWINDOW_H
