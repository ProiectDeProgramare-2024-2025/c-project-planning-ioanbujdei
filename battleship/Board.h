#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include <string>
#include <vector>
using namespace std;

const int BoardSize = 10;

int LetterToRow(char letter); // Converts a letter (A-J) to row index
void ParseCoordinates(string coord, int& row, int& column); // Splits a coordinate like "B3" into row and column
void ReadBoardFromFile(string filename, char board[BoardSize][BoardSize]); // Reads the board from file
void WriteBoardToFile(string filename, char board[BoardSize][BoardSize]); // Writes the board layout to file
//void printAttackHistory(char grid[BoardSize][BoardSize]); //Prints the attack history board

// Represents the battleship board
class Board {
private:
    char grid[BoardSize][BoardSize]; // The game grid
public:
    Board();
    void loadFromFile(string filename);                              // Load board from file
    void saveToFile(string filename);                                // Save board to file
    char& at(int row, int column);                                   // Access cell value
    void print() const;                                                    // Print board to console
    bool applyAttack(string coord);                                  // Apply an attack at given coordinate
    int countShips();                                                // Count remaining ship parts
    vector<Ship> ships;                                              // List of ships (not used in logic)
    void clearBoard();
};

#endif


