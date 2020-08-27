#include "latticeqobject.h"

#include "LatticeThread.h"

/**
 *
 * Required constructor
 *
 * @brief LatticeQObject::LatticeQObject
 * @param parent QObject
 */
LatticeQObject::LatticeQObject(QObject *parent) : QObject(parent){}

/**
 *
 * Initialise the lattice
 *
 * @brief LatticeQObject::initialise
 * @param dimension
 * @param b
 * @param e
 * @param t
 * @param parents
 * @param children
 * @param global_pop: global or local/neighbourhood
 * @param mut: mutation or no mutation
 */
void LatticeQObject::initialise(int dimension, double b, double e, int t, int parents, int children, bool global_pop, bool mut)
{
    this->t = t;
    this->parents = parents;
    this->children = children;
    this->global_pop = global_pop;
    this->mut = mut;
    lattice = new GeneticLattice(dimension, b, e);


    set_status(QString("Press \"Simulate\" to begin...."));
}

/**
 *
 * t setter
 *
 * @brief LatticeQObject::set_t
 * @param t
 */
void LatticeQObject::set_t(QString t)
{
    bool ok;
    int intTest = t.toInt(&ok);
    if (ok && intTest >= 1)
    {
        this->t = intTest;
        set_status(QString("t changed to "+t+"...."));
    }
    else
    {
        set_status(QString("Conversion to number failed..."));
    }

}

/**
 *
 * e setter
 *
 * @brief LatticeQObject::set_e
 * @param e
 */
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

/**
 *
 * b setter
 *
 * @brief LatticeQObject::set_b
 * @param b
 */
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

/**
 *
 * Dimension setter
 *
 * @brief LatticeQObject::set_dimension
 * @param dimension
 */
