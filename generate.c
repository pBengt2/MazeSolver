//Maze Generator

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
	//size
	srand(time(NULL));
	int maxSize = 60;
	int minSize = 5;
	int col = rand() % (maxSize-minSize);
	col = col+minSize;
	int row = rand() % (maxSize-minSize);
	row = row+minSize;
	
	printf("%d %d\n", col, row);	
	
	//start
	int x = rand() % col;
	x++;
	int y = rand() % row;
	y++;
	printf("%d %d\n", x, y);
	
	//end
	x = rand() % col;
	x++;
	y = rand() % row;
	y++;
	printf("%d %d\n", x, y);	
	
	//blocks
	int numBlocks = rand() % (col*row); 
	numBlocks = rand() % numBlocks;
	for (int i=0; i<numBlocks; i++){
		x = rand() % col;
		x++;
		y = rand() % row;
		y++;
		printf("%d %d\n", x, y);
	}
	
	return 0;
}