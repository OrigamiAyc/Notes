# OS

## Process Management

### Process Concept & Operations

- Concepts

	- A program (an executable file) becomes process when it is loaded into memory
	- Process in Memory

		- Text section -- Codes
		- Stack -- Temp data
		- Heap
		- Data Section -- Global variables
		- Program Counter
		- Contents of Registers

	- Process State

		- New
		- Running
		- Waiting
		- Ready
		- Terminated

	- PCB

	  Inside kernel, processes are arranged as a doubly linked list, called the task list.

		- Process State
		- Program Counter

		  location of next instruction to execute

		- CPU Registers

		  contents of all process-centric registers

		- CPU Schedualing info

		  priorities, scheduling queue pointers

		- Mem-management info

		  memory allocated to the process

		- I/O Status info

		  I/O devices allocated to process, list of open files

		- Accounting info

		  CPU used, clock time elapsed since start, time limits

- Operations

	- System must provide...

		- Process identification

			- PID

		- Process creation

			- Prarent & Child

				- fork()

				  In kernal space:
				  Firstly, copying the PCB of the parent's, then update the content of the new PCB(like PID, running time, etc.). 
				  Finally, insert the PCB in the doubly link list as a node.
				  
				  In User space:
				  Copy all the data of the parent process in the memory.

				- Tree hierarchy

				  When a process becomes an orphan, the “init” process will become the step-mother of all orphans.
				  (re-parent operation)
				  Because of the re-parent operation, there is always only one process tree.

				- Cloned Items

					- Program Counter
					- Code
					- Memory
					- Opened files

				- Un-cloned Items

					- PID
					- Parent process
					- Running time
					- Return value

		- Process execution

			- exec*()

			  The process is changing the code that is executing and never returns to the original code.
			  
			  The process that calls any one of the member of the exec system call family will throw away many things, e.g.,
			  – Memory: local variables, global variables, and dynamically allocated memory;
			  – Register value: e.g., the program counter;
			  
			  But, the process will preserve something, including:
			  – PID;
			  – Process relationship;
			  – Running time, etc.

			- wait()

			  wait() returns and wakes up the calling process when the one of its child processes changes from running to terminated.
			  
			  The kernel sets a signal handling routine(and it is a function pointer) to the process. That signal handling routine will be executed when SIGCHLD comes.
			  
			  If the parent invokes wait(), the kernel set the process to be sleeping, until SIGCHLD comes. And the signal handling routine is invoked! And destroy the child process that sends her the signal.(PCB)
			  
			  If the child has terminated when the parent invokes wait(), then the SIGCHLD is also sent to parent, and SIGCHLD is already there. So, default actions are then taken immediately.
			  
			  Lastly, the return value of wait() system call is the PID of the terminated child.

			- waitpid()

			  Depending on the parameters, waitpid() can detect child’s status changing: 
			  -from running to suspended, and
			  -from suspended to running.(different from wait())

			- exit()

			  to terminate the child process
			  
			  Step (1) Clean up most of the allocated kernel-space memory.
			  Step (2) Clean up all user-space memory.
			  Step (3) Notify the parent with SIGCHLD.

			- Process is going back and forth...

				- User space & Kernal space
				- User time & System time

				  Accessing hardware costs the process more time.
				  
				  The user time and the system time together define the performance of an application
				  – System call plays a major role in performance.
				  – Blocking system call: some system calls even stop your process until the data is available.

		- Process termination

### Threads

- Motivation

	- Application Side
	- System Side

- Concepts

	- Share the same code

	  A thread can start with one specific function. 
	  - We name it the thread function.
	  But, a thread could never return to the caller of the thread function.

	- Share the same global variable zone and the same dynamically allocated memory
	- Each thread has its own memory range for the local variables
	- Each thread comprises a thread ID, a program counter, a register set, and a stack

- Benefits

	- do parallel tasks simultaneously
	- Ease in data sharing(Global varis or DAM)
	- Economy

	  – Allocating memory and resources for process creation is costly, dozens of times slower than creating threads
	  – Context-switch between processes is also costly, several times of slower

	- Scalability

	  – Threads may be running in parallel on different cores.

- Challenges

	- Identifying tasks
	- Balance
	- Data splitting
	- Data dependency
	- Testing and debugging

- Thread Models

	- Many to One

	  – All the threads are mapped to one process structure in the kernel.
	  – Merit
	  • Easy for the kernel to implement.
	  – Drawback
	  • When a blocking system call is called, all the threads will be blocked

	- One to One

	  – Each thread is mapped to a process or a thread structure
	  – Merit: 
	  • Calling blocking system calls only block those calling threads
	  • A high degree of concurrency
	  – Drawback:
	  • Cannot create too many threads as it is restricted by the size of the kernel memory

	- Many to Many

	  – Multiple threads are mapped to multiple structures (group 
	  mapping)
	  – Merit: 
	  • Create as many threads as necessary
	  • Also have a high degree of concurrency

- Programming

	- pthread_create()
	- pthread_t(a structure)
	- pthread_self()
	- pthread_exit()

	  void pthread_exit(void *return_value);
	  
	  Together with termination, a pointer to a global variable or a piece of dynamically allocated memory is returned to the main thread.

	- pthread_join()
	- pthread_kill()

- Implicit Threading

	- Thread Pool

	  Create a number of threads in a pool where they wait for work.
	  
	  Waits until one becomes free if the pool contains no available thread.

	- OpenMP

	  Provides support for parallel programming in shared-memory environments.
	  
	  Identifies parallel regions – blocks of code that can run in parallel.

- Signal Handling
- Thread Cancellation

	- Asynchronous cancellation

	  terminates the target thread immediately
	  • Problem: Troublesome when canceling a thread which is updating data shared by other threads.

	- Deferred cancellation(default)

	  allows the target thread to periodically check if it should be cancelled (can be canceled safely).

- Thread-Local Storage(TLS)

  Thread-local storage (TLS) allows each thread to have its own copy of data.
  – TLS is visible across function invocations
  – Similar to static data
  – TLS data are unique to each thread

### Process Communication & Synchronization

