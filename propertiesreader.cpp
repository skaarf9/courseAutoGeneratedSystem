#include "propertiesreader.h"

PropertiesReader::PropertiesReader(QString fileName)
{
    this->fileName = fileName;
    QFile file(fileName);
    if(!file.open(QIODeviceBase::ReadOnly)){
        qDebug() << "文件打开失败";
    }else {
        QList<QByteArray> line;
        while(!file.atEnd()){
            QByteArray lineData = file.readLine().trimmed();
            if(lineData.isEmpty())continue;
            line = lineData.split('=');
            this->result.insert(line.at(0),line.at(1));
        }
    }
    file.close();
}

const QHash<QString,QString>& PropertiesReader::getResult()const{
    return this->result;
}

QString PropertiesReader::trimstr(std::string str){
    size_t n = str.find_last_not_of(" \r\n\t");
        if (n != std::string::npos){
            str.erase(n + 1, str.size() - n);
        }
        n = str.find_first_not_of(" \r\n\t");
        if (n != std::string::npos){
            str.erase(0, n);
        }
        return QString::fromStdString(str);
}

bool PropertiesReader::writeProperties(QString key, QString value){
    QByteArray temp;
    QFile file(this->fileName);
    if(!file.open(QIODeviceBase::ReadOnly)){
        qDebug() << "文件打开失败";
        return false;
    }else {
        QList<QByteArray> line;
        while(!file.atEnd()){
            QByteArray lineData = file.readLine().trimmed();
            if(lineData.isEmpty())continue;
            line = lineData.split('=');
            if(line.at(0) == key){
                continue;
            }
            temp.append(lineData + "\r\n");
        }
        temp.append(QString("%1=%2\r\n").arg(key, value).toStdString().c_str());
    }
    file.close();
    file.open(QIODeviceBase::Truncate | QIODeviceBase::WriteOnly);
    file.write(temp);
    file.close();
    return true;
}
