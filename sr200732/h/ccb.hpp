//
// Created by os on 8/9/22.
//

#ifndef PROJECT_BASE_CCB_HPP
#define PROJECT_BASE_CCB_HPP

#include "../h/scheduler.hpp"
#include "../lib/hw.h"
#include "../h/syscall_c.h"
#include "../h/riscv.hpp"
#include "../h/print.hpp"



class CCB {

public:

    int sis = 0;

    struct Context
    {
        uint64 ra;
        uint64 sp;
    };

    //Funckija koja se koristi za thread create
    static CCB* createThread(void(*body)(void*), void* arg);

    //Funkcija koja se koristi za thread_dispatch
    static void dispatch();

    //Funkcija koja se koristi za thread_exit()
    static int exit();


    static void contextSwitch(Context *, Context *);
    uint64* stack;
    static CCB* running;
    static uint64 timeSliceCounter;

    uint64 getTimeSlice() const { return timeSlice; }
    bool isFinished() const{ return finished;}
    void setFinished(bool finished) {this->finished = finished;}

    void *operator new(size_t size);
    void *operator new[](size_t size);
    void operator delete(void *p) noexcept;
    void operator delete[](void *p) noexcept;

    int lose = 0;

    Context context;
private:
    //Konstruktor koristi se za thread_create() sistemski poziv
    CCB(void (*body)(void *) , void *arg)
    {
        this->body = body;
        this->arg = arg;
        //Stack
        if(this->body != nullptr){
            uint64 blokSize = (DEFAULT_STACK_SIZE * 8) / 64;
            stack = (uint64*)MemoryAllocator::memalloc->memAlloc(blokSize);
            if(stack == nullptr){
                lose = 1;
            }
        }
        else{
            stack = nullptr;
        }
        //Context
        if(body != nullptr){
            this->context.ra = (uint64) &startFunction;
        }
        else{
            this->context.ra = 0;
        }
        if(stack != nullptr){
            this->context.sp = (uint64) &stack[DEFAULT_STACK_SIZE];
        }
        else{
            this->context.sp = 0;
        }
        //finished
        this->finished = false;


        //GRESKA JE TAKODJE AKO PUT NE USPE ALOKACIJU
        //if(this-> body != nullptr) { Scheduler::put(this); }

    }

    static void startFunction(void* arg);

    void (*body)(void*);
    void* arg;

    uint64 timeSlice = DEFAULT_TIME_SLICE;
    bool finished;
};


#endif //PROJECT_BASE_CCB_HPP
