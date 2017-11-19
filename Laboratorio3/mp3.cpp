#include "mp3.h"
#include "ui_mp3.h"

Mp3::Mp3(QWidget *parent) :
    QWidget(parent),
    m_pMp3Interface(new Ui::Mp3)
{
    m_pMp3Interface->setupUi(this);

    m_Playlist.addMedia(QUrl("qrc:/rsc/mp3/bensound-creepy.mp3"));
    m_Playlist.addMedia(QUrl("qrc:/rsc/mp3/bensound-epic.mp3"));
    m_Playlist.addMedia(QUrl("qrc:/rsc/mp3/bensound-instinct.mp3"));
    m_Playlist.addMedia(QUrl("qrc:/rsc/mp3/bensound-jazzyfrenchy.mp3"));
    m_Playlist.addMedia(QUrl("qrc:/rsc/mp3/bensound-pianomoment.mp3"));
    m_Playlist.addMedia(QUrl("qrc:/rsc/mp3/bensound-retrosoul.mp3"));
    m_Playlist.setCurrentIndex(FIRST_SONG);

    m_CurrentSong.setPlaylist(&m_Playlist);
    m_CurrentSong.setVolume(50);
    m_pMp3Interface->m_PauseButton->setDisabled(true);
    m_pMp3Interface->m_StopButton->setDisabled(true);
    m_pMp3Interface->m_SongName->setText(m_CurrentSong.currentMedia().canonicalUrl().toString().section("/", LAST_PART, LAST_PART).section(".", FIRST_PART, PENULTIMATE_PART));

    connect(m_pMp3Interface->m_pReturnButton, SIGNAL(released()), this, SLOT(ToMainWindow()));
    connect(m_pMp3Interface->m_PlayButton, SIGNAL(released()), this, SLOT(PlaySong()));
    connect(m_pMp3Interface->m_StopButton, SIGNAL(released()), this, SLOT(StopSong()));
    connect(m_pMp3Interface->m_PauseButton, SIGNAL(released()), this, SLOT(PauseSong()));
    connect(m_pMp3Interface->m_NextButton, SIGNAL(released()), this, SLOT(NextSong()));
    connect(m_pMp3Interface->m_PreviousButton, SIGNAL(released()), this, SLOT(PreviousSong()));
}

Mp3::~Mp3()
{
    delete m_pMp3Interface;
    delete &m_CurrentSong;
    delete &m_Playlist;
}

void Mp3::ToMainWindow()
{
    m_CurrentSong.stop();
    m_pMainWindow = new MainWindow();
    m_pMainWindow->showFullScreen();
    this->close();
}

void Mp3::PlaySong()
{
    m_CurrentSong.play();
    m_pMp3Interface->m_SongName->setText(m_CurrentSong.currentMedia().canonicalUrl().toString().section("/", LAST_PART, LAST_PART).section(".", FIRST_PART, PENULTIMATE_PART));
    m_pMp3Interface->m_PlayButton->setDisabled(true);
    m_pMp3Interface->m_PauseButton->setEnabled(true);
    m_pMp3Interface->m_StopButton->setEnabled(true);
}

void Mp3::PauseSong()
{
    m_CurrentSong.pause();
    m_pMp3Interface->m_PlayButton->setEnabled(true);
    m_pMp3Interface->m_PauseButton->setDisabled(true);
    m_pMp3Interface->m_StopButton->setEnabled(true);
}

void Mp3::StopSong()
{
    m_CurrentSong.stop();
    m_pMp3Interface->m_PlayButton->setEnabled(true);
    m_pMp3Interface->m_PauseButton->setDisabled(true);
    m_pMp3Interface->m_StopButton->setDisabled(true);
}

void Mp3::PreviousSong()
{
    m_CurrentSong.stop();
    if (m_Playlist.currentIndex() == FIRST_SONG)
        m_Playlist.setCurrentIndex(LAST_SONG);
    else
        m_Playlist.setCurrentIndex(m_Playlist.currentIndex()-ONE_STEP);
    Mp3::PlaySong();
}

void Mp3::NextSong()
{
    m_CurrentSong.stop();
    if (m_Playlist.currentIndex() == LAST_SONG)
        m_Playlist.setCurrentIndex(FIRST_SONG);
    else
        m_Playlist.setCurrentIndex(m_Playlist.currentIndex()+ONE_STEP);
    Mp3::PlaySong();
}
