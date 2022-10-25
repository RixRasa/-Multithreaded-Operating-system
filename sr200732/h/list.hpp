//
// Created by os on 8/4/22.
//

#ifndef CONTEXT_SWITCH_LIST
#define CONTEXT_SWITCH_LIST
#include "memAlloc.hpp"
#include "print.hpp"
template<typename T>
class List
{
public:
    void *operator new(size_t size);
    void *operator new[](size_t size);
    void operator delete(void *p) noexcept;
    void operator delete[](void *p) noexcept;
private:

    struct Elem
    {
        T *data;
        Elem *next;

        Elem(T *data, Elem *next) : data(data), next(next) {}
        void *operator new(size_t size);
        void *operator new[](size_t size);
        void operator delete(void *p) noexcept;
        void operator delete[](void *p) noexcept;
    };

    Elem *head, *tail;

public:
    List() : head(0), tail(0) {}

    List(const List<T> &) = delete;

    List<T> &operator=(const List<T> &) = delete;

    void addFirst(T *data)
    {
        Elem *elem = new Elem(data, head);
        head = elem;
        if (!tail) { tail = head; }
    }

    void addLast(T *data)
    {
        Elem *elem = new Elem(data, 0);
        if (tail)
        {
            tail->next = elem;
            tail = elem;
        } else
        {
            head = tail = elem;
        }
    }

    T *removeFirst()
    {
        if (!head) { return 0; }

        Elem *elem = head;
        head = head->next;
        if (!head) { tail = 0; }

        T *ret = elem->data;
        delete elem;
        return ret;
    }

    T *peekFirst()
    {
        if (!head) { return 0; }
        return head->data;
    }

    T *removeLast()
    {
        if (!head) { return 0; }

        Elem *prev = 0;
        for (Elem *curr = head; curr && curr != tail; curr = curr->next)
        {
            prev = curr;
        }

        Elem *elem = tail;
        if (prev) { prev->next = 0; }
        else { head = 0; }
        tail = prev;

        T *ret = elem->data;
        delete elem;
        return ret;
    }

    T *peekLast()
    {
        if (!tail) { return 0; }
        return tail->data;
    }
};

//OPERATORI LIST
template<typename T>
void *List<T>::operator new(size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }
    void* vracen0 = MemoryAllocator::memalloc->memAlloc(blok);
    printInteger(3);
    return vracen0;
}

template<typename T>
void *List<T>::operator new[](size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }
    return MemoryAllocator::memalloc->memAlloc(blok);
}

template<typename T>
void List<T>::operator delete(void* p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}

template<typename T>
void List<T>::operator delete[](void* p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}


template<typename T>
void *List<T>::Elem::operator new(size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }
    return MemoryAllocator::memalloc->memAlloc(blok);
}

template<typename T>
void *List<T>::Elem::operator new[](size_t size) {
    uint blok = size / 64;
    if(size % 64 != 0){
        blok++;
    }
    return MemoryAllocator::memalloc->memAlloc(blok);
}

template<typename T>
void List<T>::Elem::operator delete(void *p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}

template<typename T>
void List<T>::Elem::operator delete[](void *p) noexcept {
    MemoryAllocator::memalloc->memFree(p);
}




#endif //PROJECT_BASE_LIST_HPP
