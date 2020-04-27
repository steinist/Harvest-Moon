/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoCow.h"
#include <cstdlib>

// Cattlefarm cost 80 upgrade cost 16
// Cattlefarm size 6, 6
// Cattlefarm init max num. of employee is CATTLEFARM_MAX_NUM_EMPLOYEE_MIN
// Cattlefarm Upgrade:
//      level increases by 1;
//      max num. of employees increases by 1 until CATTLEFARM_MAX_NUM_EMPLOYEE_MAX
// Cattlefarm Makemoney:
//      min(num. of cows, num. of feeders in work) x level x 10;

const int CATTLEFARM_COST = 80;
const int CATTLEFARM_UPGRADE_COST = 16;
const int CATTLEFARM_SIZE_X = 6; const int CATTLEFARM_SIZE_Y = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MIN = 6;
const int CATTLEFARM_MAX_NUM_EMPLOYEE_MAX = (CATTLEFARM_SIZE_X-2) * (CATTLEFARM_SIZE_Y-2);

// TODO: Start to implement your code.

Cattlefarm::Cattlefarm(int x, int y):Property(CATTLEFARM_COST, CATTLEFARM_UPGRADE_COST, CATTLEFARM_MAX_NUM_EMPLOYEE_MIN) {
	setXY(x,y);
	setSize(CATTLEFARM_SIZE_X, CATTLEFARM_SIZE_Y);
}

bool Cattlefarm::checkEmployee(Employee* e) const{
	if (e == nullptr)
		return false;

	if (e->getSymbol() == 'c' || e->getSymbol() == 'd'){
		return true;
	}
	return false;
}

void Cattlefarm::upgrade() {
	Property::upgrade();
	if (getMaxNumEmployee() < CATTLEFARM_MAX_NUM_EMPLOYEE_MAX){
		setMaxNumEmployee(getMaxNumEmployee()+1);
	}
}

int Cattlefarm::makeMoney() const{
//  min(num. of cows, num. of feeders in work) x level x 10;
	int num_cow = 0, num_feeder = 0;
	const Employee** list;
	getConstEmployeeList(list);

	for (int i = 0; i < getNumEmployee(); ++i){
		if (list[i]->getSymbol() == 'c'){
			++num_cow;
		}
		if (list[i]->getSymbol() == 'd'){
			++num_feeder;
		}
	}

	int min = (num_cow < num_feeder) ? num_cow : num_feeder;
	delete[] list;
	return min * getLevel() *10;
}


void Cattlefarm::removeDiedCow() {
	const Employee** list;
	getConstEmployeeList(list);

	int num_emp = getNumEmployee();

	for (int i = 0; i < num_emp; ++i){
		if (list[i]->getSymbol() == 'c'){
			const Cow* p = dynamic_cast<const Cow*>(list[i]);
			if(!(p->isAlive())){
				Cow* c = const_cast<Cow*>(p);
				fireEmployee(c);
			}
		}
	}

	delete[] list;
}

string Cattlefarm::getName() const {
	return "Cattlefarm";
}

char Cattlefarm::getSymbol() const {
	return 'C';
}
