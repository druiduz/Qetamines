#include "header.h"
#include "MainWindow.h"

int main(int argc, char **argv){

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QApplication app(argc, argv);

    /*QTranslator translator;
    translator.load("StatsWindow_en");
    app.installTranslator(&translator);*/

    MainWindow fenetre;

    QFile file("E:/Codage/Qetamines/style.css");
    if ( file.open(QFile::ReadOnly) ){
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
    } else {
        QMessageBox::warning(NULL, ">", "Impossible d'importer le css");
    }

    fenetre.show();

    return app.exec();
}
