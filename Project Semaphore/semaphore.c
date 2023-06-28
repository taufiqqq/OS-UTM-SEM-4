#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct
{
    int passengerRequests;
    int availableDrivers;
    pthread_mutex_t mutex;
    pthread_cond_t condition;
} UberSystem;

UberSystem uber;

void init_uber_system(UberSystem *sys)
{
    sys->passengerRequests = 0;
    sys->availableDrivers = 1;
    pthread_mutex_init(&sys->mutex, NULL);
    pthread_cond_init(&sys->condition, NULL);
}

void wait_semaphore(UberSystem *sys, int passengerID)
{
    pthread_mutex_lock(&sys->mutex);
    while (sys->availableDrivers <= 0)
    {
        printf("\nwait() loop - Passenger %d is waiting for an available driver...\n", passengerID);
        pthread_cond_wait(&sys->condition, &sys->mutex);
    }
    sys->availableDrivers--;
    pthread_mutex_unlock(&sys->mutex);
}

void signal_semaphore(UberSystem *sys, int passengerID)
{
    printf("\nsignal() Passenger %d exiting car\n", passengerID);
    pthread_mutex_lock(&sys->mutex);
    sys->availableDrivers++;
    pthread_cond_signal(&sys->condition);
    pthread_mutex_unlock(&sys->mutex);
}

void *process_ride_request(void *arg)
{
    int passengerID = *(int *)arg;
    printf("\nNew ride request from passenger %d\n", passengerID);

    // Simulating a ride request
    pthread_mutex_lock(&uber.mutex);
    uber.passengerRequests++;
    pthread_mutex_unlock(&uber.mutex);

    // Wait for an available driver
    wait_semaphore(&uber, passengerID);

//critical section
    // Assign a driver to the ride request
    printf("\nUserID - %d Ride request %d assigned to a driver. Available drivers: %d\n", passengerID, passengerID, uber.availableDrivers);

    // Simulating driver's journey to pick up the passenger
    printf("\nUserID - %d Driver is on the way to pick up passenger %d\n", passengerID, passengerID);
    sleep(2);

    // Simulating the ride
    printf("\nUserID - %d Driver picked up passenger %d. Ride in progress...\n", passengerID, passengerID);
    sleep(3);

    // Simulating completion of the ride
    printf("\nUserID - %d Ride completed for passenger %d. Driver is now available.\n", passengerID, passengerID);

    // Signal that the driver is available
    signal_semaphore(&uber, passengerID);

    return NULL;
}

// Example usage

int main()
{
    printf("\nSemaphore-like Implementation - Uber-like System\n");

    init_uber_system(&uber);

    // Create multiple ride request threads
    pthread_t threads[3];
    int passengerIDs[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&threads[i], NULL, process_ride_request, (void *)&passengerIDs[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
