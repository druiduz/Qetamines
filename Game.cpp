#include "header.h"
#include "constantes.h"
#include "Game.h"

#include "Statistiques.h"
#include "GameIndicator.h"
#include "AbstractPlateau.h"
#include "PlateauWithBound.h"
#include "PlateauWoBound.h"
#include "Case.h"
#include "DataMap.h"

Game::Game(QWidget *wParent, int wLevel, int wLargeur, int wHauteur, int wMines, bool useThirdMark, bool useBC, bool useBounds) : QFrame(wParent){
    windowParent = static_cast<MainWindow *>(wParent);

    data = new DataMap(wLevel, wLargeur, wHauteur, wMines, useThirdMark, useBC, useBounds);

    nbCaseRest = (data->largeur*data->hauteur)-data->mines;
    nbMineRest = data->mines;

    idFirstCase = static_cast<int *>(calloc(2, sizeof(int)));
    idFirstCase[0] = -1;
    idFirstCase[1] = -1;

    stats = new Statistiques;

    loadSave();

    setGeometry(0, 0, data->largeur*TAILLE_CASE+2*OFFSET_BORDURE_P+2*OFFSET_BORDURE, data->hauteur*TAILLE_CASE+2*OFFSET_BORDURE_P+3*OFFSET_BORDURE+HAUTEUR_INDICATOR);
    setLineWidth(3);
    setMidLineWidth(0);
    setFrameShadow(QFrame::Raised);
    setFrameShape(QFrame::Panel);

    indicator = new GameIndicator(nbMineRest, nbCaseRest, this);
        indicator->setGeometry(OFFSET_BORDURE, OFFSET_BORDURE, data->largeur*TAILLE_CASE+2*OFFSET_BORDURE_P, HAUTEUR_INDICATOR);
        connect(indicator->getRetry(), SIGNAL(clicked()), SLOT(resetGame()));

    if(data->useBounds){
        p = new PlateauWithBound(this, data);
    }else{
        p = new PlateauWoBound(this, data);
    }
       p->setGeometry(OFFSET_BORDURE, 2*OFFSET_BORDURE+HAUTEUR_INDICATOR, data->largeur*TAILLE_CASE+2*OFFSET_BORDURE_P, data->hauteur*TAILLE_CASE+2*OFFSET_BORDURE_P);


    connexions();
    startGame();

}

Game::~Game(){
    delete(idFirstCase);
    delete(stats);
}

void Game::saveSave(){
    QSettings settings("./score.save", QSettings::IniFormat);

    settings.beginGroup("general");
        settings.setValue("nbPartie", QString::number(stats->getNbPartie()));
        settings.setValue("nbPartieWin", QString::number(stats->getNbPartieWin()));
        settings.setValue("nbPartieLose", QString::number(stats->getNbPartieLose()));
    settings.endGroup();

    settings.beginWriteArray("records_facile");
    for(int i = 0; i < 5; i++){
        settings.setArrayIndex(i);
        settings.setValue("auteur", stats->scoresLevel1[i]->auteur);
        settings.setValue("time", stats->scoresLevel1[i]->time);
        settings.setValue("date", stats->scoresLevel1[i]->date);
    }
    settings.endArray();

    settings.beginWriteArray("records_intermediaire");
    for(int i = 0; i < 5; i++){
        settings.setArrayIndex(i);
        settings.setValue("auteur", stats->scoresLevel2[i]->auteur);
        settings.setValue("time", stats->scoresLevel2[i]->time);
        settings.setValue("date", stats->scoresLevel2[i]->date);
    }
    settings.endArray();

    settings.beginWriteArray("records_expert");
    for(int i = 0; i < 5; i++){
        settings.setArrayIndex(i);
        settings.setValue("auteur", stats->scoresLevel3[i]->auteur);
        settings.setValue("time", stats->scoresLevel3[i]->time);
        settings.setValue("date", stats->scoresLevel3[i]->date);
    }
    settings.endArray();

}
void Game::loadSave(){
    QSettings settings("./score.save", QSettings::IniFormat);
    QString a;
    QString t;
    QString d;


    QVariant nbPartietmp = settings.value("general/nbPartie", "0");
    stats->setNbPartie(nbPartietmp.toInt());
    QVariant nbPartieWintmp = settings.value("general/nbPartieWin", "0");
    stats->setNbPartieWin(nbPartieWintmp.toInt());
    QVariant nbPartieLosetmp = settings.value("general/nbPartieLose", "0");
    stats->setNbPartieLose(nbPartieLosetmp.toInt());

    int sizeFacile = settings.beginReadArray("records_facile");
    for (int i = 0; i < sizeFacile; i++) {
        settings.setArrayIndex(i);
        a = settings.value("auteur").toString();
        t = settings.value("time").toString();
        d = settings.value("date").toString();
        stats->insertScore(i, 1, t, a, d);
    }
    settings.endArray();

    int sizeInter = settings.beginReadArray("records_intermediaire");
    for (int i = 0; i < sizeInter; i++) {
        settings.setArrayIndex(i);
        a = settings.value("auteur").toString();
        t = settings.value("time").toString();
        d = settings.value("date").toString();
        stats->insertScore(i, 2, t, a, d);
    }
    settings.endArray();

    int sizeDifficile = settings.beginReadArray("records_expert");
    for (int i = 0; i < sizeDifficile; i++) {
        settings.setArrayIndex(i);
        a = settings.value("auteur").toString();
        t = settings.value("time").toString();
        d = settings.value("date").toString();
        stats->insertScore(i, 3, t, a, d);
    }
    settings.endArray();
}


