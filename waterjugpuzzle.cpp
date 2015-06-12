/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Kevin Furlong, Jonathan Scrivan, and Henry Thomas
 * Date        : June 12th 2015
 * Description : Determining the most efficient way to solve the classic water
 * 				 jug problem. Given a goal and jug capacities.
 * Pledge      : We pledge our honor that we have abided by the Stevens Honor System
 * 				 Kevin Furlong, Henry Thomas, Jonathan Scrivan
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include<regex>
#include <queue>
#include "State.cpp"

using namespace std;

State cap, goal, initial;
queue<State> q;
bool visited[][];

void start_bfs() {
	//Create a new initial state
	initial = State();
	//Create a goal state.
	goal = State();
	//Create a capacities state
	cap = State();

	q.push(initial);
	while (!q.empty()) {
		createAdjacencies(q.front());
		q.pop();
	}
}

//this is a commit
vector<State> findPath(State &child) {
	vector<State> optimalPath;
	while (child != initial) {
		optimalPath.push_back(child);
		//This might not work well because we want to change the reference to child
		//not the contents of child.
		*child = child.parent();
	}
	reverse(optimalPath.begin(), optimalPath.end());
	return optimalPath;
}

void createAdjacencies(State &curr) {
	//TODO: Possibly set capacity for visited && fill visited with false
	int a = curr.a(), b = curr.b(), c = curr.c();
	//C->A
	visited = new bool[cap.a()][cap.b];
	//gives the outer array a size of the capacity of a and the inner array the capacity size of b
	// fills each index with false.. slow run time...
	for (int i = 0; i < visited.length; i++)
		{
			for (int j = 0; j < visited[i].length; j++)
			{
				visited[i][j] = false;
			}
		}
		// fills each index with false.. slow run time...
		if (c != 0 && a != cap.a()) {
			int amtMoved = min(c, (cap.a() - a));
			if (!visited[a + amtMoved][b])
				q.push(State(a + amtMoved, b, c - amtMoved, curr));
				//TODO: Update visited to true
		}

		//B->A
		if (b != 0 && a != cap.a()) {
			int amtMoved = min(b, (cap.a() - a));
			if (!visited[a + amtMoved][b])
				q.push(State(a + amtMoved, b - amtMoved, c, curr));
				//TODO: Update visited to true
		}

		//C->B
		if (c != 0 && b != cap.b()) {
			int amtMoved = min(c, (cap.b() - b));
			if (!visited[a + amtMoved][b])
				q.push(State(a, b + amtMoved, c - amtMoved, curr));
				//TODO: Update visited to true
		}

		//A->B
		if (a != 0 && b != cap.b()) {
			int amtMoved = min(a, (cap.b() - b));
			if (!visited[a + amtMoved][b])
				q.push(State(a - amtMoved, b + amtMoved, c, curr));
				//TODO: Update visited to true
		}

		//B->C
		if (b != 0 && c != cap.c()) {
			int amtMoved = min(b, (cap.c() - c));
			if (!visited[a + amtMoved][b])
				q.push(State(a, b - amtMoved, c + amtMoved, curr));
				//TODO: Update visited to true
		}

		//A->C
		if (a != 0 && c != cap.c()) {
			int amtMoved = min(a, (cap.c() - c));
			if (!visited[a + amtMoved][b])
				q.push(State(a - amtMoved, b, c + amtMoved, curr));
				//TODO: Update visited to true
		}
}

int main(int argc, char * const argv[]) {
	//Error check for correct number of arguments
	if (argc != 7) {
		cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
	}
	//argv from 1 to 3 should contain capacitys for a, b, and c (input[0] ~ input[2])
	//argv from 4 to 6 should contain goals for a, b, and c (input[3] ~ input [5])
	int input = { atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]),
			atoi(argv[5]), atoi(argv[6]) };

	//Error check that all inputs are integers
	for (int i = 0; i <= 5; i++) {
		if (regex_match(input[i],"$[0-9]+^") or input[i] <= 0) {
			cerr << "Error: Invalid capacity '" << input[i] << "' for jug A.";
			return 1;
		}

		//Check that capacity isnt less than the goal
		//TODO: This wont work exactly
		if (input[i] < input[i + 2]) {
			cerr << "Error: Goal cannot exceed capacity of jug A, B, or C.";
			return 1;
		}
	}

	//Check that sum of goal state is equal to capacity of C
	if (input[3] < (input[4] + input[5] + input[6])) {
		cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C.";
		return 1;
	}

	return 0;
}
