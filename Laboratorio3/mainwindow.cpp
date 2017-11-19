#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_pUserInterface(new Ui::MainWindow)
{
    m_pUserInterface->setupUi(this);
    MainWindow::SetupButtons();

    //Connect button signal to appropriate slot
    connect(m_pUserInterface->m_pRadio, SIGNAL(released()), this, SLOT(ToRadioWindow()));
    connect(m_pUserInterface->m_pMP3, SIGNAL(released()), this, SLOT(ToMp3Window()));
}

MainWindow::~MainWindow()
{
    delete m_pUserInterface;
}

void MainWindow::ToRadioWindow()
{
    m_RadioWindow = new Radio();
    m_RadioWindow->showFullScreen();
    this->close();
}

void MainWindow::ToMp3Window()
{
    m_Mp3Window = new Mp3();
    m_Mp3Window->showFullScreen();
    this->close();
}

void MainWindow::FullScreen()
{
    //Change icon to fullscreen resolution
    m_RadioIcon.operator =(m_RadioIconFullScreen);
    m_MP3Icon.operator =(m_MP3IconFullScreen);
    RefreshSize();

}

void MainWindow::NormalScreen()
{
    //Change icon to normal resolution
    m_RadioIcon.operator =(m_RadioIconNormal);
    m_MP3Icon.operator =(m_MP3IconNormal);
    RefreshSize();
}

void MainWindow::RefreshSize()
{
    //Update Icon according to resolution
    m_pUserInterface->m_pRadio->setIcon(m_RadioIcon);
    m_pUserInterface->m_pRadio->setFixedSize(m_RadioIcon.actualSize(m_RadioIcon.availableSizes().first()));
    m_pUserInterface->m_pRadio->setIconSize(m_RadioIcon.availableSizes().first());

    m_pUserInterface->m_pMP3->setIcon(m_MP3Icon);
    m_pUserInterface->m_pMP3->setFixedSize(m_MP3Icon.actualSize(m_MP3Icon.availableSizes().first()));
    m_pUserInterface->m_pMP3->setIconSize(m_MP3Icon.availableSizes().first());

}

void MainWindow::SetupButtons()
{
    //Buttons can expand vertically
    m_pUserInterface->m_pRadio->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_pUserInterface->m_pMP3->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    //Set initial icons for buttons
    m_RadioIcon.addFile(RADIO_ICON_FS);
    m_RadioIconNormal.addFile(RADIO_ICON);
    m_RadioIconFullScreen.addFile(RADIO_ICON_FS);
    m_MP3Icon.addFile(MP3_ICON_FS);
    m_MP3IconNormal.addFile(MP3_ICON);
    m_MP3IconFullScreen.addFile(MP3_ICON_FS);
    RefreshSize();
}