- Interprocess communication (IPC)

	- Shared Memory

	  • Establish a shared memory region, read/write to shared region
	  • Accesses are treated as routine memory accesses
	  • Faster

	- Message Passing

	  • Exchange message 
	  • Require kernel intervention
	  • Easier to implement in distributed system

		- Operations

			- send
			- receive

		- Communication Link

			- Direct communication: explicitly name each other

			  – Properties of communication link
			  • Links are established automatically (every pair can establish)
			  • A link is associated with exactly one pair of processes
			  • Between each pair, there exists exactly one link
			  – Disadvantage: limited modularity (hard-coding)

			- Indirect communication: sent to and received from mailboxes (ports)

			  – Properties of communication link
			  • A link is established between a pair of processes only if both members have a shared mailbox
			  • A link may be associated with more than two processes
			  • Between each pair, a number of different links may exist

				- ISSUE1: Who receives the message when multiple processes are associated with one link?

				  – Who gets the message?
				  – Policies 
				  • Allow a link to be associated with at most two processes
				  • Allow only one process at a time to execute a receive operation
				  • Allow the system to select arbitrarily the receiver (based on an algorithm).  Sender is notified who the receiver was.

				- ISSUE2: Who owns the mailbox?

				  – The process (ownership may be passed)
				  – The OS (need a method to create, send/receive, delete)

		- Buffering

			- Zero Capacity
			- Bounded Capacity
			- Unbounded Capacity

		- Sockets
		- Pipes

		  is a shared object.
		  
		  Kernel's point of view:
		  The pipe() system call creates a piece of shared storage in the kernel space!
		  Yet, the pipe is more than a storage: it is a FIFO queue with finite space.

			- Ordinary Pipes(unnamed)

			  – Ordinary pipes are used only for related processes (parent-child relationship)
			  • Processes must reside on the same machine
			  – Ordinary pipes are unidirectional (one-way communication)
			  – Ceases to exist after communication has finished
			  
			  Ordinary pipes allow communication in standard producer-consumer style
			  – Producer writes to one end (write-end)
			  – Consumer reads from the other end (read-end)

			- Named Pipes

			  – No parent-child relationship is necessary (processes must reside on the same machine)
			  – Several processes can use the named pipe for communication (may have several writers)
			  – Continue to exist until it is explicitly deleted
			  – Communication is bidirectional (still half-duplex)

		- Producer-Consumer Problem

	- Race Condition

	  Evil source: the shared objects
	  
	  A race condition means
	  – the outcome of an execution depends on a particular order in which the shared resource is accessed.

	- Mutual Exclusion

		- Critical Section

		  Solution: To guarantee that when one process is executing in its critical section, no other process is allowed execute in its critical section.

		- Section Entry & Exit

		  Entry:
		  Declaring the start of the critical section.
		  
		  Exit:
		  Declaring the end of the critical section.

			- Requirements

				- Requirement #1: Mutual Exclusion

				  No two processes could be simultaneously inside their critical sections.

				- Requirement #2: Progress

				  No process running outside its critical section should block other processes.

				- Requirement #3: Bounded Waiting

				  No process would have to wait forever in order to enter its critical section.

			- Challenges

				- Both operations must be atomic
				- Also need to satisfy the above requirements
				- Performance consideration

			- Solutions

				- test_and_set()
				- compare_and_swap()

			- Proposals

				- Proposal #1: Disabling Interrupt
				- Proposal #2: Mutex Locks

				  • Idea
				  – A process must acquire the lock before entering a critical section, and release the lock when it exits the critical section.
				  – Using a new shared object to detect the status of other processes, and “lock” the shared object.
				  • Implementation
				  – Calls to acquire and release locks must be performed atomically
				  – Often use hardware instructions
				  • Issue
				  – Busy waiting: Waste CPU resource
				  • Spinlock
				  • Applications
				  – Multiprocessor system 
				  • When locks are expected to be held for short times

					- Busy Waiting

						- Additional Shared Object

				- Proposal #3: Strict Alternation

				  Violate Requirement#2

				- Proposal #4: Peterson’s solution

				  • Highlights:
				  – Share two data items
				  • int turn;  //whose turn to enter its critical section
				  • Boolean interested[2];  //if a process wants to enter
				  – Processes would act as a gentleman: if you want to enter, I’ll let you first
				  – No alternation is there

					- Priority Inversion Problem

					  • A low priority process is inside the critical region, but …
					  • A high priority process wants to enter the critical region.
					  • Then, the high priority process will perform busy waiting for a time or even forever.

				- Final Proposal: Semaphore

					- Operations

					  First issue: Busy waiting
					  Solution: special_sleep() / special_wakeup(), and maintain a link list.
					  
					  Second issue: Atomicity (both operations must be atomic)
					  Solution: Disabling interrupts

						- down() or wait() -- Decrementing the count
						- up() or signal() -- Incrementing the count

					- Two Types

						- Binary Semaphore
						- Counting Semaphore

- Process Synchronization

  By using Semaphore

	- Deadlock

		- Requirements

			- Requirement #1: Mutual Exclusion

			  – Only one process at a time can use a resource.

			- Requirement #2: Hold and Wait

			  – A process must be holding at least one resource and waiting to acquire additional resources held by other processes

			- Requirement #3: No Preemption

			  – A resource can be released only voluntarily by the process holding it after that process has completed its task

			- Requirement #4: Circular Wait

		- Detect

			- Case 1: Each resource has one instance

			  • Resource-allocation graph: detect the existence of a cycle
			  • DFS search

			- Case 2: Each resource has multiple instances

			  Matrix Method, 4 data structures:
			  Existing(Total) Resources: E
			  Available Resources: A
			  Allocation Matrix: C
			  Request Matrix: R

		- Prevent & Avoid

			- Banker's Algorithm

			  Need to know the demand.
			  
			  check the state: safe(accept), unsafe(reject)

			- System State defined by (E, A, C, R)

				- Safe state: exist one running sequence to guarantee that all processes’ demand can be satisfied
				- Unsafe state: Not exist any sequence to guarantee the demand

			- Ignore(鸵鸟算法)

	- Classic Problems

		- Producer - Consumer Problem

		  Also known as the bounded-buffer problem.
		  
		  Now using Semaphores, instead of pipes.

			- Issues

				- ISSUE #1: Mutual Exculsion
				- ISSUE #2: Synchronization(Coordination)

				  – Remember the two requirements: 
				  • Insert an item when it is not FULL
				  • Consume an item when it is not EMPTY
				  – Can we use a binary semaphore?

			- Solutions

				- One Binary Semaphore to ensure ISSUE #1 
 (Mutex)
				- Two Counting Semaphores to ensure ISSUE #2 (full & empty)

				  Two semaphores are needed because the two suspension conditions are different.

		- Dining Philosophy Problem

		  • 5 philosophers, 5 plates of spaghetti, and 5 chopsticks.
		  • The jobs of each philosopher are 
		  – to think and 
		  – to eat: They need exactly two chopsticks in order to eat the spaghetti.
		  • Question: how to construct a synchronization protocol such that
		  – they will not result in any deadlocking scenarios, and
		  – they will not be starved to death

			- Philosopher i needs 
Chopsticks i and ((i+1) % N);
			- Requirements

				- Requirement #1: Mutural Exclusion
				- Requirement #2: Synchronization

				  – Should avoid any potential deadlocking execution order.

			- Problems

				- Model a chopstick as a semaphore is intuitive, but is not working.

				  The problem is that we are afraid to “down()”, as that may lead to a deadlock.

				- Using sleep() to avoid deadlock is effective, yet bringing another problem.

				  We can always create an execution order that keeps all the philosophers busy, but without useful output.

			- Solution

		- Reader - Writer Problem

		  It is a concurrent database problem.
		  
		  A writer needs to lock the database exclusively so that the readers would not retrieve inconsistent data.
		  
		  In other words, a writer is forbidden to write any data before the readers have finished reading.

			- Problems

				- Mutural Exclusion

				  relate the readers and the writers to one semaphore.
				  
				  – This guarantees no readers and writers could proceed to their critical sections at the same time.
				  – This also guarantees no two writers could proceed to their critical sections at the same time.

				- Synchronization

					- Rule #1: While a reader is reading, other readers is allowed to read the database.
					- Rule #2: While a reader is reading, no writers is allowed to write to the database.
					- Rule #3: While a writer is writing, no writers and readers are allowed to access the database.

				- Concurrency

					- Simultaneous access for multiple readers is allowed and must be guaranteed.

					  – The first reader coming to the system “down()” the “database” semaphore.
					  – The last reader leaving the system “up()” the “database” semaphore.

			- Summary

				- This solution does not limit the number of readers and the writers admitted to the system.
				- This solution gives readers a higher priority over the writers.

				  – Whenever there are readers, writers must be blocked,  not the other way round.

### Process Scheduling

- Process's Lifecycle
- Concept

	- Mainly about how to make all the ready processes become “Running” 

- Process Scheduling happens when...

	- A new process is created

	  whether the parent or the child is scheduled is up to the scheduler’s decision.

	- An existing process is terminated

	  CPU is freed.

	- A process waits for I/O

	  CPU is freed.

	- A process finishes waiting for I/O

	  The interrupt handling routine makes a scheduling request, if necessary.

- Questions

	- Question #1: How to make a ready process
