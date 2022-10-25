//
// Created by os on 8/24/22.
//
#include "../h/syscall_cpp.hpp"

//NITIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
Thread::Thread(void (*body)(void *), void *arg) {
    thread_create(&myHandle,body,arg);
}

Thread::Thread() {
    thread_create(&myHandle,Thread::wrapper, this);
}
void Thread::wrapper(void * nit) {
    Thread* pokreci = (Thread *) nit;
    pokreci->run();
}

void Thread::dispatch() {
    thread_dispatch();
}

int Thread::start() {
    Scheduler::put(myHandle);
    return 0;
}

Thread::~Thread() {
    mem_free(this->myHandle->stack);
}


//SEMAFORIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
Semaphore::Semaphore(unsigned int init) {
    sem_open(&myHandle,init);
}

Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    sem_wait(myHandle);
    return 0;
}

int Semaphore::signal() {
    return sem_signal(myHandle);
    return 0;
}


void* operator new (size_t n){
    return mem_alloc(n);
}
void operator delete (void* p) noexcept{
    mem_free(p);
}


