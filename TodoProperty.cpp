/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#include "Property.h"
#include "Employee.h"

void Property::writeToStream(ostream& os) const {
	Object::writeToStream(os);
	os << "Cost:" << getCost() << endl;
    os << "Upgrade Cost:" << getUpgradeCost() << endl;
    os << "Level:" << getLevel() << endl;
    os << "# of Employee:" << getNumEmployee() << " / " << getMaxNumEmployee() << endl;
}

void Property::upgrade() {
    m_level++;

}

void Property::getConstEmployeeList(const Employee**& employee) const {
	if (m_num_employee == 0) {
		employee =nullptr;
		return;
	}
	employee = new const Employee*[m_num_employee];
	for (int i = 0; i < m_num_employee; i++)
		employee[i] = m_employee_list[i];
}

// TODO: Start to implement your code.

Property::Property(int b_cost, int u_cost, int max_employee)
:m_cost(b_cost), m_upgrade_cost(u_cost), m_max_num_employee(max_employee){
}

Property::~Property(){
	if (m_employee_list != nullptr) {
		for (int i = 0; i < m_num_employee; ++i){
			delete m_employee_list[i];
		}
		delete[] m_employee_list;
	}
	m_num_employee = 0;
}

int Property::getCost() const{
	return m_cost;
}

int Property::getUpgradeCost() const {
	return m_upgrade_cost;
}

int Property::getLevel() const{
	return m_level;
}

int Property::getNumEmployee() const{
	return m_num_employee;
}

int Property::getMaxNumEmployee() const{
	return m_max_num_employee;
}

void Property::setMaxNumEmployee(int max) {
	m_max_num_employee = max;
}

bool Property::assignEmployee(Employee* e) {
	//If max capacity return false
	if (m_num_employee == m_max_num_employee)
		return false;

	//If unsuitable return false
	if (!checkEmployee(e)){
		return false;
	}

	//Assign first employee
	if (m_employee_list == nullptr){
		m_employee_list = new Employee*[1];
		m_employee_list[0] = e;
		++m_num_employee;

		int x = 0, y = 0;
		getXY(x, y);
		m_employee_list[0]->setXY(x+1, y+1);

		return true;
	}


	//If the e already on the list return false
	for (int i = 0; i < m_num_employee; ++i){
		if (m_employee_list[i] == e)
			return false;
	}




	//if all condition is ok

	//Copy to the old employee list
	Employee* old_employee_list[m_num_employee];
	for (int i = 0; i < m_num_employee; ++i){
		old_employee_list[i] = m_employee_list[i];
		m_employee_list[i] = nullptr;
	}
	delete[] m_employee_list;


	//Create a new employee list and assign back
	m_employee_list = new Employee*[m_num_employee+1];
	for (int i = 0; i < m_num_employee; ++i){
		m_employee_list[i] = old_employee_list[i];
		old_employee_list[i] = nullptr;
	}
	m_employee_list[m_num_employee] = e;
	++m_num_employee;




	//finding the size and position of the property
	int sx = 0, sy = 0;
	getSize(sx, sy);

	int p_x = 0, p_y = 0;
	getXY(p_x, p_y);

	//setting the position of the employee
	//the postion of 1st employee
	int ex = p_x+1, ey = p_y+1;

	//find the position of employee before
	int b_x[m_num_employee-1];
	int b_y[m_num_employee-1];
	for (int i = 0; i < m_num_employee-1; ++i){
		m_employee_list[i]->getXY(b_x[i], b_y[i]);
	}


	while (true){
		//Check if the position is taken by employee before
		bool pos_taken = false;

		for (int i = 0; i < m_num_employee-1; ++i){
			if (ex == b_x[i] && ey == b_y[i]) {
				pos_taken = true;
				break;
			}
		}


		//if position is not taken give the position to the new one
		if (!pos_taken){
			m_employee_list[m_num_employee-1]->setXY(ex, ey);
			break;
		}

		//else change position and loop
		//Change the position

		++ey;

		if (ey == p_y+sy-1){
			ey = p_y+1;
			++ex;

		}

	}


	return true;
}


bool Property::fireEmployee(Employee* e) {
	if (m_employee_list == nullptr) {
		return false;
	}

	if (e == nullptr){
		return false;
	}

	//Change the ordering of m_employee_list
	Employee* new_employee_list[m_num_employee-1];

	for (int i = 0, j = 0; i < m_num_employee; ++i, ++j){
		//for deleting
		if (m_employee_list[i] == e) {
			delete m_employee_list[i];
			m_employee_list[i] = nullptr;
			--j;
			continue;
		}

		//for copying
		new_employee_list[j] = m_employee_list[i];
	}
	--m_num_employee;

	//Delete old employee list and assign back
	delete [] m_employee_list;
	m_employee_list = new Employee*[m_num_employee];
	for (int i = 0; i < m_num_employee; ++i){
		m_employee_list[i] = new_employee_list[i];
		new_employee_list[i] = nullptr;
	}


	return true;
}




















