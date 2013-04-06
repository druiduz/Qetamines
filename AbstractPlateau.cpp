#include "header.h"
#include "AbstractPlateau.h"

#include "Case.h"
#include "DataMap.h"

/**TODO  Enlever les cases blacks au compteur dans Game **/

AbstractPlateau::AbstractPlateau(QWidget *parent) : QFrame(parent){
    setObjectName("Plateau");
}

AbstractPlateau::~AbstractPlateau(){
    delete(plateau);
}

void AbstractPlateau::initializePlateau(){
    createPlateau(data->largeur, data->hauteur);
    fillPlateau(data->mines);
}

void AbstractPlateau::createPlateau(int l, int h){
    plateau = static_cast<Case ***>(calloc(data->largeur, sizeof(Case **)));
    for(int i = 0; i < data->largeur; i++){
        plateau[i] = static_cast<Case **>(calloc(data->hauteur, sizeof(Case *)));
    }

    for(int i = 0; i < data->largeur; i++){
        for(int j = 0; j < data->hauteur; j++){
            plateau[i][j] = new Case(i, j, 0, this);
        }
    }
}

void AbstractPlateau::fillPlateau(int nb_m){
    //if(data->useBlackCases) generateBlackCases();
    /**Tableau de position des mines**/
    int *minesX = static_cast<int *>(malloc(nb_m*sizeof(int)));
    int *minesY = static_cast<int *>(malloc(nb_m*sizeof(int)));
    generateMine(nb_m, minesX, minesY);
    generateIndicator(minesX, minesY, nb_m);

    free(minesX);
    free(minesY);
}

/** Genere les Case Noirs **/
void AbstractPlateau::generateBlackCases(){
    int nombreBlacks = data->largeur*data->hauteur/10;
    int index[data->largeur][data->hauteur][2];

    for(int i = 0; i < data->largeur; i++){
        for(int j = 0; j < data->hauteur; j++){
            index[i][j][0] = i;
            index[i][j][1] = j;
        }
    }
    int x = 0;
    int y = 0;

    srand(time(NULL));
    int min = 0;
    int maxX = data->largeur;
    int maxY = data->hauteur;

    for(int i = 0; i < nombreBlacks; i++){
        do{
            x = min+(rand() % (maxX-min));
            y = min+(rand() % (maxY-min));
        }while(x < 0 || y < 0 || index[x][y][0] < 0 || index[x][y][1] < 0);

        plateau[index[x][y][0]][index[x][y][1]]->setBlack(true);
        plateau[index[x][y][0]][index[x][y][1]]->setValue(-1);
        index[x][y][0] = -1;
        index[x][y][1] = -1;
    }

}

/** Determine si une mine peut etre placé sur l'unique sortie d'une case entouré par des cases noirs **/
bool AbstractPlateau::mineIsPossibleWithBlack(int x, int y){
    Case **casesAround = getCasesAround(x, y);
    int nbBlacks = 0;
    int nbMines = 0;
    int nbCaseAround = 0;

    for(int i = 0; i < 8; i++){
        if(casesAround[i] == NULL) break;

        if(casesAround[i]->isBlack()){
            nbBlacks++;
        }
        else if(casesAround[i]->isMine()){
            nbMines++;
        }
        nbCaseAround++;
    }
    delete(casesAround);

    if(nbBlacks+nbMines >= nbCaseAround) return false;
    return true;
}

void AbstractPlateau::generateMine(int nb_m, int *minesX, int *minesY){
    int index[data->largeur][data->hauteur][2];
    for(int i = 0; i < data->largeur; i++){
        for(int j = 0; j < data->hauteur; j++){
            index[i][j][0] = i;
            index[i][j][1] = j;
        }
    }
    int x = 0;
    int y = 0;

    srand(time(NULL));
    int min = 0;
    int maxX = data->largeur;
    int maxY = data->hauteur;

    for(int i = 0; i < nb_m; i++){
        do{
            x = min+(rand() % (maxX-min));
            y = min+(rand() % (maxY-min));
        }while(x < 0 || y < 0
                    || index[x][y][0] < 0 || index[x][y][1] < 0
                    || plateau[index[x][y][0]][index[x][y][1]]->isBlack()
                    || !mineIsPossibleWithBlack(index[x][y][0], index[x][y][1]));

        plateau[index[x][y][0]][index[x][y][1]]->setValue(9);
        minesX[i] = plateau[index[x][y][0]][index[x][y][1]]->getX();
        minesY[i] = plateau[index[x][y][0]][index[x][y][1]]->getY();
        index[x][y][0] = -1;
        index[x][y][1] = -1;

    }
}

void AbstractPlateau::generateIndicator(int *minesX, int *minesY, int nb_mine){
    int x = 0;
    int y = 0;
    Case **casesAround;
    for(int i = 0; i < nb_mine; i++){
        x = minesX[i];
        y = minesY[i];

        casesAround = getCasesAround(x, y);

        for(int j = 0; j < 8; j++){
            if(casesAround[j] == NULL) break;
            casesAround[j]->addMine();
        }
        delete(casesAround);
    }

}

void AbstractPlateau::reset(){
    for(int x = 0; x < data->largeur; x++){
        for(int y = 0; y < data->hauteur; y++){
            plateau[x][y]->reset();
        }
    }
}

void AbstractPlateau::propageDeminage(int x, int y){
    Case **casesAround = getCasesAround(x, y);

    for(int i = 0; i < 8; i++){
        if(casesAround[i] == NULL) break;
        casesAround[i]->deminage();
    }
    delete(casesAround);
}

bool AbstractPlateau::hasFlagAround(int x, int y){
    int nb_flag = 0;

    Case **casesAround = getCasesAround(x, y);

    for(int i = 0; i < 8; i++){
        if(casesAround[i] == NULL) break;
        if(casesAround[i]->getFlag()){
            nb_flag++;
        }
    }
    delete(casesAround);

    return (nb_flag == plateau[x][y]->getValue());
}

void AbstractPlateau::demineAroundFlag(int x, int y){
    if(!hasFlagAround(x, y)) return;

    Case **casesAround = getCasesAround(x, y);

    for(int i = 0; i < 8; i++){
        if(casesAround[i] == NULL) break;
        if(!casesAround[i]->getFlag()){
            casesAround[i]->deminage();
        }
    }
    delete(casesAround);
}

int AbstractPlateau::getLargeur(){
    return data->largeur;
}
void AbstractPlateau::setLargeur(int l){
    data->largeur = l;
}
int AbstractPlateau::getHauteur(){
    return data->hauteur;
}
void AbstractPlateau::setHauteur(int h){
    data->hauteur = h;
}
void AbstractPlateau::setNb_mine(int nb_m){
    data->mines = nb_m;
}
Case *AbstractPlateau::getCase(int x, int y){
    return plateau[x][y];
}

