
#include <iostream>
#include <cstdlib>
#include <stack>
#include <ctime>

#include <deque>
#include <list>
#include <queue>
using namespace std;

int timer;

struct cell {

	bool NWALL;
	bool SWALL;
	bool EWALL;
	bool WWALL;
	bool WallsIntact;
	char roomLetter;
	int cellX;
	int cellY;
	int start;
	int finish;
	string color;


	int d; //distance for BFS

	int piX; //Coordinate X for parent
	int piY; //Coordinate Y for parent

};



void createMaze(cell **& iMaze, int iRow)

{

	int xAxis = iRow;
	int yAxis = iRow;

	iMaze = new cell*[iRow];
	for (int i = 0; i < iRow; i++)
	{
		//allocates matrx maze
		iMaze[i] = new cell[iRow];
	}

	char letter = 'A';
	for (int i = 0; i < xAxis; i++) {
		for (int j = 0; j < yAxis; j++) {
			iMaze[i][j].roomLetter = letter;
			iMaze[i][j].NWALL = true;
			iMaze[i][j].SWALL = true;
			iMaze[i][j].EWALL = true;
			iMaze[i][j].WWALL = true;
			iMaze[i][j].WallsIntact = true;
			iMaze[i][j].cellX = i;
			iMaze[i][j].cellY = j;
			letter++;
		}
	}

	iMaze[iRow - 1][iRow - 1].WallsIntact = false;

	//Random Lastwall break
	int i;
	i = (rand() % 2) + 1;

	if (i == 2)
	{
		iMaze[iRow - 1][iRow - 1].NWALL = false; //north of bottom right
		iMaze[iRow - 2][iRow - 1].SWALL = false; //bottom right
	}
	else
	{
		iMaze[iRow - 1][iRow - 2].EWALL = false; //west of bottom right
		iMaze[iRow - 1][iRow - 1].WWALL = false; //bottom right
	}
}

void displayShortestPathMaze(cell **& iMaze, cell *list, int iRow, int finalCount)
{
	int xAxis = iRow;
	int yAxis = iRow;

	for (int i = 0; i < xAxis; i++)
	{
		if (i == 0)
		{
			cout << "+" << " ";
			for (int z = 1; z < iRow; z++)
			{
				cout << "+" << "-";
			}
			cout << "+" << endl;
		}

		cout << "|";

		/*WEST/EAST WALLS------------------------------------------------------------------------------------------------*/
		for (int j = 0; j < yAxis; j++)
		{
			if (j + 1 == yAxis)
			{
				int v = 0;
				while(list[v].roomLetter != iMaze[i][j].roomLetter && v < finalCount)
				{
					v++;
				}
				if(list[v].roomLetter == iMaze[i][j].roomLetter)
				{
					cout << list[v].roomLetter << "|";
				}
				else if(i + 1 == iRow && j + 1 == iRow)
				{
					cout << iMaze[i][j].roomLetter << "|";
				}
				else
				{
					cout << " " << "|";
				}
			}

			if (iMaze[i][j].EWALL == true || iMaze[i][j + 1].WWALL == true)
			{
				int v = 0;
				if (j + 1 != yAxis)
				{
					while(list[v].roomLetter != iMaze[i][j].roomLetter && v < finalCount)
					{
						v++;
					}
					if(list[v].roomLetter == iMaze[i][j].roomLetter)
					{
						cout << list[v].roomLetter << "|";
					}
					else
					{
						cout << " " << "|";
					}
				}
			}

			else if (iMaze[i][j].EWALL == false || iMaze[i][j + 1].WWALL == false)
			{
				if (j + 1 != yAxis)
				{
					int v = 0;
					while(list[v].roomLetter != iMaze[i][j].roomLetter && v < finalCount)
					{
						v++;
					}
					if(list[v].roomLetter == iMaze[i][j].roomLetter)
					{
						cout << list[v].roomLetter << " ";
					}
					else
					{
						cout << " " << " ";
					}
				}
			}
		}

		cout << endl << "+";
		/*NORTH/SOUTH WALLS------------------------------------------------------------------------------------------------*/

		if (i < xAxis - 1)
		{
			for (int k = 0; k < xAxis; k++)
			{
				if (iMaze[i][k].SWALL == true || iMaze[i + 1][k].NWALL == true)
				{
					cout << "-" << "+";
				}
				else if (iMaze[i][k].SWALL == false || iMaze[i + 1][k].NWALL== false)
				{
					cout << " " << "+";
				}
			}
		}

		if (i == xAxis - 1)
		{
			for (int l = 1; l < xAxis; l++)
			{
				cout << "-" << "+";
			}
			cout << " " << "+";
		}

		cout << endl;
	}

	cout << endl << endl;
}

