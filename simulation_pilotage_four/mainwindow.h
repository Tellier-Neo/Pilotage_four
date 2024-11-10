#ifndef MAINWINDOW_H
#define MAINWINDOW_H

QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startHeating();
    void updateTemperature();
    void adjustTemperature();
    void updateGraph();

private:
    // UI elements
    QSlider *sliderPuissance;
    QLabel *labelTemp;
    QLabel *labelConsigne;
    QPushButton *startButton;
    QChartView *chartView;

    // Variables de simulation
    double currentTemp;
    double consigne;
    int puissance;
    QTimer *heatTimer;

    // Graphique
    QLineSeries *series;
    QChart *chart;
    QValueAxis *axisX;
    QValueAxis *axisY;
};

#endif // MAINWINDOW_H