void Game::connexions(){
    for(int i = 0; i < data->largeur; i++){
        for(int j = 0; j < data->hauteur; j++){
            connect(p->getCase(i, j), SIGNAL(signalDemine()), SLOT(slotDemine()));
            connect(p->getCase(i, j), SIGNAL(signalDemineAroundCase(int, int)), SLOT(slotPropageDeminage(int, int)));
            connect(p->getCase(i, j), SIGNAL(signalDemineAroundFlag(int, int)), SLOT(slotDemineAroundFlag(int, int)));
            connect(p->getCase(i, j), SIGNAL(signalCaseFlag(bool)), SLOT(slotFlag(bool)));
            connect(p->getCase(i, j), SIGNAL(signalGameOver(bool)), SLOT(slotGameOver(bool)));
        }
    }
}

void Game::startGame(){
    autoFirstDeminage(idFirstCase[0], idFirstCase[1]);

    indicator->reset();
    indicator->startChrono();
}

void Game::autoFirstDeminage(int idX, int idY){
    int x;
    int y;
    if(idX >= 0 && idY >= 0){
        x = idX;
        y = idY;
    }else{
        x = -1;
        y = -1;
        srand(time(NULL));
        int min = 0;
        int maxX = data->largeur;
        int maxY = data->hauteur;

        do{
            x = min+(rand() % (maxX-min));
            y = min+(rand() % (maxY-min));
        }while(x < 0 || y < 0 || p->getCase(x, y)->getValue() != 0 || p->getCase(x, y)->isBlack());
    }
    p->getCase(x, y)->deminage();

    idFirstCase[0] = x;
    idFirstCase[1] = y;

}

void Game::slotDemine(){
    nbCaseRest--;
    indicator->changeCaseRestante(true);

    if(nbCaseRest <= 0){
        slotGameOver(true);
    }
}

void Game::slotPropageDeminage(int x, int y){
    p->propageDeminage(x, y);
}

void Game::slotDemineAroundFlag(int x, int y){
    p->demineAroundFlag(x, y);
}

void Game::slotFlag(bool retrait){
    if(retrait){
        nbMineRest--;
    }
    else{
        nbMineRest++;
    }

    indicator->changeCaseRestante(retrait);
    indicator->changeMine(retrait);
}

void Game::resetGame(){
    slotGameOver(false);
    nbCaseRest = data->largeur*data->hauteur-data->mines;
    nbMineRest = data->mines;
    p->reset();
    indicator->reset();
    p->show();
    startGame();
}

void Game::finishGame(bool win){
    for(int i = 0; i < data->largeur; i++){
        for(int j = 0; j < data->hauteur; j++){
            if(p->getCase(i, j)->getHasCase()){
                if(!p->getCase(i, j)->getFlag() && p->getCase(i, j)->isMine()){
                    p->getCase(i, j)->afficheMine();
                }

                p->getCase(i, j)->setHasCase(false);
            }
        }
    }
}

void Game::slotGameOver(bool win){
    indicator->stopChrono();
    finishGame(win);

    stats->addPartie();
    checkRecord(win);
    saveSave();
}

void Game::checkRecord(int win){
    QString timeChrono = indicator->getHorloge()->toString("mm:ss:zzz");
    timeChrono.resize(timeChrono.length()-2);

    stats->finishedGame(data->level, timeChrono, win);
}

Statistiques *Game::getStats(){
    return stats;
}

DataMap *Game::getData(){
    return data;
}
