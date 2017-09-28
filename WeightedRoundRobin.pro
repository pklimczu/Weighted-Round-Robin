QT += qml quick

CONFIG += c++11

SOURCES += main.cpp
HEADERS += cpp/Scheduler.h
SOURCES += cpp/Scheduler.cpp
HEADERS += cpp/Queue.h
SOURCES += cpp/Queue.cpp
HEADERS += cpp/Packet.h
SOURCES += cpp/Packet.cpp

RESOURCES += qml.qrc

DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