void displayMaze(cell **& iMaze, int iRow)
{
	int xAxis = iRow;
	int yAxis = iRow;

	for (int i = 0; i < xAxis; i++)
	{
		if (i == 0) //Before any boolean statements are checked the following output will always be true when yAxis is == 0
		{
			cout << "+" << " ";
			for (int z = 1; z < iRow; z++)
			{
				cout << "+" << "-";
			}

			cout << "+" << endl;
		}
		cout << "|";

		/*WEST/EAST WALLS------------------------------------------------------------------------------------------------*/
		for (int j = 0; j < yAxis; j++) //for loop that checks the west wall ----> | |<--------- and the east wall of two index positions next to each other
		{
			cout << " "; //this space simulate a value in box position
			if (j + 1 == yAxis) //If index of of x axis is at the last position simply output a wall (east wall to be exact)
			{
				cout << "|";
			}

			if (iMaze[i][j].EWALL == true || iMaze[i][j + 1].WWALL == true) //if there is either an east or west wall see out bar
			{
				if (j + 1 != yAxis)
				{

					cout << "|";
				}
			}
			else if (iMaze[i][j].EWALL == false || iMaze[i][j + 1].WWALL== false) // if no wall simply output space
			{
				if (j + 1 != yAxis)
				{
					cout << " ";
				}
			}
		}

		cout << endl << "+";
		/*NORTH/SOUTH WALLS------------------------------------------------------------------------------------------------*/

		if (i < xAxis - 1)
		{
			for (int k = 0; k < xAxis; k++)
			{
				if (iMaze[i][k].SWALL == true || iMaze[i + 1][k].NWALL == true)
				{
					cout << "-" << "+";
				}
				else if (iMaze[i][k].SWALL == false || iMaze[i + 1][k].NWALL== false)
				{
					cout << " " << "+";
				}
			}
		}

		if (i == xAxis - 1)
		{
			for (int l = 1; l < xAxis; l++)
			{
				cout << "-" << "+";
			}
			cout << " " << "+";
		}

		cout << endl;
	}

	cout << endl << endl;
}

int goRandom(cell **& iMaze, int x, int y, int iRow) {

	//find all neighbors that are not outside walls
	bool northNeighbor = x - 1 >= 0;
	bool southNeighbor = x + 1 < iRow;
	bool eastNeighbor = y + 1 < iRow;
	bool westNeighbor = y - 1 >= 0;

	//Finds all neighbors with walls that are intact
	if (northNeighbor) {
		cout << "THERES A NORTH NEIGHBOR" << endl;
		if (!iMaze[x - 1][y].WallsIntact) {
			northNeighbor = false;

		}
	}
	if (southNeighbor) {
		cout << "THERES A SOUTH NEIGHBOR" << endl;
		if (!iMaze[x + 1][y].WallsIntact) {
			southNeighbor = false;

		}
	}
	if (eastNeighbor) {
		cout << "THERES A EAST NEIGHBOR" << endl;
		if (!iMaze[x][y + 1].WallsIntact) {
			eastNeighbor = false;

		}
	}
	if (westNeighbor) {
		cout << "THERES A WEST NEIGHBOR" << endl;
		if (!iMaze[x][y - 1].WallsIntact) {
			westNeighbor = false;

		}
	}

	//Random
	int i;

	while (northNeighbor || southNeighbor || eastNeighbor || westNeighbor) { //randomly chooses available neighbor cell
		i = rand() % 4 + 1; //1 = N, 2 = S, 3 = E, 4 = W
		//cout << "RANDOM: " << i << endl;

		if (northNeighbor && iMaze[x - 1][y].WallsIntact && i == 1) {
			cout << "GOING NORTH" << endl;
			return 1;
		}
		if (southNeighbor && iMaze[x + 1][y].WallsIntact && i == 2) {
			cout << "GOING SOUTH" << endl;
			return 2;
		}
		if (eastNeighbor && iMaze[x][y + 1].WallsIntact && i == 3) {
			cout << "GOING EAST" << endl;
			return 3;
		}
		if (westNeighbor && iMaze[x][y - 1].WallsIntact && i == 4) {
			cout << "GOING WEST" << endl;
			return 4;
		}
		//cout << "Re-roll" << endl;

	}
	cout << "NO NEW PLACSE FOUND...BACKTRACKING" << endl;
	return 0;
}

