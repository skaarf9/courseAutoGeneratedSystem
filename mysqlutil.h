#ifndef MYSQLUTIL_H
#define MYSQLUTIL_H
#include <iostream>
#include <string>
#include "propertiesreader.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class MysqlUtil
{
public:
    MysqlUtil();
    QString toString();
    void closeDatabase();
private:
    QSqlDatabase db;

    QString ip;
    QString username;
    QString password;
    QString databasename;
    QString port;
};

#endif // MYSQLUTIL_H
