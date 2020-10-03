#include <thread>
#include "ThreadedGrid.h"

ThreadedGrid::ThreadedGrid()
    : NumberGrid()
{
}

ThreadedGrid::ThreadedGrid(const int &height, const int &width)
    : NumberGrid(height, width)
{
}

ThreadedGrid::~ThreadedGrid()
{
}

void ThreadedGrid::calculateAllNumbers()
{
    unsigned int max_threads = std::thread::hardware_concurrency();
    int size = this->getHeight() / max_threads;
    for (int i = 0; i < this->getHeight(); i += size)
    {
        Task t;
        t.start = i;
        t.end = i + size - 1;

        this->mTasks.push_back(t);
    }

    std::vector<std::thread> threads;
    for (unsigned int i = 0; i < max_threads; i++)
    {
        threads.push_back(std::thread(&ThreadedGrid::worker, this));
    }

    for (unsigned int i = 0; i < max_threads; i++)
    {
        threads[i].join();
    }
}

void ThreadedGrid::worker()
{
    std::vector<Task> my_tasks;
    while (!this->mTasks.empty())
    {
        my_tasks.clear();
        this->mTasks.pop_back(my_tasks, 1);

        if (my_tasks.size() > 0)
        {
            for (int row = my_tasks[0].start; row <= my_tasks[0].end; row++)
            {
                for (int col = 0; col < this->getWidth(); col++)
                {
                    this->setNumber(row, col, calculateNumber(row, col));
                }
            }
        }
    }
}
