#include "usersview.h"

usersView::usersView(QWidget *parent)
{
     setSource(QUrl::fromPercentEncoding("qml/usersView.qml"));
     context = this->rootContext();
}

void usersView::addUser(QString photo50, QString photoid, QString first_name, QString photo100, QString id)
{
    QString liked;
    users.append(new User(photo50, photoid, first_name, liked, photo100, id));
    refresh();
}

void usersView::refresh()
{
    context->setContextProperty("usersModel", QVariant::fromValue(users));
}
