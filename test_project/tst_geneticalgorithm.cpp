#include <QtTest>

#include "../genetic_algorithm.h"
#include "../latticeqobject.h"

/**
 *
 * Test class, testing basic functionality of the program
 *
 * @brief The TestGeneticAlgorithm class
 */
class TestGeneticAlgorithm : public QObject
{
    Q_OBJECT

private:
    LatticeQObject* lattice;
    GeneticAlgorithm* ga;

private slots:
    void init();
    void cleanup();
    void test_update_param1();
    void test_update_param2();
    void test_update_param3();
    void test_update_param4();
    void test_update_param5();
    void test_update_param6();
    void test_update_param7();

    void test_change_cell1();
    void test_change_cell2();
    void test_change_cell3();
    void test_change_cell4();
    void test_change_cell5();

    void test_change_dimension1();
    void test_change_dimension2();
    void test_change_dimension3();
    void test_change_dimension4();
    void test_change_dimension5();

    void test_change_t1();
    void test_change_t2();
    void test_change_t3();
    void test_change_t4();
    void test_change_t5();

    void test_change_e1();
    void test_change_e2();
    void test_change_e3();
    void test_change_e4();
    void test_change_e5();

    void test_change_b1();
    void test_change_b2();
    void test_change_b3();
    void test_change_b4();
    void test_change_b5();

};

void TestGeneticAlgorithm::init()
{
   lattice = new LatticeQObject();
   lattice->initialise(150, 1.65, 0, 64, 100, 80, true, false);

   ga = new GeneticAlgorithm;
}

void TestGeneticAlgorithm::cleanup()
{
    delete lattice;
    delete ga;
}

void TestGeneticAlgorithm::test_update_param1()
{
    //encoding, children,  parent,  global,  mut)
    lattice->change_ga("ATTRIBUTE", "80", "100", true, false);
    QCOMPARE(lattice->get_encoding(), 2);
    QCOMPARE(lattice->get_parent(), "100");
    QCOMPARE(lattice->get_children(), "80");
    QCOMPARE(lattice->get_global_pop(), true);
    QCOMPARE(lattice->get_mutation(), false);

}
void TestGeneticAlgorithm::test_update_param2()
{
    lattice->change_ga("AUTOMATA", "80", "100", true, false);
    QCOMPARE(lattice->get_encoding(), 1);
    QCOMPARE(lattice->get_parent(), "100");
    QCOMPARE(lattice->get_children(), "80");
    QCOMPARE(lattice->get_global_pop(), true);
    QCOMPARE(lattice->get_mutation(), false);
}
void TestGeneticAlgorithm::test_update_param3()
{
    lattice->change_ga("CELLSTATE", "80", "100", true, false);
    QCOMPARE(lattice->get_encoding(), 0);
    QCOMPARE(lattice->get_parent(), "100");
    QCOMPARE(lattice->get_children(), "80");
    QCOMPARE(lattice->get_global_pop(), true);
    QCOMPARE(lattice->get_mutation(), false);
}
void TestGeneticAlgorithm::test_update_param4()
{
    lattice->change_ga("AUTOMATA", "50", "100", true, false);
    QCOMPARE(lattice->get_encoding(), 1);
    QCOMPARE(lattice->get_parent(), "100");
    QCOMPARE(lattice->get_children(), "50");
    QCOMPARE(lattice->get_global_pop(), true);
    QCOMPARE(lattice->get_mutation(), false);
}
void TestGeneticAlgorithm::test_update_param5()
{
    lattice->change_ga("AUTOMATA", "50", "20", true, false);
    QCOMPARE(lattice->get_encoding(), 1);
    QCOMPARE(lattice->get_parent(), "20");
    QCOMPARE(lattice->get_children(), "50");
    QCOMPARE(lattice->get_global_pop(), true);
    QCOMPARE(lattice->get_mutation(), false);
}

void TestGeneticAlgorithm::test_update_param6()
{
    lattice->change_ga("AUTOMATA", "50", "20", false, false);
    QCOMPARE(lattice->get_encoding(), 1);
    QCOMPARE(lattice->get_parent(), "20");
    QCOMPARE(lattice->get_children(), "50");
    QCOMPARE(lattice->get_global_pop(), false);
    QCOMPARE(lattice->get_mutation(), false);
}


void TestGeneticAlgorithm::test_update_param7()
{
    lattice->change_ga("AUTOMATA", "50", "20", true, true);
    QCOMPARE(lattice->get_encoding(), 1);
    QCOMPARE(lattice->get_parent(), "20");
    QCOMPARE(lattice->get_children(), "50");
    QCOMPARE(lattice->get_global_pop(), true);
    QCOMPARE(lattice->get_mutation(), true);
}

