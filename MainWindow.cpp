#include "header.h"
#include "constantes.h"
#include "MainWindow.h"

#include "Game.h"
#include "CustomGameWindow.h"
#include "OptionsWindow.h"
#include "StatsWindow.h"

bool MainWindow::mark = false;

MainWindow::MainWindow() : QMainWindow() {
    zoneCentral = new QWidget;
    setCentralWidget(zoneCentral);

    level = 1;
    bounds = true;
    MainWindow::mark = false;
    useBlack = false;
    loadConfig();

    _init_var();
    _init_menu();

    /*largeur = 16;
    hauteur = 16;
    nb_mine = 20;*/

    setFixedSize(largeur*TAILLE_CASE+2*OFFSET_BORDURE_P+2*OFFSET_BORDURE, hauteur*TAILLE_CASE+2*OFFSET_BORDURE_P+3*OFFSET_BORDURE+HAUTEUR_INDICATOR+18);

    gameFrame = new Game(zoneCentral, level, largeur, hauteur, nb_mine, useBlack, mark, bounds);
}

MainWindow::~MainWindow(){
    delete(zoneCentral);
}

void MainWindow::_init_var(){
    if(!largeurPerso) largeurPerso = L_DEBUTANT;
    if(!hauteurPerso) hauteurPerso = H_DEBUTANT;
    if(!minesPerso) minesPerso = MINE_DEBUTANT;

    if(level == 2){
        largeur = L_INTER;
        hauteur = H_INTER;
        nb_mine = MINE_INTER;
    }
    else if(level == 3){
        largeur = L_EXPERT;
        hauteur = H_EXPERT;
        nb_mine = MINE_EXPERT;
    }
    else if(level == 4){
        largeur = largeurPerso;
        hauteur = hauteurPerso;
        nb_mine = minesPerso;
    }
    else{
        level = 1;
        largeur = L_DEBUTANT;
        hauteur = H_DEBUTANT;
        nb_mine = MINE_DEBUTANT;
    }
}

void MainWindow::_init_menu(){
    menuJeu = menuBar()->addMenu("&Jeu");
        QAction *actionNouveau = menuJeu->addAction("&Nouveau");
        actionNouveau->setShortcut(QKeySequence(Qt::Key_F2));
    menuJeu->addSeparator();
        actionDebutant = menuJeu->addAction("&Débutant");
        actionInter = menuJeu->addAction("&Intermédiaire");
        actionExpert = menuJeu->addAction("&Expert");
        actionPerso = menuJeu->addAction("&Personnaliser...");

            QActionGroup *checkGroup = new QActionGroup(this);
            actionDebutant->setActionGroup(checkGroup);
            actionInter->setActionGroup(checkGroup);
            actionExpert->setActionGroup(checkGroup);
            actionPerso->setActionGroup(checkGroup);

        actionDebutant->setCheckable(true);
        actionInter->setCheckable(true);
        actionExpert->setCheckable(true);
        actionPerso->setCheckable(true);
        checkLvl();

    menuJeu->addSeparator();
        QAction *actionOptions = menuJeu->addAction("&Options...");
        QAction *actionStats = menuJeu->addAction("&Statistiques...");

    menuJeu->addSeparator();
        QAction *actionQuitter = menuJeu->addAction("&Quitter");

    connect(actionNouveau, SIGNAL(triggered()), this, SLOT(newGame()));
    connect(actionDebutant, SIGNAL(triggered()), this, SLOT(newGameDebutant()));
    connect(actionInter, SIGNAL(triggered()), this, SLOT(newGameInter()));
    connect(actionExpert, SIGNAL(triggered()), this, SLOT(newGameExpert()));
    connect(actionPerso, SIGNAL(triggered()), this, SLOT(newGamePerso()));

    connect(actionOptions, SIGNAL(triggered()), this, SLOT(showOptions()));
    connect(actionStats, SIGNAL(triggered()), this, SLOT(showStats()));

    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    menuAide = menuBar()->addMenu("&Aide");
        QAction *actionAbout = menuAide->addAction("A&bout");

    connect(actionAbout, SIGNAL(triggered()), qApp, SLOT(aboutQt()));


}

void MainWindow::newGame(){
    //QMessageBox::information(NULL, QString("Titre"), QString("arg"));

    closeGame();

    setFixedSize(largeur*TAILLE_CASE+2*OFFSET_BORDURE_P+2*OFFSET_BORDURE, hauteur*TAILLE_CASE+2*OFFSET_BORDURE_P+3*OFFSET_BORDURE+HAUTEUR_INDICATOR+18);

    gameFrame = new Game(zoneCentral, level, largeur, hauteur, nb_mine, bounds, false, useBlack);
    gameFrame->show();

    saveConfig();
}

void MainWindow::closeGame(){
    delete(gameFrame);
}

