#ifndef LATTICEQOBJECT_H
#define LATTICEQOBJECT_H

#include <QObject>
#include <QDebug>
#include <QUrl>
#include <QDir>
#include <chrono>
#include <ctime>
#include <string>
#include <vector>

#include "lattice.h"
class LatticeQObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ get_status NOTIFY status_changed)
    Q_PROPERTY(QString image_path READ get_path NOTIFY path_changed)
public:
    explicit LatticeQObject(QObject *parent = nullptr);
    void initialise(int, double, double, int);
    void simulate();
    QString get_status();
    Q_INVOKABLE void run_simulation();
    Q_INVOKABLE void show_lattice();
    Q_INVOKABLE void change_lattice(QString, QString, QString);
    Q_INVOKABLE void set_t(QString);
    Q_INVOKABLE void set_b(QString);
    Q_INVOKABLE void set_e(QString);
    Q_INVOKABLE void set_dimension(QString);
    void set_status(QString);
    void set_path(QString);
    Q_INVOKABLE QString get_t();
    Q_INVOKABLE QString get_b();
    Q_INVOKABLE QString get_e();
    Q_INVOKABLE QString get_dimension();
    Q_INVOKABLE void cancel();
    QString get_path();


signals:
    void status_changed();
    void path_changed();

public slots:

private:
    QString status;
    QString path;
    int t;
    Lattice* lattice;
    bool stop;
};

#endif // LATTICEQOBJECT_H
