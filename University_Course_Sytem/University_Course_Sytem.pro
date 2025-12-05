QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addinstructor.cpp \
    admin.cpp \
    dropcoursewindow.cpp \
    instructor.cpp \
    instructorcourses.cpp \
    instructorschedule.cpp \
    instructorwindow.cpp \
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
    editstudent.cpp \
    editinstructor.cpp \
    reportspage.cpp \
    analytics.cpp \
    viewdeletestudent.cpp \
    viewdeletecourse.cpp \
    viewdeleteinstructor.cpp

HEADERS += \
    addinstructor.h \
    admin.h \
    dropcoursewindow.h \
    instructor.h \
    instructorcourses.h \
    instructorschedule.h \
    instructorwindow.h \
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
    editstudent.h \
    editinstructor.h \
    reportspage.h \
    analytics.h \
    viewdeletestudent.h \
    viewdeletecourse.h \
    viewdeleteinstructor.h

FORMS += \
    addinstructor.ui \
    dropcoursewindow.ui \
    instructorcourses.ui \
    instructorschedule.ui \
    instructorwindow.ui \
    login_page.ui \
    addstudent.ui \
    addcourse.ui \
    admindashboard.ui \
    registercourse.ui \
    studentwindow.ui \
    viewenrollment.ui \
    viewschedule.ui \
    editcourse.ui \
    editstudent.ui \
    editinstructor.ui \
    reportspage.ui \
    analytics.ui \
    viewdeletestudent.ui \
    viewdeletecourse.ui \
    viewdeleteinstructor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
