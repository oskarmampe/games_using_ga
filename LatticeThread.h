#ifndef LATTICETHREAD_H
#define LATTICETHREAD_H
#include <QThread>
#include "latticeqobject.h"

class LatticeThread : public QThread {
    public:
        LatticeThread(LatticeQObject*);
        void run();
    private:
        LatticeQObject* lattice;
};

#endif // LATTICETHREAD_H
