//
// Created by os on 8/22/22.
//


#include "../h/semaphore.hpp"



Semaphore* Semaphore::open(int init) {
    Semaphore* novi= new Semaphore(init);

    return novi;
}

int Semaphore::close() {
    while(this->blockQueue.peekFirst() != nullptr){
        this->desilaSegreska = 1;
        CCB* backToReality = this->blockQueue.removeFirst();
        Scheduler::put(backToReality);
    }

    return 0;
}
int Semaphore::waitt() {
    if(this->value <= 0){

        this->value--;
        CCB* old = CCB::running;
        this->blockQueue.addLast(old);

        old->setFinished(true);

        CCB::dispatch();
    }
    else{
        this->value--;
    }
    if(this->desilaSegreska == 1){
        return -1;
    }
    else{
        return 0;
    }

}

int Semaphore::signall() {
    if(this->value < 0){
        CCB* backToReality = this->blockQueue.removeFirst();
        backToReality->setFinished(false);
        Scheduler::put(backToReality);
        this->value++;
    }
    else{
        this->value++;
    }
    return 0;
}




void *Semaphore::operator new(size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }

    return MemoryAllocator::memalloc->memAlloc(blok);
}

void *Semaphore::operator new[](size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }
    return MemoryAllocator::memalloc->memAlloc(blok);
}

void Semaphore::operator delete(void *p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}
void Semaphore::operator delete[](void *p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}


