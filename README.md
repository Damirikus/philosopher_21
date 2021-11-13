# philosopher_21

You have to write a program for the mandatory part and another one for the bonus part
but they will have the same basic rules:
• Global variables are forbidden!
• The program should take the following arguments: number_of_philosophers time_to_die
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
◦ number_of_philosophers: is the number of philosophers and also the number
of forks.
◦ time_to_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’
milliseconds after starting their last meal or the beginning of the simulation,
it dies.
◦ time_to_eat: is in milliseconds and is the time it takes for a philosopher to
eat. During that time they will need to keep the two forks.
◦ time_to_sleep: is in milliseconds and is the time the philosopher will spend
sleeping.
◦ number_of_times_each_philosopher_must_eat: argument is optional, if all
philosophers eat at least ’number_of_times_each_philosopher_must_eat’ the
simulation will stop. If not specified, the simulation will stop only at the death
of a philosopher.
• Each philosopher should be given a number from 1 to ’number_of_philosophers’.
• Philosopher number 1 is next to philosopher number ’number_of_philosophers’.
Any other philosopher with the number N is seated between philosopher N - 1 and
philosopher N + 1.
About the logs of your program:
• Any change of status of a philosopher must be written as follows (with X replaced
with the philosopher number and timestamp_in_ms the current timestamp in milliseconds):
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
• The status printed should not be scrambled or intertwined with another philosopher’s status.
• You can’t have more than 10 ms between the death of a philosopher and when it
will print its death.
• Again, philosophers should avoid dying!
