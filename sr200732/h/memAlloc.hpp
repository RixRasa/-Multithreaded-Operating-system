//
// Created by os on 8/7/22.
//

#ifndef PROJECT_BASE_MEMALLOC_HPP
#define PROJECT_BASE_MEMALLOC_HPP
#include "../lib/hw.h"

//Struktura SegmendDeskriptora
struct SegDesc{
    SegDesc* next;
    SegDesc* prev;
    size_t sizeBajt;
};


//Klasa MemoryAllocator
class MemoryAllocator
{
public:
    void* memAlloc(uint64 sizeBlok);
    int memFree(void* addres);

    static MemoryAllocator* getInstance();
    static MemoryAllocator* memalloc;
private:
    SegDesc* headFree;

    //static uint64 firstTime

};



#endif //PROJECT_BASE_MEMALLOC_HPP
