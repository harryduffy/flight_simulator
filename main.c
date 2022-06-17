#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "simulator.h"

/*
    Plane Visualisation
    
    1. A-B-C -|- E-F-G
    _______/\ ________
            \/
    i. A-B-C -|- E-F-G
    j. A-B-C -|- E-F-G
    _______/\ ________
            \/
    n. A-B-C -|- E-F-G
*/

int main(int argc, char** argv) {

    if (3 != argc) {
        return -1;
    }

    int plane_rows = strtol(argv[1], NULL, 10);
    int plane_cols = strtol(argv[2], NULL, 10);
    if (-1 == check_input(plane_rows, plane_cols)) {
        return -1;
    }
    

    // instantiate the plane
    Passenger** passengers = plane_init(plane_rows, plane_cols);

    // simulate by rows
    simulate_by_rows(plane_rows, plane_cols, passengers);

    // free all heap-based memory
    plane_destroy(plane_rows, passengers);

    return 0;

}

Passenger** plane_init(int amount_rows, int amount_cols) {

    /*
    Stored in 2D 'Passenger' array:
        [ 
            [.,.,.],[.,.,.],
            [.,.,.],[.,.,.],
            [.,.,.],[.,.,.] etc
        ]
    */
        
    Passenger** passengers = (Passenger**) malloc(amount_rows*amount_cols*sizeof(Passenger)); 

    int pass_id = 0;
    for (int r = 0; r < amount_rows; r++) {
        Passenger* row = (Passenger*) malloc(amount_cols*sizeof(Passenger));

        for (int c = 0; c < amount_cols; c++) {
            Passenger p = {.id=pass_id, .in_seat=0, .in_row=0, .row=r, .col=c};
            row[c] = p;
            pass_id++;
        }
        passengers[r] = row;
    }

    return passengers;

}

int plane_destroy(int amount_rows, Passenger** passengers) {
    
    for (int r = 0; r < amount_rows; r++) {
        free(passengers[r]);
    }
    free(passengers);

    return 1;
}

void repr_plane(int amount_rows, int amount_cols, Passenger** passengers) {

    for (int r = 0; r < amount_rows; r++) {
        printf("Row #%d. ", r);
        for (int c = 0; c < amount_cols; c++) {
            if (c == amount_cols-1) {
                printf("%d\n", passengers[r][c].in_seat);
                continue;
            } else if (c == amount_cols/2) {
                printf("|-%d-", passengers[r][c].in_seat);
                continue;
            }
            printf("%d-", passengers[r][c].in_seat);
        }
    }
}

void simulate_by_rows(int amount_rows, int amount_cols, Passenger** passengers) {

    // can do like percent in seat and stuff would be cool
    
    /*
        Idea:
            - passengers load plane by back half then by front half (back half must be completely filled before front half enters)
            - passengers load the plane randomly, some passengers may have to wait at their row
                before they can be seated (if they are not on window seat or middle seat if window seat has already
                been filled)
            - above point surmised: only once all members of a certain row have reached their row can they get into their seat
            - passengers load plane at a rate of 1 person per second
    */

    printf("\nSeating front:\n");
    repr_plane(amount_rows, amount_cols, passengers);
    printf("\n");
    clock_t t = clock();
    // O(n^2)
    int amount_seated = 0;
    while(amount_seated < ((amount_rows/2)*amount_cols)) {
        
        int row = rand() % amount_rows/2; 
        int col = rand() % amount_cols;

        if (1 == passengers[row][col].in_row) {
            continue;
        }
        
        if (1 != passengers[row][col].in_row) {
            printf("Passenger %d is walking to their seat.\n", passengers[row][col].id);
            printf("|");
            for (int t = 0; t < row; t++) {
                printf("-");
                fflush(stdout);
                sleep(1);
            }
            printf("|\n");

            passengers[row][col].in_row = 1;
            
            int counter = 0;
            for (int c = 0; c < amount_cols; c++) {
                if (1 == passengers[row][c].in_row) {
                    counter++;
                }
            }
            if (counter == amount_cols) {
                printf("\nRow %d has been filled!\n", row);
                for (int c = 0; c < amount_cols; c++) {
                    passengers[row][c].in_seat = 1;
                }
                repr_plane(amount_rows, amount_cols, passengers);
                printf("\n");
                amount_seated += amount_cols;
            }
        }
        sleep(1);
    }

    printf("Seating back:\n");
    repr_plane(amount_rows, amount_cols, passengers);
    printf("\n");
    amount_seated = 0;
    while(amount_seated < ((amount_rows/2)*amount_cols)) {
        
        int row = (amount_rows/2) + rand() % amount_rows/2; 
        int col = rand() % amount_cols;

        if (1 == passengers[row][col].in_row) {
            continue;
        }
        
        if (1 != passengers[row][col].in_row) {
            printf("Passenger %d is walking to their seat.\n", passengers[row][col].id);
            printf("|");
            for (int t = 0; t < row; t++) {
                printf("-");
                fflush(stdout);
                sleep(1);
            }
            printf("|\n");

            passengers[row][col].in_row = 1;
            
            int counter = 0;
            for (int c = 0; c < amount_cols; c++) {
                if (1 == passengers[row][c].in_row) {
                    counter++;
                }
            }
            if (counter == amount_cols) {
                for (int c = 0; c < amount_cols; c++) {
                    passengers[row][c].in_seat = 1;
                }
                repr_plane(amount_rows, amount_cols, passengers);
                printf("\n");
                amount_seated += amount_cols;
            }
        }
        sleep(1);
    }
    t = clock() - t;

    printf("Everyone seated. Time taken: %lu seconds.\n", t);
    printf("By Harry Duffy\n\n");
    
    
}

int check_input(int amount_rows, int amount_cols) {

    if (0 == amount_rows) {
        printf("Invalid amount of plane rows. Location: %s.%d\n", __FILE__, __LINE__);
        return -1;
    } else if (0 == amount_cols) {
        printf("Invalid amount of plane cols. Location: %s.%d\n", __FILE__, __LINE__);
        return -1;
    }

    if (amount_cols % 2 != 0) {
        printf("Invalid amount of plane cols. Location: %s.%d\n", __FILE__, __LINE__);
        return -1;
    } else if (amount_cols < 4) {
        printf("Invalid amount of plane cols. Location: %s.%d\n", __FILE__, __LINE__);
        return -1;
    }

    return 1;
}