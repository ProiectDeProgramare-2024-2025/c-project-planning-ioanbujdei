#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

// Generates a random valid coordinate in format like "C7"
string generateRandomCoordinate() {
    char row = 'A' + rand() % 10;
    char column = '0' + rand() % 10;
    return string(1, row) + column;
}

// Adds the new attacked coordinate to the file
void appendAttackToFile(const string& filename, const string& coord) {
    ofstream file(filename, ios::app);
    file << coord << "\n";
}

//Print attack history board
void printAttackHistory(char grid[BoardSize][BoardSize]) {
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
                cout << "\033[32m" << cell << "\033[0m ";
            else if (cell == 'O')
                cout << "\033[31m" << cell << "\033[0m ";
            else
                cout << cell << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    // Expect exactly 3 arguments: attack coordinate, board1 file, board2 file
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <player1_attack_coord> <board1_file> <board2_file>\n";
        return 1;
    }

    string attackCoord = argv[1];             // Coordinate of player 1's attack
    string board1File = argv[2];              // Player 1's board file
    string board2File = argv[3];              // Computer's board file
    string attackHistoryFile = "attackHistory.txt"; // File for storing attack history

    Board Board1;
    Board Board2;

    // Load both boards from file at the start of each run
    Board1.loadFromFile(board1File);
    Board2.loadFromFile(board2File);

    // Prevent the game from continuing if someone already won
    if (Board1.countShips() == 0 || Board2.countShips() == 0) {
        if (Board1.countShips() == 0)
            cout << "\033[31mGame over: Computer already won.\033[0m" << endl;
        else
            cout << "\033[32mGame over: You won. Congratulation!\033[0m" << endl;
        return 0;
    }

    srand(time(0)); // Seed random number generator

    // Player 1 attack
    cout << "\033[36mYou attacked: " << attackCoord << "\033[0m" << endl;
    Board2.applyAttack(attackCoord);
    appendAttackToFile(attackHistoryFile, attackCoord);

    // Check if player 1 won
    if (Board2.countShips() == 0) {
        cout << "\033[32mYou win!\033[0m" << endl;
        ofstream clearFile(attackHistoryFile, ios::trunc);
        clearFile.close();
        Board1.saveToFile(board1File);
        Board2.saveToFile(board2File);
        return 0;
    }

    // Computer attack phase
    string computerCoordinate;
    bool valid = false;
    do {
        computerCoordinate = generateRandomCoordinate();
        int row, col;
        ParseCoordinates(computerCoordinate, row, col);
        char cell = Board1.at(row, col);
        if (cell == 'S' || cell == '.') valid = true;
    } while (!valid);

    cout << "\033[36mComputer attacked: " << computerCoordinate << "\033[0m" << endl;
    Board1.applyAttack(computerCoordinate);

    // Print player1 board
    cout << "\n\033[36mYour board right now:\033[0m\n" << endl;
    Board1.print();
    cout << "\033[36mYou have " << Board1.countShips() << " ship parts left.\033[0m\n" << endl;

    // Build attack history board
    char attackGrid[BoardSize][BoardSize];
    for (int i = 0; i < BoardSize; ++i)
        for (int j = 0; j < BoardSize; ++j)
            attackGrid[i][j] = '.';

    ifstream history(attackHistoryFile);
    string previousCoord;
    while (history >> previousCoord) {
        int r, c;
        ParseCoordinates(previousCoord, r, c);
        char cell = Board2.at(r, c);
        if (cell == 'X')
            attackGrid[r][c] = 'X';
        else if (cell == 'O')
            attackGrid[r][c] = 'O';
    }
    history.close();

    // Print attack history board
    cout << "\n\033[36mYour previous attacks (only X for hits, O for misses):\033[0m\n" << endl;
    printAttackHistory(attackGrid);

    cout << "\033[36mComputer has " << Board2.countShips() << " ship parts left.\033[0m\n" << endl;

    // Check if computer won
    if (Board1.countShips() == 0) {
        cout << "\033[31mComputer wins!\033[0m" << endl;
        ofstream clearFile(attackHistoryFile, ios::trunc);
        clearFile.close();
    }

    // Save updated boards
    Board1.saveToFile(board1File);
    Board2.saveToFile(board2File);

    return 0;
}
