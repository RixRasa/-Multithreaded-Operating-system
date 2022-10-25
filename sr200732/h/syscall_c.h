//
// Created by os on 8/7/22.
//

#ifndef PROJECT_BASE_SYSCALL_C_H
#define PROJECT_BASE_SYSCALL_C_H

#include "../lib/hw.h"
#include "../lib/console.h"

//Alokacija
void* mem_alloc(size_t size);
int mem_free(void* adresa); //NE VRACA GRESKE MOZE DA SE NAMESTI SA JOS JEDNOM STRUKTUROM ALOCIRANIH

//Niti
typedef struct CCB* thread_t;
int thread_create(thread_t* handle, void(*start_routine)(void*), void* arg); //GReske moguce pri alokaciji samoj i alokaciji steka to je reseno ali greska pri Scheduler::put()
void thread_dispatch(); // nema nacina da se vrati greska gucii smo
int thread_exit(); // Moze doci do greske zbog alokacije u scheduler::put(); ..... mozda ima sanse i Scheduler::get() da bude greska ako vrati nullptr ali mislim da bas nije moguce

//Semafori
typedef struct Semaphore* sem_t;
int sem_open(sem_t* handle, unsigned init); //pokrivene greske pri mogucoj alokaciji  ..... //OVDE TAKODJE INICIJALIZUJEM NEW LIST TO MOZE MZD DA PREOPTERETI MEMORIJU
int sem_close(sem_t handle);
int sem_wait(sem_t id);
int sem_signal(sem_t id); //Moze doci do greske zbog alokacije u scheduler::put()

//Console
//const int EOF = -1;
void putc(char); //Nema gresaka
char getc(); // ima greske al ne znam kako

/*
//Niti FINAL BOSS
//typedef  unsigned long time_t;   //ovo vljd ima u hw.h
int time_sleep(time_t);
*/

//void prebaciUkorisnicki();
#endif //PROJECT_BASE_SYSCALL_C_H






