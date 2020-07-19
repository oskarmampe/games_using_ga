#include "LatticeThread.h"

LatticeThread::LatticeThread(LatticeQObject* new_lattice)
{
    lattice = new_lattice;
}

void LatticeThread::run()
{
    lattice->simulate();
}
