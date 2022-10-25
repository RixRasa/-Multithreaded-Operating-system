//
// Created by os on 8/9/22.
//

#include "../h/ccb.hpp"

uint64 CCB::timeSliceCounter = 0;
CCB *CCB::running = nullptr;

void CCB::dispatch()
{
    CCB *old = running;
    if (!old->isFinished()) { Scheduler::put(old); }
    running = Scheduler::get();
    /*if(running->sis == 1){
        Riscv::ms_sstatus(Riscv::SSTATUS_SPP);
    }
    if(running->sis == 0){
        Riscv::mc_sstatus(Riscv::SSTATUS_SPP);
    }*/
    CCB::contextSwitch(&(old->context), &(running->context));

}

CCB *CCB::createThread(void (*body)(void *) , void *arg) {
    CCB* novo = new CCB(body,arg);
    if(novo->lose == 1){
        return nullptr;
    }
    return novo;
}

void CCB::startFunction(void *arg) {

    Riscv::popSppSpie();

    running->body(running->arg);
    running->setFinished(true);
    thread_dispatch();
}

void *CCB::operator new(size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }

    return MemoryAllocator::memalloc->memAlloc(blok);
}

void *CCB::operator new[](size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }
    return MemoryAllocator::memalloc->memAlloc(blok);
}

void CCB::operator delete(void *p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}
void CCB::operator delete[](void *p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}

int CCB::exit() {
    //GRESKA SE VRACA KADA NE USPE ALOKACIJA PUTA ILI DEALOKACIJA GETA
    CCB *old = running;
    old->setFinished(true);
    if (!old->isFinished()) { Scheduler::put(old); }
    running = Scheduler::get();
    /*if(running->sis == 1){
        Riscv::ms_sstatus(Riscv::SSTATUS_SPP);
    }
    if(running->sis == 0){
        Riscv::mc_sstatus(Riscv::SSTATUS_SPP);
    }*/
    CCB::contextSwitch(&(old->context), &(running->context));
    return 0;

}



