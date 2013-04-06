#include "header.h"
#include "GameIndicator.h"

GameIndicator::GameIndicator(int gMinesRest, int gCaseRest, QWidget *parent) : QFrame(parent){

    caseRest = gCaseRest;
    minesRest = gMinesRest;

    setLineWidth(1);
    setMidLineWidth(3);
    setFrameShadow(QFrame::Sunken);
    setFrameShape(QFrame::Panel);

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(QString("black")));

    mine = new QLCDNumber(3);
        mine->setSegmentStyle(QLCDNumber::Outline);
        mine->setDigitCount(3);
        mine->display(minesRest);
        mine->setLineWidth(1);
        mine->setMidLineWidth(1);
        mine->setFrameShadow(QFrame::Sunken);
        mine->setFrameShape(QFrame::Panel);
        mine->setObjectName("LCD");

    caseRestant = new QLCDNumber(8);
        mine->setSegmentStyle(QLCDNumber::Outline);
        mine->setDigitCount(8);
        mine->display(caseRest);
        mine->setLineWidth(1);
        mine->setMidLineWidth(1);
        mine->setFrameShadow(QFrame::Sunken);
        mine->setFrameShape(QFrame::Panel);
        mine->setObjectName("LCD");

    retry = new QPushButton("_");

    chrono = new QTimer();
        chrono->setInterval(ECHELLE_TIMER);

    time = new QLabel("00:00:0");
    horloge = new QTime(0, 0);

    topLayout = new QHBoxLayout(this);
        topLayout->addWidget(mine);
            topLayout->setAlignment(mine, Qt::AlignLeft);
        topLayout->addWidget(caseRestant);
            topLayout->setAlignment(caseRestant, Qt::AlignLeft);
        topLayout->addWidget(retry);
            topLayout->setAlignment(retry, Qt::AlignCenter);
        topLayout->addWidget(time);
            topLayout->setAlignment(time, Qt::AlignRight);

}

GameIndicator::~GameIndicator(){
    chrono->stop();
    delete(chrono);
    delete(horloge);
}

void GameIndicator::setMinesRest(int mines){
    minesRest = mines;
}

QPushButton *GameIndicator::getRetry(){
    return retry;
}

QTimer *GameIndicator::getChrono(){
    return chrono;
}

QTime *GameIndicator::getHorloge(){
    return horloge;
}

void GameIndicator::reset(){
    mine->display(minesRest);
    caseRestant->display(caseRest);
    time->setText("00:00:0");
    horloge->setHMS(0, 0, 0);
}

void GameIndicator::changeMine(bool action){
    int value = mine->intValue();
    if(action){
        mine->display(--value);
    }
    else{
        mine->display(++value);
    }
}

void GameIndicator::changeCaseRestante(bool action){
    int value = caseRestant->intValue();
    if(action){
        caseRestant->display(--value);
    }
    else{
        caseRestant->display(++value);
    }
}

void GameIndicator::updateTime(){
   *horloge = horloge->addMSecs(ECHELLE_TIMER);
    time->setText(horloge->toString("mm:ss:z ").remove(7, 8));
}

void GameIndicator::startChrono(){
    connect(chrono, SIGNAL(timeout()), SLOT(updateTime()));
    chrono->start();
}

void GameIndicator::stopChrono(){
    chrono->disconnect(SIGNAL(timeout()));
    chrono->stop();
}

