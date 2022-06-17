typedef struct passenger {
    // char* name; maybe do this one later
    int id;
    int row;
    int col;
} Passenger;

Passenger** plane_init(int amount_rows, int amount_cols);
int plane_destroy(Passenger** passengers);
void repr_plane(int amount_rows, int amount_cols, Passenger** passengers);