#include "latticeqobject.h"

#include "LatticeThread.h"
LatticeQObject::LatticeQObject(QObject *parent) : QObject(parent)
{

}
void LatticeQObject::initialise(int dimension, double b, double e, int t)
{
    std::vector<std::vector<double>> payoff_matrix;
    std::vector<double> payoff_row1{1., 0.};
    std::vector<double> payoff_row2{b, e};
    this->t = t;
    payoff_matrix.push_back(payoff_row1);
    payoff_matrix.push_back(payoff_row2);

    lattice = new GeneticLattice(dimension, b, e);

    set_status(QString("Press \"Simulate\" to begin...."));
}

void LatticeQObject::set_t(QString t)
{
    bool ok;
    int intTest = t.toInt(&ok);
    if (ok)
    {
        this->t = intTest;
        set_status(QString("t changed to "+t+"...."));
    }
    else
    {
        set_status(QString("Conversion to number failed..."));
    }

}

void LatticeQObject::set_e(QString e)
{
    bool ok;
    double doubleTest = e.toDouble(&ok);
    if (ok)
    {
        lattice->set_e(doubleTest);
        set_status(QString("e changed to "+e+"...."));
    }
    else
    {
        set_status(QString("Conversion to number failed..."));
    }
}

void LatticeQObject::set_b(QString b)
{
    bool ok;
    double doubleTest = b.toDouble(&ok);
    if (ok)
    {
        lattice->set_b(doubleTest);
        set_status(QString("b changed to "+b+"...."));
    }
    else
    {
        set_status(QString("Conversion to number failed..."));
    }
}

void LatticeQObject::set_dimension(QString dimension)
{
    bool ok;
    double intTest = dimension.toDouble(&ok);
    if (ok)
    {
        lattice->set_dimension(intTest);
        set_status(QString("dimension changed to "+dimension+"...."));
    }
    else
    {
        set_status(QString("Conversion to number failed..."));
    }
}

QString LatticeQObject::get_t()
{
    return QString::number(t);
}

QString LatticeQObject::get_e()
{
    return QString::number(this->lattice->get_e());
}

QString LatticeQObject::get_b()
{
    return QString::number(this->lattice->get_b());
}

QString LatticeQObject::get_dimension()
{
    return QString::number(this->lattice->get_dimension());
}

QString LatticeQObject::get_path()
{
    return path;
}

void LatticeQObject::set_path(QString path)
{
    this->path = path;
    emit path_changed();
}

void LatticeQObject::cancel()
{
    stop = true;
}

void LatticeQObject::reset_lattice()
{
    int dimension = lattice->get_dimension();
    double b = lattice->get_b();
    double e = lattice->get_e();
    delete lattice;
    lattice = new GeneticLattice(dimension, b, e);
}

void LatticeQObject::simulate()
{
    mutex.lock();
    set_status(QString("Running Simulation...."));
    stop = false;
    std::time_t time = std::time(nullptr);
    std::tm tm = *std::localtime(&time);
    char buffer[256];

    strftime(buffer, sizeof(buffer), "%Y%b%d_%H%M%S", &tm);
    QDir().mkdir(QDir::current().absolutePath() + "/" + QString(buffer));

    set_status(QString("BEGINNING OF SIMULATION"));
    for (int i = 0; i < t; ++i)
    {
        if(stop)
        {
            reset_lattice();
            set_status(QString("STOPPING..."));
            mutex.unlock();
            return;
        }
        set_status("Start of " +  QString::number(i) + " simulation....");
        QString img_path(QDir::current().absolutePath() + "/" + QString(buffer) + "/" + QString::number(i) + ".ppm");
        try
        {
            lattice->simulate(img_path.toStdString());
        }
        catch (std::runtime_error &er)
        {
            set_status("ERROR READING FILE....");
        }

        set_path("file:///" + img_path);
        set_status("End of " +  QString::number(i) + " simulation....");
    }

    set_status(QString("END OF SIMULATION"));
    mutex.unlock();
}

QString LatticeQObject::get_status()
{
    return this->status;
}

void LatticeQObject::set_status(QString status)
{
    this->status = status;
    emit status_changed();
}


void LatticeQObject::run_simulation()
{
    LatticeThread* thread = new LatticeThread(this);

    thread->start();

}

void LatticeQObject::show_lattice()
{
    QString img_path(QDir::current().absolutePath() + "/current_board.ppm");
    lattice->save_lattice(img_path.toStdString());
    set_path("");
    set_path("file:///" + img_path);
}

void LatticeQObject::change_lattice(QString x, QString y, QString c)
{
    bool xok;
    bool yok;
    double xInt = x.toInt(&xok);
    double yInt = y.toInt(&yok);
    if (xok && yok)
    {
        QString img_path(QDir::current().absolutePath() + "/current_board.ppm");
        lattice->change_lattice(xInt, yInt, c.toStdString().data()[0]);
        QDir().remove(img_path);
        set_path("");
        show_lattice();
    }
    else
    {
        set_status(QString("Conversion to number failed..."));
    }

}
