//
//  container.h
//  CCRender
//
//  Created by wenyang on 2023/11/21.
//

#ifndef container_h
#define container_h
#include <list>
#include <mutex>
#include <thread>
#include <atomic>
namespace cc {

template <typename T>
class queue:public std::list<T> {
    
public:
    
    queue(){
        
    }
    
    ~queue(){}
    
    void enqueue(T t){
        m_lock.lock();
        this->push_back(t);
        m_lock.unlock();
    }
    
    T dequeue(){
        
        m_lock.lock();
        auto t = this->front();
        this->pop_front();
        m_lock.unlock();
        return t;
    }
    T pop(){
        
        m_lock.lock();
        auto t = this->back();
        this->pop_back();
        m_lock.unlock();
        return t;
    }
    
    size_t size(){
        m_lock.lock();
        auto e = std::list<T>::size();
        m_lock.unlock();
        return e;
    }
    bool is_empty(){
        return size() > 0;
    }
    
    void lock_function(std::function<void(std::list<T>&)> callback){
        m_lock.lock();
        callback(*this);
        m_lock.unlock();
    }
private:
    std::mutex m_lock;
};

template<class T,bool once>
class runner;


template<class T,bool once>
class runner{
    
    std::atomic_bool m_close = false;
    
    std::atomic_int m_millseconds = 20;
    
    std::mutex mutx;
    
    std::thread* m_thread;
    
    std::function<void(runner&)> m_callback;
    
public:


    inline void sleep_millisec(int millseconds){
        std::this_thread::sleep_for(std::chrono::milliseconds(millseconds));
    }
    inline void sleep_nanosec(int nanoseconds){
        std::this_thread::sleep_for(std::chrono::nanoseconds(nanoseconds));
    }
    
    inline bool is_close(){
        bool close = m_close;
        
        return close;
    }
    inline void next_loop_sleep_millsseconds(int ms){
        m_millseconds = ms;
    }
    void run(){
        while(!m_close){
            mutx.lock();
            if(m_close){
                mutx.unlock();
                return;
            }else{
                m_callback(*this);
                mutx.unlock();
            }
            if(once){
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(m_millseconds));
        }
    }
    void close(){
        m_close = true;
        if(mutx.try_lock()){
            mutx.unlock();
        }
    }
    
    runner() {}
    
    runner(std::function<void(runner&)> callback):m_callback(callback){
        m_thread = new std::thread(&runner::run,this);
    }
    ~runner(){
        close();
        if(m_thread != nullptr){
            mutx.lock();
            if(m_thread->joinable()){
                m_thread->join();
            }
            delete m_thread;
            mutx.unlock();
        }
    }

};
};

#endif /* container_h */
