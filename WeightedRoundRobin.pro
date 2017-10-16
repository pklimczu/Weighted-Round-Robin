QT += qml quick

CONFIG += c++11

SOURCES += main.cpp
HEADERS += cpp/Packet.h
SOURCES += cpp/Packet.cpp
HEADERS += cpp/Queue.h
SOURCES += cpp/Queue.cpp
HEADERS += cpp/Scheduler.h
SOURCES += cpp/Scheduler.cpp
HEADERS += cpp/SimulationPresenter.h
SOURCES += cpp/SimulationPresenter.cpp
HEADERS += cpp/presenter/QueueItem.h
SOURCES += cpp/presenter/QueueItem.cpp
HEADERS += cpp/presenter/QueueModel.h
SOURCES += cpp/presenter/QueueModel.cpp
HEADERS += cpp/presenter/ResultItem.h
SOURCES += cpp/presenter/ResultItem.cpp

#HEADERS +=
#SOURCES +=

RESOURCES += qml.qrc

DEFINES += QT_DEPRECATED_WARNINGS

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
