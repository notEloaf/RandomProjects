#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//Cell of sodoku board, set is true if the value was given by the user initially
struct cell{
	int val = 0;
	bool set = false;
};

//Forward declaration for printing a board
void print_board(cell board[9][9]);

//Position of pointer
int X = 0;
int Y = 0;

//Move pointer forwards
void move_pointer(){
	X++;
	if(X >= 9){
		X = 0;
		Y++;
	}
}

//Move pointer backwards
void backtrack(){
	if(X == 0 && Y == 0){
		return;
	}
	X--;
	if(X < 0){
		X = 8;
		Y--;
	}
}

//Check if value at (x,y) is valid in the current board
bool valid_value(cell board[9][9], int x, int y){
	int sectorX = x/3;
	int sectorY = y/3;

	int val = board[x][y].val;

	//Check the 3x3 sector this value resides in
	for(int dx = 3 * sectorX; dx < 3*sectorX+3; dx++){
		for(int dy = 3 * sectorY; dy < 3*sectorY+3; dy++){
			if(board[dx][dy].val == val && (x != dx && y != dy)){
				return false;
			}
		}
	}

	//Check the row
	for(int dx = 0; dx < 9; dx++){
		if(dx != x && board[dx][y].val == val){
			return false;
		}
	}

	//Check the column
	for(int dy = 0; dy < 9; dy++){
		if(dy != y && board[x][dy].val == val){
			return false;
		}
	}

	return true;
}

int main(int argc, char const *argv[])
{
	std::ifstream input("input.txt");
	std::string line;
	

	cell board[9][9];

	//Put sodoku board into a matrix
	int line_number = 0;
	while(input >> line){
		for(int x = 0; x < line.length(); x++){
			
			if(line[x] == '-'){
				board[x][line_number].val = 0;
			}else{
				board[x][line_number].val = line[x]-'0';
				board[x][line_number].set = true;
			}
			
			
		}
		line_number++;
	}
	
	print_board(board);

	//Run until pointer reaches end
	while(Y < 9){
		//Find first non given value
		while(board[X][Y].set == true && Y < 9){
			move_pointer();
		}
		
		//increment until a valid value is found or value becomes greater than 9
		board[X][Y].val++;
		while(!valid_value(board,X,Y)){
			board[X][Y].val++;
			if(board[X][Y].val > 9){
				break;
			}
		}

		//if the current value is 9 backtrack until the first non given value, otherwise move pointer forwards
		if(board[X][Y].val > 9){
			board[X][Y].val = 0;
			backtrack();
			while(board[X][Y].set){
				backtrack();
			}
		}else{
			move_pointer();
		}
	}


	std::cout << "\nSolution:" << std::endl;
	print_board(board);

	

	return 0;
}

//Prints out current board
void print_board(cell board[9][9]){
	std::cout << '\n';
	for(int y = 0; y < 9; y++){
		if(y==0){
			std::cout << "-------------\n";
		}
		for(int x = 0; x < 9; x++){
			if(x==0){
				std::cout << '|';
			}
			if(board[x][y].val == 0){
				std::cout << ' ';
			}else {
				std::cout << board[x][y].val;
			}
			if((x+1)%3==0){
				std::cout << '|';
			}
		}
		std::cout << '\n';
		if((y+1)%3==0){
			std::cout << "-------------\n";
		}
	}
}