become running? (Note that the running process may not terminate at that time)

	  Context Swiching

	- Question #2: How to decide which process hould be running? 

	  Scheduling criteria & scheduling algorithms

	- Question #3: How to design scheduling in a real/specific system? 

	  Multiprocessor system, real-time system, algorithm eveluation

- Context Switching

  Context switching is the actual switching procedure, from one process to another.
  
  Context switching has a price to pay…
  So, minimizing the number of context switching may help boosting system performance.

	- Steps

		- 1. Backup all registers’ values.
		- 2. load the context of the new process into the main memory and into the CPU.

- Scheduling Criteria

	- Classes of Scheduling

		- Nonpreemptive Scheduling
		- Preemptive Scheduling

		  -When particular kinds of interrupts and events are detected, the process would leave the scheduler.

	- Performance Measures

		- CPU Utilization

		  The higher, the better.

		- Throughput

		  Number of processes that are completed per time unit.
		  
		  The higher, the better.

		- Turnaround Time

		  Time to execute the process: interval from the time of submission to the time of completion (total running time + waiting time+ doing I/O).
		  
		  The lower the better.

		- Ready Time

		  The time spent waiting in the ready queue.
		  
		  The lower the better.

		- Response Time

		  The time from the submission of a request until the first response is produced (useful measure for interactive systems).
		  
		  The lower the better.

- Scheduling Algorithms

	- FIFO

	  No Preemptive
	  
	  Sensitive to input.
	  – The average waiting time is often long

	- Shortest-Job-First(SJF)

	  Nonpreemptive SJF
	  
	  Preemptive SJF:
	  -Preemption happens when a new process arrives at the system.
	  -Then, the scheduler steps in and selects the next task based on their remaining CPU requirements.
	  Shortest-remaining-time-first
	  
	  Challenge: How to know the length of the next CPU request?
	  And maybe some processes starve to death.

	- Round-Robin(RR)

	  – Every process is given a quantum, or the amount of time allowed to execute.
	  – When the quantum of a process is used up (i.e., 0), the process releases the CPU and this is the preemption.
	  – Then, the scheduler steps in and it chooses the next process which has a non-zero quantum to run.
	  
	  Processes are running one-by-one, like a circular queue.
	  – Designed specially for time-sharing systems.
	  
	  The responsiveness of the processes is great under the RR algorithm.
	  
	  -How to set the size of the time quantum?
	  -In practice: 10-100ms
	  -A rule of thumb: 80% CPU burst should be shorter than the time quantum.

	- Priority Scheduling

	  – A task is given a priority (and is usually an integer).
	  – A scheduler selects the next process based on the priority.
	  
	  Problem: Indefinite blocking or starvation
	  Solution: Aging (gradually increase the priority of waiting processes)

	- Priority Scheduling with Mutiple quenes

		- Fixed Priority

		  – It is still a priority scheduler.
		  – But, at each priority class, different schedulers may be deployed.
		  
		  • Properties: process is assigned a fix priority when they are submitted to the system.
		  • The highest priority class will be selected.
		  – To prevent high-priority tasks from running indefinitely.
		  – The tasks with a higher priority should be short-lived, but important;
		  • Lower priority classes will be scheduled only when the upper priority classes has no tasks.
		  high-priority task preempting a low-priority task.

		- Flexible Priority

- Applications & Scenarios

	- Multiple Processors
	- Real-time Systems

		- Hard real-time systems
		- Soft real-time systems
		- Algorithms

			- Rate Monotonic Scheduling

			  Assumption: Processes require CPU at constant periods: processing time t and period p (rate 1/p)
			  
			  Each process is assigned a priority proportional to its rate, and schedule processes with a static priority policy with preemption (fixed priority)

			- Earliest-deadline-first scheduling (EDF)

			  Dynamically assigns priorities according to deadline (the earlier the deadline, the higher the priority)
			  
			  EDF only requires the announcement of deadlines

	- Linux Scheduler

	  • A multiple queue, (kind of) static priority scheduler.
	  
	  CFS

	- Algorithm Evaluation

## Memory Management

### From a Programmer’s Perspective

