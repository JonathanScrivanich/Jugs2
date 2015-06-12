/*******************************************************************************
 * Name        : State.cpp
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

using namespace std;

class State {
public:
	State(int a, int b, int c, State &p) :
			a_(a), b_(b), c_(c), parent_(p) {
	}
	int a() {
		return a_;
	}
	int b() {
		return b_;
	}
	int c() {
		return c_;
	}

	State parent(){
		return parent_;
	}

	string to_string() const {
		return "(" + a_ + ", " + b_ + ", " + c_ + ")";
	}
private:
	int a_, b_, c_;
	State *parent_;
};
