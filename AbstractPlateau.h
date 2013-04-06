#ifndef _ABSTRACTPLATEAU_H_
#define _ABSTRACTPLATEAU_H_

#define NB_CASE_AROUND 8

#include <QtGui>

class Case;
class DataMap;

class AbstractPlateau : public QFrame{

    Q_OBJECT;

    public:
        AbstractPlateau(QWidget *parent);
        virtual ~AbstractPlateau();

        void initializePlateau();
        void createPlateau(int l, int h);
        void fillPlateau(int nb_m);
        void generateBlackCases();
        bool mineIsPossibleWithBlack(int x, int y);

        void generateMine(int nb_m, int *minesX, int *minesY);
        void generateIndicator(int *minesX, int *minesY, int nb_mine);

        void reset();

        bool hasFlagAround(int x, int y);

        virtual Case **getCasesAround(int x, int y) =0;

        int getLargeur();
        void setLargeur(int l);
        int getHauteur();
        void setHauteur(int h);
        void setNb_mine(int nb_m);
        Case *getCase(int x, int y);

    public slots:
        void propageDeminage(int x, int y);
        void demineAroundFlag(int x, int y);

    signals:
        void signalFirstDeminage(int idX, int idY);
        void signalGameOver(bool win);

    protected:
        DataMap *data;

        Case ***plateau;
};

#endif
