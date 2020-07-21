#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "latticeqobject.h"
#include "genetic_algorithm.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QScopedPointer<LatticeQObject> lattice(new LatticeQObject);

    qmlRegisterUncreatableType<LatticeQObject>("App", 1, 0, "LatticeQObject", "");

    lattice->initialise(300, 1.65, 0, 64);

    GeneticAlgorithm ga;

    ga.simulate();

    QQmlApplicationEngine engine;



    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.rootContext()->setContextProperty("lattice", lattice.data());
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
