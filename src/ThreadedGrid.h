#include "NumberGrid.h"
#include "ThreadedVector.h"

class Task
{
public:
    int start;
    int end;
};

class ThreadedGrid : public NumberGrid
{
public:
    // The default constructor. Leaves the task queue empty, and lets the parent class default constructor set values for its data members.
    ThreadedGrid();
    // Leaves the task queue empty, and passes the parameters on to the parent class constructor.
    ThreadedGrid(const int &height, const int &width);
    // Empty, but required destructor.
    virtual ~ThreadedGrid();
    // Overrides the method of the parent class. Uses the worker method in several threads to do the work. Be sure to manage the task queue, and clean up the threads when they have finished. Use the thread library to decide how many threads to launch, based on the capacity of the computer.
    virtual void calculateAllNumbers();
    // As long as tasks are available in the task queue, get one, and complete it.
    virtual void worker();

private:
    ThreadedVector<Task> mTasks;
};