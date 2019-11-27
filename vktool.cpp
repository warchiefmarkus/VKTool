#include "vktool.h"

//-- NAM factory with NAM with caching for QML
class MyNetworkAccessManagerFactory : public QQmlNetworkAccessManagerFactory
{
public:
    virtual QNetworkAccessManager *create(QObject *parent);
};

QNetworkAccessManager *MyNetworkAccessManagerFactory::create(QObject *parent)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager(parent);
    QNetworkDiskCache* cache = new QNetworkDiskCache(parent);
    cache->setMaximumCacheSize(500*1024*1024); // 500 Mb
    cache->setCacheDirectory("cacheDir");
    nam->setCache(cache);
    return nam;
}

// define the singleton provider function (callback) for Export and Share global properties in QML
static QJSValue exportQML(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    QJSValue exportQML = scriptEngine->newObject();
    return exportQML;
}

VKTool::VKTool(QWidget *parent) : QQuickWidget(parent)
{
    qmlRegisterSingletonType("VKTool", 1, 0, "Shared", exportQML);
    setSource(QUrl("qrc:/qml/menu.qml"));
    // SET CACHED NAM TO QMLENGINE TO
    MyNetworkAccessManagerFactory* namFactory = new MyNetworkAccessManagerFactory();
    this->engine()->setNetworkAccessManagerFactory(namFactory);
    menu = (QObject*) this->rootObject();

    connect(menu, SIGNAL(showGroups(QString,QString)),this, SIGNAL(showGroups(QString,QString)));

    vkApi = new ApiMethodExecutor();
    vkauth = new VkAuthenticator("5494949","notify,friends,photos,audio,video,docs,notes,pages,status,wall,groups,messages,offline");

    connect(vkauth, SIGNAL(tokenReceived(QString)), this, SLOT(tokenRecived(QString)));
    connect(vkauth, SIGNAL(error(QString)), this, SLOT(showMSG(QString)));

    // LOAD CONFIG
    LoadIni("config.ini");
    // Read folder with Kate Mobile tracks to rename
    if ( settings->contains("renameFolder")){
          renameFolder = ReadConfig("renameFolder").toString();
    }else{
        renameFolder = "RenamedTracks";
    }

    // Read token
    if( settings->contains("token"))
    {
        qDebug() << " have token ";
        if(ReadConfig("expires").toInt()==0){ // its a unlimit token
            Token = ReadConfig("token").toString();
            vkApi->setToken(Token);
            tokenGot(Token);
            QQmlProperty property(menu, "token");
            property.write(Token);

            getAccount();
            QQmlProperty property1(menu, "user_id");
            property1.write(loginedUserId);
            //get_profile();
        }
        else if(ReadConfig("expDate").toDate()<=QDate::currentDate()){  // if no doesnt it token expire
            Token = ReadConfig("token").toString();
            vkApi->setToken(Token);
            tokenGot(Token);

            getAccount();
            QQmlProperty property1(menu, "user_id");
            property1.write(loginedUserId);
        }
    }else{  // if havent token login
        qDebug() << " need login ";
        //QMetaObject::invokeMethod(wallObj, "showLogin");
        //! DIRECT CONNECT BUT WITH OTHER APP ID
        //login("380********","parol");
        //!HOOK LOGIN WITHOUT FORMS BUT NOT DIRECT CONNECT BUT WITH OUR APP ID
        vkauth->authenticate();
    }


    PythonQt::init(PythonQt::RedirectStdOut);
    PythonQt_QtAll::init();
    mainModule = PythonQt::self()->getMainModule();
    PythonQtScriptingConsole(NULL, mainModule);
    mainModule.evalScript("import sys\n");
    mainModule.evalScript(QString("sys.path.append('%1')\n").arg(QDir::currentPath().append("/Scripts")));
    mainModule.evalScript(QString("sys.path.append('%1')\n").arg("C:/Users/user/Desktop/WinPython-32bit-3.4.3.7/python-3.4.3/Lib/site-packages"));
    mainModule.evalScript("import main\n");
    runFunc = mainModule.evalScript("main.DataMain()\n", Py_eval_input);


//    // Read logined info
//    if(settings->contains("logined")){
//        if(ReadConfig("logined").toString()=="true"){
//            qDebug() << " we logined ";
//            loginedUserId =  ReadConfig("userId").toString();
//            QQmlProperty property1(menu, "user_id");
//            property1.write(loginedUserId);
//        }
//        // else get login
//        else{
//            getAccount();
//            QQmlProperty property1(menu, "user_id");
//            property1.write(loginedUserId);
//        }
//    }else{
//        getAccount();
//        QQmlProperty property1(menu, "user_id");
//        property1.write(loginedUserId);
//    }
    //this->setMaximumWidth(200);
}

VKTool::~VKTool()
{
}

void VKTool::LoadIni(QString path)
{
    settings = new QSettings(path, QSettings::IniFormat);
}

