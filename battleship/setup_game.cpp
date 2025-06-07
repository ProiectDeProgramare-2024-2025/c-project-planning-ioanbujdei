#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "Board.h"

void placeComputerShip(int shipSize, Board* computer_board);

class setupInfo{
    public:
    int game_ongoing;
    int ship5_placed;
    int ship4_placed;
    int ship3_1_placed;
    int ship3_2_placed;
    int ship2_placed;

    public:
    void loadFromFile(std::string);
    void saveToFile(std::string);
};


void setupInfo::loadFromFile(std::string setup_info){
    ifstream fsetup_info(setup_info);

    std::string line;
    std::string token;

    std::getline(fsetup_info, line);
    token = line.substr(line.find('=') + 1, 1);
    game_ongoing = std::stoi(token);

    std::getline(fsetup_info, line);
    token = line.substr(line.find('=') + 1, 1);
    ship5_placed = std::stoi(token);

    std::getline(fsetup_info, line);
    token = line.substr(line.find('=') + 1, 1);
    ship4_placed = std::stoi(token);

    std::getline(fsetup_info, line);
    token = line.substr(line.find('=') + 1, 1);
    ship3_1_placed = std::stoi(token);

    std::getline(fsetup_info, line);
    token = line.substr(line.find('=') + 1, 1);
    ship3_2_placed = std::stoi(token);
    
    std::getline(fsetup_info, line);
    token = line.substr(line.find('=') + 1, 1);
    ship2_placed = std::stoi(token);
}


void printHelp(){
    std::cout << "---Battleship---" << std::endl;
    std::cout << "help - prints manual" << std::endl;
    std::cout << "new_game - creates new game" << std::endl;
    std::cout << "place <ship_coords1> <ship_coords2> - places a ship." << std::endl;
    std::cout << "Ships must be placed in order of decreasing size." << std::endl;
    std::cout << "reveal - prints player and computer game boards" << std::endl;
}


void newGame(setupInfo* setup_info, Board* player_board, Board* computer_board){
    //print board before
    std::cout << "Player Board before:" << std::endl;
    player_board->print();
    std::cout << std::endl;

    //set game_ongoing to 0
    setup_info->game_ongoing = 0;

    //set ships to not placed
    setup_info->ship5_placed = 0;
    setup_info->ship4_placed = 0;
    setup_info->ship3_1_placed = 0;
    setup_info->ship3_2_placed = 0;
    setup_info->ship2_placed = 0;

    //clear boards
    player_board->clearBoard();
    computer_board->clearBoard();
    
    //save setup_info to file
    ofstream file("setup_info.txt");
    file << "game_ongoing" << "=" << setup_info->game_ongoing << std::endl;
    file << "ship5_placed" << "=" << setup_info->ship5_placed << std::endl;
    file << "ship4_placed" << "=" << setup_info->ship4_placed << std::endl;
    file << "ship3_1_placed" << "=" << setup_info->ship3_1_placed << std::endl;
    file << "ship3_2_placed" << "=" << setup_info->ship3_2_placed << std::endl;
    file << "ship2_placed" << "=" << setup_info->ship2_placed << std::endl;

    //save boards to file
    player_board->saveToFile("board1.txt");
    computer_board->saveToFile("board2.txt");

    //print board after
    std::cout << "Player Board after:" << std::endl;
    player_board->print();

}

