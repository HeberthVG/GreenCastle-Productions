#include "radio.h"
#include "ui_radio.h"

Radio::Radio(QWidget *parent) :
    QWidget(parent),
    m_pRadioInterface(new Ui::Radio)
{
    m_pRadioInterface->setupUi(this);

    m_iPrevFreq = 883;

    connect(m_pRadioInterface->m_pReturnButton, SIGNAL(released()),
            this, SLOT(ToMainWindow()));
    connect(m_pRadioInterface->m_pStation, SIGNAL(valueChanged(int)),
            this, SLOT(SetStation()));

    //m_pRadioInterface->m_pDisplay->setSegmentStyle(QLCDNumber::Outline);
}

Radio::~Radio()
{
    delete m_pRadioInterface;
}

void Radio::ToMainWindow()
{
    m_pMainWindow = new MainWindow();
    m_pMainWindow->showFullScreen();
    this->close();
}

void Radio::SetStation()
{
    m_dFreq = m_pRadioInterface->m_pStation->value();
    //m_iError = ((int)m_dFreq-m_iPrevFreq)%STEP;
    //m_iPrevFreq = m_dFreq;
    //m_dFreq -= m_iError;
    m_dFreq /= TO_STATION;
    m_pRadioInterface->m_pDisplay->display(m_dFreq);
}

