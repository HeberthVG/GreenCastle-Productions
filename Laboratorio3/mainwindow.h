#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "radio.h"
#include "mp3.h"

class Mp3;
class Radio;

#define RADIO_ICON    "/home/hgvalver/Documentos/Qt-Projects/MP3-Radio/imgs/radio-7.jpg"
#define MP3_ICON      "/home/hgvalver/Documentos/Qt-Projects/MP3-Radio/imgs/mp3-30.png"
#define RADIO_ICON_FS "/home/hgvalver/Documentos/Qt-Projects/MP3-Radio/imgs/radio-fs.jpg"
#define MP3_ICON_FS   "/home/hgvalver/Documentos/Qt-Projects/MP3-Radio/imgs/mp3-fs.png"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void SetupButtons();
    void RefreshSize();
    ~MainWindow();

private slots:
    void NormalScreen();
    void FullScreen();
    void ToRadioWindow();
    void ToMp3Window();

private:
    QPushButton *m_pButton;
    QIcon m_MP3Icon, m_MP3IconNormal, m_MP3IconFullScreen;
    QIcon m_RadioIcon, m_RadioIconNormal, m_RadioIconFullScreen;
    Ui::MainWindow *m_pUserInterface;
    Radio *m_RadioWindow;
    Mp3 *m_Mp3Window;
};

#endif // MAINWINDOW_H