- User-space Memory Management

	- Address Space

	  - Memory of a process is divided into segments 
	  - This way of arranging memory is called segmentation
	  
	  – On a 32-bit Linux system, the user-space addressing space is around 3GB.

	- Code & Constants

	  • Constants are stored in code segment.
	  – The memory for constants is decided by the program code
	  – Accessing of constants are done using addresses (or pointers).
	  • Codes and constants are both read-only.(It'll invoke segmentation fault if user tries to modify the constants.)

	- Data Segment & BSS

	  A static variable is treated as the same as a global variable!

		- Data Segment

		  – Containing initialized global and static variables.
		  – Only the compiler cares about the difference!
		  
		  The data segment has the required space already allocated.

		- Block Started by Symbol

		  – Containing uninitialized global and static variables.
		  
		  BSS is just a bunch of symbols. The space is not yet allocated.
		  The space will be allocated to the process once it starts executing.
		  This is why BSS is called “Block Started by Symbol”.

	- Stack

	  LIFO

		- Contains...

			- All local variables

			  When a function is called, the local variables are allocated in the stack.
			  When a function returns, the local variables are deallocated from the stack.

			- All Function parameters
			- Program Arguments
			- Environment Variables

	- Heap

	  Dynamically Allocated Memory
	  
	  – Dynamic: not defined at compile time.
	  
	  – Allocation: only when you ask for memory, you would be allocated the memory.

		- malloc()

		  When “malloc()” is called, the “brk()” system call is invoked accordingly.
		  “brk()” system call can grow or shrink the allocated area. 
		  
		  malloc() will create a Data structure ahead of the allocated space to manage the allocated space, which is also maintained by malloc().
		  A pointer is used for creating a linked list of de-allocated block.
		  An integer number records the size of de-allocated block.

			- Case #1: if there is no suitable free block…

			  – then, the malloc() function should call brk() system call…in order to claim more heap space.

			- Case #2: if there is a suitable free block

			  – the malloc() function should reuse that free block.

			- Allocation Algorithms

				- First fit
				- Next fit

				  similar to first fit, but start where previous search finishes

				- Best fit
				- Worst fit

		- free()

		  The free() call may shrink the heap space.
		  
		  – When a program calls “free(ptr)”, then the address “ptr” must be the start of a piece of memory obtained by a previous “malloc()” call.

			- Case #1: de-allocating the last block.
			- Case #2: de-allocating an intermediate block.

			  There exists a linked list of de-allocated block.

			- Coalescing

		- Implicit Linked List
		- Explicit Linked List
		- Segregated Free List

		  – Different free lists for different size classes
		  
		  – Allocation
		  • Search appropriate list (larger size)
		  • Found and split
		  • Not found: search next

			- Buddy system

			  (power-of-two block size)

		- OOM(Out of Memory)

			- Lazy Allocation

			  As well as local variables.

		- Other Issues

			- External Fragmentation

			  – The heap memory looks like a map with many holes
			  – It is the source of inefficiency because of the unavoidable search for suitable space
			  – The memory wasted because external fragmentation is inevitable

			- Internal Fragmentation

			  – Payload is smaller than allocated block size
			  – Padding for alignment
			  – Placement policy
			  • Allocate a big block for small request

	- Segmentation Fault

	  When you are accessing a piece of memory that is not allowed to be accessed(try to access the unallocated/unused area or try to write the read only area), then the OS returns you an error called – segmentation fault.
	  
	  Every process’ segments are independent and distinct.

### From the Kernel’s Perspective

- Virtual Memory

	- Memory Management Unit(MMU)

	  – MMU is designed to perform address translation.
	  – The MMU is an on-CPU device.

		- Step 1: Translate Vritual-Addr to Physical-Addr

		  When CPU wants to fetch an instruction, the virtual address is sent to MMU and is translated into a physical address.

		- Step 2: The memory returns the instruction 
addressed in physical address.
		- Step 3: The CPU decodes the instruction.

		  – An instruction always stores virtual addresses, but not physical addresses.

		- Step 4: With the help of the MMU, the target memory is retrieved.

	- Merit

		- 1. Different processes use the same virtual addresses, They may be translated to different physical addresses.

		  – Recall the “pid” variable in the example using fork().
		  – The address translation helps the CPU to retrieve data in a non-contiguous layout (the process address space is contiguous ).

		- 2. Memory sharing can be implemented

		  – This is how threads share memory!
		  – This is how different processes share codes!

		- 3. Memory growth can be implemented

		  – When the memory of a process grows, the newly-allocated memory is not required to be contiguous.

- MMU Implementation & Paging

	- MMU Implementation

		- Paging

		  A kind of partitial lookup table: Only mappes the first 20 bits.
		  so, Virtual addresses within the same page are always mapped to the same physical page.
		  
		  • This technique is called paging.
		  – This partitions the memory into fixed blocks called pages.
		  – The lookup table inside the MMU is now called the page table.
		  
		  – Each process should have its own page table.

			- PropertiesAdjacent virtual pages are not guaranteed to be mapped to adjacent physical pages(or frames).
			- A page is the basic unit of memory allocation.

			  The allocation is in a page-by-page manner.
			  The same case for the growth of the stack.

			- Internal Fragmentation
			- Page Table Design

			  – Who can tell which virtual page is allocated?
			  – Who can tell which page is on which device?
			  ......

			- Page Table Structure

			  – Divide the page table into pieces
			  or Multilevel Page Table

			- Performance Boost

				- 1. Large Pages

				  • Reduce the page table entries
				  • Cons?
				  – Internal fragmentation
				  – Deduplication

				- 2. Caching: Translation Lookaside Buffer 
 (TLB)

				  The search in TLB is fast: Part of the instruction pipeline
				  
				  The size of TLB is small: e.g., 32-1024 entries

- Demand Paging

  • The reality is: allocation is done in a lazy way!
  – The system only says that the memory is allocated.
  – Yet, it is not really allocated until you access it.
  As a matter of fact, malloc() does not involve any memory allocation, only involving the allocation of the virtual address page.
  
  This lazy way is called demand paging.

	- Page Fault

	  – the MMU finds that a virtual page involved is invalid,
	  – the CPU then generates an interrupt called page fault.

		- Page Fault Handling Routine

		  – The kernel knows the page allocation for all processes. 
		  – It allocates a memory page for that request.
		  – Last, the page table entry for Page E is updated.
		  
		  when the routine finds that all frames are allocated?
		  – Then, we need the help of the swap area.

			- Swap Area

			  Reside in Hard Disk.

				- Step 1: Select a victim virtual page and copy the victim to the swap area.
				- Step 2: Allocate the free frame to the new frame allocation request.
				- Size

					- At least the same as the size of the physical 
memory

	- Copy on Write

	  Copy-on-write technique allows the parent and the child processes to share pages after the fork() system call is invoked.
	  
	  A new, separated page will be copied and modified only when one of the processes wants to write on a shared page.

	- Performance

	  Effective Access Time:
	  (1 - p)ma + p x page fault time
	  ma: Memory access Time(10 - 200 ns)
	  p: prob. of a page fault
	  page fault time: ms

- Page Replacement Algorithms

  – It is the job of the kernel to find a victim page in the physical memory, and…
  – write the victim page to the swap space.

	- Optimal

	  If I know the future, then I know how to do better.
	  the page reference string is given in advance.
	  
	  • Replace strategy:
	  – To replace the page that will not be used for the longest period of time.

	- FIFO

	  – The victim page will always be the oldest page.
	  – The age of a page is counted by the time period that it is stored in the memory.

	- Least Recently Used(LRU)

	  • Strategy:
	  – Attach every frame with an age, which is an integer.
	  – When a page is just accessed,
	  • no matter that page is originally on a frame or not, set its age to be 0.
	  • Other frames’ ages are incremented by 1.

	- Second-Chance Algorithm

	  – A reference bit for each page (set by hardware)
	  LRU approximation
	  
	  – Give the page a second chance if its reference bit is on
	  If a page is heavily used, its reference bit will be very likely to be on.

	- Performance

		- Belady's anomaly

		  Stack algorithms: never exhibit Belady's anomaly

- Allocation of Frames

	- Allocation for user processes

	  • Constrains
	  – Limit on number of frames
	  • Upper bound: total available frames
	  • Lower bound: has a minimum number
	  – Performance consideration (limit page-fault rate)
	  – Defined by computer architecture (instructions)
	  – Process will be suspended if the number of allocated frames falls below the minimum requirement

	- Allocation Algorithms

		- Equal Allocation

		  m frames, n processes, then allocate every process m/n frames.
		  Memory Waste

		- Proportional Alloction

		  Size of Pi is Si, then allocate Pi: m x Si/(S1 + ... Sn) frames

		- Priority-based Scheme

		  – Ratio depends on both process size and priority

	- Thrashing

	  – Frequent page fault
	  • Replace a page that will be needed again right away
	  – This is called thrashing 
	  • Spend more time paging than executing

		- Solution

			- Provide as many frames as needed

			  • Use working-set strategy to estimate needed frames
			  – Working set: the set of pages in the recent Δ page references
			  • Use page-fault frequency

- Allocation for Kernel Memory

	- Features

		- Varying (small) size requirement: different data structures
		- Contiguous requirement (certain hardware devices interact with physical memory)
		- Paging: Internal fragmentation

	- Buddy System

	  Allocate memory from a fixed-size segment
	  – Power-of-2 allocator (11 orders)
	  – Advantage: coalescing

	- Slab Alloction

	  Allocate memory for small objects (limit fragmentation)
	  – Slab: one/more contiguous pages
	  – Cache: one/more slabs 
	  • A separate cache for each unique kernel data structure

- Memory Mapped File

	- Memory Mapped a File

	  associate a part of the virtual address space with the file

	- File Access

		- Initial Access to File(Demand Paging)
		- Subsequent reads/writes: routine memory accesses
		- Improves performance

## Storage Management

### Mass Storage

- Disk Structure

	- Physical View

		- Physical Address

			- Track

			  The surface of a platter is divided into tracks

			- Sector

			  Track is divided into sectors (512B data + ECC)

			- Cylinder

			  Set of tracks that are at one arm position

		- Access: Seek + Rotate
		- Seek Time: move disk arm to desired cylinder
		- Rotational latency

			- Constant liner velocity (CLV)
			- Constant angular velocity (CAV)

	- Logical View

		- Address Mapping
		- Disk Management

			- Bad Disk Management

			  Disks are prone to failures: defective sectors are 
			  common (bad blocks)
			  Need to handle defective sectors: bad block 
			  management
			  
			  Maintain a list of bad blocks (initialized during low-level formatting) and preserve an amount of spare sectors
			  
			  Sector sparing/forwarding: replace a bad sector logically with one spare 
			  sector
			  • Problem: invalidate disk scheduling algorithm
			  • Solution: spare sectors in each cylinder + spare cylinder
			  
			  Sector slipping: remap to the next sector (data movement is needed)

			- Disk Formatting

				- Step 1: Low-level formatting/physical formatting

				  Divide into sectors so disk controller can read/write
				  Fills the disk with a special data structure for each sector (data area(512B), 
				  header and trailer (sector number & ECC))
				   The controller automatically does the ECC processing henever a sector 
				  is read/written
				  Done at factory, used for testing and initializing (e.g., the mapping). It is also possible to set the sector size (256B, 512B, 1K, 4K)

				- Step 2: How to use disks to hold files after shipment?

					- Choice 1: File System

					   Partition into one or more groups of cylinders (each as a separate disk)
					   Logical formatting: creating a FS by storing the initial FS data structures 
					   I/O optimization: Disk I/O (via blocks) & file system I/O (via clusters), why?
					  • More sequential access, fewer random access

					- Choice 2: Raw Disk

					   Use disk partition as a large sequential array of logical blocks, without FS 
					   Raw I/O: bypass all FS services (buffer cache, prefetching…), be able to 
					  control exact disk location

- Disk Scheduling

  Choose the next request in the pending queue to service so as to minimize the seek time

	- I/O Access Procedure

	  – Seek: move the head to the desired cylinder
	  – Rotate: spin to the target sector on the track

	- Scheduling Algorithms

		- FCFS Scheduling

		  First Come, First Served
		  
		  – Intrinsically fair, but does not provide the fastest service

		- Shortest Seek Time First (SSTF)

		  – Choose the request with the least seek time
		  – Choose the request closest to the current head position
		  
		  Not Optimal & may cause Starvation

		- SCAN Scheduling

		  Scan back and forth
		  – Starts at one end, moves toward the other end
		  – Service the requests as it reaches each cylinder
		  – Reverse the direction 
		  – Elevator algorithm
		  
		  Cons:
		  If the heaviest density of requests is at the other end of the disk
		  They need to wait for a long time

		- C-SCAN Scheduling

		  Circular Scan back and forth
		  – A variant of SCAN: immediately return when reaches the end
		  – Aim for providing a more uniform wait time

		- LOOK

		  No need to move across the full width of the disk, but only need to reach the final request

		- C-LOOK

		  No need to move across the full width of the disk, but only need to reach the final request
		  
		  Goes only as far as the final request
		  – Look for a request before moving
		  
		  Look for a request before continuing to move in a given direction

		- Selection

- Solid-State Drivers(SSDs)

	- SSD Architecture

		- SSD Components

			- Multiple Flash Packages

			  Package > die/chip > plane > block > page

			- Controllers
			- RAM
			- Flash Cell

			  • Each cell stores one bit (or multiple bits)
			  • Program operation can only change the value from 1 to 0 (erase operation changes the value from 0 to 1)
			  – No overwritten
			  • The floating gate becomes thinner as the cell undergoes more program-erase cycles
			  – Decreasing reliability

			- Flash Types

				- NAND Flash

					- SLC
					- MLC

				- NOR Flash

	- SSD Operations

		- Read
		- Write
		- Erase

		  – In unit of blocks (64/128 pages) 
		  – Change all bits to 1
		  – Much slower than read/write: 1.5ms
		  
		  • Each block can only tolerate limited number of P/E cycles
		  – SLC: 100K, MLC: 10K, TLC (several K to several hundred)
		  • The number of maximum P/E cycles decreases when
		  – More bits are stored in one cell
		  – The feature size of flash cell decreases (72nm, 34nm, 25nm)

		- Delete

		  – Simply mark the page as invalid

		- Overwrite/Update

		  – Does not support in-place overwrite
		  – Data can only be programmed to clean pages

		- Read-Modify-Write
		- TRIM

		  • Improve write performance degraded by RMW
		  – The OS also sends a TRIM command to SSD after delete pages
		  – Requires both OS and SSD to support
		  
		  TRIM avoids slow RMW operation during write, so it increases write performance

	- Flash Translation Layer

		- Functionalities

			- Address Mapping

				- Sector Mapping

				  Mapping table is large: requires a large amount of RAM

				- Block Mapping

				  • The logical sector offset is the same with the physical sector offset
				  
				  Smaller mapping table
				  If the FS issues writes with identical lsn, many erases

				- Hybrid Mapping

				  • First use block mapping, then use sector mapping in each block
				  
				  Small mapping table
				  Avoid a lot of erase operations
				  Longer time to identify the location of a page

				- Log-structured Mapping

				  Data blocks: block mapping
				  Log blocks: sector mapping

			- Garbage Collection

			  • Due to the existence of invalid pages, GC must be called to reclaim storage
			  – Choose a candidate block
			  – Write valid pages to another free block
			  – Erase the original block

				- GC Algorithms

				  • Tradeoff in GC design
				  – Efficiency: minimize writes
				  – Wear-leveling: erase every block as even as possible
				  – Tradeoff
				  – GC is considered together with wear-leveling
				  
				  • Algorithms
				  – Greedy, random, and their variants
				  – Hot/cold identification

			- Wear-leveling

	- Research Topics

- RAID

  RAID: Redundant Array of Inexpensive (independent) Disks
  
  In the past
   Combine small and cheap disks as a cost-effective alternative to large and expensive disks
  
  Nowadays
   Higher performance
   Higher reliability via redundant data
   Larger storage capacity
  
  Many different levels of RAID systems
   Different levels of redundancy, capacity, cost…

	- Evaluation

		- Performance
		- Reliability
		- Cost

	- Level

		- RAID 0

		  • Block-level striping, no redundancy
		  • Provides higher data-transfer rate
		  • Does not improve reliability. Once a disk fails, data loss may happen (MTTF: mean time to failure)

		- RAID 1

		  • Data mirroring (RAID1)
		   Two copies of the data are held 
		  on two physical disks, and the 
		  data is always identical.
		   Replication
		  • High storage cost
		   Twice as many disks are required 
		  to store the same data when 
		  compared to RAID 0.
		   Even worse storage efficiency 
		  with more copies

		- RAID 0+1

		  • RAID 0 provides (reliability)? and 
		  RAID 1 provides reliability
		  • RAID 0+1 (RAID01)
		   First data striping
		   Then data mirroring

			- high storage cost

		- RAID 1+0

		  • RAID 1+0 (RAID10)
		   First data mirroring
		   Then data striping

		- RAID 4

		  • Parity generation: Each parity block is the XOR value of the corresponding data disks
		  
		  • Block-level data striping
		  
		  • Data and parity blocks are distributed across disks
		  
		  • Dedicated parity disk

			- RMW(Read-Modify-Write)

			  • Suppose A1 will be updated to A1’
			  • Both A1 and Ap(Parity Block) need to be updated
			  Then Ap' = Ap xor A1 xor A1'
			  • Read-modify-write (RMW)

			- RRW(Read-Reconstruct-Write)

			  • Suppose A1 will be updated to A1’, and A2 will be updated to A2'
			  • A1, A2 and Ap(Parity Block) need to be updated
			  Then Ap' = A3 xor A1' xor A2'
			  • Read-modify-write (RMW)

			- Problems

			  • Problems of RAID 4
			  • Disk bandwidth are not fully utilized
			  • Parity disk will not be accessed under normal mode
			  • Parity disk may become the bottleneck
			  • E.g., updating A1, B2, C3

		- RAID 5

		  • Similar to RAID 4
		  • One parity per stripe
		  
		  • Key difference
		  • Uniform parity distribution
		  
		  • RAID 5 is an ideal combination of 
		  • good performance
		  • good fault tolerance
		  • high capacity
		  • storage efficiency

		- RAID 6

		  • RAID-6 protects against two disk failures by maintaining two parities
		  • Encoding/decoding operations:
		   Based on Galois field

	- RDP Code
	- Erasure Codes
	- Topics

### File System

- Programmer's Perspective

	- Outline

		- Files
		- Directories
		- Layout

		  It determines how a FS stores data in the disk.
		  
		  – The layout affects many things:
		  • The speed in operating on the file systems;
		  • The reliability in using the file systems;
		  • The allocation and de-allocation of disk spaces.

	- Introduction

	  • A FS must be stored on a device.
	  – But, a device may or may not contain any FS.
	  – Some storage devices can host more than one FS.
	  • A storage device is only a dummy container.
	  – It doesn’t know and doesn’t need to know what FS-es are stored inside it.
	  – The OS instructs the storage device how the data should be stored.

	- File

	  – File provides a long-term information storage.
	  • It is persistent and survives after process termination.
	  – File is also a shared object for processes to ccess  concurrently.
	  
	  When a file is named, it becomes independent of the process, the user, and even the system

		- OS Perspective

		  A file is a logical storage unit (a sequence of logical records), it is an abstract data type.

		- User Perspective

		  the smallest allotment of logical secondary storage.

		- Typical Attributes

		  • File attributes are FS dependent.
		  – Not OSdependent.
		  
		  A set of File Attributes and File Content(or entity) are usually stored separately.

			- Name

			  Human-readable form

			- Identifier

			  Unique tag (a number which identifies the file within the FS)

			- Type

			  Text file, source file, executable file…

			- Location

			  Pointer to a device and to the location of the file on the device

			- Size

			  Number of bytes, words, or blocks

			- Time/Date

			  Creation, last modification, last use…

			- Protection

			  Access control information (read/write/execute)

		- File Permissions
		- Pathname & Filename

		  The pathname is unique within the entire file system.
		  The filename is not unique within the entire file system.
		  The filename is only unique within the directory that it resides.
		  
		  The OS kernel translates the pathname into a set of data addresses on the device.
		  That means the pathname is the key!

	- Operations

		- 'FILE' Structure

			- File Descriptor

			  A file descriptor is just an array index for each process to locate
			  its opened files.
			  
			  Although a file is opened by two different processes, the kernel uses one structure to maintain it!

			- Buffer
			- Other helpful data...

		- File Operations

			- Kinds

				- Create
				- Write
				- Read
				- Reposition
				- Delete
				- Truncate

				  Keeps attributes only

			- Open File Table

			  An open() system call is provided, and it is called before a file is 
			  first used
			  
			  OS keeps a table containing information about all open files (per-process and system-wide table)
			  
			  The file will be closed when it is no longer being actively used, 
			  using close() system call

			- Opening a File

			  Opening a file only involves the pathname and the attributes of the file, instead of the file content!

				- Step 1: The process supplies a pathname  to the OS.
				- Step 2: The OS looks for the file attributes of the target file in the disk.
				- Step 3: The disk returns the file attributes.
				- Step 4: The OS then associates the attributes to a number and the number is called the file descriptor.
				- Step 5: The OS returns the file descriptor to the process.

			- Read from Open Files

				- Step 1: The process supplies a file descriptor to the OS.
				- Step 2: The OS reads the file attributes and uses the stored attributes to locate the required data.
				- Step 3: The disk returns the required data.

				  - File data is stored in a fixed size cache in the kernel.

				- Step 4: The OS fills the buffer provided by the process with the data. Write data to the userspace buffer.

			- read() & write()

				- read()

					- Step 1: Check whether the end of the file is reached or not.

					  [ Comparing size and file seek. ]:
					  Compare the data in File Attributes and Runtime Attributes.(Kernel level, list of Opened Files)

					- Step 2: Reading data
					- Step 3: File data is stored in a fixed size cache in the kernel.
					- Step 4: Write data to the userspace buffer.

				- write()

					- Step 1: Write data to the kernel buffer.
					- Step 2: According to the data length, 
(1) change in file size, if any, and
(2) change in the file seek.
					- Step 3: The call returns.
					- Step 4: The buffered data will be flushed to the disk from time to time.

	- Directory

	  A directory is a file.
	  
	  A directory file is an array of directory entries.
	  
	  An directory entry consists of :
	  Name of the stored file
	  Location of the attributes of the stored file(or the attributes themselves)

		- Directory Traversal Process

			- Step 1: The process then supplies the OS the unique pathname(suppose we want to open the file '/bin/ls')
			- Step 2: The OS retrieves the  directory file of the root directory ‘/’(in Linux)
			- Step 3: The disk returns the directory file.
			- Step 4: The OS looks for the name “bin” in the directory file.
			- Step 5: If found, the in the OS retrieves the directory file of “/bin” using the information of the file attributes of “bin”.
			- Step 6: The OS looks for the name “ls” in the directory file “bin”.
If found, then the OS knows that the file “/bin/ls” is found, and it starts the previously-discussed procedures to open the file “/bin/ls"

		- File Creation

		  File creation == Update of the directory file
		  
		  Note: “touch text.txt” will only create the directory entry,  and there is no allocation for the file content, that's why when I type “touch text.txt” but “text.txt” does not exist.

		- File Delete

		  • Removing a file is the reverse of the creation process.

- File System Layout

	- Rules

		- 1. Every data written to the device must be able to be retrieved
		- 2. Every FS operation should be done as efficient as possible
		- 3. When a file is removed, the FS should free the corresponding space.

	- Trial 1.0: The Contiguous Allocation

	  Just like a book
	  
	  Contiguous allocation is very similar to the way we write a book. It starts with the table of content, which we call the root directory.

		- Basics

			- Root Directory
			- locate the allocated space and the free 
space in O(n)
			- File Delete easily

		- Drawbacks

			- Extern Fragmentation

			  Althought the defragmentation process may help.
			  But very expensive

			- File Size Growth Problem

		- Can used on read-only files(just like a book)

	- Trial 2.0: The Linked List Allocation
(Blocking)

	  To avoid allocating space in a contiguous manner!

		- Basics

			- Step 1: Chop the storage device into equal-sized blocks.
			- Step 2: Fill the new file into the empty space in a block-by-block manner.
			- Step (3): The root directory…becomes strange/complicated.

			  Since a directory file is an array, it is difficult to pretend to be a linked list….

		- cons

	- Trial 2.1: Linked List Allocation
(Real Linked List)
To write the block # of the next block into the first 4 bytes of each block.

	  Real linked list
	  
	  The Root Directory only needs to store the first block of the files, as well as the file size.
	  The last block of a file may not be fully filled.

		- Free Space Management

		  Extra data is needed to maintain a free list.
		  
		  We can also maintain the free blocks as a linked list, too.

		- Pros

			- 1. External fragmentation problem is solved
			- 2. Files can grow and shrink freely
			- 3. Free block management is easy to implement

		- Cons

			- 1. Random access performance problem

			  The OS needs to access a series of blocks before it can access an arbitrary block  (O(n)).

			- 2. Internal Fragmentation

			  This empty space will be wasted since no other files can be allowed to fill such space.

	- Trial 2.2: File Allocation Table (FAT)

	  The only difference between 2.2 and 2.1:
	  All the information about the next block #s are centralized, and it is called FAT.
	  
	  And Root Directory nolonger stores the File Size.
	  
	  The random access problem can be eased by keeping a cached version of FAT inside the kernel.
	  
	  If this table is partially kept on the cache, then extra I/O requests will be generated in locating the next block #.

		- Read a File

			- Step 1: Look for the first block # of the file.
			- Step 2: Read the file allocation table to determine the location of the next block.
			- Step 3: The process stops until the block with the “next block # = 0”.

		- Brief Introduction

		  – A block is named a cluster.
		  – The main difference among all the versions of FAT FS-es is the cluster address size.
		  
		  – The larger the cluster address size is, the larger the size of the file allocation table.
		  – The larger the cluster size is, the larger the size of the disk partition is.

			- FAT 12

			  Cluster Address length = 12
			  Numbers of Clusters = 4K

			- FAT 16

			  Cluster Address length = 16
			  Numbers of Clusters = 64K

			- FAT 32

			  Cluster Address length = 32
			  Numbers of Clusters = 256M

		- FAT Caching to get good Random Access Performance

	- Trial 3.0: The Index-Node(inode) Allocation

		- Index-Node Structure

		  An innovative design of the index node,  called extent.

			- Direct Block (Contains 12 Block Pointers)
			- Indirect Block
			- Double Indirect Block
			- Triple Indirect Block

		- Root Directory

		  Now Root Directory stores the index node # of files which resides in Root Directory(in Linux: '/').

		- Index Node Table

		  It is arranged as an array. So, looking up an index node will be fast.
		  
		  Searching the index nodes using the index node #.

		- More Storage Usage

		  – The index-node allocation uses more storage: 
		  • to trade for a larger file size (with fixed-size index nodes).
		  – The indirect blocks are the extrathings.

		- Root Directory & Sub-directories

			- Sub-directory

			  Directory is also a file, so it has an inode too
			  
			  each directory entry keeps the address of the file attributes, not the attributes themselves

			- Traversing

	- File system information and partitioning

		- FS Informantion

		  Because different storage device has different needs, so FS informantion shouldn't store in kernel.
		  
		  Solution: The workaround is to save those information on the device.
		  
		  In FAT* & NTFS: Boot Sector
		  In Ext*: Superblock

		- Disk Partitions

		  Partitioning is needed to 
		  – limit the file system size
		  – support multiple file systems on a single disk
		  
		  – A disk partition is a logical space…
		  • A file system must be stored in a partition.
		  • An operating system must be hosted in a partition.

			- Boot Code

			  the code specifies which partition to boot.

			- Partition Table

				- Stores...

					- First Sector
					- The Length
					- The Type of a Partition

			- Master Boot Record (MBR)
			- Benefits

				- Performance

				  A smaller file system is more efficient!

				- Multi-Booting

				  You can have a Windows XP + Linux + Mac installed on a single hard disk (not using VMware).

				- Data Management

				  You can have one logical drive to store movies, one logical drive to store the OS-related files, etc.

- Detail of FAT32

	- Typical Layout

		- Boot Sector (1 Sector)

		  Store FS-specific parameters

		- FSINFO (1 Sector)

		  Free-space management

		- Reserved Sectors

		  size: Variable, can be changed during format

		- FAT (2 pieces)

		  A robust design: if “FAT 1” is corrupted or containing bad sectors, then “FAT 2” can act as a backup.
		  
		  Variable, depends on disk size and cluster size.

		- Root Directory

		  Start of the directory tree
		  size: At least 1 cluster, depend on the number of directory entries

	- Directory & File Attributes

		- Directory Traversal
		- Directory Entry

		  Note. This is the 8+3 naming convention.
		  8 characters for name + 3 characters for file extension
		  
		  The FAT is defined to use little-endian byte ordering, as its original implementation was on the Intel x86 platform

		- LFN(Long File Name) Directory Entry

		  Adding more entries to represent the filename
		  
		  Each LFN entry represents 13 characters in Unicode, i.e., 2 bytes per character.
		  Yet, the sequence is upside-down!
		  
		  First(0) Byte is the Sequence Number
		  
		  Byte 11 is always 0x0F to indicate that is a LFN.
		  
		  The terminating directory entry has the sequence number OR-ed with 0x40.

	- File Operations

		- Read Files

		  Note. The file size may also help determining if the last cluster is reached

			- Step 1: Read the content of the target Cluster
			- Step 2: Look for the next cluster
			- Step 3: Since the FAT has marked “EOF”, we 
have reached the last cluster

			  Note. The file size help determine how many bytes to read from the last cluster.

		- Write Files

			- Step 1: Locate the Last Cluster
			- Step 2: Start writing to the non-full Cluster
			- Step 3: Allocate the next cluster through FSINFO

			  The search for the next free cluster is a circular, next-available search.
			  
			  Why implementing next-available? 
			  Principle of locality
			  
			  Why circular? 
			  To find out every free block

			- Step 4: Updates the FATs and FSINFO
			- Step 5: When write finishes, update the file size

		- Delete FIles

			- Step 1: De-allocate all the blocks involved. Update FSINFO and FATs.
			- Step 2: Change the first byte of the directory entry to 0xE5.
LFN entries also receive the same treatment.

			  (Delete the Directory entry)

		- Recover Deleted Files

		  Principle of “rescue” deleted file
		  Data persists unless the sectors are reallocated and overwritten.

- Details of Ext2/3 File System

	- Layout

		- Index-Node Allocation

		  • The file system is not that simple…
		  – it is divided into groups, and …
		  – every group has the same structure.
		  
		  For reliability and Performance

			- Group

				- SuperBlock

				  All the Group has the same SuperBlock
				  
				  For reliability
				  
				  The superblock in Group 0 is called the primary superblock.
				  Other superblocks are called the backup superblock. 
				  
				  Stores the FS specific data
				  Total number of inodes in the system.
				  Total number of blocks in the system.
				  Number of reserved blocks
				  Total number of free blocks.
				  Total number of free inodes.
				  Location of the first block.
				  The size of a block.

				- GDT(Group Descriptor Table)
				- Block Bitmap

				  A bit string that represents if a block is allocated or not.

				- Inode Bitmap

				  A bit string that represents if an inode is allocated or not.
				  
				  That also means the number of files in the file system is fixed!

				- Inode Table
				- Data Blocks

	- Inode and Directory Structure

		- Inode Structure

		  Bigger than normal Inode, contains more information about the files.
		  
		  128 Bytes per Inode

		- Directory Structure

		  The directory entry stores the file name and the inode #.

		- Accessing Directory File

	- Link File

		- Hard Link

		  A hard link is a directory entry pointing to an existing file.
		  – No new file content is created!
		  Conceptually speaking, this creates a file with two pathnames.
		  
		  Special hard links
		  – The directory “.” is a hard link to itself.
		  – The directory “..” is a hard link to the parent directory.

			- Link Count in Inode

			  It stores the number of directory entries pointing to the inode.

		- Symbolic Link

		  A symbolic link is a file.
		  – Unlike the hard link, a new inode is created for each symbolic link.
		  – It stores the pathname (shortcut)
		  
		  How to store the target path?
		  – If the pathname is less than 60 characters
		  – It is stored in the 12 direct block and the 3 indirect block pointers.
		  – Else, one extra data block is allocated

	- Buffer Cache

		- Kernel Buffer Cache

		  – The kernel will keep a set of copies of the read/written data blocks.
		  – The space that stores those blocks are called the buffer cache.
		  – It is used for reducing the time in accessing those blocks in the near future
		  
		  Why effective?
		  – Principle of locality
		  
		  Remember, those cached data is stored in the kernel even though the corresponding file is closed!
		  
		  By the way, the cache is managed under the LRU algorithm.

			- Page Cache

			  It buffers the data blocks of an opened file.

			- Directory Entry Cache

			  Directory entry is stored in the kernel.

			- Inode Cache

			  The content of an inode is stored in the kernel temporary.

			- Write Mode

				- Write-through Mode

				  Both the on-disk and the cached copies update together.

				- Write-back Mode

				  When a piece of data is going to be written to a file, the cached copy is updated first. The update of the on-disk copy is delayed.
				  
				  On-demand writing dirty blocks back.

		- Readahead

		  A blocking system call that stores requested range of data into the kernel page caches
		  Later read() calls over the range will not block.
		  
		  – When a file reading operation is requesting for Block x, there is a chance that Block x+1 will also be needed.

	- Journaling

	  A journal is the log book for the file system.
	  – It is kept inside the file system, i.e., inside the disk.
	  
	  • In database: Write-ahead logging
	  • In file systems: Journaling
	  – Applications: Linux ext3 and ext4, Windows NTFS
	  
	  Basic idea: when updating the disk, before overwriting the structures in place, first write down a little note describing what you are about to do
	  
	  • In order to make use of the journal:
	  – A set of file system operations becomes an atomic transaction.
	  • Either all operations are completed successfully, or
	  • no operation is completed.
	  
	  – A transaction marks all the changes that will be done to the FS.
	  – Every transaction is written to the journal.

		- Data Journaling

		  – Write all data (metadata+data) to journal
		  • Before writing them to their final disk locations, we first write them to log (a.k.a. journal)
		  
		  • The log is of finite size
		  – What problems may arise if it is full?
		  • Long time to replay
		  • Unable to append new transactions
		  
		  • Manage as a circular log
		  – Free space after checkpointing

			- Journaling Layout

				- TxB(Transaction Begin Block)

				  • It contains some kind of transaction identifier (TID)

				- I[v2](Inode)
				- B[v2](Bitmap)
				- Db(Data Block)
				- TxE(Transaction End Block)

				  • Marker of the end of this transaction
				  • It also contain the TID

			- CheckPoint

			  – Overwrite the old structures in the file system after the transaction being safely on disk

			- Operation Sequence

				- Journal Write

				  • Write the transaction to log and wait for these writes to complete
				  • TxB, all pending data, metadata updates, TxE

					- Issue 1 block at a time

					  • It is slow because of waiting for each to complete

					- Issue all blocks at once

					  • Five writes -> a single sequential write: Faster way
					  • However, it is unsafe…
					  • The disk internally may perform scheduling and complete small pieces of the big write in any order

						- When crash occurs during the writes to journal. That's may cause some data lost
						- Solution

							- Journal Wirte

							  • First step: writes all blocks except the TxE block to journal

							- Journal Commit

							  • Second step: file system issues the write of the TxE
							  Make sure the write of TxE is atomic

						- Operation Sequence

						  The write order must be guaranteed

							- Journal Write
							- Journal Commit
							- CheckPoint

						- Recovery

							- Case 1: crash happens before journal commit

							  Easy! Skip the pending update

							- Case 2: crash happens after journal commit, but before checkpoint

							  Replay transactions in order. Called redo logging

				- CheckPoint

				  • Write the pending metadata and data updates to their final locations

		- MetaData Journaling

		  Logging metadata only, to avoid write every Data Block to disk twice. So Data Block will not write to Journal

			- Write-back Mode: No Order Restriction

			  – How about data is written to disk after journal commit?
			  • File system is consistent (from the perspective of metadata)
			  • Metadata points to garbage data

			- Ordered Mode

			  – Data is written to file system before journal commit
			  – Rule: 
			  • Write the pointed-to object before the object that points to it
			  • Core of crash consistency
			  – Widely deployed by Ext3, NTFS, etc.

			- Write Sequence

				- 1. Data Write
				- 2. Journal MetaData Write
				- 3. Journal Commit
				- 4. CheckPoint MetaData
				- 5. Free

		- Working Principle

		  – All the changes to the FS are written to the journal first, including:
		  • the changes in the metadata, i.e., information other than the file content. E.g., the inodes, the directory entries, etc.
		  • the file data (depends on data journaling/metadata journaling)
		  
		  – Then, the system call returns to the user process.
		  
		  – Meanwhile, the entries in the journal are replayed and the changes are reflected to the actual file system.

	- VFS(Virtual File System)

	  VFS: an FS abstraction layer
	  – Transparently and uniformly supports multiple FSes
	  – A VFS specifies an interface 
	  – A specific FS implements this interface

### I/O System

- I/O Hardware

	- Incredible Variety of I/O Devices

		- Storage
		- Transmission
		- Human-Interface

	- Common Concepts

		- Port

		  connection point for device

		- Bus

		  daisy chain or shared direct access
		  
		  PCI bus common in PCs and servers, PCI Express (PCIe) 
		  expansion bus connects relatively slow devices

		- Controller(Host Adapter)

		  – electronics that operate port, bus, device
		  Sometimes integrated
		  Sometimes separate circuit board (host adapter)

			- How to Control Devices

			  Devices usually have registers where device driver places commands, addresses, and data to write, or read data from registers after command execution
			  Data-in register, data-out register, status register, control register

			- How to Communicate with Controller

			  Devices have addresses, used by
			  Direct I/O instructions
			  Memory-mapped I/O
			  – Device data and command registers mapped to processor address space

- Polling(轮询)

	- For each Byte of I/O

		- 1. Read busy bit from status register until 0

		  Step 1 is busy-wait cycle to wait for I/O from device
		  Reasonable if device is fast
		  But inefficient if device is slow

		- 2. Host sets read or write bit and if write copies data into data-out register
		- 3. Hosts sets Command-Ready bit
		- 4. Controller sets busy bit, executes transfer
		- 5. Controller clears busy bit, error bit, command-ready bit when transfer done

- Interrupts

	- CPU Interrupt-Request Line

	  Triggered by I/O Devices
	  
	  Checked by processor after each instruction

		- Maskable Interrupt
		- Nonmaskable Interrupt

	- Interrupt Handler
	- Interrupt Vector

	  to dispatch interrupt to correct handler
	  Context switch at start and end
	  Based on priority, some are nonmaskable
	  Interrupt chaining if more than one device at same interrupt number

	- also used for Exceptions

	  Terminate process, crash system due to hardware error

	- System Call

- Direct Memory Access (DMA)

  Used to avoid programmed I/O (one byte at a time) (程序控制I/O) for large data movement 
  Requires DMA controller
  Bypasses CPU to transfer data directly between device & memory

	- How to Work?

	  OS writes DMA command block into memory 
	  Source and destination addresses
	  Read or write mode
	  Count of bytes
	  
	  Writes location of command block to DMA controller, then CPU can continue to execute other tasks
	  
	  DMA controller masters bus and does the transmission without CPU
	  DMA-request and DMA acknowledge between DMA controller and device controller

- Application I/O Interface

	- How to provide a standard and uniform I/O interface

		- Abstraction (抽象)
		- Encapsulation (封装)
		- Layering (分层)

- I/O Devices

	- Block Devices

		- Disk Drivers

		  Commands include read, write, seek
		  Raw I/O, direct I/O, or file-system access
		  Memory-mapped file access possible
		  	   - File mapped to virtual memory and clusters brought via demand paging
		  DMA

	- Character Device

		- Keyboards
		- Mice
		- Serial Ports

	- Network Devices

	  Socket Interface

- Clock & Timers

  Functionalities of hardware clock and timer
  Get current time
  Get elapsed time
  Timer
  
  Programmable interval timer (可编程间隔定时器) used for timings, periodic interrupts
  Process scheduler: interrupt when time quantum is zero
  I/O subsystem: periodic flush

- 2 I/O Methods

	- Synchronous
	- Asynchronous

- Kernel I/O Subsystem

  Kernel I/O subsystem provides many services

	- I/O Scheduling

	  Maintain a per-device queue
	  Re-ordering the requests
	  Average waiting time, fairness, etc.

	- Buffering

	  - store data in memory while transferring between devices
	  To cope with device speed mismatch
	  To cope with device transfer size mismatch
	  To maintain “copy semantics” (e.g., copy from application’s buffer to kernel buffer)

	- Caching

	  - faster device holding copy of data
	  Always just a copy
	  Key to performance
	  Sometimes combined with buffering

	- Spooling

	  - hold output for a device
	  If device can serve only one request at a time, e.g., Printing

	- Error Handling & I/O Protection

	  OS can recover from disk read error, device unavailable, transient write failures
	  All I/O instructions defined to be privileged

	- Power Management

## Overview

### OS Services

- for helping users

	- UI
	- Program execution
	- I/O operations
	- FS manipulation
	- Communications
	- Error detection

- for ensuring efficiency

	- Resource alloction
	- Accounting -- Keep track of resources
	- Protection & Security

*XMind - Trial Version*