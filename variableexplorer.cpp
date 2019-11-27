#include "variableexplorer.h"

VariableExplorer::VariableExplorer(QWidget *parent)
{
    setSource(QUrl("qrc:/qml/variableExplorer.qml"));
    context = this->rootContext();

    variables.append(new VariableObject("Item 1", "int", "32", "wwwww"));
    variables.append(new VariableObject("Item 2", "list", "12", "wwwwwww"));
    variables.append(new VariableObject("Item 3", "dataframe", "15", "wwwwww"));
    variables.append(new VariableObject("Item 4", "string", "11","wwwww"));
    refresh();

    //QObject* root = (QObject*) this->rootObject();
    //connect(this, SIGNAL(log(QString, QString)),root, SIGNAL(log(QString, QString)));
}

// Add variable to Variable Explorer
void VariableExplorer::addVariable(QString name, QString type, QString value)
{
    variables.append(new VariableObject(name, type,QString::number(value.size()), value));
    qDebug() << "WWWWW" <<  QString::number(value.size());
    refresh();
}

void VariableExplorer::refresh()
{
    context->setContextProperty("variableModel", QVariant::fromValue(variables));
}

void VariableExplorer::edit(int index)
{

}
