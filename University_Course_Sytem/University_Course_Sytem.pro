QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addinstructor.cpp \
    admin.cpp \
    deletecourse.cpp \
    deleteinstructor.cpp \
    deletestudent.cpp \
    dropcoursewindow.cpp \
    instructor.cpp \
    instructorcourses.cpp \
    instructorschedule.cpp \
    instructorwindow.cpp \
    listcourses.cpp \
    listinstructors.cpp \
    liststudents.cpp \
    main.cpp \
    login_page.cpp \
    registercourse.cpp \
    registration_system.cpp \
    student.cpp \
    addstudent.cpp \
    addcourse.cpp \
    admindashboard.cpp \
    course.cpp \
    studentwindow.cpp \
    viewenrollment.cpp \
    viewschedule.cpp \
    editcourse.cpp \
    reportspage.cpp \
    statisticswindow.cpp

HEADERS += \
    addinstructor.h \
    admin.h \
    deletecourse.h \
    deleteinstructor.h \
    deletestudent.h \
    dropcoursewindow.h \
    instructor.h \
    instructorcourses.h \
    instructorschedule.h \
    instructorwindow.h \
    listcourses.h \
    listinstructors.h \
    liststudents.h \
    login_page.h \
    registercourse.h \
    registration_system.h \
    student.h \
    addstudent.h \
    addcourse.h \
    admindashboard.h \
    course.h \
    studentwindow.h \
    viewenrollment.h \
    viewschedule.h \
    editcourse.h \
    reportspage.h \
    statisticswindow.h

FORMS += \
    addinstructor.ui \
    deletecourse.ui \
    deleteinstructor.ui \
    deletestudent.ui \
    dropcoursewindow.ui \
    instructorcourses.ui \
    instructorschedule.ui \
    instructorwindow.ui \
    listcourses.ui \
    listinstructors.ui \
    liststudents.ui \
    login_page.ui \
    addstudent.ui \
    addcourse.ui \
    admindashboard.ui \
    registercourse.ui \
    studentwindow.ui \
    viewenrollment.ui \
    viewschedule.ui \
    editcourse.ui \
    reportspage.ui \
    statisticswindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
