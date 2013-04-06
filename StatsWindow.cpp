#include "header.h"
#include "StatsWindow.h"

#include "Statistiques.h"

StatsWindow::StatsWindow(QWidget *parent, Statistiques *stats) : QDialog(parent){
    setWindowTitle("Statistiques");
    setGeometry(150, 150, 330, 365);

    statsBox = new QGroupBox("Statistiques générales");
    nbPartie = new QLabel(QString("Nombre de parties jouées : ").append(QString::number(stats->getNbPartie())));
    nbWinLab = new QLabel(QString("Nombre de victoires : ").append(QString::number(stats->getNbPartieWin())));
    nbLoseLab = new QLabel(QString("Nombre de défaites : ").append(QString::number(stats->getNbPartieLose())));
    pourcentWin = new QLabel(QString("Pourcentage de victoires : ").append(QString::number(stats->getPourcentWin())).append(QString("%")));
    statsBoxlayout = new QVBoxLayout(statsBox);
        statsBoxlayout->addWidget(nbPartie);
        statsBoxlayout->addWidget(nbWinLab);
        statsBoxlayout->addWidget(nbLoseLab);
        statsBoxlayout->addWidget(pourcentWin);

    /** Onglets pour chaques difficultés **/
    onglets = new QTabWidget;
    onglets->setGeometry(0, 0, 500, 200);

        int nb_record = 0;
        /** Page Level 1 **/
        for(int i = 0; i < NB_RECORD_PER_LVL; i++){
            if(stats->scoresLevel1[i]->time != "00:00:0"){
                nb_record++;
            }
            else break;
        }
        page1Model = new QStandardItemModel(nb_record, 3);
            page1Model->setHorizontalHeaderLabels(QStringList("Auteur")<<QString("Temps")<<QString("Date"));
            for(int i = 0; i < nb_record; i++){
                page1Model->setItem(i, 0, new QStandardItem(stats->scoresLevel1[i]->auteur));
                page1Model->setItem(i, 1, new QStandardItem(stats->scoresLevel1[i]->time));
                page1Model->setItem(i, 2, new QStandardItem(stats->scoresLevel1[i]->date));
            }

        page1View = new QTableView;
            page1View->setSortingEnabled(true);
            page1View->setModel(page1Model);
            page1View->sortByColumn(1, Qt::AscendingOrder);
            QHeaderView *page1VHeader = page1View->verticalHeader();
                page1VHeader->hide();


        /** Page Level 2 **/
        nb_record = 0;
        for(int i = 0; i < NB_RECORD_PER_LVL; i++){
            if(stats->scoresLevel2[i]->time != "00:00:0"){
                nb_record++;
            }
            else break;
        }
        page2Model = new QStandardItemModel(nb_record, 3);
            page2Model->setHorizontalHeaderLabels(QStringList("Auteur")<<QString("Temps")<<QString("Date"));
            for(int i = 0; i < nb_record; i++){
                page2Model->setItem(i, 0, new QStandardItem(stats->scoresLevel2[i]->auteur));
                page2Model->setItem(i, 1, new QStandardItem(stats->scoresLevel2[i]->time));
                page2Model->setItem(i, 2, new QStandardItem(stats->scoresLevel2[i]->date));
            }

        page2View = new QTableView;
            page2View->setSortingEnabled(true);
            page2View->sortByColumn(1, Qt::AscendingOrder);
            page2View->setModel(page2Model);
            QHeaderView *page2VHeader = page2View->verticalHeader();
                page2VHeader->hide();

        /** Page Level 3 **/
        nb_record = 0;
        for(int i = 0; i < NB_RECORD_PER_LVL; i++){
            if(stats->scoresLevel3[i]->time != "00:00:0"){
                nb_record++;
            }
            else break;
        }
        page3Model = new QStandardItemModel(nb_record, 3);
            page3Model->setHorizontalHeaderLabels(QStringList("Auteur")<<QString("Temps")<<QString("Date"));
            for(int i = 0; i < nb_record; i++){
                page3Model->setItem(i, 0, new QStandardItem(stats->scoresLevel3[i]->auteur));
                page3Model->setItem(i, 1, new QStandardItem(stats->scoresLevel3[i]->time));
                page3Model->setItem(i, 2, new QStandardItem(stats->scoresLevel3[i]->date));
            }

        page3View = new QTableView;
            page3View->setSortingEnabled(true);
            page3View->sortByColumn(1, Qt::AscendingOrder);
            page3View->setModel(page3Model);
            QHeaderView *page3VHeader = page3View->verticalHeader();
                page3VHeader->hide();

    onglets->addTab(page1View, "Facile");
    onglets->addTab(page2View, "Intermédiaire");
    onglets->addTab(page3View, "Expert");

    fermer = new QPushButton("Fermer");

    validLayout = new QHBoxLayout;
        validLayout->setAlignment(Qt::AlignRight);
        validLayout->addWidget(fermer);

    globalLayout = new QVBoxLayout(this);
        globalLayout->addWidget(statsBox);
        globalLayout->addWidget(onglets);
        globalLayout->addLayout(validLayout);

    connect(fermer, SIGNAL(clicked()), this, SLOT(accept()));
}

StatsWindow::~StatsWindow(){

}
