#include "header.h"
#include "Statistiques.h"
#include "NewScoreWindow.h"

Statistiques::Statistiques(){
    nbPartie = 0;
    nbPartieWin = 0;
    nbPartieLose = 0;

    scoresLevel1 = static_cast<struct Score **>(calloc(NB_RECORD_PER_LVL, sizeof(struct Score **)));
    scoresLevel2 = static_cast<struct Score **>(calloc(NB_RECORD_PER_LVL, sizeof(struct Score **)));
    scoresLevel3 = static_cast<struct Score **>(calloc(NB_RECORD_PER_LVL, sizeof(struct Score **)));

    _init_score();
}

Statistiques::~Statistiques(){
    for(int i = 0; i < NB_RECORD_PER_LVL; i++){
        delete(scoresLevel1[i]);
        delete(scoresLevel2[i]);
        delete(scoresLevel3[i]);
    }
    delete(scoresLevel1);
    delete(scoresLevel2);
    delete(scoresLevel3);
}

void Statistiques::_init_score(){
    for(int i = 0; i < NB_RECORD_PER_LVL; i++){
        scoresLevel1[i] = new Score();
        scoresLevel2[i] = new Score();
        scoresLevel3[i] = new Score();
    }
}

void Statistiques::finishedGame(int level, QString time, bool win){
    if(win){
        QString auteur;
        QString dateNow = QDate::currentDate().toString("dd/MM/yyyy");
        if(level == 1){
            for(int i = 0; i < NB_RECORD_PER_LVL; i++){
                if(scoresLevel1[i]->time > time || scoresLevel1[i]->time == QString("00:00:0")){
                    /** Pop Up affiche record et demande speudo **/
                    NewScoreWindow newScorePopup(NULL, time);
                    if(!newScorePopup.exec()){
                        auteur = newScorePopup.getAuteur()->text();
                    }
                    insertScore(i, level, time, auteur, dateNow);
                    nbPartieWin++;
                    break;
                }
            }
        }
        else if(level == 2){
            for(int i = 0; i < NB_RECORD_PER_LVL; i++){
                if(scoresLevel2[i]->time > time || scoresLevel2[i]->time == QString("00:00:0")){
                    /** Pop Up affiche record et demande speudo **/
                    NewScoreWindow newScorePopup(NULL, time);
                    if(!newScorePopup.exec()){
                        auteur = newScorePopup.getAuteur()->text();
                    }
                    insertScore(i, level, time, auteur, dateNow);
                    nbPartieWin++;
                    break;
                }
            }
        }
        else if(level == 3){
            for(int i = 0; i < NB_RECORD_PER_LVL; i++){
                if(scoresLevel3[i]->time > time || scoresLevel3[i]->time == QString("00:00:0")){
                    /** Pop Up affiche record et demande speudo **/
                    NewScoreWindow newScorePopup(NULL, time);
                    if(!newScorePopup.exec()){
                        auteur = newScorePopup.getAuteur()->text();
                    }
                    insertScore(i, level, time, auteur, dateNow);
                    nbPartieWin++;
                    break;
                }
            }
        }
    }
    else{
        nbPartieLose++;
    }
}

void Statistiques::insertScore(int i, int level, QString t, QString a, QString d){
    if(level == 1){
        if(scoresLevel1[i]->time != "00:00:0"){
            decaleScore(i, level);
        }
        scoresLevel1[i]->auteur = a;
        scoresLevel1[i]->time = t;
        scoresLevel1[i]->date = d;
    }
    else if(level == 2){
        if(scoresLevel2[i]->time != "00:00:0"){
            //QMessageBox::information(NULL, QString("Titre"), QString("arg"));
            decaleScore(i, level);
        }
        scoresLevel2[i]->auteur = a;
        scoresLevel2[i]->time = t;
        scoresLevel2[i]->date = d;
    }
    else if(level == 3){
        if(scoresLevel3[i]->time != "00:00:0"){
            decaleScore(i, level);
        }
        scoresLevel3[i]->auteur = a;
        scoresLevel3[i]->time = t;
        scoresLevel3[i]->date = d;
    }

}

void Statistiques::decaleScore(int i, int level){

    for(int j = NB_RECORD_PER_LVL-1; j > i; j--){
        if(level == 1){
            scoresLevel1[j]->auteur = scoresLevel1[j-1]->auteur;
            scoresLevel1[j]->time = scoresLevel1[j-1]->time;
            scoresLevel1[j]->date = scoresLevel1[j-1]->date;
        }
        else if(level == 2){
            scoresLevel2[j]->auteur = scoresLevel2[j-1]->auteur;
            scoresLevel2[j]->time = scoresLevel2[j-1]->time;
            scoresLevel2[j]->date = scoresLevel2[j-1]->date;
        }
        else if(level == 3){
            scoresLevel3[j]->auteur = scoresLevel3[j-1]->auteur;
            scoresLevel3[j]->time = scoresLevel3[j-1]->time;
            scoresLevel3[j]->date = scoresLevel3[j-1]->date;
        }
        j--;
    }
}

void Statistiques::addPartie(){
    nbPartie++;
}
void Statistiques::setNbPartie(int nb){
    nbPartie = nb;
}
int Statistiques::getNbPartie(){
    return nbPartie;
}
void Statistiques::setNbPartieWin(int nb){
    nbPartieWin = nb;
}
int Statistiques::getNbPartieWin(){
    return nbPartieWin;
}
void Statistiques::setNbPartieLose(int nb){
    nbPartieLose = nb;
}
int Statistiques::getNbPartieLose(){
    return nbPartieLose;
}
float Statistiques::getPourcentWin(){
    return (nbPartieWin*100)/nbPartie;
}

