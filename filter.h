#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QQuickWidget>

//Filter
class Filter : public QQuickWidget
{
    Q_OBJECT
public:
    explicit Filter(QWidget *parent = 0);
    QQmlContext *context;

signals:
    void selected(QString sex, QString online, QString country, QString city, QString bdate, QString name);


};

#endif // FILTER_H
