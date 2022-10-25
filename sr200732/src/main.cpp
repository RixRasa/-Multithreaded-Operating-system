//
// Created by os on 8/13/22.
//
#include "../h/riscv.hpp"
#include "../h/syscall_c.h"
#include "../h/print.hpp"
#include "../h/ccb.hpp"
#include "../h/Console.hpp"
#include "userMain.cpp"

//#include "../h/Threads_C_API_test.hpp"
//#include "../h/ConsumerProducer_C_API_test.h"
//#include "../h/Threads_CPP_API_test.hpp"
//#include "../h/ConsumerProducer_CPP_API_test.hpp"
#include "../h/ConsumerProducer_CPP_Sync_API_test.hpp"
int main(){



    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
    //Riscv::ms_sstatus(Riscv::SSTATUS_SIE);

    thread_t* handle1 = new thread_t;
    thread_create(handle1,nullptr, nullptr);
    CCB::running = *handle1;

    thread_t* handle2 = new thread_t;
    thread_create(handle2,userMain, nullptr);

    while(!((*handle1)->isFinished())){
        thread_dispatch();
    }
    /*thread_t* handle2 = new thread_t;
    thread_create(handle2,Console::KontrolorPutc, nullptr);
    (*handle2)->sis = 1;
    //Riscv::ms_sstatus(Riscv::SSTATUS_SIE);*/

    //producerConsumer_C_API();
    //Threads_C_API_test();
    //Threads_CPP_API_test();
    //ConsumerProducerCPP::testConsumerProducer();
    //producerConsumer_CPP_Sync_API();

    printString("\nFInished\n");
    Riscv::mc_sstatus(Riscv::SSTATUS_SIE);

    return 0;
}