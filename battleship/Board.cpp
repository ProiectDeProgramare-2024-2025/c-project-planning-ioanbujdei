#include "Board.h"
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;

//Converting letters (from the text file with coordinates) to rows
int LetterToRow(char letter){
    letter = toupper(letter);
    return int(letter) - 65;
}

//Converting a string to a row and a column
void ParseCoordinates(string coord, int& row, int& column){
    row = LetterToRow(coord[0]);
    column = coord[1] - '0';
}

// Reads the board state from a text file into a 2D grid
void ReadBoardFromFile(string filename, char board[BoardSize][BoardSize]){
    ifstream file(filename);
    for (int i = 0; i < BoardSize; ++i)
        for (int j = 0; j < BoardSize; ++j)
            file >> board[i][j];
}

// Writes the current board state to a text file
void WriteBoardToFile(string filename, char board[BoardSize][BoardSize]){
    ofstream file(filename);
    for (int i = 0; i < BoardSize; ++i) {
        for (int j = 0; j < BoardSize; ++j) {
            file << board[i][j] << " ";
        }
        file << "\n";
    }
}

Board::Board() {}

// Loads the board from a file
void Board::loadFromFile(string filename) {
    ReadBoardFromFile(filename, grid);
}

// Saves the board to a file
void Board::saveToFile(string filename) {
    WriteBoardToFile(filename, grid);
}

char& Board::at(int row, int column) {
    return grid[row][column];
}

// Prints the current state of the board
void Board::print() const {
    cout << "  ";
    for (int column = 0; column < BoardSize; column++) {
        cout << column << " ";
    }
    cout << endl;

    for (int row = 0; row < BoardSize; row++) {
        cout << char('A' + row) << " ";
        for (int column = 0; column < BoardSize; column++) {
            char cell = grid[row][column];
            if (cell == 'X')
                cout << "\033[32m" << "X" << "\033[0m ";
            else if (cell == 'O')
                cout << "\033[31m" << "O" << "\033[0m ";
            else if (cell == 'S')
                cout << "\033[36m" << "S" << "\033[0m ";
            else
                cout << cell << " ";
        }
        cout << endl;
    }
}


bool Board::applyAttack(string coord) {
    // Check if the coordinate is valid (e.g. A0 to J9)
    coord[0] = toupper(coord[0]);
    if (coord.length() != 2 || coord[0] < 'A' || coord[0] > 'J' || coord[1] < '0' || coord[1] > '9') {
        cout << "\033[33mInvalid coordinate. Please choose a row between 'A' and 'J' and a column between '0' and '9'\033[0m" << endl;
        return false;
    }

    int row, column;
    ParseCoordinates(coord, row, column);

    char& cell = at(row, column);
    if (cell == 'S') {
        cell = 'X';
        cout << "\033[32mHit!\033[0m" << endl;
        return true;
    } else if (cell == '.') {
        cell = 'O';
        cout << "\033[31mMiss!\033[0m" << endl;
        return false;
    } else {
        cout << "\033[33mAlready attacked.\033[0m" << endl;
        return false;
    }
}


// Counts how many ship cells ('S') are still on the board
int Board::countShips() {
    int shipsLeft = 0;
    for (int i = 0; i < BoardSize; i++)
        for (int j = 0; j < BoardSize; j++)
            if (at(i, j) == 'S')
                shipsLeft++;
    return shipsLeft;
}

// Clears board 
void Board::clearBoard(){
    for (int i = 0; i < BoardSize; ++i)
        for (int j = 0; j < BoardSize; ++j)
            grid[i][j] = '.';
}
