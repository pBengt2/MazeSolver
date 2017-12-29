//
// Solve maze in dynamic linked list created from input
//
// Peter Bengtson
// Windows 7 64bit, notepad++
// U. of Illinois, Chicago
// CS211, Fall 2016
// Project 3
//

//maze debug:
//arranged with number pad
//789	7 above+left, 8 above, 9 above+right
//4 6	4 left, 6 right
//123	1 below+left, 2 below, 3 below+right


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int DEBUG = FALSE;

typedef struct linkedList{
	int x;
	int y;
	struct linkedList *next;
	struct linkedList *prev;
} linkedList;

void printSolution(linkedList* head){
	//empty
	if (head==NULL){
		printf("\nThe maze has no solution.\n");
		return;
	}
	
	//print solution
	linkedList* cur = head;
	linkedList* temp;
	printf("\nA solution to the maze:\n");
	
	int i = 0;
	while (cur != NULL){
		if (i%5 == 0)
			printf("\n");
		i++;
		
		printf("(%d,%d) ", (cur->x)+1, (cur->y)+1);
		temp = cur;
		cur= cur->next;
		free(temp); //free node after printing
	}
	printf("\n");
	return;
}

void printMaze(char** maze, int x, int y){
	printf("\n");
	
	//top border
	for (int i=0; i<=x+1; i++)
		printf("*");
	printf("\n");
	
	//loop through and print char's
	for (int j=0; j<y; j++){
		printf("*");
		for (int i=0; i<x; i++){
			if (maze[i][j] == 'u')
				printf(".");
			else if(maze[i][j]== 'b')
				printf("*");
			else
				printf("%c", maze[i][j]);
		}
		printf("*\n");
	}
	
	//bot border
	for (int i=0; i<=x+1; i++)
		printf("*");
	printf("\n");
	return;
}

void printMazeInfo(char** maze, int x, int y){
	//print size
	printf("\nSize of Maze: %dx%d\n", x, y);
	
	//find start and end coords
	int xLoc = 0;
	int yLoc = 0;
	int found = FALSE;
	for (int i =0; i<x; i++){
		for (int j=0; j<y; j++){
			if (maze[i][j]=='s'){ //s found
				if (found == TRUE){ //e previously found
					printf("Start Location: %dx%d\n", i+1, j+1);
					printf("End Location: %dx%d\n", xLoc, yLoc);
					return;
				}
				found = TRUE;
				xLoc = i+1;
				yLoc = j+1;
			}
			else if (maze[i][j]=='e'){ //e found
				if (found == TRUE){ //s previously found
					printf("Start Location: %dx%d\n", xLoc, yLoc);
					printf("End Location: %dx%d\n", i+1, j+1);
					return;
				}
				found = TRUE; 
				xLoc = i+1;
				yLoc = j+1;
			}
		}
	}
	return;
}

linkedList* push(linkedList* cur, int x, int y){
	//print push if debugging
	if (DEBUG==TRUE){
		printf("push: %d, %d\n", x, y);		
	}
	//add new node, return pointer to it
	linkedList* temp = (linkedList*)malloc(sizeof(linkedList));
	temp->x = x;
	temp->y = y;
	temp->next = NULL;
	temp->prev = cur;
	cur->next = temp;
	return temp;
}

linkedList* pop(linkedList* cur){
	//free cur, return pointer to prev
	linkedList* temp = cur->prev;
	free(cur);
	temp->next = NULL;
	return temp;
}

char** createMaze(int x, int y){
	//dynamically allocate char array
	char** maze = (char**)malloc(sizeof(char*)*x);
	maze[0] = (char*)malloc(sizeof(char)*x*y);
	for (int i=0; i<x; i++)
		maze[i] = (*maze + y * i);
	
	for (int i = 0; i<x; i++)
		for (int j=0; j<y; j++)
			maze[i][j]='u';
	return maze;
}

int left(linkedList** cur, char** m, int x, int y, int col, char c){
	//if c matches char to left, push, and return true. Else false.
	x--;
	if (x >= 0){
		if (m[x][y]==c){
			*cur = push(*cur, x, y);
			return TRUE;
		}
	}
	return FALSE;
}

char right(linkedList** cur, char** m, int x, int y, int col, char c){
	//if c matches char to right, push, and return true. Else false.	
	x++;
	if (x < col){
		if (m[x][y]==c){
			*cur = push(*cur, x, y);
			return TRUE;
		}
	}
	return FALSE;	
}

