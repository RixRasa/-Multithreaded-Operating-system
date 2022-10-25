//
// Created by os on 8/23/22.
//

#ifndef PROJECT_BASE_SYSCALL_CPP_HPP
#define PROJECT_BASE_SYSCALL_CPP_HPP
#include "syscall_c.h"
#include "scheduler.hpp"
#include "ccb.hpp"

//OPERATOR
void* operator new (size_t n);
void operator delete (void* p) noexcept;


//NITI
class Thread {
public:

    static void wrapper(void* a);

    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();

    int start ();

    static void dispatch ();
    //static int sleep (time_t);
protected:
    Thread ();
    virtual void run () {}

private:
    thread_t myHandle;
};



//SEMAFORI
class Semaphore {
public:
    Semaphore (unsigned init = 1);

    virtual ~Semaphore ();
    int wait ();

    int signal ();
private:
    sem_t myHandle;
};
/*
class PeriodicThread : public Thread {
protected:
    PeriodicThread (time_t period);
    virtual void periodicActivation () {}
};
*/
class Console {
public:
    static char getc (){
        return __getc();
    }

    static void putc (char c){
        __putc(c);
    }

};
#endif //PROJECT_BASE_SYSCALL_CPP_HPP

