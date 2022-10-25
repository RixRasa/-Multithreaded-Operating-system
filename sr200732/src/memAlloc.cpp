//
// Created by os on 8/21/22.
//
#include "../h/memAlloc.hpp"

//Definisanje statickih podataka i funkcija
//uint64 MemoryAllocator::firstTime = 0;
MemoryAllocator* MemoryAllocator::memalloc = nullptr;

//GET INSTANCE FUNKCIJA ZA SINGLTON
MemoryAllocator* MemoryAllocator::getInstance() {
    if(MemoryAllocator::memalloc == nullptr){ //Prvi put instanciras
        memalloc = (MemoryAllocator *) HEAP_START_ADDR;

        memalloc->headFree = (SegDesc*)((char*)HEAP_START_ADDR + sizeof(MemoryAllocator));
        memalloc->headFree->sizeBajt = (char*)HEAP_END_ADDR - ((char*)memalloc->headFree + sizeof(SegDesc)) + 1;
        memalloc->headFree->next = nullptr;
        memalloc->headFree->prev = nullptr;
    }
    return MemoryAllocator::memalloc;
}

//MEM_ALLOC FUNCKIJA
void* MemoryAllocator::memAlloc(uint64 sizeBlok) {
    size_t sizeBytes = sizeBlok * MEM_BLOCK_SIZE; // izracunavamo koliko bajtova moramo da alociramo u odnosu na broj blokova koji moramo da alociramo

    //Trazenje bloka koji moze da zadovolji datu trazenu velicinu za alokaciju
    SegDesc* tmp = headFree;
    SegDesc* prev = nullptr;
    SegDesc* next = nullptr;
    for(;tmp != nullptr; tmp = tmp->next){
        prev = tmp->prev;
        next = tmp->next;
        if(tmp->sizeBajt >= sizeBytes){ break; }
    }

    //Ako se ne nadje nijedan blok koji zadovoljava velicinu alokacija nije uspela
    if(tmp == nullptr){
        //NEMOGUCA ALOKACIJA
        return nullptr;
    }

    //Sama alokacija dva slucaja: 1. Ostace dovoljno memorije(ceo blok) i parcacemo na dva dela 2.Nece ostati dovoljno memorije alciramo ceo segment
    size_t remainingSize = tmp->sizeBajt - sizeBytes;
    //Prvi slucaj: ostalo je dovoljno memorije parca se
    if(remainingSize >= sizeof(SegDesc) + MEM_BLOCK_SIZE){
        tmp->sizeBajt = sizeBytes;
        size_t offset = sizeof(SegDesc) + sizeBytes;

        SegDesc* newDesc = (SegDesc*)((char*)tmp + offset);
        newDesc->sizeBajt = remainingSize - sizeof(SegDesc);

        if(prev){
            prev->next = newDesc;
        }
        else{
            headFree = newDesc;
        }
        newDesc->prev = prev;

        if(next){
            next->prev = newDesc;
        }
        newDesc->next = next;
    }
        //Drugi slucaj: nije ostalo dovoljno memorije alocira se ceo blok
    else{
        if(prev) prev->next = next;
        else headFree = tmp->next;
        if(next) next->prev = prev;
    }
    tmp->next = nullptr;
    tmp->prev = nullptr;
    return (char*)tmp + sizeof(SegDesc);
}

//MEM_FREE + POMOCNA FUNKCIJA TRY TO JOIN
void Join(SegDesc* tmp){
    if(tmp == nullptr)
    {
        return;
    }
    SegDesc* next = tmp->next;
    if(tmp->next != nullptr && (char*)tmp + tmp->sizeBajt + sizeof(SegDesc) == (char*)(tmp->next)) { //provera dal se granicis i dal trebas da se spajas
        tmp->sizeBajt += tmp->next->sizeBajt + sizeof(SegDesc);
        tmp->next = tmp->next->next;
        if (tmp->next) tmp->next->prev = tmp;
        //Da li trebam next i prev od tmp->next-a da resim tj da ih stavim na null!!! BITNO POGLEDATI (DODATO)
        next->next = nullptr;
        next->prev = nullptr;
    }
}

//Greske su kada nista nije alocirano a dealocira se i kada se salje pogresna adresa za dealokaciju !!!!
int MemoryAllocator::memFree(void *addres) {
    SegDesc* blkFree = (SegDesc*)((char*)addres - sizeof(SegDesc));

    SegDesc* tmp = 0;
    if(!headFree || (char*)blkFree < (char*)headFree){
        tmp = 0;
    }
    else{
        for(tmp = headFree; tmp->next != nullptr && (char*)blkFree > (char*)(tmp->next); tmp=tmp->next );
    }

    blkFree->prev = tmp;
    if(tmp) blkFree->next = tmp->next;
    else blkFree->next = headFree;
    if(blkFree->next) blkFree->next->prev = blkFree;
    if(tmp) tmp->next = blkFree;
    else headFree = blkFree;

    Join(blkFree);
    Join(tmp);

    //OVO POGLEDAJ
    return 0;
}
