#ifndef VARIABLEEXPLORER_H
#define VARIABLEEXPLORER_H

#include <QObject>
#include <QtQuickWidgets/QtQuickWidgets>

// VARIABLE OBJECT
class VariableObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString datatype READ datatype WRITE setDatatype NOTIFY datatypeChanged)
    Q_PROPERTY(QString size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)


public:
    VariableObject(QObject *parent=0){ }
    VariableObject(const QString &name, const QString &datatype, const QString &size, const QString &value,QObject *parent=0): QObject(parent), m_name(name), m_datatype(datatype), m_size(size), m_value(value){ }

    QString name() const {
        return m_name;
    }

    void setName(const QString &name){
        if (name != m_name) {
            m_name = name;
            emit nameChanged();
        }
    }

    QString datatype() const  {
        return m_datatype;
    }

    void setDatatype(const QString &datatype){
        if (m_datatype != m_datatype) {
            m_datatype = datatype;
            emit datatypeChanged();
        }
    }

    QString size() const  {
        return m_size;
    }

    void setSize(const QString &size){
        if (m_size != m_size) {
            m_size = size;
            emit sizeChanged();
        }
    }

    QString value() const  {
        return m_value;
    }

    void setValue(const QString &value){
        if (m_value != m_value) {
            m_value = value;
            emit valueChanged();
        }
    }

signals:
    void nameChanged();
    void datatypeChanged();
    void sizeChanged();
    void valueChanged();




private:
    QString m_name;
    QString m_datatype;
    QString m_size;
    QString m_value;
};

// VARIABLE EXPLORER
class VariableExplorer : public  QQuickWidget
{
    Q_OBJECT
public:
    explicit VariableExplorer(QWidget *parent = 0);
    QList<QObject*> variables;
    QQmlContext *context;
    ~VariableExplorer(){}

public slots:
    void addVariable(QString name, QString type, QString value);
    void refresh();
    void edit(int index);

signals:


};
#endif // VARIABLEEXPLORER_H
