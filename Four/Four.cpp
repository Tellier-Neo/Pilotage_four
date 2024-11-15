#include "Four.h"
#include <QTimer>

Four::Four(QWidget* parent)
    : QMainWindow(parent), cardId(-1), timeElapsed(0.0)
{
    isHeating = false;
    temp = 20;
    consigne = 20;
    puissance = 0;
    intervalleEchantillon = 10000;

    ui.setupUi(this);

    graphScene = new QGraphicsScene(this);
    ui.temperatureGraphView->setScene(graphScene);

    graphScene->setSceneRect(0, 0, 600, 300);
    ui.temperatureGraphView->setRenderHint(QPainter::Antialiasing);


    sampleTimer = new QTimer(this);

    connect(sampleTimer, &QTimer::timeout, this, &Four::UpdateStatutChauffage);

    InitializeCard();

}

void Four::InitializeCard()
{
    cardId = Register_Card(PCI_9111DG, 0);
    if (cardId >= 0) {
        ui.cardLogBox->addItem("Ouverture carte OK");
        AI_9111_Config(cardId, TRIG_INT_PACER, P9111_TRGMOD_SOFT, 0);
        ReadTension();
    }
    else {
        ui.cardLogBox->addItem("Erreur d'ouverture de la carte");
    }
}

void Four::ReadTension()
{
    if (cardId >= 0) {
        double tension;
        if (AI_VReadChannel(cardId, 0, AD_B_10_V, &tension) < 0) {
            ui.cardLogBox->addItem("Erreur tension");
        }
        else {
            ui.cardLogBox->addItem("Tension: " + QString::number(tension));
        }
    }
}

void Four::ReadTemperature()
{
    if (cardId >= 0) {
        double tension;
        if (AI_VReadChannel(cardId, 0, AD_B_10_V, &tension) < 0) {
            ui.cardLogBox->addItem("Erreur temperature");
        }
        else {
            double temperature = 43.76 * tension - 58.29;

            ui.tempStatLabel->setText(QString("Temperature actuelle: %1.C").arg(temperature));
            ui.graphicBox->addItem("Temperature: " + QString::number(temperature) + " .C");

            // Limite la température à 65°C
            if (temperature > 65.0) {
                stopHeat();
                ui.cardLogBox->addItem("Temperature trop elevee : Chauffage arrete !");
                return;
            }

            // Mise à jour des affichages
            ui.tempStatLabel->setText(QString("Temperature actuelle : %1.C").arg(temperature));

            // Mise à jour du graphique
            UpdateGraph(temperature);
        }
    }
}

void Four::OnFourButtonClicked()
{
    if (!isHeating)
    {
        startHeat();
    }
    else
    {
        stopHeat();
    }
}

void Four::startHeat()
{
    if (cardId < 0) {
        ui.cardLogBox->addItem("Erreur carte non initialisee.");
        return;
    }

    double tension = (puissance / 100.0) * 10.0;

    if (AO_VWriteChannel(cardId, 0, tension) < 0) {
        ui.cardLogBox->addItem("Erreur demarrage de chauffage.");
    }
    else {
        ui.cardLogBox->addItem("Chauffage demarre a " + QString::number(tension) + "V");
        isHeating = true;
        sampleTimer->start(intervalleEchantillon);
        ui.pushButton->setText("Arret");
    }
}


void Four::stopHeat()
{
    if (cardId < 0) {
        ui.cardLogBox->addItem("Erreur carte non initialisee");
        return;
    }

    if (AO_VWriteChannel(cardId, 0, 0.0) < 0) {
        ui.cardLogBox->addItem("Erreur arret de chauffage");
    }
    else {
        ui.cardLogBox->addItem("Chauffage arrete");
        isHeating = false;
        sampleTimer->stop();
        ui.pushButton->setText("Chauffer");
    }
}

void Four::SetPower(int value)
{
    puissance = value;
    ui.powerValue->setText(QString("%1%").arg(puissance));
    ui.powerStatLabel->setText(QString("Puissance: %1%").arg(puissance));

    // Appliquer la nouvelle puissance si le four chauffe déjà
    if (isHeating) {
        startHeat();
    }
}