void DFSCreateMaze(cell **& iMaze, int iRow) {

	stack<cell> CellStack;
	int TotalCells = iRow * iRow;
	//Starting locations
	int x = 0;
	int y = 0;

	//cell CurrentCell = iMaze[x][y];
	iMaze[x][y].WallsIntact = false;
	int VisitedCells = 1;

	int goDirection;

	cout << "START: " << iMaze[x][y].roomLetter << endl;

	while (VisitedCells < TotalCells - 1) {
		goDirection = goRandom(iMaze, x, y, iRow); //Choose random direction with all walls intact
		if (goDirection > 0) {
			if (goDirection == 1) {
				//Knock down current North Wall and neighbor's south wall
				//cout << "GOING NORTH" << endl;
				iMaze[x][y].NWALL = false;
				iMaze[x][y].WallsIntact = false;
				iMaze[x - 1][y].SWALL = false;
				iMaze[x - 1][y].WallsIntact = false;
				//Push Current Cell Location on the CellStack
				CellStack.push(iMaze[x][y]);
				//Make the new cell Current Cell
				x--;

				//Add 1 to VisitedCells
				VisitedCells++;
				cout << "********Next: " << iMaze[x][y].roomLetter << endl;
				cout << "X: " << x << " Y: " << y << endl;

			} else if (goDirection == 2) {
				//Knock down current South Wall and neighbor's North wall
				//cout << "GOING SOUTH" << endl;

				iMaze[x][y].SWALL = false;
				iMaze[x][y].WallsIntact = false;
				iMaze[x + 1][y].NWALL = false;
				iMaze[x + 1][y].WallsIntact = false;
				//Push Current Cell Location on the CellStack
				CellStack.push(iMaze[x][y]);
				//Make the new cell Current Cell
				x++;
				//Add 1 to VisitedCells
				VisitedCells++;
				cout << "********Next: " << iMaze[x][y].roomLetter << endl;
				cout << "X: " << x << " Y: " << y << endl;

			} else if (goDirection == 3) {
				//Knock down current East Wall and neighbor's West wall
				//cout << "GOING EAST" << endl;

				iMaze[x][y].EWALL = false;
				iMaze[x][y].WallsIntact = false;
				iMaze[x][y + 1].WWALL = false;
				iMaze[x][y + 1].WallsIntact = false;
				//Push Current Cell Location on the CellStack
				CellStack.push(iMaze[x][y]);
				//Make the new cell Current Cell
				y++;
				//Add 1 to VisitedCells
				VisitedCells++;

				cout << "********Next: " << iMaze[x][y].roomLetter << endl;
				cout << "X: " << x << " Y: " << y << endl;

			} else {
				//Knock down current West Wall and neighbor's East wall
				//cout << "GOING WEST" << endl;

				iMaze[x][y].WWALL = false;
				iMaze[x][y - 1].EWALL = false;
				iMaze[x][y].WallsIntact = false;
				iMaze[x][y - 1].WallsIntact = false;
				//Push Current Cell Location on the CellStack
				CellStack.push(iMaze[x][y]);
				//Make the new cell Current Cell
				y--;
				//Add 1 to VisitedCells
				VisitedCells++;
				cout << "********Next: " << iMaze[x][y].roomLetter << endl;
				cout << "X: " << x << " Y: " << y << endl;

			}

		} else {
			x = CellStack.top().cellX;
			y = CellStack.top().cellY;

			cout << "*******BACKSPACING TO: " << iMaze[x][y].roomLetter << endl;
			cout << "X: " << x << " Y: " << y << endl;
			CellStack.pop();

		}
	}

}

void wallCheck(cell **& iMaze, int iRow)
{
	for (int i = 0; i < iRow; i++) {
		for (int j = 0; j < iRow; j++) {
			cout << iMaze[i][j].roomLetter << ": " << iMaze[i][j].finish
					<< endl;
		}
	}
}

