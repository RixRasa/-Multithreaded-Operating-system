//
// Created by os on 8/24/22.
//
/*
#include "../h/Console.hpp"
#include "../lib/console.h"
Console* Console::konzola = nullptr;

void *Console::operator new(size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }

    return MemoryAllocator::memalloc->memAlloc(blok);
}


void Console::operator delete(void *p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}



Console *Console::getInstance() {
    if(Console::konzola == nullptr){
        Console::konzola =  new Console;
        konzola->jelMozeDaSeStaviPUTC = Semaphore::open(256);
        konzola->jelMozeDaSeUzmePUTC = Semaphore::open(0);
        konzola->jelMozeDaSeUzmeGETC = Semaphore::open(0);
        return konzola;

    }
    else{
        return Console::konzola;
    }

}

void Console::putc(char c) {

    this->jelMozeDaSeStaviPUTC->waitt();
    //__putc(c);
    this->putcNiz[tailPut] = c;
    tailPut = (tailPut + 1) % capPut;
    //printInteger(tailPut);

    this->jelMozeDaSeUzmePUTC->signall();


}

char Console::getc() {
    printInteger(4);
    char c;
    this->jelMozeDaSeUzmeGETC->waitt();
    //printInteger(4);
    c = konzola->getcNiz[konzola->headGet]; //stavili smo char
    konzola->headGet = (konzola->headGet + 1) % konzola->capGet;


    return c;
}

void Console::KontrolorPutc(void*) {

    Console* konzola = Console::getInstance();

    while((*((char*)CONSOLE_STATUS) & CONSOLE_TX_STATUS_BIT) == (1 << 5)){

        //Onda nema vise sta da se stavi iz buffer u konzolu
        konzola->jelMozeDaSeUzmePUTC->waitt();

        if((*((char*)CONSOLE_STATUS) & CONSOLE_TX_STATUS_BIT) != (1 << 5)){break;}

        char* c = (char*) CONSOLE_TX_DATA;
        *c = konzola->putcNiz[konzola->headPut];
        //__putc(*c);
        konzola->headPut = (konzola->headPut + 1) % konzola->capPut;

        konzola->jelMozeDaSeStaviPUTC->signall();

    }
}
*/