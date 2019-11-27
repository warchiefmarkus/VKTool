#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtQuickWidgets/QtQuickWidgets>

#include <QList>
#include <QDebug>
#include <QListWidget>
#include <QDate>
#include <QDateTime>

#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include <gui/PythonQtScriptingConsole.h>
#include <variableexplorer.h>
#include <graph.h>
#include <usersview.h>
#include <filter.h>
#include <vktool.h>

//!-----------------------TIME PROFILING FUNCTIONS
static QTime start;
static QTime end;
#define PST (start =  QTime::currentTime());
#define PEN(name) {end = QTime::currentTime(); qDebug() << "PROFILING " << name << (float(start.msecsTo(end))/1000) << " s";};
//!-----------------------------------------------




// GROUPLIST
class GroupList : public  QQuickWidget
{
    Q_OBJECT
private:

public:
    explicit GroupList(QWidget *parent = 0, QString user_id = "")
    {
        setSource(QUrl("qrc:/qml/groupList.qml"));
        QObject* root = (QObject*) this->rootObject();
        connect(root, SIGNAL(getMembers(QString,QString,QString)),this, SIGNAL(getMembers(QString, QString, QString)));
        connect(root, SIGNAL(groupsVar(QString,QString,QString)), this, SIGNAL(groupsVar(QString,QString,QString)));
    }
    ~GroupList(){}

signals:
    void getMembers(QString,QString,QString);
    void groupsVar(QString,QString,QString);

public slots:
    void setToken(QString token){
        QObject* root = (QObject*) this->rootObject();
        //QQmlProperty property1(root, "user_id");
        //property1.write(user_id);
        QQmlProperty property(root, "token");
        property.write(token);
    }

};

// MAINWINDOW
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

    QDockWidget *dock;
    QDockWidget *dock1;
    QDockWidget *dock2;
    QDockWidget *dockVariable;

    GroupList* qml;
    Graph* graphView;
    usersView* UsersView;
    VKTool* vkMenu;
    Filter* filter;
    QList<QDockWidget *> dockWidgets;

    QString token;

    QVariant graphList;

    static MainWindow* getInstance();
    static void redirectLog(QtMsgType type, const QMessageLogContext &, const QString & str);

signals:
    void log(QString, QString);

    void setGraphUid(QVariantList);


private slots:
    void pyth();
    void showGroups(QString,QString);
    void getMembers(QString group, QString offset ,QString count);
    void showFilterList(QString sex, QString online, QString country, QString city, QString bdate, QString name);

    void tokenGot(QString tok){
        this->token = tok;
    }

    void showSelected(QString f, QString e){
        qDebug() << f << e << " SEL SLOT";
        UsersView->clear();
        for (int i=f.toInt(); i<=e.toInt(); i++){
            UsersView->addUser(graphList.toList().at(4).toList().at(i).toString(),
                               graphList.toList().at(5).toList().at(i).toString(),
                               graphList.toList().at(0).toList().at(i).toString(),
                               graphList.toList().at(3).toList().at(i).toString(),
                               graphList.toList().at(2).toList().at(i).toString().split(".").at(0));

        }
    }

private:
    void createActions();
    void createStatusBar();
    void createDockWindows();

    static MainWindow* instance;

    QMenu *viewMenu;
};


#endif
