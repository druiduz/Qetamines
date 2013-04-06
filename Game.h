#ifndef _GAME_H_
#define _GAME_H_

#include <QtGui>

class MainWindow;
class GameIndicator;
class AbstractPlateau;
class PlateauWithBound;
class PlateauWoBound;
class Case;
class DataMap;
class Statistiques;

class Game : public QFrame{

    Q_OBJECT;

    public:
        Game(QWidget *wParent, int wLevel, int wLargeur, int wHauteur, int wMines, bool wThirdMark=false, bool useBC=false, bool useBounds=false);
        ~Game();

        void saveSave();
        void loadSave();

        void connexions();
        void startGame();
        void autoFirstDeminage(int idX=-1, int idY=-1);

        void finishGame(bool win=false);

        void checkRecord(int win);

        int getLargeur();
        void setLargeur(int l);
        int getHauteur();
        void setHauteur(int h);
        Statistiques *getStats();
        DataMap *getData();

    public slots:
        void slotDemine();

        void slotPropageDeminage(int x, int y);
        void slotDemineAroundFlag(int x, int y);
        void slotFlag(bool retrait=true);

        void slotGameOver(bool win=false);

        void resetGame();

    private:
        MainWindow *windowParent;
            GameIndicator *indicator;
            AbstractPlateau *p;

        DataMap *data;

        int nbCaseRest;
        int nbMineRest;

        int *idFirstCase;
        Statistiques *stats;
};

#endif