void LatticeQObject::set_dimension(QString dimension)
{
    bool ok;
    int intTest = dimension.toInt(&ok);
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

/**
 *
 * Encoding setter
 *
 * @brief LatticeQObject::set_encoding
 * @param encoding
 */
void LatticeQObject::set_encoding(QString encoding)
{
    if (encoding == "CELLSTATE")
    {
        lattice->set_encoding(GeneticIndividual::CELLSTATE);
    }
    else if(encoding == "AUTOMATA")
    {
        lattice->set_encoding(GeneticIndividual::AUTOMATA);
    }
    else if(encoding == "ATTRIBUTE")
    {
        lattice->set_encoding(GeneticIndividual::ATTRIBUTE);
    }

}

/**
 *
 * Parent setter
 *
 * @brief LatticeQObject::set_parent
 * @param parents
 */
void LatticeQObject::set_parent(QString parents)
{
    bool ok;
    int intTest = parents.toInt(&ok);
    if (ok && intTest <= get_dimension().toInt())
    {
        this->parents = intTest;
        set_status(QString("parents changed to "+parents+"...."));
    }
    else
    {
        set_status(QString("Conversion to number failed..."));
    }
}

/**
 *
 * Children setter
 *
 * @brief LatticeQObject::set_children
 * @param children
 */
void LatticeQObject::set_children(QString children)
{
    bool ok;
    int intTest = children.toInt(&ok);
    if (ok && intTest <= get_dimension().toInt())
    {
        this->children = intTest;
        set_status(QString("children changed to "+children+"...."));
    }
    else
    {
        set_status(QString("Conversion to number failed..."));
    }
}

/**
 *
 * Global population setter
 *
 * @brief LatticeQObject::set_global_pop
 * @param global_pop
 */
void LatticeQObject::set_global_pop(bool global_pop)
{
    this->global_pop = global_pop;
}

/**
 *
 * Mutation setter
 *
 * @brief LatticeQObject::set_mutation
 * @param mut
 */
void LatticeQObject::set_mutation(bool mut)
{
    this->mut = mut;
}

/**
 *
 * t getter
 *
 * @brief LatticeQObject::get_t
 * @return t
 */
QString LatticeQObject::get_t()
{
    return QString::number(t);
}

/**
 *
 * e getter
 *
 * @brief LatticeQObject::get_e
 * @return e
 */
QString LatticeQObject::get_e()
{
    return QString::number(this->lattice->get_e());
}

/**
 *
 * Encoding getter
 *
 * @brief LatticeQObject::get_encoding
 * @return encoding
 */
int LatticeQObject::get_encoding()
{
    if(lattice->get_encoding() == GeneticIndividual::CELLSTATE)
    {
        return 0;
    }
    else if(lattice->get_encoding() == GeneticIndividual::AUTOMATA)
    {
        return 1;
    }
    else if(lattice->get_encoding() == GeneticIndividual::ATTRIBUTE)
    {
        return 2;
    }
}

/**
 *
 * b getter
 *
 * @brief LatticeQObject::get_b
 * @return b
 */
QString LatticeQObject::get_b()
{
    return QString::number(this->lattice->get_b());
}

/**
 *
 * Dimension getter
 *
 * @brief LatticeQObject::get_dimension
 * @return dimension
 */
QString LatticeQObject::get_dimension()
{
    return QString::number(this->lattice->get_dimension());
}

/**
 *
 * Parent getter
 *
 * @brief LatticeQObject::get_parent
 * @return parent
 */
QString LatticeQObject::get_parent()
{
    return QString::number(parents);
}

/**
 *
 * Children getter
 *
 * @brief LatticeQObject::get_children
 * @return children
 */
QString LatticeQObject::get_children()
{
    return QString::number(children);
}

/**
 *
 * Global population getter
 *
 * @brief LatticeQObject::get_global_pop
 * @return global or local/neighbourhood
 */
bool LatticeQObject::get_global_pop()
{
    return global_pop;
}

/**
 *
 * Mutation getter
 *
 * @brief LatticeQObject::get_mutation
 * @return mutation
 */
bool LatticeQObject::get_mutation()
{
    return this->mut;
}

/**
 *
 * Path getter
 *
 * @brief LatticeQObject::get_path
 * @return path
 */
QString LatticeQObject::get_path()
{
    return path;
}

/**
 *
 * A simulate with reset
 *
 * @brief LatticeQObject::simulate_test
 */
void LatticeQObject::simulate_test()
{
    simulate();
    reset_lattice(true);
}

/**
 *
 * Path setter
 *
 * @brief LatticeQObject::set_path
 * @param path
 */
void LatticeQObject::set_path(QString path)
{
    this->path = path;
    emit path_changed();
}

/**
 *
 * Cell getter
 *
 * @brief LatticeQObject::get_cell
 * @param i: row
 * @param j: column
 * @return cell
 */
GeneticIndividual LatticeQObject::get_cell(int i, int j)
{
    return lattice->get_cell(i, j);
}

/**
 *
 * Cancel the thread
 *
 * @brief LatticeQObject::cancel
 */
void LatticeQObject::cancel()
{
    stop = true;
}

/**
 *
 * Reset the lattice. A hard reset means reset parameters back to default
 * Soft reset (hard_reset == false) would use the previous parameters.
 *
 * @brief LatticeQObject::reset_lattice
 * @param hard_reset
 */
void LatticeQObject::reset_lattice(bool hard_reset)
{
    int dimension;
    double b;
    double e;

    if (hard_reset)
    {
        dimension = 150;
        b = 1.65;
        e = 0.0;
        t = 64;
        parents = 100;
        children = 80;
        mut = false;
    }
    else
    {
         dimension = lattice->get_dimension();
         b = lattice->get_b();
         e = lattice->get_e();
    }
    delete lattice;
    lattice = new GeneticLattice(dimension, b, e);
}

/**
 *
 * Simulate a generation using a genetic algorithm
 *
 * @brief LatticeQObject::simulate
 */
void LatticeQObject::simulate()
{
    // Lock the mutex so no multiple threads can use the method
    mutex.lock();
    set_status(QString("Running Simulation...."));
    qDebug() << "Running Simulation....";
    stop = false;

    // Get the current date and time to name the folder
    std::time_t time = std::time(nullptr);
    std::tm tm = *std::localtime(&time);
    char buffer[256];

    strftime(buffer, sizeof(buffer), "%Y%b%d_%H%M%S", &tm);
    QDir().mkdir(QDir::current().absolutePath() + "/" + QString(buffer));

    set_status(QString("BEGINNING OF SIMULATION"));
    qDebug() << "BEGINNING OF SIMULATION";
    for (int i = 0; i < t; ++i)
    {
        if(stop)
        {// if stopped button was pressed
            reset_lattice(false);
            set_status(QString("STOPPING..."));
            mutex.unlock();
            return;
        }
        set_status("Start of " +  QString::number(i) + " simulation....");
        QString img_path(QDir::current().absolutePath() + "/" + QString(buffer) + "/" + QString::number(i+1) + ".ppm");
        try
        {
            lattice->simulate(img_path.toStdString(), parents, children, global_pop, mut);
        }
        catch (std::runtime_error &er)
        {
            set_status("ERROR READING FILE....");
        }

        set_path("file:///" + img_path);
        set_status("End of " +  QString::number(i) + " simulation....");
    }

    set_status(QString("END OF SIMULATION"));
    qDebug() << "END OF SIMULATION";
    reset_lattice(false);
    mutex.unlock();
}

/**
 *
 * Status getter
 *
 * @brief LatticeQObject::get_status
 * @return
 */
QString LatticeQObject::get_status()
{
    return this->status;
}

/**
 *
 * Status setter
 *
 * @brief LatticeQObject::set_status
 * @param status
 */
void LatticeQObject::set_status(QString status)
{
    this->status = status;
    emit status_changed();
}


/**
 *
 * Run the simulation by creating a thread.
 *
 * @brief LatticeQObject::run_simulation
 */
void LatticeQObject::run_simulation()
{
    LatticeThread* thread = new LatticeThread(this);

    thread->start();

}

/**
 *
 * Show the lattice
 *
 * @brief LatticeQObject::show_lattice
 */
void LatticeQObject::show_lattice()
{
    QString img_path(QDir::current().absolutePath() + "/current_board.ppm");
    lattice->save_lattice(img_path.toStdString());
    set_path(""); // needed to update the image, setting the path of the image to be the same does not update it
    set_path("file:///" + img_path);
}

/**
 *
 * Do multiple simulations, which are included in the report.
 *
 * @brief LatticeQObject::test
 */
void LatticeQObject::test()
{
    this->global_pop = true;
    test_batch();
    this->global_pop = false;
    test_batch();
}

/**
 *
 * A single batch of simulations.
 *
 * @brief LatticeQObject::test_batch
 */
void LatticeQObject::test_batch()
{
    //Different encoding
    set_encoding("CELLSTATE");
    simulate_test();
    set_encoding("ATTRIBUTE");
    simulate_test();
    set_encoding("AUTOMATA");
    simulate_test();
    //different t
    set_t("64");
    simulate_test();
    set_t("128");
    simulate_test();
    set_t("256");
    simulate_test();
    //different dimension
    set_dimension("10");
    simulate_test();
    set_dimension("25");
    simulate_test();
    set_dimension("50");
    simulate_test();
    set_dimension("75");
    simulate_test();
    set_dimension("100");
    simulate_test();
    set_dimension("125");
    simulate_test();
    set_dimension("150");
    simulate_test();
    set_dimension("175");
    simulate_test();
    set_dimension("200");
    simulate_test();
    set_dimension("225");
    simulate_test();
    set_dimension("250");
    simulate_test();
    set_dimension("275");
    simulate_test();
    set_dimension("300");
    simulate_test();//19
    //different e
    set_e("0");
    simulate_test();
    set_e("0.1");
    simulate_test();
    set_e("0.2");
    simulate_test();
    set_e("0.3");
    simulate_test();
    set_e("0.4");
    simulate_test();
    set_e("0.5");
    simulate_test();
    set_e("0.6");
    simulate_test();
    set_e("0.7");
    simulate_test();
    set_e("0.8");
    simulate_test();
    set_e("0.9");
    simulate_test();
    set_e("1");
    simulate_test(); // 30
    //different b
    set_b("1.2");
    simulate_test();
    set_b("1.25");
    simulate_test();
    set_b("1.3");
    simulate_test();
    set_b("1.35");
    simulate_test();
    set_b("1.4");
    simulate_test();
    set_b("1.45");
    simulate_test();
    set_b("1.5");
    simulate_test();
    set_b("1.55");
    simulate_test();
    set_b("1.6");
    simulate_test();
    set_b("1.65");
    simulate_test();
    set_b("1.7");
    simulate_test();
    set_b("1.75");
    simulate_test();
    set_b("1.8"); // 43
    simulate_test();
    //different initial lattice defect positions
    // ONE SQUARE
    change_lattice("73", "73", "c");
    change_lattice("73", "74", "c");
    change_lattice("73", "75", "c");
    change_lattice("74", "73", "c");
    change_lattice("74", "75", "c");
    change_lattice("75", "73", "c");
    change_lattice("75", "74", "c");
    change_lattice("75", "75", "c");
    simulate_test();
    // A CROSS
    change_lattice("73", "73", "c");
    change_lattice("73", "75", "c");
    change_lattice("75", "73", "c");
    change_lattice("75", "75", "c");
    simulate_test();
    //different number of parents/children 45
    if(this->global_pop)
    {
        this->parents = 25;
        simulate_test();
        this->parents = 50;
        simulate_test();
        this->parents = 75;
        simulate_test();
        this->parents = 100;
        simulate_test();
        this->parents = 125;
        simulate_test();
        this->parents = 150;
        simulate_test();
        // CHILDREN
        this->parents = 100;
        this->children = 25;
        simulate_test();
        this->children = 50;
        simulate_test();
        this->children = 75;
        simulate_test();
        this->children = 100;
        simulate_test();
        this->children = 125;
        simulate_test();
        this->children = 150;
        simulate_test();
    }
    this->mut = true;
    simulate_test();
    this->mut = false;
    simulate_test();
}

/**
 *
 * Change the parameters of the genetic algorithm
 *
 * @brief LatticeQObject::change_ga
 * @param encoding
 * @param children
 * @param parent
 * @param global: global or local/neighbourhood
 * @param mut: mutation
 */
void LatticeQObject::change_ga(QString encoding, QString children, QString parent, bool global, bool mut)
{
    set_encoding(encoding);
    set_children(children);
    set_parent(parent);
    set_global_pop(global);
    set_mutation(mut);
}

/**
 *
 * Change the lattice
 *
 * @brief LatticeQObject::change_lattice
 * @param i: row
 * @param j: column
 * @param c: strategy
 */
void LatticeQObject::change_lattice(QString i, QString j, QString c)
{
    bool xok;
    bool yok;
    double xInt = i.toInt(&xok);
    double yInt = j.toInt(&yok);
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