void VKTool::WriteConfig(QString name, QVariant value)
{
    settings->setValue(name, value);
}

QVariant VKTool::ReadConfig(QString name)
{
    return settings->value(name);
}
// divide count to dump users to 25k (size for one max dump from vk)
QVariant VKTool::numDivTo25K(int number)
{
     int counter = qCeil(number/25000);
     int ost = number - counter*25000;
     return QVariantList() << counter << ost;
}

QVariant VKTool::getMembers(QString group, QString offset, QString count)
{
    qDebug() << group << offset << count;

    int offs = offset.toInt();
    QVariantList jsonAnswer;

    // for cnt times (25K times in count) getMembers with 25K users size param
    for (int cnt = 0;  cnt < numDivTo25K(count.toInt()).toList().at(0).toInt(); cnt++){
        PARAMS getMembersParams;
        getMembersParams.insert("gid",group);
        getMembersParams.insert("offset",QString::number(offs));
        getMembersParams.insert("count","25000");
        jsonAnswer = vkApi->executeMethod("execute.getMembers",getMembersParams).toVariantMap().value("response").toMap().value("members").toList();
        offs+=25000;
        qDebug() << " c++ load 25K set " << cnt << jsonAnswer.size();
    }
    // one times getMembers with ost (<then 25K) users size param
    {
        PARAMS getMembersParams;
        getMembersParams.insert("gid",group);
        getMembersParams.insert("offset",QString::number(offs));
        getMembersParams.insert("count",numDivTo25K(count.toInt()).toList().at(1).toString());
        jsonAnswer.append(vkApi->executeMethod("execute.getMembers",getMembersParams).toVariantMap().value("response").toMap().value("members").toList());
        offs+= numDivTo25K(count.toInt()).toList().at(1).toInt();
        qDebug() << " c++ ostatok set " << jsonAnswer.size();
    }

    // parse each like in row and if like == null then set null in model for this place and continue for row
//    qDebug() << " PARSING LIKES ";
//    QList<QString> likes;

//    foreach (QVariant pair, jsonAnswer) {
//       if(pair.toMap().value("photo_id")!=QVariant::Invalid){
//           likes.append(pair.toMap().value("photo_id").toString());
//       }else{
//           likes.append(QString(" "));
//       }
//    }
    //qDebug() << " LIKES " << likes.size() << likes;

    QVariantList* vl = new QVariantList();
    vl->insert(0,jsonAnswer);

    // split to 5 lists by pandas and add likes as new lists to result
    QVariant result;
    runFunc.call("parse", *vl);

    return result;
}

QVariant VKTool::getFiltered(QString sex, QString online, QString country, QString city, QString bdate, QString name)
{
    QVariantList vl;
    vl << sex;
    vl << online;
    vl << country;
    vl << city;
    vl << bdate;
    vl << name;
    qDebug() << " DEB ";
    QVariant result = runFunc.call("filter",vl);
    return result;
}

//! direct connect login
void VKTool::login(QString login, QString password)
{
    //---------Direct Authorization
    qDebug() <<  login << password;
    QJsonObject answer = vkApi->get(QUrl("https://oauth.vk.com/token?grant_type=password&scope=notify,friends,photos,audio,video,docs,notes,pages,status,offers,questions,wall,groups,messages,notifications,stats,ads,offline&client_id=3697615&client_secret=AlVXZFMUqyrnABp8ncuU&username="+login+"&password="+password+"&v=5.24"));
    qDebug() << answer;
    Token = answer.toVariantMap().value("access_token").toString();
    Expires.append("0");
    WriteConfig("token", Token);
    WriteConfig("expires",Expires);
    WriteConfig("expDate",QDate::currentDate().addDays(1).toString());
    qDebug() << Token;
    vkApi->setToken(Token);
    tokenGot(Token);
    QQmlProperty property(menu, "token");
    property.write(Token);
}

void VKTool::getAccount()
{
    qDebug() << " GET ACCOUNT ";
    PARAMS params;
    params.insert("fields","photo_max,counters");//photo_50,photo_100,photo_200,photo_400_orig,

    QJsonObject userJson = vkApi->executeMethod("users.get",params);
    QVariantList List = userJson.toVariantMap().value("response").toList();
    QVariantMap current = List[0].toMap();

    QString name = current.value("first_name").toString();
            name.append(" ");
            name.append(current.value("last_name").toString());

    loginedUserId = current.value("id").toString();
}
//! hook connect login
void VKTool::tokenRecived(QString tok)
{
    Token = tok;
    Expires.append("0");
    WriteConfig("token", Token);
    WriteConfig("expires",Expires);
    WriteConfig("expDate",QDate::currentDate().addDays(1).toString());
    qDebug() << Token;
    vkApi->setToken(Token);
    tokenGot(Token);
    QQmlProperty property(menu, "token");
    property.write(Token);

    getAccount();
    QQmlProperty property1(menu, "user_id");
    property1.write(loginedUserId);
}
