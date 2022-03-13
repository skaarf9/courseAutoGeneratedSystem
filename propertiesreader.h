#ifndef PROPERTIESREADER_H
#define PROPERTIESREADER_H
#include <QFile>
#include <QString>
#include <QHash>
#include <string>
#include <QDebug>

class PropertiesReader
{
public:
    PropertiesReader(QString fileName);
    const QHash<QString,QString>& getResult()const;
    QString trimstr(std::string str);
    bool writeProperties(QString key, QString value);
private:
    QString fileName;
    QHash<QString,QString> result;
};

#endif // PROPERTIESREADER_H
