#include "LatticeThread.h"

/**
 *
 * Lattice thread constructor, requires a lattice to simulate.
 *
 * @brief LatticeThread::LatticeThread
 * @param new_lattice
 */
LatticeThread::LatticeThread(LatticeQObject* new_lattice)
{
    lattice = new_lattice;
}

/**
 *
 * Run the simulation
 *
 * @brief LatticeThread::run
 */
void LatticeThread::run()
{
    lattice->simulate();
}