char down(linkedList** cur, char** m, int x, int y, int row, char c){
	//if c matches char below, push, and return true. Else false.	
	y--;
	if (y >= 0){
		if (m[x][y]==c){
			*cur = push(*cur, x, y);
			return TRUE;
		}
	}
	return FALSE;
}

char up(linkedList** cur, char** m, int x, int y, int row, char c){
	//if c matches char to above, push, and return true. Else false.	
	y++;
	if (y < row){
		if (m[x][y]==c){
			*cur = push(*cur, x, y);
			return TRUE;
		}
	}
	return FALSE;
}

linkedList* move(linkedList* head, char** m, int col, int row){
	linkedList* cur = head;
	
	//find end position
	int endx = 0;
	int endy = 0;
	for (int i=0; i<col; i++){
		for (int j=0; j<row; j++){
			if (m[i][j]=='e'){
				endx = i;
				endy = j;
	}	}	}
					
	
	while (head!= NULL){
		int notFound = FALSE;
		int x = cur->x;
		int y = cur->y;
		//check for end; right, left, up, down
		if (right(&cur, m, x, y, col, 'e') == TRUE)
			return head;
		else if (left(&cur, m, x, y, col, 'e') == TRUE)
			return head;	
		else if (up(&cur, m, x, y, row, 'e') == TRUE)
			return head;		
		else if (down(&cur, m, x, y, row, 'e') == TRUE)
			return head;
		//check for unused; check towards end first
		else if ((endx-x == 0)&&(endy-y>0)){ //above
			if (up(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y+1] = '2';
			else if (right(&cur, m, x, y, col, 'u') == TRUE)
				m[x+1][y] = '2';
			else if (left(&cur, m, x, y, col, 'u') == TRUE)
				m[x-1][y] = '2';	
			else if (down(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y-1] = '2';
			else
				notFound = TRUE;			
		}
		else if ((endx-x==0)&&(endy-y<0)){ //below
			if (down(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y-1] = '8';
			else if (right(&cur, m, x, y, col, 'u') == TRUE)
				m[x+1][y] = '8';
			else if (left(&cur, m, x, y, col, 'u') == TRUE)
				m[x-1][y] = '8';
			else if (up(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y+1] = '8';
			else
				notFound = TRUE;	
		}
		else if ((endx-x<0)&&(endy-y==0)){ //left
			if (left(&cur, m, x, y, col, 'u') == TRUE)
				m[x-1][y] = '4';
			else if (up(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y+1] = '4';			
			else if (down(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y-1] = '4';
			else if (right(&cur, m, x, y, col, 'u') == TRUE)
				m[x+1][y] = '4';
			else
				notFound = TRUE;	
		}
		else if ((endx-x>0)&&(endy-y==0)){ //right
			if (right(&cur, m, x, y, col, 'u') == TRUE)
				m[x+1][y] = '6';
			else if (down(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y-1] = '6';
			else if (up(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y+1] = '6';
			else if (left(&cur, m, x, y, col, 'u') == TRUE)
				m[x-1][y] = '6';
			else
				notFound = TRUE;	
		}		
		else if ((endx-x > 0) && (endy-y >0)){ //upper right
			if (right(&cur, m, x, y, col, 'u') == TRUE)
				m[x+1][y] = '3';
			else if (up(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y+1] = '3';	
			else if (down(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y-1] = '3';
			else if (left(&cur, m, x, y, col, 'u') == TRUE)
				m[x-1][y] = '3';
			else
				notFound = TRUE;
		}
		else if((endx-x > 0) && (endy-y < 0)){ //right down
			if (right(&cur, m, x, y, col, 'u') == TRUE)
				m[x+1][y] = '9';
			else if (down(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y-1] = '9';
			else if (left(&cur, m, x, y, col, 'u') == TRUE)
				m[x-1][y] = '9';
			else if (up(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y+1] = '9';
			else
				notFound = TRUE;
			
		}
		else if((endx-x < 0) && (endy-y > 0)){ //left up
			if (left(&cur, m, x, y, col, 'u') == TRUE)
				m[x-1][y] = '1';
			else if (up(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y+1] = '1';		
			else if (right(&cur, m, x, y, col, 'u') == TRUE)
				m[x+1][y] = '1';
			else if (down(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y-1] = '1';
			else
				notFound = TRUE;
		}
		else {//left down
			if (left(&cur, m, x, y, col, 'u') == TRUE)
				m[x-1][y] = '7';
			else if (down(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y-1] = '7';
			else if (right(&cur, m, x, y, col, 'u') == TRUE)
				m[x+1][y] = '7';
			else if (up(&cur, m, x, y, row, 'u') == TRUE)
				m[x][y+1] = '7';
			else
				notFound = TRUE;
		}
		//not found. pop from stack
		if (notFound == TRUE){
			if (cur->prev != NULL){
				cur = pop(cur);
				if (DEBUG == TRUE)
					printf("pop: %d, %d\n", x, y);
			}
			else{
				if (DEBUG == TRUE)
					printf("pop: %d, %d\n", x, y);
				free(cur);
				return NULL;
			}
		}		
	}
	return NULL;
}

linkedList* solveMaze(char** maze, int col, int row){
	linkedList* head = (linkedList*)malloc(sizeof(linkedList));
	//find start position; add to stack
	for (int i=0; i<col; i++){
		for (int j=0; j<row; j++){
			if (maze[i][j]=='s'){
				head->x = i;
				head->y = j;
				head->next = NULL;
				head->prev = NULL;
				maze[i][j]=='b';
				if (DEBUG == TRUE)
					printf("push: %d, %d\n", i, j);
			}
		}
	}
	
	//move through maze
	head = move(head, maze, col, row);
	return head;
}

char** input(char* filename, int* col, int* row){
	//open file
	FILE *fp;
	fp = fopen(filename, "r");
	
	//check if file opened
	if (fp==NULL){
		fprintf(stderr, "%s failed to open\n", filename);
		exit(-1);
	}
	
	//read file
	char line[256];
	char* token; 
	
	char** maze;		
	int i = 0;
	int x = 0;
	int y = 0;
	//loop to read input
	while (fgets(line, 256, fp) != NULL){
		//get input
		token = strtok(line, " ");
		if(token==NULL) //check for empty line
			break;
		x = atoi(token);
		token = strtok(NULL, " ");
		if(token==NULL) //check for empty line
			break;
		y = atoi(token);

		//initialize maze
		if (i==0){
			if (x > 0 && y > 0){
				*col = x;
				*row = y;
				maze = createMaze(*col, *row);
				i++;
			}
			else{
				fprintf(stderr, "Invalid: Maze sizes must be greater than 0\n");
			}
		}
		//fill positions
		else if ((x > 0 && x <= *col) && (y > 0 && y <= *row)){
			x--; y--;
			//start coord
			if (i == 1){
				maze[x][y] = 's';
				i++;
			}
			//end coord
			else if (i == 2){
				if (maze[x][y] != 's'){
					maze[x][y] = 'e';
					i++;
				}
				else{
					fprintf(stderr, "Invalid: Start and end positions cannot be the same. \n");
				}
			}
			//blocked coords
			else{
				if (maze[x][y] != 's' && maze[x][y] != 'e'){
					maze[x][y]='b';
				}
				else{
					fprintf(stderr, "Invalid (%dx%d): Cannot block start or end.\n", x, y);
				}
			}
		}
		else{
			fprintf(stderr, "Invalid (%dx%d): Outside of range 1x1 to %dx%d.\n", x, y, *row, *col);
		}
	}
	if (i<3){
		fprintf(stderr, "Too few valid lines entered.");
		exit(-1);
	}
	
	fclose(fp); //close file
	
	return maze;
}

int main(int argc, char** argv){
	//get filename
	char* fname = (char*)malloc(sizeof(char));
	
	//check command line inputs
	if (argc > 3){
		fprintf(stderr, "Too many arguements");
		exit(-1);
	}
	
	for (int i=0; i<argc; i++){
		if ('-' == argv[i][0] && 'd' == argv[i][1]){
			DEBUG=TRUE; 	
		}
		else {
			strcpy(fname, argv[i]);
		}
	}
	
	//call input
	char** maze;
	int col = 0;
	int row = 0;
	maze = input(fname, &col, &row);
	free(fname);
	
	//print maze
	printMazeInfo(maze, col, row);
	printMaze(maze, col, row);
	
	//call solve
	linkedList* head = (linkedList*)malloc(sizeof(linkedList));
	head = solveMaze(maze, col, row);
	
	//if debug print altered maze
	if (DEBUG==TRUE)
		printMaze(maze, col, row);
	
	//print solution path
	printSolution(head);
	
	free(maze);
	
	return 0;
}