int placeShip(std::string coord1, std::string coord2, setupInfo* setup_info, Board* player_board, Board* computer_board){

    //are coordinates valid
    if (coord1.length() != 2 || coord1[0] < 'A' || coord1[0] > 'J' || coord1[1] < '0' || coord1[1] > '9') {
        cout << "\033[33mInvalid coordinate. Please choose a row between 'A' and 'J' and a column between '0' and '9'\033[0m" << endl;
        return -1;
    }

    if (coord2.length() != 2 || coord2[0] < 'A' || coord2[0] > 'J' || coord2[1] < '0' || coord2[1] > '9') {
        cout << "\033[33mInvalid coordinate. Please choose a row between 'A' and 'J' and a column between '0' and '9'\033[0m" << endl;
        return -1;
    }


    int row1, column1, row2, column2;
    ParseCoordinates(coord1, row1, column1);
    ParseCoordinates(coord2, row2, column2);

    //put cooardinates in order
    if(row1 > row2){
        int tmp = row1;
        row1 = row2;
        row2 = tmp;
    }

    if(column1 > column2){
        int tmp = column1;
        column1 = column2;
        column2 = tmp;
    }

    //is a game ongoing
    if(setup_info->game_ongoing == 1){
        std::cout << "Error: a game is ongoing!" << std::endl;
        std::cout << "Start a new game to place ships." << std::endl;
        return -1;
    }

    //is it a line?
    if((row1 == row2 || column1 == column2) == false){
        std::cout << "Error: coordinates not in line!" << std::endl;
        return -1;
    }

    //is the ship the right size
    if(setup_info->ship5_placed == 0){
        if(((row2 - row1) +1 == 5 || (column2 - column1) +1== 5) == false){
            std::cout << "Error: wrong size ship!" << std::endl;
            std::cout << "A ship of size 5 should be placed!" << std::endl;
            return -1;
        }
    }
    else if(setup_info->ship4_placed == 0){
        if(((row2 - row1) +1 == 4 || (column2 - column1) +1== 4) == false){
            std::cout << "Error: wrong size ship!" << std::endl;
            std::cout << "A ship of size 4 should be placed!" << std::endl;
            return -1;
        }
    }
    else if(setup_info->ship3_1_placed == 0){
        if(((row2 - row1) +1 == 3 || (column2 - column1) +1== 3) == false){
            std::cout << "Error: wrong size ship!" << std::endl;
            std::cout << "A ship of size 3 should be placed!" << std::endl;
            return -1;
        }
    }
    else if(setup_info->ship3_2_placed == 0){
        if(((row2 - row1) +1 == 3 || (column2 - column1) +1== 3) == false){
            std::cout << "Error: wrong size ship!" << std::endl;
            std::cout << "A second ship of size 3 should be placed!" << std::endl;
            return -1;
        }
    }
    else if(setup_info->ship2_placed == 0){
        if(((row2 - row1) +1 == 2 || (column2 - column1) +1== 2) == false){
            std::cout << "Error: wrong size ship!" << std::endl;
            std::cout << "A ship of size 2 should be placed!" << std::endl;
            return -1;
        }
    }



    //check if spots free
    if(row1 == row2){
        for(int j = column1; j <= column2; j++){
            if(player_board->at(row1,j) != '.'){
               std::cout << "Error: spot occupied!" << std::endl;
               return -1;
            }
        }
    }
    else if(column1 == column2){
        for(int i = row1; i <= row2; i++){
            if(player_board->at(i,column1) != '.'){
               std::cout << "Error: spot occupied!" << std::endl; 
               return -1;
            }
        }
    }

    //print board before
    std::cout << "Player Board before:" << std::endl;
    player_board->print();
    std::cout << std::endl;

    //ok, finally place
    if(row1 == row2){
        for(int j = column1; j <= column2; j++){
            player_board->at(row1,j) = 'S';
        }
    }
    else if(column1 == column2){
        for(int i = row1; i <= row2; i++){
            player_board->at(i,column1) = 'S';
        }
    }

    
    //mark the ship as placed in setup_info
         if((((row2 - row1) +1) == 5 || ((column2 - column1) +1) == 5)){setup_info->ship5_placed = 1;}
    else if((((row2 - row1) +1) == 4 || ((column2 - column1) +1) == 4)){setup_info->ship4_placed = 1;}
    else if((((row2 - row1) +1) == 3 || ((column2 - column1) +1) == 3)){
        if(setup_info->ship3_1_placed == 0){setup_info->ship3_1_placed = 1;}
        else{setup_info->ship3_2_placed = 1;}
    }
    else if((((row2 - row1) +1) == 2 || ((column2 - column1) +1) == 2)){
        setup_info->ship2_placed = 1;
        //if all ships placed, set game_ongoing to 1
        setup_info->game_ongoing = 1;
    }

    //place computer ship
         if((((row2 - row1) +1) == 5 || ((column2 - column1) +1) == 5)){placeComputerShip(5, computer_board);}
    else if((((row2 - row1) +1) == 4 || ((column2 - column1) +1) == 4)){placeComputerShip(4, computer_board);}
    else if((((row2 - row1) +1) == 3 || ((column2 - column1) +1) == 3)){placeComputerShip(3, computer_board);}
    else if((((row2 - row1) +1) == 2 || ((column2 - column1) +1) == 2)){placeComputerShip(2, computer_board);}


    //save everything
    //save setup_info to file
    ofstream file("setup_info.txt");
    file << "game_ongoing" << "=" << setup_info->game_ongoing << std::endl;
    file << "ship5_placed" << "=" << setup_info->ship5_placed << std::endl;
    file << "ship4_placed" << "=" << setup_info->ship4_placed << std::endl;
    file << "ship3_1_placed" << "=" << setup_info->ship3_1_placed << std::endl;
    file << "ship3_2_placed" << "=" << setup_info->ship3_2_placed << std::endl;
    file << "ship2_placed" << "=" << setup_info->ship2_placed << std::endl;

    //save boards to file
    player_board->saveToFile("board1.txt");
    computer_board->saveToFile("board2.txt");

    //print board after
    std::cout << "Player Board after:" << std::endl;
    player_board->print();
    std::cout << std::endl;


    return 0;
}

