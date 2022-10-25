//
// Created by os on 8/5/22.
//

//
// Created by marko on 20.4.22..
//

#include "../h/semaphore.hpp"
#include "../h/print.hpp"
#include "../lib/console.h"
#include "../h/Console.hpp"

void Riscv::popSppSpie()
{

    __asm__ volatile ("csrw sepc, ra");
    __asm__ volatile ("sret");
}

typedef struct CCB* thread_t;
typedef struct Semaphore* sem_t;


void Riscv::handleSupervisorTrap()
{
    uint64 scause = r_scause(); //Ovo koristimo da bi nasli koji prekid/izuzetak/sistemski poziv se dogodilo

    uint64 typeOfCall;
    __asm__ volatile("mv %[typeOfCall], a0 " : [typeOfCall] "=r" (typeOfCall));



    // ECALL
    if(scause == 0x0000000000000009UL || scause == 0x0000000000000008UL)
    {
        uint64 volatile spc = r_sepc();//preskakanje na sledecu insturkciju kako ne bi ponovo zavrsili u "ecall-u"
        spc = spc +4;
        w_sepc(spc);
        uint64 volatile sstatus = r_sstatus();

        //ALOKACIJAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        //Alokacija Memorije
        if(typeOfCall == 1){
            uint64 sizeBlok;
            __asm__ volatile("mv %[sizeBlok], a1 " : [sizeBlok] "=r" (sizeBlok));

            MemoryAllocator* mem = MemoryAllocator::getInstance();
            void* adresa = (void*)mem->memAlloc(sizeBlok);

            //__asm__ volatile("mv a0, %[adresa]" : : [adresa] "r" (adresa));
            __asm__ volatile("sd %[adresa], 10*8(fp)": : [adresa] "r" (adresa));

        }

        //Dealokacija Memorije
        else if(typeOfCall == 2){
            void* adresa;
            __asm__ volatile("mv %[adresa], a1 " : [adresa] "=r" (adresa));

            MemoryAllocator* mem = MemoryAllocator::getInstance();
            int povVrednost = mem->memFree(adresa);

            //__asm__ volatile("mv a0, %[povVrednost]" : : [povVrednost] "r" (povVrednost));
            __asm__ volatile("sd %[povVrednost], 10*8(fp)": : [povVrednost] "r" (povVrednost));

        }


        //NITIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
        //thread_create
        else if(typeOfCall == 11){

            uint64 volatile spc = r_sepc();
            uint64 volatile sstatus = r_sstatus();
            thread_t* handle;
            void (*body) (void*);
            void* arg;
            //void* stack;
            __asm__ volatile("ld %[handle], 11*8(fp) " : [handle] "=r" (handle));
            __asm__ volatile("ld %[body], 12*8(fp) " : [body] "=r" (body));
            __asm__ volatile("ld %[arg], 13*8(fp) " : [arg] "=r" (arg));
            //__asm__ volatile("ld %[stack],14*8(fp) " : [stack] "=r" (stack));
            *handle = nullptr; //dodato
            *(handle) = CCB::createThread(body,arg);

            int result;
            if(*handle != nullptr){
                result = 0;
            } else{ result = -1; }

            //__asm__ volatile("mv a0,%[result] " : : [result] "r" (result));
            __asm__ volatile("sd %[result], 10*8(fp)": : [result] "r" (result));


            w_sstatus(sstatus);
            w_sepc(spc);

        }
        //thread_dispatch
        else if(typeOfCall == 13){


            CCB::dispatch();
            w_sstatus(sstatus);
            w_sepc(spc);


        }

        //thread_exit()
        else if(typeOfCall == 12){
            int rezultat = 0;
            rezultat = CCB::exit();
            w_sstatus(sstatus);
            w_sepc(spc);
            //__asm__ volatile("mv a0,%[rezultat] " : : [rezultat] "r" (rezultat));
            __asm__ volatile("sd %[rezultat], 10*8(fp)": : [rezultat] "r" (rezultat));

        }


        //SEMAFORIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
        //sem_open()
        else if(typeOfCall == 21){
            sem_t* handle;
            int init;
            __asm__ volatile("ld %[handle], 11*8(fp) " : [handle] "=r" (handle));
            __asm__ volatile("ld %[init], 12*8(fp) " : [init] "=r" (init));
            *handle = nullptr;
            *handle = Semaphore::open(init);
            int result;
            if(*handle != nullptr){
                result = 0;
            } else{
                result = -1;
            }

            //__asm__ volatile("mv a0,%[result] " : : [result] "r" (result));
            __asm__ volatile("sd %[result], 10*8(fp)": : [result] "r" (result));


        }

        //sem_close
        else if(typeOfCall == 22){
            sem_t handle;
            __asm__ volatile("ld %[handle], 11*8(fp) " : [handle] "=r" (handle));
            int result = handle->close();
            //__asm__ volatile("mv a0,%[result] " : : [result] "r" (result));
            __asm__ volatile("sd %[result], 10*8(fp)": : [result] "r" (result));
        }

        //sem_wait
        else if(typeOfCall == 23){
            sem_t handle;
            __asm__ volatile("ld %[handle], 11*8(fp) " : [handle] "=r" (handle));
            int result = handle->waitt();
            w_sstatus(sstatus);
            w_sepc(spc);
            //__asm__ volatile("mv a0,%[result] " : : [result] "r" (result));
            __asm__ volatile("sd %[result], 10*8(fp)": : [result] "r" (result));
        }

        //sem_signal
        else if(typeOfCall == 24){
            sem_t handle;
            __asm__ volatile("ld %[handle], 11*8(fp) " : [handle] "=r" (handle));
            int result = handle->signall();
            //__asm__ volatile("mv a0,%[result] " : : [result] "r" (result));
            __asm__ volatile("sd %[result], 10*8(fp)": : [result] "r" (result));
        }
        /*
        else if(typeOfCall == 50){
            Riscv::mc_sstatus(Riscv::SSTATUS_SPP);
        }*/


        //KONZOLAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
        //getC
        else if(typeOfCall == 41){
            /*
            Console* k = Console::getInstance();
            char result = k->getc();
            w_sstatus(sstatus);
            w_sepc(spc);
            //__asm__ volatile("mv a0,%[result] " : : [result] "r" (result));
            __asm__ volatile("sd %[result], 10*8(fp)": : [result] "r" (result));
             */

        }

        //putC
        else if(typeOfCall == 42){
            /*
            char handle;
            __asm__ volatile("ld %[handle], 11*8(fp) " : [handle] "=r" (handle));
            Console* k = Console::getInstance();

            k->putc(handle);
            w_sstatus(sstatus);
            w_sepc(spc);
            //__asm__ volatile("mv a0,%[result] " : : [result] "r" (result));
            */

        }


    }
    else if (scause == 0x8000000000000001UL)
    {
        mc_sip(SIP_SSIP);
        /*
        //printInteger(1);
        // interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)
        mc_sip(SIP_SSIP);

        CCB::timeSliceCounter++;
        if (CCB::timeSliceCounter >= CCB::running->getTimeSlice())
        {
            //printInteger(2);
            uint64 volatile sepc = r_sepc();
            uint64 volatile sstatus = r_sstatus();
            CCB::timeSliceCounter = 0;
            CCB::dispatch();
            w_sstatus(sstatus);
            w_sepc(sepc);
        }
*/

    }
    else if (scause == 0x8000000000000009UL)
    {
        /*
        // interrupt: yes; cause code: supervisor external interrupt (PLIC; could be keyboard)
        //console_handler();
        int plicClm = plic_claim();

        //konzola poslala prekid
        if(plicClm == 10){


            while((*((char*)CONSOLE_STATUS) & CONSOLE_RX_STATUS_BIT) == 1){
                //printInteger(2);
                printInteger(1);
                Console* konzola = Console::getInstance();
                //ako je Niz koji sluzi za getC pun


                    char* CharKontroler = (char*) CONSOLE_RX_DATA;
                    konzola->getcNiz[konzola->tailGet] = *CharKontroler;  //stavili smo char
                    konzola->tailGet = (konzola->tailGet + 1) % konzola->capGet;
                    __putc(*CharKontroler);
                    konzola->jelMozeDaSeUzmeGETC->signall();// povecali smo broj charova
                    if(konzola->tailGet == 0) {
                        break;
                    }


            }
            plic_complete(plicClm);
        }
         */
        console_handler();
    }
    else{
        /*printInteger(r_scause());
        printString("\n");
        printInteger(r_sepc());
        printString("\n");
        printInteger(r_stval());
        printString("\n");*/
    }
}