void TestGeneticAlgorithm::test_change_cell1()
{
    lattice->change_lattice("0", "0", "d");
    lattice->change_lattice("74", "74", "c");
    lattice->change_lattice("74", "75", "c");
    lattice->change_lattice("74", "73", "c");
    lattice->change_lattice("75", "74", "c");
    lattice->change_lattice("75", "75", "c");
    lattice->change_lattice("75", "73", "c");
    lattice->change_lattice("73", "74", "c");
    lattice->change_lattice("73", "75", "c");
    lattice->change_lattice("73", "73", "c");

    for (int i = 0; i < lattice->get_dimension(); ++i)
    {
        for (int j = 0; j < lattice->get_dimension(); ++j)
        {
            if ( i == 0 && j == 0)
            {
                QCOMPARE('d', lattice->get_cell(i, j).get_strategy());
            }
            else
            {
                QCOMPARE('c', lattice->get_cell(i, j).get_strategy());
            }
        }
    }
}
void TestGeneticAlgorithm::test_change_cell2()
{
    lattice->change_lattice("149", "149", "d");
    lattice->change_lattice("74", "74", "c");
    lattice->change_lattice("74", "75", "c");
    lattice->change_lattice("74", "73", "c");
    lattice->change_lattice("75", "74", "c");
    lattice->change_lattice("75", "75", "c");
    lattice->change_lattice("75", "73", "c");
    lattice->change_lattice("73", "74", "c");
    lattice->change_lattice("73", "75", "c");
    lattice->change_lattice("73", "73", "c");

    for (int i = 0; i < lattice->get_dimension(); ++i)
    {
        for (int j = 0; j < lattice->get_dimension(); ++j)
        {
            if ( i == 149 && j == 149)
            {
                QCOMPARE('d', lattice->get_cell(i, j).get_strategy());
            }
            else
            {
                QCOMPARE('c', lattice->get_cell(i, j).get_strategy());
            }
        }
    }
}
void TestGeneticAlgorithm::test_change_cell3()
{
    lattice->change_lattice("150", "150", "d");
    lattice->change_lattice("74", "74", "c");
    lattice->change_lattice("74", "75", "c");
    lattice->change_lattice("74", "73", "c");
    lattice->change_lattice("75", "74", "c");
    lattice->change_lattice("75", "75", "c");
    lattice->change_lattice("75", "73", "c");
    lattice->change_lattice("73", "74", "c");
    lattice->change_lattice("73", "75", "c");
    lattice->change_lattice("73", "73", "c");

    for (int i = 0; i < lattice->get_dimension(); ++i)
    {
        for (int j = 0; j < lattice->get_dimension(); ++j)
        {
            QCOMPARE('c', lattice->get_cell(i, j).get_strategy());
        }
    }
}
void TestGeneticAlgorithm::test_change_cell4()
{
    lattice->change_lattice("0", "0", "d");

    for (int i = 0; i < lattice->get_dimension(); ++i)
    {
        for (int j = 0; j < lattice->get_dimension(); ++j)
        {
            if ( (i == 0 && j == 0) || ((i == 73 || i == 74 || i == 75) && (j == 73 || j == 74 || j == 75) ))
            {
                QCOMPARE('d', lattice->get_cell(i, j).get_strategy());
            }
            else
            {
                QCOMPARE('c', lattice->get_cell(i, j).get_strategy());
            }
        }
    }
}

void TestGeneticAlgorithm::test_change_cell5()
{
    lattice->change_lattice("74", "74", "d");

    for (int i = 0; i < lattice->get_dimension(); ++i)
    {
        for (int j = 0; j < lattice->get_dimension(); ++j)
        {
            if ((i == 73 || i == 74 || i == 75) && (j == 73 || j == 74 || j == 75))
            {
                QCOMPARE('d', lattice->get_cell(i, j).get_strategy());
            }
            else
            {
                QCOMPARE('c', lattice->get_cell(i, j).get_strategy());
            }
        }
    }
}

void TestGeneticAlgorithm::test_change_dimension1()
{
    lattice->set_dimension("200");

    QCOMPARE("200", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}

void TestGeneticAlgorithm::test_change_dimension2()
{
    lattice->set_dimension("250");

    QCOMPARE("250", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}

void TestGeneticAlgorithm::test_change_dimension3()
{
    lattice->set_dimension("test");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}

void TestGeneticAlgorithm::test_change_dimension4()
{
    lattice->set_dimension("0");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}

void TestGeneticAlgorithm::test_change_dimension5()
{
    lattice->set_dimension("-20");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}


void TestGeneticAlgorithm::test_change_t1()
{
    lattice->set_t("12");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("12", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}

void TestGeneticAlgorithm::test_change_t2()
{
    lattice->set_t("test");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_t3()
{
    lattice->set_t("1");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("1", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_t4()
{
    lattice->set_t("0");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_t5()
{
    lattice->set_t("-1");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}

void TestGeneticAlgorithm::test_change_e1()
{
    lattice->set_e("0.5");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0.5", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_e2()
{
    lattice->set_e("test");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_e3()
{
    lattice->set_e("0");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_e4()
{
    lattice->set_e("-0.5");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("-0.5", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_e5()
{
    lattice->set_e("1");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("1", lattice->get_e());
}

void TestGeneticAlgorithm::test_change_b1()
{
    lattice->set_b("0.5");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("0.5", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_b2()
{
    lattice->set_b("test");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1.65", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_b3()
{
    lattice->set_b("0");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("0", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_b4()
{
    lattice->set_b("-0.5");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("-0.5", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}
void TestGeneticAlgorithm::test_change_b5()
{
    lattice->set_b("1");

    QCOMPARE("150", lattice->get_dimension());
    QCOMPARE("64", lattice->get_t());
    QCOMPARE("1", lattice->get_b());
    QCOMPARE("0", lattice->get_e());
}

QTEST_APPLESS_MAIN(TestGeneticAlgorithm)

#include "tst_geneticalgorithm.moc"
