//
// Created by os on 8/5/22.
//

#ifndef PROJECT_BASE_SCHEDULER_HPP
#define PROJECT_BASE_SCHEDULER_HPP
#include "list.hpp"


class CCB;

class Scheduler
{
private:
    void *operator new(size_t size);
    void *operator new[](size_t size);
    void operator delete(void *p) noexcept;
    void operator delete[](void *p) noexcept;
    static List<CCB> readyCoroutineQueue;

public:
    static CCB* get();

    static void put(CCB* ccb);
};


#endif //PROJECT_BASE_SCHEDULER_HPP
