#include "mysqlutil.h"

MysqlUtil::MysqlUtil()
{
    PropertiesReader prop("../GraduationProject/sql.properties");
    QHash<QString,QString> sqlConfig = prop.getResult();
    db = QSqlDatabase::addDatabase("QMYSQL");
    this->ip = sqlConfig.take("ip");
    this->username = sqlConfig.take("username");
    this->password = sqlConfig.take("password");
    this->databasename = sqlConfig.take("databasename");
    this->port = sqlConfig.take("port");
//    qDebug() << this->toString();
    db.setHostName(this->ip);
    db.setUserName(this->username);
    db.setPassword(this->password);
    db.setDatabaseName(this->databasename);
    if(!db.open()){
        qDebug() << "不能连接" <<db.lastError().text();
        return;
    }else {
        qDebug() << "连接成功!";
    }
}

QString MysqlUtil::toString(){
    return QString("ip:[" + this->ip + "] username:[" + this->username + "] password:[" + this->password + "] databasename:[" +this->databasename + "] port:[" + this->port + "]");
}

void MysqlUtil::closeDatabase(){
    this->db.close();
}
