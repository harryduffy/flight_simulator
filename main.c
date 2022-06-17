#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simulator.h"

/*
    Plane Visualisation
    
    1. A-B-C -|- E-F-G
    _______/\ ________
            \/
    i. A-B-C -|- E-F-G
    j. A-B-C -|- E-F-G
    k. A-B-C -|- E-F-G
    l. A-B-C -|- E-F-G
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
    if (0 == plane_rows) {
        printf("Invalid amount of plane rows. Location: %s.%d\n", __FILE__, __LINE__);
        return -1;
    } else if (0 == plane_cols) {
        printf("Invalid amount of plane cols. Location: %s.%d\n", __FILE__, __LINE__);
        return -1;
    }

    if (plane_cols % 2 != 0) {
        printf("Invalid amount of plane cols. Location: %s.%d\n", __FILE__, __LINE__);
        return -1;
    } else if (plane_cols < 4) {
        printf("Invalid amount of plane cols. Location: %s.%d\n", __FILE__, __LINE__);
        return -1;
    }

    // instantiate the plane
    Passenger** passengers = plane_init(plane_rows, plane_cols);

    repr_plane(plane_rows, plane_cols, passengers);

    // free all heap-based memory
    plane_destroy(passengers);

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
            Passenger p = {.id=pass_id, .row=r, .col=c};
            row[c] = p;
            pass_id++;
        }
        passengers[r] = row;
    }

    return passengers;

}

int plane_destroy(Passenger** passengers) {
    // free(passengers);
    // need to free all the rows as well

    // can check error codes here or something

    return 1;
}

void repr_plane(int amount_rows, int amount_cols, Passenger** passengers) {

    for (int r = 0; r < amount_rows; r++) {
        printf("Row #%d. ", r);
        for (int c = 0; c < amount_cols; c++) {
            if (c == amount_cols-1) {
                printf("%d\n", passengers[r][c].id);
                continue;
            } else if (c == amount_cols/2) {
                printf("|-%d-", passengers[r][c].id);
                continue;
            }
            printf("%d-", passengers[r][c].id);
        }
    }
}