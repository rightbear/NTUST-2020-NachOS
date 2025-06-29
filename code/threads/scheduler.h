// scheduler.h 
//	Data structures for the thread dispatcher and scheduler.
//	Primarily, the list of threads that are ready to run.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "copyright.h"
#include "list.h"
#include "thread.h"
#include <list>

// The following class defines the scheduler/dispatcher abstraction -- 
// the data structures and operations needed to keep track of which 
// thread is running, and which threads are ready but not running.

enum SchedulerType {
    RR,     // Round Robin
    SJF,
    Priority,
	FIFO,
    SRTF
};

class sleepList {
    public:
        sleepList():_current_interrupt(0) {};
        void PutToSleep(Thread *t, int x);
    bool PutToReady();
    bool IsEmpty();
    private:
        class sleepThread {
            public:
                sleepThread(Thread* t, int x):
                    sleeper(t), when(x) {};
                Thread* sleeper;
                int when;
        };
    int _current_interrupt;
    std::list<sleepThread> _threadlist;
};

class Scheduler {
  public:
	Scheduler();		// Initialize list of ready threads 
	Scheduler(SchedulerType type);
	~Scheduler();				// De-allocate ready list

	void ReadyToRun(Thread* thread);	
    					// Thread can be dispatched.
	Thread* FindNextToRun();	// Dequeue first thread on the ready 
					// list, if any, and return thread.
	void Run(Thread* nextThread, bool finishing);
	    				// Cause nextThread to start running
	void CheckToBeDestroyed();	// Check if thread that had been
    					// running needs to be deleted
	void Print();			// Print contents of ready list
    	
    void setSchedulerType(SchedulerType t) {schedulerType = t;}
	SchedulerType getSchedulerType() {return schedulerType;}

    // SelfTest for scheduler is implemented in class Thread
    
  private:
	SchedulerType schedulerType;
	List<Thread *> *readyList;	// queue of threads that are ready to run,
					// but not running
	Thread *toBeDestroyed;		// finishing thread to be destroyed
    					// by the next thread that runs
};

#endif // SCHEDULER_H
