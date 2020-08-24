#ifndef LATTICETHREAD_H
#define LATTICETHREAD_H
#include <QThread>
#include "latticeqobject.h"
/**
 *
 * Lattice thread class. Used to be able to update the lattice, without blocking the main GUI thread.
 *
 * @brief The LatticeThread class
 */
class LatticeThread : public QThread {
    public:
        // QThread methods
        LatticeThread(LatticeQObject*);
        void run();
    private:
        // Pass the lattice to simulate
        LatticeQObject* lattice;
};

#endif // LATTICETHREAD_H
