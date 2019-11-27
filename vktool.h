#ifndef VKTOOL_H
#define VKTOOL_H
#include <QtQuickWidgets/QtQuickWidgets>
#include <QSettings>
#include <connection/apimethodexecutor.h>
#include <QQmlNetworkAccessManagerFactory>
#include <QQmlContext>
#include <QQmlProperty>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QEventLoop>
#include <QTimer>
#include <QNetworkRequest>
#include <vkauthenticator/vkauthenticator.h>
#define PARAMS QMap<QString,QString>

#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#include <gui/PythonQtScriptingConsole.h>
// VKTOOL VKMENU
class VKTool : public  QQuickWidget
{
    Q_OBJECT
private:
     QObject * menu;
     QSettings * settings;

public:
     explicit VKTool(QWidget *parent = 0);
     ~VKTool();

     ApiMethodExecutor* vkApi;
     VkAuthenticator * vkauth;

     void LoadIni(QString path);
     void WriteConfig(QString name, QVariant value);
     QVariant ReadConfig(QString name);


     QVariant numDivTo25K(int number);

     QVariant getMembers(QString group, QString offset, QString count);

     QString Token;
     QString Expires;
     QString renameFolder;

     //----------------GLOBAL SETTINGS
     QString photoSize;
     QString loginedUserId;
     QString loginedPhotoMax;
     QString loginedUserName;
     QString loginedFollowers;
     QString loginedSubscriptions;
     QString loginedFriends;

     //--------------MSG
     QMessageBox msgBox;




     //------------Python
     PythonQtObjectPtr mainModule;
     PythonQtObjectPtr runFunc;


     QVariant getFiltered(QString sex, QString online, QString country, QString city, QString bdate, QString name);



signals:
     void haveToken();
     void showGroups(QString, QString);
     void tokenGot(QString);

public slots:
     void login(QString login, QString password);
     void getAccount();

     void tokenRecived(QString tok);
     void showMSG(QString msg){
         msgBox.setText(msg);
         msgBox.exec();
     }

};

#endif // VKTOOL_H
