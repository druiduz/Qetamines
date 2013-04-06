#include "header.h"
#include "NewScoreWindow.h"

NewScoreWindow::NewScoreWindow(QWidget *wParent, QString time) : QDialog(wParent){

    score = new QLabel(QString("Nouveau record : ").append(time));

    auteur = new QLineEdit("Anonymous");
        auteur->setInputMask("XXXXXXXXXXXXXXX");
        auteur->selectAll();

    validate = new QPushButton("OK");
    validateLayout = new QHBoxLayout;
        validateLayout->setAlignment(Qt::AlignRight);
        validateLayout->addWidget(validate);

    globalLayout = new QVBoxLayout(this);
        globalLayout->addWidget(score);
        globalLayout->addWidget(auteur);
        globalLayout->addLayout(validateLayout);

    connect(validate, SIGNAL(clicked()), this, SLOT(reject()));
}

NewScoreWindow::~NewScoreWindow(){

}

QLineEdit *NewScoreWindow::getAuteur(){
    return auteur;
}
