QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    admin.cpp \
    instructor.cpp \
    main.cpp \
    login_page.cpp \
    registration_system.cpp \
    student.cpp \
    addstudent.cpp \
    addcourse.cpp \
    admindashboard.cpp \
    course.cpp \
    studentwindow.cpp

HEADERS += \
    admin.h \
    instructor.h \
    login_page.h \
    registration_system.h \
    student.h \
    addstudent.h \
    addcourse.h \
    admindashboard.h \
    course.h \
    studentwindow.h

FORMS += \
    login_page.ui \
    addstudent.ui \
    addcourse.ui \
    admindashboard.ui \
    studentwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    courses.txt
