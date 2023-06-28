#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <semaphore.h>

#define MAX_DRIVERS 2
#define MAX_NAME_LENGTH 20
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_PASSENGERS 3

typedef struct
{
    char name[MAX_NAME_LENGTH];
    bool available;
} Driver;

Driver drivers[MAX_DRIVERS];
sem_t semaphore;

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    Driver *assignedDriver;
    bool inRide;
} Passenger;

Passenger passengers[MAX_PASSENGERS];

void initializeDrivers()
{
    for (int i = 0; i < MAX_DRIVERS; i++)
    {
        sprintf(drivers[i].name, "Driver %d", i + 1);
        drivers[i].available = true;
    }
}

void displayAvailableDrivers()
{
    printf("Available drivers:\n");
    for (int i = 0; i < MAX_DRIVERS; i++)
    {
        if (drivers[i].available)
        {
            printf("%d. %s\n", i + 1, drivers[i].name);
        }
    }
}

void bookDriver(Passenger *passenger)
{
    sem_wait(&semaphore);

    if (passenger->assignedDriver != NULL && passenger->inRide)
    {
        printf("You already have an active ride. Please complete the current ride first.\n");
        sem_post(&semaphore);
        return;
    }

//kena implement semaphore punya variable sini
//means availibility, wait and signal tu
    int driverIndex = -1;
    for (int i = 0; i < MAX_DRIVERS; i++)
    {
        if (drivers[i].available)
        {
            driverIndex = i;
            break;
        }
    }

    if (driverIndex != -1)
    {
        drivers[driverIndex].available = false;
        passenger->assignedDriver = &drivers[driverIndex];
        printf("%s assigned to passenger %s.\n", passenger->assignedDriver->name, passenger->username);
        passenger->inRide = true;
    }
    else
    {
        printf("No available drivers at the moment. Please try again later.\n");
    }

    sem_post(&semaphore);
}

void updateRideStatus(Passenger *passenger)
{
    sem_wait(&semaphore);

    if (passenger->assignedDriver != NULL)
    {
        printf("Ride completed. Driver %s is now available.\n", passenger->assignedDriver->name);
        passenger->assignedDriver->available = true;
        passenger->inRide = false;
    }
    else
    {
        printf("You do not have an active ride.\n");
    }

    sem_post(&semaphore);
}

int login()
{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("--- UTM UBER LOGIN ---\n");
    printf("user: ");
    scanf("%s", username);
    printf("pass: ");
    scanf("%s", password);

    int passengerIndex = -1;
    for (int i = 0; i < MAX_PASSENGERS; i++)
    {
        if (strcmp(passengers[i].username, username) == 0 && strcmp(passengers[i].password, password) == 0)
        {
            passengerIndex = i;
            break;
        }
    }

    if (passengerIndex != -1)
    {
        printf("Login successful!\n");
        return passengerIndex;
    }
    else
    {
        printf("Invalid username or password.\n");
        return -1;
    }
}

int main()
{
    int choice;

    initializeDrivers();

    sem_init(&semaphore, 0, 1);

    strcpy(passengers[0].username, "user1");
    strcpy(passengers[0].password, "pass1");
    passengers[0].assignedDriver = NULL;
    passengers[0].inRide = false;

    strcpy(passengers[1].username, "user2");
    strcpy(passengers[1].password, "pass2");
    passengers[1].assignedDriver = NULL;
    passengers[1].inRide = false;

    strcpy(passengers[2].username, "user3");
    strcpy(passengers[2].password, "pass3");
    passengers[2].assignedDriver = NULL;
    passengers[2].inRide = false;

    printf("--- UTM UBER SYSTEM ---\n");

    while (true)
    {
        printf("\n1. Login\n");
        printf("2. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {

            int passengerIndex = login();
            if (passengerIndex != -1)
            {
                bool loggedIn = true;
                while (loggedIn)
                {
                    printf("\n--- Uber System --- \n");
                    printf("1. Book a driver\n");
                    printf("2. Update ride status\n");
                    printf("3. Logout\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);

                    switch (choice)
                    {
                    case 1:
                        bookDriver(&passengers[passengerIndex]);
                        printf("\n--- Uber System ---\n");
                        if (passengers[passengerIndex].assignedDriver != NULL)
                        {
                            printf("Driver assigned: %s\n", passengers[passengerIndex].assignedDriver->name);
                        }
                        break;
                    case 2:
                        updateRideStatus(&passengers[passengerIndex]);
                        printf("\n--- Uber System ---\n");
                        break;
                    case 3:
                        printf("Logging out...\n");
                        loggedIn = false;
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                    }
                }
            }
            else
            {
                printf("Login failed. Please try again.\n");
            }

            break;
        }

        case 2:
            printf("Exiting UTM UBER SYSTEM...\n");
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
