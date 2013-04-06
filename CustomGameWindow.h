#ifndef _CUSTOMGAMEWINDOW_H_
#define _CUSTOMGAMEWINDOW_H_

//#include <QtGui>

class CustomGameWindow : public QDialog{

    public:
        CustomGameWindow(int lPerso, int hPerso, int mPeros, QWidget *parent);
        ~CustomGameWindow();

        int getLargeur();
        int getHauteur();
        int getMines();

    private:
        QVBoxLayout *globalLayout;
            QGroupBox *groupEdit;
                QFormLayout *fLayout;
                    QLineEdit *largeurEdit;
                    QLineEdit *hauteurEdit;
                    QLineEdit *minesEdit;
            QHBoxLayout *validLayout;
                QPushButton *valider;
                QPushButton *annuler;

        int largeurPerso;
        int hauteurPerso;
        int minesPerso;

};

#endif
