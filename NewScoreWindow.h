#ifndef _NEWSCOREWINDOW_H_
#define _NEWSCOREWINDOW_H_

/**
* Class gérant la fenêtre récapitulatif lors d'un nouveau record
**/

#include <QtGui>

class NewScoreWindow : public QDialog{

    public:
        NewScoreWindow(QWidget *wParent, QString time);
        ~NewScoreWindow();

        QLineEdit *getAuteur();

    private:
        QVBoxLayout *globalLayout;
            QLabel *score;
            QLineEdit *auteur;

            QHBoxLayout *validateLayout;
                QPushButton *validate;

};

#endif