void DFS_Visit(cell **& iMaze, int x, int y, int iRow) {

	cout << "               TIMER: " << timer << endl;
	cout << "CALLING DFS_VISIT" << endl;
	cout << iMaze[x][y].roomLetter << endl;
	//cout << "X:" << x << " Y: " << y << endl;

	timer = timer + 1;
	iMaze[x][y].start = timer;
	iMaze[x][y].color = "GREY";

	//check what neighbors are adjacent node
	//for each adjacent node

	if (!iMaze[x][y].NWALL && iMaze[x - 1][y].color == "WHITE") {
		DFS_Visit(iMaze, x - 1, y, iRow);

	}
	if (!iMaze[x][y].SWALL && iMaze[x + 1][y].color == "WHITE") {
		DFS_Visit(iMaze, x + 1, y, iRow);

	}
	if (!iMaze[x][y].EWALL && iMaze[x][y + 1].color == "WHITE") {
		DFS_Visit(iMaze, x, y + 1, iRow);

	}
	if (!iMaze[x][y].WWALL && iMaze[x][y - 1].color == "WHITE") {
		DFS_Visit(iMaze, x, y - 1, iRow);

	}
	//////
	iMaze[x][y].finish = timer;
	cout << iMaze[x][y].roomLetter << " is now BLACK" << endl;
	cout << "ENDING TIMER IS NOW: " << timer << endl;
	iMaze[x][y].color = "BLACK";
	timer = timer + 1;

}

void DFS(cell **& iMaze, int iRow) {

	cout << "CALLING DFS" << endl;
	for (int i = 0; i < iRow; i++) {
		for (int j = 0; j < iRow; j++) {

			iMaze[i][j].color = "WHITE";

		}
	}

	timer = 0;
	for (int i = 0; i < iRow; i++) {
		for (int j = 0; j < iRow; j++) {
			if (iMaze[i][j].color == "WHITE") {
				DFS_Visit(iMaze, i, j, iRow);
			}

		}
	}

}

void DFSshortestPath(cell **& iMaze, int iRow) {

	cell *list;
	list = new cell[iRow * iRow];

	int counter = 0;

	//puts matrix into array list
	for (int i = 0; i < iRow; i++) {
		for (int j = 0; j < iRow; j++) {

			list[counter] = iMaze[i][j];
			counter++;

		}
	}

	//array list is sorted by finishing times

	for (int i = 0; i <= iRow * iRow - 1; i++) {
		for (int j = i + 1; j <= iRow * iRow - 1; j++) {

			if (list[i].finish < list[j].finish) {

				cell temp;
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;

			}

		}
	}

	cout << "THIS SHOULD BE SORTED" << endl;
	for (int p = 0; p < iRow * iRow; p++) {
		cout << list[p].finish << endl;

	}

	cout << "SHORTEST PATH ORDER: " << endl;

	//while in room L and has no SWALL or room O and no EWALL
	counter = 0;



	while ((list[counter].roomLetter != iMaze[iRow - 1][iRow - 2].roomLetter
			&& !iMaze[iRow - 1][iRow - 2].EWALL) || (list[counter].roomLetter
			!= iMaze[iRow - 2][iRow - 1].roomLetter && !iMaze[iRow - 2][iRow
			- 1].SWALL)) {


		cout << list[counter].roomLetter << endl;
		counter++;

	}
	cout << list[counter].roomLetter << endl;
	cout << iMaze[iRow - 1][iRow - 1].roomLetter << endl;

	int finalCount = counter;

	counter = 0;
	cout << endl << endl << endl;

	displayShortestPathMaze(iMaze, list, iRow, finalCount);

}

