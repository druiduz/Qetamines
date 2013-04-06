#include "header.h"
#include "PlateauWoBound.h"

#include "Case.h"
#include "DataMap.h"

PlateauWoBound::PlateauWoBound(QWidget *parent, DataMap *d) : AbstractPlateau(parent){
    data = d;

    setLineWidth(2);
    setMidLineWidth(0);
    setFrameShadow(QFrame::Sunken);
    setFrameShape(QFrame::Panel);

    initializePlateau();
}

/** Retourne les reférences des cases aux alentours de (x, y) **/
Case **PlateauWoBound::getCasesAround(int x, int y){
    Case **casesAround = static_cast<Case **>(calloc(8, sizeof(Case *)));

    for(int i = 0; i < 8; i++)  casesAround[i] = NULL;
    int i = 0;

    if(x > 0 && x < data->largeur-1){
        /** Zone central **/
        if(y > 0 && y < data->hauteur-1){
            casesAround[i++] = plateau[x-1][y-1]; /** NO **/
            casesAround[i++] = plateau[x][y-1]; /** N **/
            casesAround[i++] = plateau[x+1][y-1]; /** NE **/
            casesAround[i++] = plateau[x+1][y]; /** E **/
            casesAround[i++] = plateau[x+1][y+1]; /** SE **/
            casesAround[i++] = plateau[x][y+1]; /** S **/
            casesAround[i++] = plateau[x-1][y+1]; /** SO **/
            casesAround[i++] = plateau[x-1][y]; /** O **/
        }
        /*** Wo bounds ***/
        /**Zone Top **/
        else if(y == 0){
            casesAround[i++] = plateau[x-1][data->hauteur-1]; /** NO **/
            casesAround[i++] = plateau[x][data->hauteur-1]; /** N **/
            casesAround[i++] = plateau[x+1][data->hauteur-1]; /** NE **/
            casesAround[i++] = plateau[x+1][y]; /** E **/
            casesAround[i++] = plateau[x+1][y+1]; /** SE **/
            casesAround[i++] = plateau[x][y+1]; /** S **/
            casesAround[i++] = plateau[x-1][y+1]; /** SO **/
            casesAround[i++] = plateau[x-1][y]; /** O **/
        }
        /** Zone Bottom **/
        else if(y == data->hauteur-1){
            casesAround[i++] = plateau[x-1][y-1]; /** NO **/
            casesAround[i++] = plateau[x][y-1]; /** N **/
            casesAround[i++] = plateau[x+1][y-1]; /** NE **/
            casesAround[i++] = plateau[x+1][y]; /** E **/
            casesAround[i++] = plateau[x+1][0]; /** SE **/
            casesAround[i++] = plateau[x][0]; /** S **/
            casesAround[i++] = plateau[x-1][0]; /** SO **/
            casesAround[i++] = plateau[x-1][y]; /** O **/
        }
        /*** End Wo Bounds ***/

    }
    /*** Wo Bounds ***/
    else if(x == 0){
        /** Zone Left **/
        if(y > 0 && y < data->hauteur-1){
            casesAround[i++] = plateau[data->largeur-1][y-1]; /** NO **/
            casesAround[i++] = plateau[x][y-1]; /** N **/
            casesAround[i++] = plateau[x+1][y-1]; /** NE **/
            casesAround[i++] = plateau[x+1][y]; /** E **/
            casesAround[i++] = plateau[x+1][y+1]; /** SE **/
            casesAround[i++] = plateau[x][y+1]; /** S **/
            casesAround[i++] = plateau[data->largeur-1][y+1]; /** SO **/
            casesAround[i++] = plateau[data->largeur-1][y]; /** O **/
        }
        /** Zone Top-Left **/
        else if(y == 0){
            casesAround[i++] = plateau[data->largeur-1][data->hauteur-1]; /** NO **/
            casesAround[i++] = plateau[x][data->hauteur-1]; /** N **/
            casesAround[i++] = plateau[x+1][data->hauteur-1]; /** NE **/
            casesAround[i++] = plateau[x+1][y]; /** E **/
            casesAround[i++] = plateau[x+1][y+1]; /** SE **/
            casesAround[i++] = plateau[x][y+1]; /** S **/
            casesAround[i++] = plateau[data->largeur-1][y+1]; /** SO **/
            casesAround[i++] = plateau[data->largeur-1][y]; /** O **/
        }
        /** Zone Bottom-Left **/
        else if(y == data->hauteur-1){
            casesAround[i++] = plateau[data->largeur-1][y-1]; /** NO **/
            casesAround[i++] = plateau[x][y-1]; /** N **/
            casesAround[i++] = plateau[x+1][y-1]; /** NE **/
            casesAround[i++] = plateau[x+1][y]; /** E **/
            casesAround[i++] = plateau[x+1][0]; /** SE **/
            casesAround[i++] = plateau[x][0]; /** S **/
            casesAround[i++] = plateau[data->largeur-1][0]; /** SO **/
            casesAround[i++] = plateau[data->largeur-1][y]; /** O **/
        }
    }else if(x == data->largeur-1){
        /** Zone Right **/
        if(y > 0 && y < data->hauteur-1){
            casesAround[i++] = plateau[x-1][y-1]; /** NO **/
            casesAround[i++] = plateau[x][y-1]; /** N **/
            casesAround[i++] = plateau[0][y-1]; /** NE **/
            casesAround[i++] = plateau[0][y]; /** E **/
            casesAround[i++] = plateau[0][y+1]; /** SE **/
            casesAround[i++] = plateau[x][y+1]; /** S **/
            casesAround[i++] = plateau[x-1][y+1]; /** SO **/
            casesAround[i++] = plateau[x-1][y]; /** O **/
        }
        /** Zone Top-Right **/
        else if(y == 0){
            casesAround[i++] = plateau[x-1][data->hauteur-1]; /** NO **/
            casesAround[i++] = plateau[x][data->hauteur-1]; /** N **/
            casesAround[i++] = plateau[0][data->hauteur-1]; /** NE **/
            casesAround[i++] = plateau[0][y]; /** E **/
            casesAround[i++] = plateau[0][y+1]; /** SE **/
            casesAround[i++] = plateau[x][y+1]; /** S **/
            casesAround[i++] = plateau[x-1][y+1]; /** SO **/
            casesAround[i++] = plateau[x-1][y]; /** O **/
        }
        /** Zone Bottom-Right **/
        else if(y == data->hauteur-1){
            casesAround[i++] = plateau[x-1][y-1]; /** NO **/
            casesAround[i++] = plateau[x][y-1]; /** N **/
            casesAround[i++] = plateau[0][y-1]; /** NE **/
            casesAround[i++] = plateau[0][y]; /** E **/
            casesAround[i++] = plateau[0][0]; /** SE **/
            casesAround[i++] = plateau[x][0]; /** S **/
            casesAround[i++] = plateau[x-1][0]; /** SO **/
            casesAround[i++] = plateau[x-1][y]; /** O **/
        }
    }

    /*** End Wo Bounds ***/

    return casesAround;
}

