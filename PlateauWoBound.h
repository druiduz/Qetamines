#ifndef _PLATEAUWOBOUND_H_
#define _PLATEAUWOBOUND_H_

#include <QtGui>

#include "AbstractPlateau.h"

class PlateauWoBound : public AbstractPlateau{

    Q_OBJECT;

    public:
        PlateauWoBound(QWidget *parent, DataMap *d);

        Case **getCasesAround(int x, int y);

};

#endif