void Four::SetConsigne(int value)
{
    consigne = (double)value;
    ui.consigneValue->setText(QString("%1.C").arg(consigne));
    ui.consigneStatLabel->setText(QString("Consigne: %1.C").arg(consigne));
}

double coef = 5.0;

void Four::UpdateStatutChauffage()
{
    ReadTemperature();
    ReadTension();
}

void Four::UpdateGraph(double temperature)
{
    // Ajoute le nouveau point
    dataPoints.emplace_back(timeElapsed, temperature);

    // Efface la scène pour un nouveau dessin
    graphScene->clear();

    // Définir l'espace pour les axes et les unités
    const int margin = 50; // Espace autour du graphique pour les unités
    const int graphWidth = 600 + margin;  // Largeur du graphique
    const int graphHeight = 300 + margin; // Hauteur du graphique

    // Ajoute les axes avec marges
    graphScene->addLine(margin, graphHeight - margin, graphWidth, graphHeight - margin, QPen(Qt::black, 2)); // Axe X
    graphScene->addLine(margin, graphHeight - margin, margin, 0, QPen(Qt::black, 2));                      // Axe Y

    // Ajoute des graduations sur l'axe X (temps), toutes les 1 minute (60 secondes)
    for (int i = 0; i <= 10; ++i) { // Jusqu'à 10 minutes (10 graduations pour 1 minute chacune)
        int x = margin + i * 60; // 1 minute = 60 pixels
        graphScene->addLine(x, graphHeight - margin, x, graphHeight - margin - 5, QPen(Qt::black)); // Petite graduation
        graphScene->addText(QString("%1").arg(i))->setPos(x - 10, graphHeight - margin + 5); // Texte (en minutes)
    }

    // Ajoute des graduations sur l'axe Y (température de 10°C à 80°C, tous les 5°C)
    for (int i = 0; i <= 14; ++i) { // Jusqu'à 80°C
        int y = graphHeight - margin - i * 20; // 5°C = 20 pixels
        graphScene->addLine(margin, y, margin + 5, y, QPen(Qt::black)); // Petite graduation
        graphScene->addText(QString("%1").arg(10 + i * 5))->setPos(margin - 35, y - 10); // Texte sans "°C"
    }

    // Ajoute les unités sur les axes
    graphScene->addText("Temps en minutes")->setPos((graphWidth - margin) / 2, graphHeight - margin + 20); // Axe X
    QGraphicsTextItem* yAxisLabel = graphScene->addText("Temperature en degre Celsius");
    yAxisLabel->setRotation(-90);
    yAxisLabel->setPos(margin - 50, (graphHeight - margin) / 2 + 20); // Axe Y

    // Trace les points et les relie
    QPointF lastPoint(margin, graphHeight - margin - dataPoints[0].y() * 3); // Premier point
    for (size_t i = 0; i < dataPoints.size(); ++i) {
        QPointF currentPoint(margin + (dataPoints[i].x() / 60.0) * 60, graphHeight - margin - dataPoints[i].y() * 3); // Position échelle

        // Dessine une ligne entre les points
        if (i > 0) {
            graphScene->addLine(QLineF(lastPoint, currentPoint), QPen(Qt::blue, 2));
        }

        // Dessine un point pour la température
        graphScene->addEllipse(currentPoint.x() - 3, currentPoint.y() - 3, 6, 6, QPen(Qt::red), QBrush(Qt::red));
        lastPoint = currentPoint;
    }

    // Met à jour le temps écoulé
    timeElapsed += intervalleEchantillon / 1000.0; // Intervalle d'échantillonnage en secondes
}

Four::~Four()
{
    // Arrête le chauffage si nécessaire pour éviter tout problème lors de la fermeture de l'application
    if (isHeating) {
        stopHeat();
    }

    // Stoppe le timer pour éviter d'essayer de déclencher une opération après la fermeture
    if (sampleTimer) {
        sampleTimer->stop();
    }

    // Libère la mémoire allouée pour la scène graphique
    if (graphScene) {
        delete graphScene;
    }

    // Supprime le timer (bien que sampleTimer soit déjà supprimé dans le parent, c'est une bonne pratique)
    delete sampleTimer;
}