void BFS(cell **& iMaze, int iRow){
	cout<< "CALLING BFS"<<endl;



	for(int i = 0; i < iRow; i++){ //initializes each vector to white, the distances to 0, and the axis' as 0
		for(int j = 0; j < iRow; j++){
			iMaze[i][j].color = "WHITE";
			iMaze[i][j].d = 0;
			iMaze[i][j].piX = 0;
			iMaze[i][j].piY = 0;
		}
	}

	queue<cell> BFS_Queue;

	int x = 0;
	int y = 0;

	iMaze[x][y].color = "GREY"; 	//The starting value's color is initialized to "GREY"
	iMaze[x][y].d = 0;
	iMaze[x][y].piX = 0;
	iMaze[x][y].piY = 0;

	BFS_Queue.push(iMaze[x][y]); //Adding the starting position to the queue





	//cell v; // a vertex


	while(!BFS_Queue.empty()){ //While the queue BFS_Queue still has gray vertices
		x = BFS_Queue.front().cellX;
		y = BFS_Queue.front().cellY;
		BFS_Queue.pop(); //determines the gray vertex u at the head of the queue and is then removed from the queue
		if (!iMaze[x][y].NWALL && iMaze[x - 1][y].color == "WHITE") { //Checks the north wall
			iMaze[x-1][y].color = "GREY";
			iMaze[x-1][y].d = iMaze[x][y].d +1;
			iMaze[x-1][y].piX = iMaze[x][y].cellX;
			iMaze[x-1][y].piY = iMaze[x][y].cellY;
			BFS_Queue.push(iMaze[x-1][y]); //
		}
		if (!iMaze[x][y].SWALL && iMaze[x + 1][y].color == "WHITE") {//Checks the south wall
			iMaze[x+1][y].color = "GREY";
			iMaze[x+1][y].d = iMaze[x][y].d +1;
			iMaze[x+1][y].piX = iMaze[x][y].cellX;
			iMaze[x+1][y].piY = iMaze[x][y].cellY;
			BFS_Queue.push(iMaze[x+1][y]);

		}
		if (!iMaze[x][y].EWALL && iMaze[x][y + 1].color == "WHITE") { //Checks the east wall
			iMaze[x][y+1].color = "GREY";
			iMaze[x][y+1].d = iMaze[x][y].d +1;
			iMaze[x][y+1].piX = iMaze[x][y].cellX;
			iMaze[x][y+1].piY = iMaze[x][y].cellY;
			BFS_Queue.push(iMaze[x][y+1]);

		}
		if (!iMaze[x][y].WWALL && iMaze[x][y - 1].color == "WHITE") { //Checks the west wall
			iMaze[x][y-1].color = "GREY";
			iMaze[x][y-1].d = iMaze[x][y].d +1;
			iMaze[x][y-1].piX = iMaze[x][y].cellX;
			iMaze[x][y-1].piY = iMaze[x][y].cellY;
			BFS_Queue.push(iMaze[x][y-1]);

		}

		iMaze[x][y].color = "BLACK"; //Once all of the vertexes adjacent to u have been colored gray, u is then colored black

	}



}



void shortestPathBFS(cell **& iMaze, int iRow){
	cell *list;
	list = new cell[iRow * iRow];
	int counter = 0;

	//puts matrix into array list
	for (int i = 0; i < iRow; i++) {
		for (int j = 0; j < iRow; j++) {

			list[counter] = iMaze[i][j];
			counter++;

		}
	}

	cell *goodList; //List of cells we want to keep

	goodList = new cell[iRow*iRow]; //a new list is initialized called "goodList" that will hold the values we want to keep

	int goodCount = 0;

	//If a number is greater than P disregard it



	for(int i = 0; i < iRow; i++){
		for(int j = 0; j < iRow; j++){
			if(iMaze[i][j].d < iMaze[iRow-1][iRow-1].d){
				goodList[goodCount] = iMaze[i][j];//disregard iMaze[i][j]
				goodCount++;
			}
		}
	}
	for(int i = 0; i < goodCount; i++){
		cout<<goodList[i].roomLetter<<" ";
	}

	cout<<"P";

	cout << endl << endl << endl;

	displayShortestPathMaze(iMaze, goodList, iRow, goodCount);
}


int main() {
	srand(time(0));
	cell **myMaze;
	int myRow = 4;
	createMaze(myMaze, myRow);
	DFSCreateMaze(myMaze, myRow);



	//cout << "This is the initial maze: " << endl << endl;
	//displayMaze(myMaze, myRow);
	DFS(myMaze, myRow);
	//wallCheck(myMaze, myRow);
	cout << "SHORTEST PATH DFS" << endl;
	DFSshortestPath(myMaze, myRow);

	cout<<"SHORTEST PATH BFS"<<endl;
	BFS(myMaze, myRow);
	shortestPathBFS(myMaze, myRow);
	return 0;
}

