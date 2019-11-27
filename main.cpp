#include <QApplication>
#include "mainwindow.h"
#include <QtGlobal>
#include <QtDebug>


int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    Q_INIT_RESOURCE(dockwidgets); 
    MainWindow* mainWin = MainWindow::getInstance();
    //qInstallMessageHandler(MainWindow::getInstance()->redirectLog);
    //MainWindow::getInstance()->connect(MainWindow::getInstance(),SIGNAL(log(QString,QString)),  MainWindow::getInstance()->qmlConsole, SIGNAL(log(QString,QString)));
    mainWin->show();

    return app.exec();
}
