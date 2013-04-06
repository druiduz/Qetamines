#include "header.h"
#include "constantes.h"
#include "Case.h"
#include "MainWindow.h"
#include "AbstractPlateau.h"

Case::Case(){

}

Case::Case(int i, int j, int val, AbstractPlateau *pParent) : QFrame(pParent) {
    setObjectName("case");
    parent = pParent;
    x = i;
    y = j;
    value = val;

    setGeometry(x*TAILLE_CASE+OFFSET_BORDURE_P, y*TAILLE_CASE+OFFSET_BORDURE_P, TAILLE_CASE, TAILLE_CASE);
    setLineWidth(0);
    setMidLineWidth(1);
    setFrameShape(QFrame::WinPanel);
    setFrameShadow(QFrame::Raised);

    label = new QLabel("    ", this);

    hasCase = true;
    flag = false;
    thirdMark = false;
    black = false;

    installEventFilter(this);

}

Case::~Case(){

}

void Case::setValue(int val){
    value = val;
}
int Case::getValue(){
    return value;
}

int Case::getX(){
    return x;
}
int Case::getY(){
    return y;
}

bool Case::getHasCase(){
    return hasCase;
}
void Case::setHasCase(bool b){
    hasCase = b;
}
bool Case::getFlag(){
    return flag;
}
bool Case::getThirdMark(){
    return thirdMark;
}

void Case::setBlack(bool b){
    black = b;
    setStyleSheet("background-color: black;");
}
bool Case::isBlack(){
    return black;
}

void Case::addMine(){
    value++;
}
bool Case::notMine(){
    return (value<9);
}
bool Case::isMine(){
    return (value>=9);
}

/** Slot appelé lors de click de case **/
void Case::deminage(){
    if(!hasCase || black) return;

    hasCase = false;
    thirdMark = false;
    setLineWidth(1);
    setMidLineWidth(0);
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);

    label->setText(showValue(value));

    if(flag && notMine()){
        emit signalCaseFlag(false);
    }
    else{
        emit signalDemine();

        if(value >= 9){
            label->setText(showValue(value, QString("red"), QString("black")));
            emit signalGameOver(false);
        }
        else if(value == 0){
            emit signalDemineAroundCase(x, y);
        }
    }
}

void Case::putFlagOneMine(){
    if(!flag){
        flag = !flag;
        label->setText(showValue());
        emit signalCaseFlag(true);
    }
    else{
        flag = !flag;
        label->setText(showValue());
        emit signalCaseFlag(false);
    }
}
void Case::putFlagOrMarkOneMine(){
    if(!flag && !thirdMark){
        flag = true;
        label->setText(showValue());
        emit signalCaseFlag(true);
    }
    else if(flag && !thirdMark){
        flag = false;
        thirdMark = true;
        label->setText(showValue());
        emit signalCaseFlag(false);
    }
    else if(!flag && thirdMark){
        thirdMark = false;
        label->setText(showValue());
    }
}

/** Permet de gérer les autres event de click que click gauche **/
bool Case::eventFilter(QObject *obj, QEvent *event){
    if(event->type() == QEvent::MouseButtonPress){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        if(!black){
            if(mouseEvent->buttons() == (Qt::LeftButton|Qt::RightButton)){
                if(!hasCase && value > 0){
                    emit signalDemineAroundFlag(x, y);
                }
                return false;
            }
            else if(mouseEvent->button() == Qt::RightButton){ //TODO: Click droit pas assez rapide, on doit attendre un peu avant un second click droit
                if(hasCase){
                    if(MainWindow::mark)
                        putFlagOrMarkOneMine();
                    else
                        putFlagOneMine();
                }
                return false;
            }
            else if(mouseEvent->button() == Qt::LeftButton){
                if(hasCase && !flag)
                    deminage();
                return false;
            }
            else if(mouseEvent->button() == Qt::MidButton){
                if(!hasCase && value > 0){
                    emit signalDemineAroundFlag(x, y);
                }
                return false;
            }
            else
                return QFrame::eventFilter(obj, event);
        }else return QFrame::eventFilter(obj, event);

    }
    return QFrame::eventFilter(obj, event);
}

QString Case::showValue(int val, const QString color, const QString backg_color){
    QString s;
    if(flag) s =  "<strong>&nbsp;&nbsp;!&nbsp;</strong>";
    else if(thirdMark) s = "<strong>&nbsp;?&nbsp;</strong>";
    else{
        if(val > 9){
            s = "<strong style=\"color: "+color+"; background-color: "+backg_color+";\">&nbsp;#&nbsp;&nbsp;</strong>";
        }else{
            switch(val){
                case 0: s = "    ";
                    break;
                case 1: s = "<strong style=\"color: red;\">&nbsp;1&nbsp;</strong>";
                    break;
                case 2: s = "<strong style=\"color: blue;\">&nbsp;2&nbsp;</strong>";
                    break;
                case 3: s = "<strong>&nbsp;3&nbsp;</strong>";
                    break;
                case 4: s = "<strong>&nbsp;4&nbsp;</strong>";
                    break;
                case 5: s = "<strong>&nbsp;5&nbsp;</strong>";
                    break;
                case 6: s = "<strong>&nbsp;6&nbsp;</strong>";
                    break;
                case 7: s = "<strong>&nbsp;7&nbsp;</strong>";
                    break;
                case 8: s = "<strong>&nbsp;8&nbsp;</strong>";
                    break;
                case 9: s = "<strong style=\"color: "+color+"; background-color: "+backg_color+";\">&nbsp;#&nbsp;&nbsp;</strong>";
                    break;
            }
        }
    }
    return s;
}

void Case::afficheMine(){
    if(!hasCase) return;

    hasCase = false;

    setLineWidth(1);
    setMidLineWidth(0);
    /*setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Plain);*/
    setFrameShape(QFrame::Panel);
    setFrameShadow(QFrame::Sunken);
    label->setText(showValue(value));
}

void Case::reset(){
    hasCase = true;
    flag = false;
    thirdMark = false;
    label->setText("   ");

    setLineWidth(0);
    setMidLineWidth(1);
    setFrameShape(QFrame::WinPanel);
    setFrameShadow(QFrame::Raised);
    show();
}

