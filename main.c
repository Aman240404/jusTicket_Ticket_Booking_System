#include <stdio.h>
#include <string.h>
#include "Screens/splash.c"
#include "Screens/logged_in.c"
#include "Screens/registered.c"

// Struct for User Registration
struct User {
    char username[50];
    char password[50];
};

// Struct for Movie Listing and Booking
struct Movie {
    char name[50];
    int availableSeats;
    float pricePerSeat;
    int seatNumber[100]; // Array to track seat numbers
};

struct User users[10];
int userCount = 0;

struct Movie movies[3] = {
    {"HIT:The third Case", 100, 200.0, {0}},
    {"Vidutalai:Part-2", 80, 250.0, {0}},
    {"Fateh", 50, 300.0, {0}}
};

// Register a User
void registerUser() {
    printf("Enter username: ");
    scanf("%s", users[userCount].username);
    printf("Enter password: ");
    scanf("%s", users[userCount].password);
    userCount++;
    printf("-------------------------------------------Registration successful!----------------------------------------------------\n");
    registered();
}

// Authenticate User
int loginUser() {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(username, users[i].username) == 0 &&
            strcmp(password, users[i].password) == 0) {
            printf("---------------------------------------------------Login successful!----------------------------------------------\n");
            logged_in();
            return 1;
        }
    }
    printf("Invalid credentials.\n");
    return 0;
}

// List Movies
void listMovies() {
    printf("\nAvailable Movies:\n");
    for (int i = 0; i < 3; i++) {
        printf("%s - Seats: %d - Price: %.2f\n",
               movies[i].name, movies[i].availableSeats, movies[i].pricePerSeat);
    }
}

// Book Seats and Show Seat Numbers
void bookSeats() {
    char movieName[50];
    int seats, assignedSeats[100];
    printf("Enter movie name: ");
    scanf("%s", movieName);
    printf("Enter number of seats: ");
    scanf("%d", &seats);

    for (int i = 0; i < 3; i++) {
        if (strcmp(movieName, movies[i].name) == 0) {
            if (movies[i].availableSeats >= seats) {
                movies[i].availableSeats -= seats;

                // Assign seat numbers
                int count = 0;
                for (int j = 0; j < 100; j++) {
                    if (movies[i].seatNumber[j] == 0) { // Check if seat is available
                        movies[i].seatNumber[j] = 1;   // Mark seat as booked
                        assignedSeats[count++] = j + 1; // Assign seat number
                        if (count == seats) break;
                    }
                }

                printf("Booking successful! Total price: %.2f\n", seats * movies[i].pricePerSeat);
                printf("Your seat numbers are: ");
                for (int k = 0; k < seats; k++) {
                    printf("%d ", assignedSeats[k]);
                }
                printf("\n");
                return;
            } else {
                printf("Not enough seats available.\n");
                return;
            }
        }
    }
    printf("Movie not found.\n");
}

int main() {
    title();
    int choice, loggedIn = 0;

    while (1) {
        printf("\nMenu:\n1. Register\n2. Login\n3. List Movies\n4. Book Seats\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loggedIn = loginUser();
                break;
            case 3:
                if (loggedIn) {
                    listMovies();
                } else {
                    printf("--------------------------------------------Please log in first.-------------------------------------------\n");
                }
                break;
            case 4:
                if (loggedIn) {
                    bookSeats();
                } else {
                    printf("--------------------------------------------Please log in first.-------------------------------------------\n");
                }
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}