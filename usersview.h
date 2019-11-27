#ifndef USERSVIEW_H
#define USERSVIEW_H

#include <QObject>
#include <QtQuickWidgets/QtQuickWidgets>


class User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString photo50 READ photo50 WRITE setPhoto50 NOTIFY photo50Changed)
    Q_PROPERTY(QString photoid READ photoid WRITE setPhotoid NOTIFY photoidChanged)
    Q_PROPERTY(QString first_name READ first_name WRITE setFirst_name NOTIFY first_nameChanged)
    Q_PROPERTY(QString liked READ liked WRITE setLiked NOTIFY likedChanged)
    Q_PROPERTY(QString photo100 READ photo100 WRITE setPhoto100 NOTIFY photo100Changed)
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)

public:
    User(QObject *parent=0){ }
    User(const QString &photo50, const QString &photoid, QString &first_name, QString &liked, QString &photo100, QString &id, QObject *parent=0): QObject(parent), m_photo50(photo50), m_photoid(photoid), m_first_name(first_name), m_liked(liked), m_photo100(photo100), m_id(id){ }

    QString photo50() const {
        return m_photo50;
    }

    void setPhoto50(const QString &photo50){
        if (photo50 != m_photo50) {
            m_photo50 = photo50;
            emit photo50Changed();
        }
    }

    QString photoid() const  {
        return m_photoid;
    }

    void setPhotoid(const QString &photoid){
        if (photoid != m_photoid) {
            m_photoid = photoid;
            emit photoidChanged();
        }
    }


    QString first_name() const  {
        return m_first_name;
    }

    void setFirst_name(const QString &first_name){
        if (first_name != m_first_name) {
            m_first_name = first_name;
            emit first_nameChanged();
        }
    }

    QString liked() const  {
        return m_liked;
    }

    void setLiked(const QString &liked){
        if (liked != m_liked) {
            m_liked = liked;
            emit likedChanged();
        }
    }

    QString photo100() const  {
        return m_photo100;
    }

    void setPhoto100(const QString &photo100){
        if (photo100 != m_photo100) {
            m_photo100 = photo100;
            emit photo100Changed();
        }
    }

    QString id() const  {
        return m_id;
    }

    void setId(const QString &id){
        if (id != m_id) {
            m_id = id;
            emit idChanged();
        }
    }


signals:
    void photo50Changed();
    void photoidChanged();
    void first_nameChanged();
    void likedChanged();
    void photo100Changed();
    void idChanged();

private:
    QString m_photo50;
    QString m_photoid;
    QString m_first_name;
    QString m_liked;
    QString m_photo100;
    QString m_id;
};

// Users view
class usersView : public QQuickWidget
{
    Q_OBJECT
public:
    explicit usersView(QWidget *parent = 0);
    QList<QObject*> users;
    QQmlContext *context;
    ~usersView(){}

    QString mToken;


signals:

public slots:
    void addUser(QString photo50, QString photoid, QString first_name, QString photo100, QString id);
    void clear(){ users.clear();}
    void refresh();
    void setToken(QString token){
        mToken = token;
        QObject* root = (QObject*) this->rootObject();
        QQmlProperty property(root, "token");
        property.write(token);
    }
};


#endif // USERSVIEW_H
