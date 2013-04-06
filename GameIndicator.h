#ifndef _GAMEINDICATOR_H_
#define _GAMEINDICATOR_H_

#define ECHELLE_TIMER 100

#include <QtGui>

class GameIndicator : public QFrame{

    Q_OBJECT;

    public:
        GameIndicator(int gMinesRest, int gCaseRest, QWidget *parent);
        ~GameIndicator();

        void setMinesRest(int mines);
        QPushButton *getRetry();
        QTimer *getChrono();
        QTime *getHorloge();

        void changeMine(bool action); /**True : retire une mine, false : ajoute**/
        void changeCaseRestante(bool action);
        void reset();
        void startChrono();
        void stopChrono();

    public slots:
        void updateTime();

    private:
        QHBoxLayout *topLayout;
            QLCDNumber *mine;
            QLCDNumber *caseRestant;
            QPushButton *retry;
            //QLCDNumber *time;
            QLabel *time;

        QTimer *chrono;
        QTime *horloge;
        int caseRest;
        int minesRest;

};

#endif
