//
// Created by os on 8/5/22.
//
#include "../h/scheduler.hpp"

List <CCB> Scheduler::readyCoroutineQueue ;

CCB* Scheduler::get() {
    return readyCoroutineQueue.removeFirst();
}

void Scheduler::put(CCB *ccb) {
    readyCoroutineQueue.addLast(ccb);
}

void *Scheduler::operator new(size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }

    return MemoryAllocator::memalloc->memAlloc(blok);
}

void *Scheduler::operator new[](size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }
    return MemoryAllocator::memalloc->memAlloc(blok);
}

void Scheduler::operator delete(void *p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}
void Scheduler::operator delete[](void *p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}