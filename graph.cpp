#include "graph.h"
#include <QtCore/QDebug>

Q_DECLARE_METATYPE(QVector<float>)

Graph::Graph(QWidget *parent)
{
    rootContext()->setContextProperty("dataSource", &dataSource);
    setSource(QUrl::fromLocalFile("qml/graph.qml"));
    QObject* root = (QObject*) rootObject();
    connect(root, SIGNAL(selected(QString,QString)),this, SIGNAL(selected(QString, QString)));
}

void Graph::setUids(QVariantList lst)
{
    QObject* root = (QObject*) this->rootObject();
    QMetaObject::invokeMethod(root, "setUids",
            Q_ARG(QVariant, QVariant::fromValue(lst))
          );
}

void Graph::showUids(QVariantList data)
{
    //! CONVERSATION QVariantList of uids to array of float points
    QVector<QPointF> points;
    points.reserve(data.size());
    int i = 0;
    foreach (QVariant e, data) {
        points << QPointF(i,e.toFloat());
        i++;
    }

    dataSource.setUids(points);
    QMetaObject::invokeMethod((QObject*)this->rootObject(), "update");
}
