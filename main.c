#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ROWS 29
#define COLS 65 * 2 + 1
#define ON  '#'
#define OFF ' '

int grid[ROWS][COLS] = {0};
int neighbours[ROWS][COLS] = {0};

int map_row(int row) {
    if (row < 0) return ROWS + row;
    if (row >= ROWS) return row - ROWS;
    return row;
}

int map_col(int col) {
    if (col < 0) return COLS + col;
    if (col >= COLS) return col - COLS;
    return col;
}

int isalive(int row, int col) {
    return grid[row][col];
}

int isvalid(int row, int col) {
    return (row >= 0 && row < ROWS) && (col >= 0 && col < COLS);
}

int count_neighbours(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            if (!isvalid(row + i, col + j)) continue;
            if (isalive(row + i, col + j)) count++;
        }
    }
    return count;
}

void update_neighbours() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) 
            neighbours[i][j] = count_neighbours(i, j);
    }
}

void update_grid() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (isalive(i, j)) {
                if (neighbours[i][j] < 2 || neighbours[i][j] > 3) {
                    grid[i][j] = 0; 
                }
            } else {
                if (neighbours[i][j] == 3) {
                    grid[i][j] = 1;
                }
            }
        }
    }
}

void print_grid() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j)
            if (isalive(i, j))
                putchar(ON);
            else 
                putchar(OFF);
        putchar('\n');
    }
}

void init_cell(int row, int col, int cell) {
    grid[map_row(row)][map_col(col)] = cell;
}

void init_glider(int row, int col) {
    init_cell(row, col + 1, 1);
    init_cell(row + 1, col + 2, 1);
    init_cell(row + 2, col, 1);
    init_cell(row + 2, col + 1, 1);
    init_cell(row + 2, col + 2, 1);
}

void init_block(int row, int col) {
    init_cell(row, col, 1);
    init_cell(row, col + 1, 1);
    init_cell(row + 1, col, 1);
    init_cell(row + 1, col + 1, 1);
}

void init_beehive(int row, int col) {
    init_cell(row, col + 1, 1);
    init_cell(row, col + 2, 1);
    init_cell(row + 1, col, 1);
    init_cell(row + 1, col + 3, 1);
    init_cell(row + 2, col + 1, 1);
    init_cell(row + 2, col + 2, 1);
}

void init_blinker(int row, int col) {
    init_cell(row, col, 1);
    init_cell(row, col + 1, 1);
    init_cell(row, col + 2, 1);
}

void init_toad(int row, int col) {
    init_cell(row, col + 1, 1);
    init_cell(row, col + 2, 1);
    init_cell(row, col + 3, 1);
    init_cell(row + 1, col, 1);
    init_cell(row + 1, col + 1, 1);
    init_cell(row + 1, col + 2, 1);
}

void init_beacon(int row, int col) {
    init_cell(row, col, 1);
    init_cell(row, col + 1, 1);
    init_cell(row + 1, col, 1);
    init_cell(row + 1, col + 1, 1);
    init_cell(row + 2, col + 2, 1);
    init_cell(row + 2, col + 3, 1);
    init_cell(row + 3, col + 2, 1);
    init_cell(row + 3, col + 3, 1);
}

void init_lwss(int row, int col) {
    init_cell(row, col + 1, 1);
    init_cell(row, col + 2, 1);
    init_cell(row + 1, col, 1);
    init_cell(row + 1, col + 3, 1);
    init_cell(row + 2, col, 1);
    init_cell(row + 2, col + 3, 1);
    init_cell(row + 3, col + 1, 1);
    init_cell(row + 3, col + 2, 1);
    init_cell(row + 3, col + 3, 1);
}

void init_gosper_glider_gun(int row, int col) {
    init_cell(row, col + 24, 1);
    init_cell(row + 1, col + 22, 1);
    init_cell(row + 1, col + 24, 1);
    init_cell(row + 2, col + 12, 1);
    init_cell(row + 2, col + 13, 1);
    init_cell(row + 2, col + 20, 1);
    init_cell(row + 2, col + 21, 1);
    init_cell(row + 2, col + 34, 1);
    init_cell(row + 2, col + 35, 1);
    init_cell(row + 3, col + 11, 1);
    init_cell(row + 3, col + 15, 1);
    init_cell(row + 3, col + 20, 1);
    init_cell(row + 3, col + 21, 1);
    init_cell(row + 3, col + 34, 1);
    init_cell(row + 3, col + 35, 1);
    init_cell(row + 4, col + 0, 1);
    init_cell(row + 4, col + 1, 1);
    init_cell(row + 4, col + 10, 1);
    init_cell(row + 4, col + 16, 1);
    init_cell(row + 4, col + 20, 1);
    init_cell(row + 4, col + 21, 1);
    init_cell(row + 5, col + 0, 1);
    init_cell(row + 5, col + 1, 1);
    init_cell(row + 5, col + 10, 1);
    init_cell(row + 5, col + 14, 1);
    init_cell(row + 5, col + 16, 1);
    init_cell(row + 5, col + 17, 1);
    init_cell(row + 5, col + 22, 1);
    init_cell(row + 5, col + 24, 1);
    init_cell(row + 6, col + 10, 1);
    init_cell(row + 6, col + 16, 1);
    init_cell(row + 6, col + 24, 1);
    init_cell(row + 7, col + 11, 1);
    init_cell(row + 7, col + 15, 1);
    init_cell(row + 8, col + 12, 1);
    init_cell(row + 8, col + 13, 1);
}

void init_simkin_glider_gun(int row, int col) {

    // Left block
    init_cell(row + 10, col + 10, 1);
    init_cell(row + 10, col + 11, 1);
    init_cell(row + 11, col + 10, 1);
    init_cell(row + 11, col + 11, 1);

    // Right block
    init_cell(row + 14, col + 22, 1);
    init_cell(row + 14, col + 23, 1);
    init_cell(row + 15, col + 22, 1);
    init_cell(row + 15, col + 23, 1);

    // Small glider
    init_cell(row + 12, col + 20, 1);
    init_cell(row + 12, col + 21, 1);
    init_cell(row + 13, col + 20, 1);
    init_cell(row + 13, col + 22, 1);
    init_cell(row + 14, col + 21, 1);

    // Left R-pentomino
    init_cell(row + 8, col + 8, 1);
    init_cell(row + 8, col + 9, 1);
    init_cell(row + 9, col + 7, 1);
    init_cell(row + 9, col + 8, 1);
    init_cell(row + 10, col + 8, 1);

    // Right R-pentomino
    init_cell(row + 16, col + 21, 1);
    init_cell(row + 16, col + 22, 1);
    init_cell(row + 17, col + 20, 1);
    init_cell(row + 17, col + 21, 1);
    init_cell(row + 18, col + 21, 1);
}


void grid_init() {
    int row = ROWS / 2;
    int col = COLS / 2;
    // init_glider(row, col);
    // init_block(row, col);
    // init_beehive(row, col);
    // init_blinker(row, col);
    // init_toad(row, col);
    // init_beacon(row, col);
    // init_lwss(row, col);
    init_gosper_glider_gun(0, 0);
    // init_simkin_glider_gun(0, 0);
}


void run() {
    grid_init();
    int quit = 0;

    while (!quit) {
        print_grid();
        putchar('\n');
        update_neighbours();
        update_grid();
        usleep(50000);
        system("clear");
    }
}

int main(void) {
    run();
    return 0;
}
