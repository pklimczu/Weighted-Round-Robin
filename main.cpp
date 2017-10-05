#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "cpp/Scheduler.h"

int main(int argc, char *argv[])
{
    // link max throughput, endtime
    Scheduler scheduler(800, 3000.0);
    // name, lambda, avgPacketSize, weight, buffor size
    scheduler.addQueue(new Queue("K1", 10, 11000, 100, 10));
    scheduler.addQueue(new Queue("K2", 10, 11000, 200, 10));
    scheduler.addQueue(new Queue("K3", 10, 11000, 100, 10));
//    scheduler.addQueue(new Queue("K4", 100, 11000, 100, 1000000));
//    scheduler.addQueue(new Queue("K5", 100, 11000, 100, 1000000));
//    scheduler.addQueue(new Queue("K6", 100, 11000, 100, 1000000));
//        scheduler.addQueue(new Queue("K7", 100, 11000, 100, 1000000));
//            scheduler.addQueue(new Queue("K8", 100, 11000, 100, 1000000));
    scheduler.run();

//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
//    QGuiApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

//    return app.exec();
}
