#ifndef _PLATEAUWITHBOUND_H_
#define _PLATEAUWITHBOUND_H_

#include <QtGui>

#include "AbstractPlateau.h"

class PlateauWithBound : public AbstractPlateau{

    Q_OBJECT;

    public:
        PlateauWithBound(QWidget *parent, DataMap *d);

        Case **getCasesAround(int x, int y);

};

#endif
