#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QtQuickWidgets/QtQuickWidgets>
#include <QtCharts/QAbstractSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QAreaSeries>
#include <QtQuick/QQuickView>
#include <QtQuick/QQuickItem>
#include <QtCore/QDebug>
#include <QtCore/QtMath>

QT_CHARTS_USE_NAMESPACE
Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

class DataSource : public QObject
{
    Q_OBJECT
public:
    explicit DataSource(QObject *parent = 0):
        QObject(parent)
    {
        qRegisterMetaType<QAbstractSeries*>();
        qRegisterMetaType<QAbstractAxis*>();
    }

public slots:
//    void generateData(int col){
//        // Remove previous data
//        m_data.clear();
//        // Append the new data depending on the type
//        m_data.reserve(col);
//        for (int j(0); j < col; j++) {
//            //
//            qreal x(0);
//            qreal y(0);
//            y = qSin(3.14159265358979 / 50 * j) + 0.5 + (qreal) rand() / (qreal) RAND_MAX;
//            x = j;
//            //
//            m_data.append(QPointF(x, y));
//        }
//    }

    void setUids(QVector<QPointF> data){
        m_data = data;
    }

    void update(QAbstractSeries *series){
        if (series) {
            QXYSeries *xySeries = static_cast<QXYSeries *>(series);
            // Use replace instead of clear + append, it's optimized for performance
            xySeries->replace(m_data);
        }
    }

private:
    QVector<QPointF> m_data;
};

// Graph View
class Graph : public QQuickWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = 0);
    QQmlContext *context;

    void showUids(QVariantList data);
    DataSource dataSource;

signals:
    void selected(QString, QString);

public slots:
    void setUids(QVariantList);
};

#endif // GRAPH_H
