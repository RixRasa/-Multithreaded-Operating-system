//
// Created by os on 8/22/22.
//

#ifndef PROJECT_BASE_SEMAPHORE_HPP
#define PROJECT_BASE_SEMAPHORE_HPP

#include "ccb.hpp"
class Semaphore{

    explicit Semaphore(int init){
       this->value = init;

    }

    int value = 0;
    int desilaSegreska = 0;
    //potrebno za blokiranje
    void *operator new(size_t size);
    void *operator new[](size_t size);
    void operator delete(void *p) noexcept;
    void operator delete[](void *p) noexcept;

    List<CCB> blockQueue;
public:
    static Semaphore* open(int init);

    int close();
    int waitt();
    int signall();
};
#endif //PROJECT_BASE_SEMAPHORE_HPP
