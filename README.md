# PHILOSOPHERS

## Description
Philosopher's Dilemma is a simulation of philosophers sitting around a circular table, each with a bowl of rice and a fork between them. The philosophers alternate between eating, sleeping, and thinking. However, they must share the forks with their neighboring philosophers. If a philosopher is unable to eat for a certain period or encounters a deadlock while waiting for the forks, they may die. The goal of the simulation is to prevent any philosopher from dying by carefully managing their actions and resources.

## Requirements
- C Compiler
- Pthread library

## Usage

```bash
# Clone this project
git clone https://github.com/laugarci/philosophers

# Access
cd philosophers

# To run the simulation, compile the philo program using the provided Makefile:
make

# To run (example)
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
./philo 100 120 80 80 5

# To remove objects
make clean

# To remove objects and executable
make fclean

```

## Log Output
The program will print the states of philosophers in the following format:

- timestamp_in_ms X has taken a fork: Philosopher X has picked up a fork.
- timestamp_in_ms X is eating: Philosopher X is currently eating.
- timestamp_in_ms X is sleeping: Philosopher X is currently sleeping.
- timestamp_in_ms X is thinking: Philosopher X is currently thinking.
- timestamp_in_ms X died: Philosopher X has died.

## Implementation Details
The program utilizes POSIX threads (pthread) to represent each philosopher as a separate thread. Mutexes are used to protect the forks, ensuring that philosophers access them in a synchronized manner and avoid deadlocks. The program employs the gettimeofday function to calculate timestamps for the log output. The usleep function is used for time delays during eating, sleeping, and thinking.
