#ifndef MP3_H
#define MP3_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMediaMetaData>

#include "mainwindow.h"

#define FIRST_SONG        0
#define LAST_SONG         5
#define ONE_STEP          1
#define FIRST_PART        0
#define LAST_PART        -1
#define PENULTIMATE_PART -2

class MainWindow;

namespace Ui {
class Mp3;
}

class Mp3 : public QWidget
{
    Q_OBJECT

public:
    explicit Mp3(QWidget *parent = 0);
    ~Mp3();

private slots:
    void ToMainWindow();
    void PlaySong();
    void StopSong();
    void PauseSong();
    void NextSong();
    void PreviousSong();

private:
    Ui::Mp3 *m_pMp3Interface;
    MainWindow *m_pMainWindow;
    QMediaPlayer m_CurrentSong;
    QMediaPlaylist m_Playlist;
};

#endif // MP3_H
