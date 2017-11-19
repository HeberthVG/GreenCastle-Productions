#ifndef RADIO_H
#define RADIO_H

#include <QWidget>

#include "mainwindow.h"
class MainWindow;

#define STEP       4
#define TO_STATION 10

namespace Ui {
class Radio;
}

class Radio : public QWidget
{
    Q_OBJECT

public:
    explicit Radio(QWidget *parent = 0);
    ~Radio();

private slots:
    void ToMainWindow();
    void SetStation();

private:
    Ui::Radio *m_pRadioInterface;
    MainWindow *m_pMainWindow;
    double m_dFreq;
    int m_iPrevFreq, m_iError;
};

#endif // RADIO_H
