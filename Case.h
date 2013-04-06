#ifndef _MINE_H_
#define _MINE_H_

#include <QtGui>

class AbstractPlateau;

class Case : public QFrame {

    Q_OBJECT;

    public:
        Case();
        Case(int i, int j, int val, AbstractPlateau *pParent);
        ~Case();

        QString showValue(int val=0, const QString color="black", const QString backg_color="");

        void setValue(int val);
        int getValue();
        int getX();
        int getY();
        void setHasCase(bool b);
        bool getHasCase();
        bool getFlag();
        bool getThirdMark();
        void setBlack(bool b);
        bool isBlack();

        void addMine();
        bool notMine();
        bool isMine();
        void afficheMine();

        void reset();

    public slots:
        void deminage();

    signals:
        void signalDemine();
        void signalDemineAroundCase(int, int);
        void signalCaseFlag(bool);
        void signalDemineAroundFlag(int x, int y);
        void signalGameOver(bool);

    private:
        bool eventFilter(QObject *obj, QEvent *event);
        void putFlagOneMine();
        void putFlagOrMarkOneMine();

        QLabel *label;

        AbstractPlateau *parent;
        int value;
        bool black;
        int x;
        int y;
        bool hasCase;
        bool flag;
        bool thirdMark;
};

#endif
