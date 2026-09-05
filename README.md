# Philosophers

An implementation of the classic **Dining Philosophers Problem** in C, developed as part of the **42 curriculum**.

This project focuses on **multithreading, synchronization, mutexes, race conditions, and concurrent programming**.

## 🧠 About the Project

The goal of **Philosophers** is to simulate a group of philosophers sitting around a table.

Each philosopher repeatedly performs three actions:

1. Thinking
2. Eating
3. Sleeping

Each philosopher needs **two forks** to eat: the fork on their left and the fork on their right.

Since the philosophers run concurrently, the main challenge is to correctly manage shared resources while avoiding:

* Race conditions
* Deadlocks
* Data inconsistencies
* Unsynchronized access to shared data

The program must also monitor the philosophers and detect when one of them dies from starvation.

## ✨ Features

* One thread per philosopher.
* Mutex-based synchronization.
* Shared fork management.
* Precise simulation of eating, sleeping and thinking.
* Death detection.
* Configurable number of philosophers.
* Configurable timing parameters.
* Protection against race conditions.
* Proper thread creation and cleanup.
* Proper mutex initialization and destruction.
* Accurate timestamped output.

## 🍴 The Dining Philosophers Problem

Each philosopher has access to two forks shared with their neighbors.

For a philosopher to eat:

```text
        Fork
          |
     Philosopher
      /        \
   Fork        Fork
```

The philosopher must acquire both forks before eating.

This creates a concurrency problem because several philosophers may attempt to access the same forks simultaneously.

The implementation must synchronize access to these shared resources using **mutexes**.

## 🧵 Multithreading

Each philosopher is represented by a separate thread.

The threads execute concurrently and simulate the behavior of the philosophers.

Conceptually:

```text
Main Thread
    |
    +--- Philosopher 1 Thread
    |
    +--- Philosopher 2 Thread
    |
    +--- Philosopher 3 Thread
    |
    +--- Philosopher 4 Thread
    |
    +--- Philosopher N Thread
```

The program also needs to monitor the state of the philosophers and determine whether one of them has exceeded their allowed time without eating.

## 🔒 Mutexes

Forks are shared resources, so access to them must be protected.

Mutexes are used to ensure that two philosophers cannot use the same fork simultaneously.

For example:

```c
pthread_mutex_lock(&fork);

pthread_mutex_unlock(&fork);
```

Mutexes help prevent **race conditions** when multiple threads access shared data.

## ⚠️ Concurrency Challenges

One of the main challenges of the project is correctly synchronizing multiple threads.

The implementation must handle:

### Race Conditions

Several threads may try to read or modify the same data simultaneously.

Shared variables therefore need appropriate synchronization.

### Deadlocks

A deadlock can occur when philosophers wait indefinitely for forks held by other philosophers.

The implementation must avoid situations where every philosopher is waiting for a resource that another philosopher holds.

### Starvation

A philosopher must not be prevented indefinitely from eating because other philosophers continuously acquire the available forks.

## 📋 Arguments

The program is launched with:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep
```

An optional fifth argument can specify the number of times each philosopher must eat:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep number_of_times_each_philosopher_must_eat
```

### Parameters

| Argument                                    | Description                                      |
| ------------------------------------------- | ------------------------------------------------ |
| `number_of_philosophers`                    | Number of philosophers and forks                 |
| `time_to_die`                               | Maximum time a philosopher can go without eating |
| `time_to_eat`                               | Time spent eating                                |
| `time_to_sleep`                             | Time spent sleeping                              |
| `number_of_times_each_philosopher_must_eat` | Optional number of meals required                |

## 🚀 Installation

Clone the repository:

```bash
git clone <repository-url>
cd philo
```

Compile the project:

```bash
make
```

## ▶️ Usage

Example:

```bash
./philo 5 800 200 200
```

This starts a simulation with:

* 5 philosophers
* 800 ms before a philosopher dies
* 200 ms spent eating
* 200 ms spent sleeping

With the optional meal limit:

```bash
./philo 5 800 200 200 7
```

The simulation ends when every philosopher has eaten the required number of times.

## 📊 Output

The program displays timestamped actions for each philosopher.

Example:

```text
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 3 is thinking
400 1 is thinking
```

The output makes it possible to follow the state of each philosopher during the simulation.

## 🛠️ Technologies

* **C**
* **POSIX Threads (`pthread`)**
* **Mutexes**
* **Makefile**
* **Git**
* **Unix/Linux**

## 🧠 Concepts Practiced

This project allowed me to develop a deeper understanding of:

* Multithreading.
* POSIX threads.
* Mutexes.
* Thread synchronization.
* Concurrent programming.
* Race conditions.
* Deadlocks.
* Resource sharing.
* Critical sections.
* Thread lifecycle management.
* Precise time measurement.
* `usleep`.
* Memory management.
* Process synchronization concepts.


## 🧹 Makefile Commands

```bash
make
make clean
make fclean
make re
```

* `make` — compiles the project.
* `make clean` — removes object files.
* `make fclean` — removes object files and the executable.
* `make re` — cleans and recompiles the project.

## 🎯 Project Objective

The main objective of **Philosophers** was to understand how concurrent programs work and how multiple threads can safely share resources.

The project provided practical experience with **threads, mutexes, synchronization and race-condition prevention**, while implementing a classic computer science problem.

## 👤 Author

**Noura Akebli**

42 Network
