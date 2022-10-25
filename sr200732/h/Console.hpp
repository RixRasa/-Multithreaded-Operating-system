//
// Created by os on 8/24/22.
//
/*
#ifndef PROJECT_BASE_CONSOLE_HPP
#define PROJECT_BASE_CONSOLE_HPP
#include "../lib/hw.h"
#include "memAlloc.hpp"
#include "syscall_c.h"
#include "semaphore.hpp"


class Console
{
public:
    void putc(char c);
    char getc();

    Semaphore* jelMozeDaSeUzmePUTC;
    Semaphore* jelMozeDaSeStaviPUTC;
    Semaphore* jelMozeDaSeUzmeGETC;


    static Console* getInstance();
    static Console* konzola;

    char getcNiz[256];
    int tailGet = 0;
    int headGet = 0;
    int capGet = 256;
    int getCNizBrojac = 0;

    char putcNiz[256];
    int tailPut = 0;
    int headPut = 0;
    int capPut = 256;

    int velicinaNizova = 256;

    void *operator new(size_t size);
    //void *operator new[](size_t size);
    void operator delete(void *p) noexcept;
    //void operator delete[](void *p) noexcept;

    static void KontrolorPutc(void*);



private:
    //SegDesc* headFree;

    //static uint64 firstTime

};



#endif //PROJECT_BASE_CONSOLE_HPP
*/