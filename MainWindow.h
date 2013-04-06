#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtGui>

class Game;
class CustomGameWindow;
class OptionsWindow;
class StatsWindow;

class MainWindow : public QMainWindow {

    Q_OBJECT;

    public:
        MainWindow();
        ~MainWindow();

        void validInfosPerso(CustomGameWindow *custom);
        void invalidInfosPerso();

        void validInfosOptions(OptionsWindow *options);

        void checkLvl();
        void saveConfig();
        void loadConfig();

        bool getBounds();
        void setBounds(bool b);
        bool getMark();
        void setMark(bool m);
        int getLevel();
        void setLevel(int lvl);
        int getLargeur();
        void setLargeur(int l);
        int getHauteur();
        void setHauteur(int l);
        int getNb_mine();
        void setNb_mine(int nb_m);
        int getLargeurPerso();
        void setLargeurPerso(int lP);
        int getHauteurPerso();
        void setHauteurPerso(int hP);
        int getMinesPerso();
        void setMinesPerso(int mP);

        static bool mark;

    public slots:
        void newGame();
        void closeGame();

        void newGameDebutant();
        void newGameInter();
        void newGameExpert();
        void newGamePerso();

        void showOptions();
        void showStats();

    private:
        void _init_var();
        void _init_menu();

        /**Menu**/
        QMenu *menuJeu;
            QAction *actionDebutant;
            QAction *actionInter;
            QAction *actionExpert;
            QAction *actionPerso;
        QMenu *menuAide;

        QWidget *zoneCentral;
            Game *gameFrame;

        bool bounds;
        bool thirdMark;
        bool useBlack;
        int level;
        int largeur;
        int hauteur;
        int nb_mine;

        int largeurPerso;
        int hauteurPerso;
        int minesPerso;
};


#endif
