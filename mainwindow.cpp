#include <QtWidgets>
#include "mainwindow.h"
#include <QTime>

MainWindow* MainWindow::instance = 0;
MainWindow* MainWindow::getInstance(){
    if(instance==0){
        instance = new MainWindow;
    }
    return instance;
}

MainWindow::MainWindow() 
{
    createActions();
    createStatusBar();
    createDockWindows();

    setWindowTitle(tr("VKTool"));
    setUnifiedTitleAndToolBarOnMac(true);
    setGeometry(300,80,1300,900);
    setDockNestingEnabled(true);

}

void MainWindow::redirectLog(QtMsgType type, const QMessageLogContext &, const QString & str)
{
       switch (type) {
       case QtDebugMsg:
           MainWindow::getInstance()->log(QString("MSG: %1").arg(str),"black");
           break;
       case QtWarningMsg:
           MainWindow::getInstance()->log(QString("WRN: %1").arg(str), "green");
       break;
       case QtCriticalMsg:
           MainWindow::getInstance()->log(QString("CRT: %1").arg(str), "blue");
       break;
       case QtFatalMsg:
           MainWindow::getInstance()->log(QString("FTL: %1").arg(str), "red");
       break;
       }
}

// ACTIONS
void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *fileToolBar = addToolBar(tr("File"));

    QAction *quitAct = fileMenu->addAction(tr("&Quit"), this, &QWidget::close);
    quitAct->setShortcuts(QKeySequence::Quit);
    quitAct->setStatusTip(tr("Quit the application"));


    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

    viewMenu = menuBar()->addMenu(tr("&View"));
    menuBar()->addSeparator();
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    QAction *python = helpMenu->addAction(tr("&Python"), this, &MainWindow::pyth);
}

void MainWindow::getMembers(QString group, QString offset ,QString count)
{    
    PST;
    //graphList = vkMenu->getMembers(group,offset,count);
    vkMenu->getMembers(group,offset,count);
    PEN("Graph");


}

void MainWindow::showFilterList(QString sex, QString online, QString country, QString city, QString bdate, QString name)
{
    qDebug() << " SHOW FILTERLIST SLOT EMITED " << sex << online << country << city << bdate << name;
    graphList = vkMenu->getFiltered(sex, online, country, city, bdate, name);
    qDebug() << " DEBUG" << graphList.toList().size();

    //qDebug() << " GRAPH LIST " << graphList.toList().at(2).toList();
    QVariantList st( graphList.toList().at(2).toList());
    PST;
    //graphView->dataSource.generateData(1000000);
    graphView->showUids(st);
    //setGraphUid(st);
    PEN("setGraphUid");
}

void MainWindow::pyth()
{

}

// GROUPS DOCK
void MainWindow::showGroups(QString uid, QString token)
{
    this->token = token;
    UsersView->setToken(token);

    dock2 = new QDockWidget(tr("Groups"), this);
    splitDockWidget(dock1, dock2, Qt::Horizontal);
    qml = new GroupList(dock2,uid);
    qml->setToken(token);
    qml->setMinimumHeight(300);
    connect(qml, SIGNAL(getMembers(QString,QString,QString)),this, SLOT(getMembers(QString,QString,QString)));

    qml->setResizeMode(QQuickWidget::SizeRootObjectToView);
    dock2->setWidget(qml);
    viewMenu->addAction(dock2->toggleViewAction());

    // filter
    QDockWidget * dock1S = new QDockWidget(tr("Filter"),this);
    dock1S->setMinimumHeight(500);
    filter = new Filter(dock1S);
    connect(filter, SIGNAL(selected(QString, QString, QString, QString, QString, QString)),this, SLOT(showFilterList(QString, QString, QString, QString, QString, QString)));
    filter->setResizeMode(QQuickWidget::SizeRootObjectToView);
    dock1S->setWidget(filter);
    splitDockWidget(dock2, dock1S, Qt::Vertical);
    viewMenu->addAction(dock1S->toggleViewAction());
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::createDockWindows()
{
    // VK Menu
    dock1 = new QDockWidget(tr("VK Menu"),this);
    dock1->setMinimumHeight(300);
    vkMenu  = new VKTool(dock1);
    connect(vkMenu, SIGNAL(showGroups(QString,QString)),this, SLOT(showGroups(QString,QString)));
    connect(vkMenu, SIGNAL(tokenGot(QString)), this, SLOT(tokenGot(QString)));
    vkMenu->setResizeMode(QQuickWidget::SizeRootObjectToView);
    dock1->setWidget(vkMenu);
    addDockWidget(Qt::LeftDockWidgetArea, dock1);
    viewMenu->addAction(dock1->toggleViewAction());


    // Graph
    dock = new QDockWidget(tr("Graph"),this);
    graphView = new Graph(dock);
    graphView->setMinimumHeight(300);
    connect(graphView, SIGNAL(selected(QString,QString)), this, SLOT(showSelected(QString,QString)));
    connect(this, SIGNAL(setGraphUid(QVariantList)), graphView, SLOT(setUids(QVariantList)));
    graphView->setResizeMode(QQuickWidget::SizeRootObjectToView);
    dock->setWidget(graphView);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    // UserView
    dock = new QDockWidget(tr("Users"),this);
    UsersView = new usersView(dock);
    UsersView->setResizeMode(QQuickWidget::SizeRootObjectToView);
    dock->setWidget(UsersView);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

//    dockWidgets = findChildren<QDockWidget *>();
//    this->resizeDocks(dockWidgets, {180 , 200, 200, 100}, Qt::Horizontal);
//    this->resizeDocks(dockWidgets, {180 , 200, 200, 100}, Qt::Vertical);
}