void MainWindow::newGameDebutant(){
    level = 1;
    largeur = L_DEBUTANT;
    hauteur = H_DEBUTANT;
    nb_mine = MINE_DEBUTANT;
    newGame();
}
void MainWindow::newGameInter(){
    level = 2;
    largeur = L_INTER;
    hauteur = H_INTER;
    nb_mine = MINE_INTER;
    newGame();
}
void MainWindow::newGameExpert(){
    level = 3;
    largeur = L_EXPERT;
    hauteur = H_EXPERT;
    nb_mine = MINE_EXPERT;
    newGame();
}
void MainWindow::newGamePerso(){
    CustomGameWindow *custom = new CustomGameWindow(largeurPerso, hauteurPerso, minesPerso, this);
    if(custom->exec()){
        validInfosPerso(custom);
    }else{
        invalidInfosPerso();
    }
    delete(custom);
}

void MainWindow::validInfosPerso(CustomGameWindow *custom){
    int errors = 0;

    if(custom->getMines() <= 0 || custom->getMines() >= custom->getLargeur()*custom->getHauteur()){
        errors++;
    }
    if(custom->getLargeur() >= MAX_LARGEUR || custom->getHauteur() >= MAX_HAUTEUR){
        errors++;
    }
    if(!errors){
        largeur = custom->getLargeur();
        hauteur = custom->getHauteur();
        nb_mine = custom->getMines();

        largeurPerso = custom->getLargeur();
        hauteurPerso = custom->getHauteur();
        minesPerso = custom->getMines();
        level = 4;
        newGame();
    }
    else{
        checkLvl();
    }
}
void MainWindow::invalidInfosPerso(){
    checkLvl();
}

void MainWindow::showOptions(){
    OptionsWindow *options = new OptionsWindow(bounds, MainWindow::mark, useBlack, this);
    if(options->exec()){
        validInfosOptions(options);
    }
    delete(options);
}
void MainWindow::validInfosOptions(OptionsWindow *options){
    bounds = !(options->getCheckBounds()->isChecked());
    MainWindow::mark = options->getCheckThirdMark()->isChecked();
    useBlack = options->getCheckBlack()->isChecked();
}

void MainWindow::showStats(){
    StatsWindow *stats = new StatsWindow(this, gameFrame->getStats());
    if(stats->exec()){

    }
    delete(stats);
}

void MainWindow::checkLvl(){
    if(level == 1) actionDebutant->setChecked(true);
    else if(level == 2) actionInter->setChecked(true);
    else if(level == 3) actionExpert->setChecked(true);
    else if(level == 4) actionPerso->setChecked(true);
}

void MainWindow::saveConfig(){
    QSettings settings(INI_PATH, QSettings::IniFormat);

    settings.beginGroup("Parametre");
        settings.setValue("bounds", static_cast<int>(bounds));
        settings.setValue("mark", static_cast<int>(MainWindow::mark));
        settings.setValue("level", level);
    settings.endGroup();

    settings.beginGroup("PartiePerso");
        settings.setValue("largeur", largeurPerso);
        settings.setValue("hauteur", hauteurPerso);
        settings.setValue("mines", minesPerso);
    settings.endGroup();
}
void MainWindow::loadConfig(){
    QSettings settings(INI_PATH, QSettings::IniFormat);

    int tmp;
    tmp = static_cast<int>(settings.value("Parametre/bounds","1").toString().toInt());
    bounds = (tmp)?true:false;

    tmp = static_cast<int>(settings.value("Parametre/mark","0").toString().toInt());
    MainWindow::mark = (tmp)?true:false;
    level = static_cast<int>(settings.value("Parametre/level","2").toString().toInt());

    largeurPerso = static_cast<int>(settings.value("PartiePerso/largeurPerso","16").toString().toUInt());
    hauteurPerso = static_cast<int>(settings.value("PartiePerso/hauteurPerso","16").toString().toUInt());
    minesPerso = static_cast<int>(settings.value("PartiePerso/minesPerso","40").toString().toUInt());

}

/** Accesseurs **/
bool MainWindow::getBounds(){
    return bounds;
}
void MainWindow::setBounds(bool b){
    bounds = b;
}
bool MainWindow::getMark(){
    return MainWindow::mark;
}
void MainWindow::setMark(bool m){
    MainWindow::mark = m;
}
int MainWindow::getLevel(){
    return level;
}
void MainWindow::setLevel(int lvl){
    level = lvl;
}
int MainWindow::getLargeur(){
    return largeur;
}
void MainWindow::setLargeur(int l){
    largeur = l;
}
int MainWindow::getHauteur(){
    return hauteur;
}
void MainWindow::setHauteur(int h){
    hauteur = h;
}
int MainWindow::getNb_mine(){
    return nb_mine;
}
void MainWindow::setNb_mine(int nb_m){
    nb_mine = nb_m;
}
int MainWindow::getLargeurPerso(){
    return largeurPerso;
}
void MainWindow::setLargeurPerso(int lP){
    largeurPerso = lP;
}
int MainWindow::getHauteurPerso(){
    return hauteurPerso;
}
void MainWindow::setHauteurPerso(int hP){
    hauteurPerso = hP;
}
int MainWindow::getMinesPerso(){
    return minesPerso;
}
void MainWindow::setMinesPerso(int mP){
    minesPerso = mP;
}

