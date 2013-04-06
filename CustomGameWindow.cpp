#include "header.h"
#include "CustomGameWindow.h"

CustomGameWindow::CustomGameWindow(int lPerso, int hPerso, int mPerso, QWidget *parent) : QDialog(parent){
    setWindowTitle("Partie personnalisée");

    largeurPerso = lPerso;
    hauteurPerso = hPerso;
    minesPerso = mPerso;

    /**Formulaire**/
    largeurEdit = new QLineEdit(QString::number(largeurPerso));
        largeurEdit->setInputMask("999");
        largeurEdit->selectAll();
    hauteurEdit = new QLineEdit(QString::number(hauteurPerso));
        hauteurEdit->setInputMask("999");
        hauteurEdit->selectAll();
    minesEdit = new QLineEdit(QString::number(minesPerso));
        minesEdit->setInputMask("999");
        minesEdit->selectAll();

    fLayout = new QFormLayout();
        fLayout->addRow("Largeur : ", largeurEdit);
        fLayout->addRow("hauteur : ", hauteurEdit);
        fLayout->addRow("Mines : ", minesEdit);

    groupEdit = new QGroupBox("Personnalisation du la grille");
    groupEdit->setLayout(fLayout);
    /**----------**/

    /**Actions buttons**/
    valider = new QPushButton("Valider");
    annuler = new QPushButton("Annuler");

    validLayout = new QHBoxLayout;
        validLayout->setAlignment(Qt::AlignRight);
        validLayout->addWidget(valider);
        validLayout->addWidget(annuler);
    /**---------------**/

    globalLayout = new QVBoxLayout(this);
        globalLayout->addWidget(groupEdit);
        globalLayout->addLayout(validLayout);

    connect(valider, SIGNAL(clicked()), this, SLOT(accept()));
    connect(annuler, SIGNAL(clicked()), this, SLOT(reject()));

}

CustomGameWindow::~CustomGameWindow(){

}


int CustomGameWindow::getLargeur(){
    return (int)largeurEdit->text().toUInt();
}

int CustomGameWindow::getHauteur(){
    return (int)hauteurEdit->text().toUInt();
}

int CustomGameWindow::getMines(){
    return (int)minesEdit->text().toUInt();
}
