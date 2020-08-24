#ifndef LATTICEQOBJECT_H
#define LATTICEQOBJECT_H

#include <QObject>
#include <QDebug>
#include <QUrl>
#include <QDir>
#include <QMutex>
#include <chrono>
#include <ctime>
#include <string>
#include <vector>

#include "geneticlattice.h"
class LatticeQObject : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ get_status NOTIFY status_changed)
    Q_PROPERTY(QString image_path READ get_path NOTIFY path_changed)
public:
    explicit LatticeQObject(QObject *parent = nullptr);

    void initialise(int, double, double, int, int, int, bool, bool);
    void simulate();
    QString get_status();
    Q_INVOKABLE void run_simulation();
    Q_INVOKABLE void show_lattice();

    Q_INVOKABLE void change_lattice(QString, QString, QString);
    Q_INVOKABLE void change_ga(QString, QString, QString, bool, bool);

    Q_INVOKABLE void set_t(QString);
    Q_INVOKABLE void set_b(QString);
    Q_INVOKABLE void set_e(QString);
    Q_INVOKABLE void set_dimension(QString);
    Q_INVOKABLE void set_encoding(QString);
    Q_INVOKABLE void set_parent(QString);
    Q_INVOKABLE void set_children(QString);
    Q_INVOKABLE void set_global_pop(bool);
    Q_INVOKABLE void set_mutation(bool);
    void set_status(QString);
    void set_path(QString);

    GeneticIndividual get_cell(int, int);

    Q_INVOKABLE QString get_t();
    Q_INVOKABLE QString get_b();
    Q_INVOKABLE QString get_e();
    Q_INVOKABLE int get_encoding();
    Q_INVOKABLE QString get_dimension();
    Q_INVOKABLE QString get_parent();
    Q_INVOKABLE QString get_children();
    Q_INVOKABLE bool get_global_pop();
    Q_INVOKABLE bool get_mutation();
    Q_INVOKABLE void test();

    Q_INVOKABLE void cancel();

    void reset_lattice(bool);
    QString get_path();
    QMutex mutex;


signals:
    void status_changed();
    void path_changed();

public slots:

private:
    void simulate_test();
    void test_batch();
    QString status;
    QString path;
    int t;
    GeneticLattice* lattice;
    bool stop;
    bool global_pop;
    bool mut;
    int parents;
    int children;
};

#endif // LATTICEQOBJECT_H
