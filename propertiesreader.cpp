#include "propertiesreader.h"

PropertiesReader::PropertiesReader(QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODeviceBase::ReadOnly)){
        qDebug() << "文件打开失败";
    }else {
        QList<QByteArray> line;
        while(!file.atEnd()){
            line = file.readLine().split('=');
            this->result.insert(line.at(0),trimstr(line.at(1).toStdString()));
        }
    }
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
