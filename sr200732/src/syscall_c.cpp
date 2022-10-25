//
// Created by os on 8/16/22.
//
#include "../h/syscall_c.h"


//ALOKACIJAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
void* mem_alloc(size_t size){
    //Izracunavanje broja blokova kojih moramo da zauzmemo

    uint64 sizeBajt = size;
    uint64 sizeBlok = 0;
    if(sizeBajt % MEM_BLOCK_SIZE == 0){
        sizeBlok = sizeBajt/MEM_BLOCK_SIZE;
    }
    else{
        sizeBlok = sizeBajt/MEM_BLOCK_SIZE + 1;
    }

    //Upisivanje potrebnih argumenata i Poziv sistemskog poziva
    __asm__ volatile("li a0,1 \n\t"
                     "mv a1, %[sizeBlok]"
            :
            : [sizeBlok] "r" (sizeBlok));

    __asm__ ("ecall");

    uint64 adresa;
    __asm__ volatile("mv %[adresa], a0 " : [adresa] "=r" (adresa)); //Premestanje vrednosti iz a0 u promenljivu 'adresa'

    return (void*) adresa; //Vracanje vrednosti
}

int mem_free(void* adresa){
    //Upisivanje potrebnih argumenata i Poziv sistemskog poziva
    __asm__ volatile("mv a1,a0 \n\t"
                     "li a0,2 \n\t"
                     "ecall");

    int i = 0;
    __asm__ volatile("mv %[i], a0 " : [i] "=r" (i)); //Premestanje vrednosti iz a0 u promenljivu 'i'

    return i;
}


//NITIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
int thread_create(thread_t* handle, void(*start_routine)(void*), void* arg){
    /*uint64* stack;
    void* volatile stackPointer = 0;
    //Alociranje steka
    if(start_routine != nullptr){
        stack = new uint64[DEFAULT_STACK_SIZE];
        stackPointer = (void*) &stack[DEFAULT_STACK_SIZE];
    }
    else{
        stack = nullptr;
        stackPointer = nullptr;
    }*/
    __asm__ volatile(
            "mv a3,a2 \n\t"
            "mv a2,a1 \n\t"
            "mv a1,a0 \n\t"
            "li a0,11 \n\t"
            );

    /*__asm__ volatile("mv a4, %[stackPointer]"
            :
            : [stackPointer] "r" (stackPointer));*/

    __asm__ volatile("ecall");

    int i = 0;
    __asm__ volatile("mv %[i], a0 " : [i] "=r" (i)); //Premestanje vrednosti iz a0 u promenljivu 'i'

    return i;
}

void thread_dispatch(){

    __asm__ volatile("li a0,13 \n\t"
                     "ecall");
}

int thread_exit(){
    __asm__ volatile("li a0,12 \n\t"
                     "ecall");

    int i = 0;
    __asm__ volatile("mv %[i], a0 " : [i] "=r" (i)); //Premestanje vrednosti iz a0 u promenljivu 'i'

    return i;
}


//SEMAFORIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
int sem_open(sem_t* handle, unsigned init){

    __asm__ volatile("mv a2,a1 \n\t"
                     "mv a1, a0 \n\t"
                     "li a0, 21 \n\t"
                     "ecall");

    int i = 0;
    __asm__ volatile("mv %[i], a0 " : [i] "=r" (i)); //Premestanje vrednosti iz a0 u promenljivu 'i'

    return i;
}
int sem_close(sem_t handle){

    __asm__ volatile("mv a1, a0 \n\t"
                     "li a0, 22\n\t"
                     "ecall");


    int i = 0;
    __asm__ volatile("mv %[i], a0 " : [i] "=r" (i)); //Premestanje vrednosti iz a0 u promenljivu 'i'

    return i;
}
int sem_wait(sem_t id){

    __asm__ volatile("mv a1, a0 \n\t"
                     "li a0, 23 \n\t"
                     "ecall");

    int i = 0;
    __asm__ volatile("mv %[i], a0 " : [i] "=r" (i)); //Premestanje vrednosti iz a0 u promenljivu 'i'

    return i;
}
int sem_signal(sem_t id){

    __asm__ volatile("mv a1, a0 \n\t"
                     "li a0, 24\n\t"
                     "ecall");

    int i = 0;
    __asm__ volatile("mv %[i], a0 " : [i] "=r" (i)); //Premestanje vrednosti iz a0 u promenljivu 'i'

    return i;
}

//KONZOLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//PUTC
void putc(char c){
    /*
    __asm__ volatile("mv a1, a0 \n\t"
                     "li a0, 42\n\t"
                     "ecall");
*/
    __putc(c);
}

char getc(){
/*
    __asm__ volatile("li a0, 41\n\t"
                     "ecall");
    char i = 0;
    __asm__ volatile("mv %[i], a0 " : [i] "=r" (i)); //Premestanje vrednosti iz a0 u promenljivu 'i'

    return i;
*/
    return __getc();
}


/*
void prebaciUkorisnicki(){
    __asm__ volatile("li a0, 50\n\t"
                     "ecall");
}
*/