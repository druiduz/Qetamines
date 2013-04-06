#ifndef _STATISTIQUES_H_
#define _STATISTIQUES_H_

/**
* Class gérant les scores pour chaques modes ainsi que les statistiques global tel que le nombre de parties jouées
**/

#define NB_RECORD_PER_LVL 5

struct Score{
    QString auteur;
    QString time;
    QString date;

    Score(){
        auteur = QString("Anonymous");
        time = QString("00:00:0");
        date = QString("00");
    }
};

class Statistiques{

    public:
        Statistiques();
        ~Statistiques();

        void _init_score();

        void finishedGame(int level, QString time, bool win);
        void insertScore(int i, int level, QString t, QString a=QString("Anonymous"), QString d=QString("00/00/00"));

        void addPartie();
        void setNbPartie(int nb);
        int getNbPartie();
        void setNbPartieWin(int nb);
        int getNbPartieWin();
        void setNbPartieLose(int nb);
        int getNbPartieLose();
        float getPourcentWin();

        int nbPartie;
        int nbPartieWin;
        int nbPartieLose;
        float pourcentWin;

        struct Score **scoresLevel1;
        struct Score **scoresLevel2;
        struct Score **scoresLevel3;

    private:
        void decaleScore(int i, int level);
};

#endif
