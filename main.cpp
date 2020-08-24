#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlEngine>
#include <QQmlContext>

#include "latticeqobject.h"
#include "genetic_algorithm.h"

/**
 *
 * Main Entry of the Application
 *
 * @brief qMain
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char *argv[])
{
    // Required QT Code
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // Create a scoped pointer, so that it gets deleted correctly
    QScopedPointer<LatticeQObject> lattice(new LatticeQObject);

    // Register the class with QML, so that it can be invoked inside QML file
    qmlRegisterUncreatableType<LatticeQObject>("App", 1, 0, "LatticeQObject", "");

    // Initialise the lattice with default as described in report
    //
    lattice->initialise(150, // dimension
                        1.65, // b
                        0, // e
                        64, // t
                        100, // parents
                        80, // children
                        true, //global
                        false); // mutation

    // Required QT code that loads up the GUI from qml file.
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
