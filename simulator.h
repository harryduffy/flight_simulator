typedef struct passenger {
    // char* name; maybe do this one later
    int id;
    int in_seat;
    int row;
    int col;
} Passenger;

Passenger** plane_init(int amount_rows, int amount_cols);

int plane_destroy(int amount_rows, Passenger** passengers);

void repr_plane(int amount_rows, int amount_cols, Passenger** passengers);

void simulate_by_cols(int amount_rows, int amount_cols, Passenger** passengers);

void simulate_by_rows(int amount_rows, int amount_cols, Passenger** passengers);
