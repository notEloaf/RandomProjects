#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <chrono>
#include <thread>

//WIDTH and HEIGHT of board
const int WIDTH = 100;
const int HEIGHT = 50;

//Max number of iterations to do
const int LIMIT = 100;

//Number of iterations performed
int count;

//Forward declerations
void draw(const bool board[WIDTH][HEIGHT]);
int get_neighbours(const bool board[WIDTH][HEIGHT], const int x, const int y);


int main(int argc, char const *argv[])
{
	count = 0;
	int ticks = 0;
	bool board[WIDTH][HEIGHT];
	bool updateBoard[WIDTH][HEIGHT];

	srand(time(NULL));

	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			double r = double(rand()) / RAND_MAX;
			if(r > 0.9){
				board[x][y] = true;
			}else{
				board[x][y] = false;
			}
		}
	}

	while(true && count <= LIMIT){
		draw(board);
		count++;
	
		//Loop over board, construct new board following GOL rules
		for(int y = 0; y < HEIGHT; y++){
			for(int x = 0; x < WIDTH; x++){
				int N = get_neighbours(board,x,y);
				switch(N){
					case 2:
						updateBoard[x][y] = board[x][y];
						break;
					case 3:
						updateBoard[x][y] = true;
						break;
					default:
						updateBoard[x][y] = false;
						break;
				}
			}
		}

		//Make the current board equal to the new calculate board
		for(int y = 0; y < HEIGHT; y++){
			for(int x = 0; x < WIDTH; x++){
				board[x][y] = updateBoard[x][y];
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return 0;
}

//Draw the given board
void draw(const bool board[WIDTH][HEIGHT]){
	system("clear");
	for(int y = 0; y < HEIGHT; y++){
		for(int x = 0; x < WIDTH; x++){
			if(y == 0 || y == HEIGHT-1){
				std::cout << '-';
			}else if(x == 0 || x == WIDTH-1){
				std::cout << '|';
			}else if(board[x][y] == true){
				std::cout << '#';
			}else{
				std::cout << ' ';
			}
		}
		std::cout << "\n";
	}
	std::cout << "Frame: " << count << "/" << LIMIT << "\n";
}

//Find the amount of true neighbours around (x,y)
int get_neighbours(const bool board[WIDTH][HEIGHT], const int x, const int y){
	int count = 0;
	for(int dx = -1; dx <= 1; dx++){
		for(int dy = -1; dy <= 1; dy++){
			if(x + dx >= 0 && x+dx < WIDTH && y+dy >= 0 && y+dy < HEIGHT){
				if(board[x+dx][y+dy] == true){
					count ++;
				}
			}
		}
	}
	return board[x][y] ? count-1 : count;
}
