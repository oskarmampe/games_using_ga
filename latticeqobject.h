#ifndef LATTICEQOBJECT_H
#define LATTICEQOBJECT_H

#include <QObject>
#include <QDebug>
#include <QUrl>

#include <tuple>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>


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
    QString get_path();


signals:
    void status_changed();
    void path_changed();

public slots:

private:
    int dimension;
    double e;
    double b;
    int t;
    QString status;
    QString path;

    std::vector<std::vector<char>> lattice;
    std::vector<std::vector<char>> old_lattice;
    std::vector<std::vector<double>> payoff_matrix;

    std::vector<std::vector<int>> get_neighbours(std::vector<int>);
    double play_with_neighbours(char, std::vector<char>);
    std::vector<std::vector<std::tuple<char, double>>> get_payoff_values();
    std::vector<std::vector<char>> update(std::vector<std::vector<std::tuple<char, double>>>);
    void print_lattice(QString);


};

#endif // LATTICEQOBJECT_H
