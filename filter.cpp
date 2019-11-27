#include "filter.h"

Filter::Filter(QWidget *parent)
{
    setSource(QUrl::fromLocalFile("qml/filter.qml"));
    QObject* root = (QObject*) rootObject();
    connect(root, SIGNAL(showFilter(QString, QString, QString, QString, QString, QString)),this, SIGNAL(selected(QString, QString, QString, QString, QString, QString)));
}