void placeComputerShip(int shipSize, Board* computer_board){
    std::srand(time(0));
    int direction =  std::rand() % 2;

    bool place_succesful = false;

    int row, column;

    while(place_succesful == false){
        //right to left
        if(direction == 0){
            row = std::rand() % 10;
            column = std::rand() % (10 - shipSize);
        }
        //up to down
        else{
            row = std::rand() % (10 - shipSize);
            column = std::rand() % 10;
        }
        //are spots free?
        if(direction == 0){
            for(int j = column; j < column + shipSize; j++){
                if(computer_board->at(row,j) != '.'){
                    continue;
                }
            }
        }
        else{
            for(int i = row; i < row + shipSize; i++){
                if(computer_board->at(i,column) != '.'){
                    continue;
                }
            }
        }

        //ok, place
        if(direction == 0){
            for(int j = column; j < column + shipSize; j++){
                if(computer_board->at(row,j) = 'S'){
                    place_succesful = true;
                }
            }
        }
        else{
            for(int i = row; i < row + shipSize; i++){
                if(computer_board->at(i,column) = 'S'){
                    place_succesful = true;
                }
            }
        }
    }


}

void revealBoards(Board* player_board, Board* computer_board){

    std::cout << "Player Board:" << std::endl;
    player_board->print();
    std::cout << std::endl;

    std::cout << "Computer Board:" << std::endl;
    computer_board->print();


}



int main(int argc, char* argv[])
{
    //make object for setup_info
    setupInfo setup_info;
    setup_info.loadFromFile("setup_info.txt");

    //create boards
    Board player_board;
    player_board.loadFromFile("board1.txt");
    Board computer_board;
    computer_board.loadFromFile("board2.txt");

    //read option argument
    std::string option;
    if(argc <= 1){
        std::cout << "Error: Not enough arguments!" << std::endl;
        return -1;
    }
    else{
        option = argv[1];
    }

    //execute option
    if(option == "help"){printHelp();}
    else if(option == "new_game"){newGame(&setup_info, &player_board, &computer_board);}
    else if(option == "place"){
        if (argc != 4){
            std::cout << "Error: wrong number of arguments!" << std::endl;
            return -1;
        }
        std::string coord1 = argv[2];
        std::string coord2 = argv[3];
        placeShip(coord1, coord2, &setup_info, &player_board, &computer_board);
    }
    else if(option == "reveal"){revealBoards(&player_board, &computer_board);}
    else{std::cout << "Error: unknown command!" << std::endl;}



    
}