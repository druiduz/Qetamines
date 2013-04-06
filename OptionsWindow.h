#ifndef _OPTIONSWINDOW_H_
#define _OPTIONSWINDOW_H_

class OptionsWindow : public QDialog{

    public:
        OptionsWindow(bool bounds=false, bool mark=false, bool useBlack=false, QWidget *parent=0);
        ~OptionsWindow();

        QCheckBox *getCheckBounds();
        QCheckBox *getCheckThirdMark();
        QCheckBox *getCheckBlack();

    private:
        QVBoxLayout *globalLayout;
            QCheckBox *checkBounds;
            QCheckBox *checkThirdMark;
            QCheckBox *checkBlack;

            QHBoxLayout *validLayout;
                QPushButton *valider;
                QPushButton *annuler;

};

#endif
