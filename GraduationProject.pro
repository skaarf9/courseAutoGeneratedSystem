QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#INCLUDEPATH += "C:\Program Files\MySQL\MySQL Server 8.0\include"
#LIBS += "C:\Program Files\MySQL\MySQL Server 8.0\lib\libmysql.lib"
#DESTDIR = $$PWD/lib/aa/
SOURCES += \
    classroom.cpp \
    classroomAndTime.cpp \
    course.cpp \
    courseSelectionStrategy.cpp \
    coursedisplaywidget.cpp \
    editclasswidget.cpp \
    main.cpp \
    mainwindow.cpp \
    myClass.cpp \
    myTime.cpp \
    mysqlutil.cpp \
    propertiesreader.cpp \
    subject.cpp \
    teacher.cpp

HEADERS += \
    classroom.h \
    classroomAndTime.h \
    course.h \
    courseSelectionStrategy.h \
    coursedisplaywidget.h \
    editclasswidget.h \
    mainwindow.h \
    myClass.h \
    myTime.h \
    mysqlutil.h \
    propertiesreader.h \
    subject.h \
    teacher.h

FORMS += \
    coursedisplaywidget.ui \
    editclasswidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitattributes \
    .gitignore \
    GraduationProject.pro.user \
    school.sql \
    sql.properties \
    sql.propertity
