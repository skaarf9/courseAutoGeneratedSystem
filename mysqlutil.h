#ifndef MYSQLUTIL_H
#define MYSQLUTIL_H
#include <iostream>
#include <string>
#include "propertiesreader.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <exception>

class MysqlUtil
{
public:
    MysqlUtil();
    MysqlUtil(QString username, QString password);
    QString toString();
    void closeDatabase();
    QSqlDatabase getConn();
private:
    QSqlDatabase db;

    QString ip;
    QString username;
    QString password;
    QString databasename;
    QString port;
};

#endif // MYSQLUTIL_H
