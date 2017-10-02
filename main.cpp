#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cpp/Scheduler.h"

int main(int argc, char *argv[])
{
    Scheduler scheduler(5,1);
    scheduler.addQueue(new Queue("a1", 5, 10, 5, 5));
    scheduler.addQueue(new Queue("a2", 5, 100, 100, 5));
    scheduler.run();

//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    return app.exec();
}
