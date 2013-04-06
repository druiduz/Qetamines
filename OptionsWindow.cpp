#include "header.h"
#include "OptionsWindow.h"

OptionsWindow::OptionsWindow(bool bounds, bool mark, bool useBlack, QWidget *parent) : QDialog(parent){
    setWindowTitle("Options");

    checkBounds = new QCheckBox("Utiliser les bords communiquant");
        checkBounds->setChecked(!bounds);
    checkThirdMark = new QCheckBox("Autoriser les marques \'?\'");
        checkThirdMark->setChecked(mark);
    checkBlack = new QCheckBox("Jouer avec certaines cases noires ?");
        checkBlack->setChecked(useBlack);

    /**Actions buttons**/
    valider = new QPushButton("Valider");
    annuler = new QPushButton("Annuler");

    validLayout = new QHBoxLayout;
        validLayout->setAlignment(Qt::AlignRight);
        validLayout->addWidget(valider);
        validLayout->addWidget(annuler);
    /**---------------**/

    globalLayout = new QVBoxLayout(this);
        globalLayout->addWidget(checkBounds);
        globalLayout->addWidget(checkThirdMark);
        globalLayout->addWidget(checkBlack);
        globalLayout->addLayout(validLayout);

    connect(valider, SIGNAL(clicked()), this, SLOT(accept()));
    connect(annuler, SIGNAL(clicked()), this, SLOT(reject()));
}

OptionsWindow::~OptionsWindow(){

}

QCheckBox *OptionsWindow::getCheckBounds(){
    return checkBounds;
}
QCheckBox *OptionsWindow::getCheckThirdMark(){
    return checkThirdMark;
}
QCheckBox *OptionsWindow::getCheckBlack(){
    return checkBlack;
}
