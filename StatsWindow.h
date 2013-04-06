#ifndef _STATSWINDOW_H_
#define _STATSWINDOW_H_

class Statistiques;

class StatsWindow : public QDialog{
    public:
        StatsWindow(QWidget *parent, Statistiques *stats);
        ~StatsWindow();

    private:
        QVBoxLayout *globalLayout;
            QGroupBox *statsBox;
                QVBoxLayout *statsBoxlayout;
                    QLabel *nbPartie;
                    QLabel *nbWinLab;
                    QLabel *nbLoseLab;
                    QLabel *pourcentWin;

            QTabWidget *onglets;
                QStandardItemModel *page1Model;
                    QTableView *page1View;
                QStandardItemModel *page2Model;
                    QTableView *page2View;
                QStandardItemModel *page3Model;
                    QTableView *page3View;

            QHBoxLayout *validLayout;
                QPushButton *fermer;

};

#endif
