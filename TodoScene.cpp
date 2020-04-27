/*
 * File Created: Mon Mar 16 2020
 * Author:
 * SID:
*/

#include "Scene.h"
#include "Property.h"
#include "TodoFarmland.h"
#include "TodoCattlefarm.h"
#include "Employee.h"
#include "TodoFarmer.h"
#include "TodoFeeder.h"
#include "TodoCow.h"

const int SCENE_W = 45;
const int SCENE_H = 10;
const int PROPERTY_X = 35;
const int SCENE_INIT_MONEY = 200;

Scene::Scene()
: m_objects(nullptr), m_num_objects(0), m_money(SCENE_INIT_MONEY) {
    nextRound();
}

Scene::~Scene() {
    //shallowremove employees
    for(int i = m_num_objects-1; i >= 0; i--) {
        if (m_objects[i]->getObjectType()==ObjectType::EMPLOYEE)
            shallowRemoveEmployee(dynamic_cast<Employee*>(m_objects[i]));
    }
    // remove properties
    for(int i = m_num_objects-1; i >= 0; i--) {
        if (m_objects[i]->getObjectType()==ObjectType::PROPERTY)
            delete m_objects[i];
    }
    delete[] m_objects;
}

void Scene::shallowRemoveEmployee(Employee* e) {
    if (m_num_objects <= 0) return;
    if (m_num_objects == 1 && e == m_objects[0]) {
        m_num_objects = 0;
        m_objects = nullptr;
        return;
    }
    int i;
	for (i = 0; i < m_num_objects; i++) {
		if (m_objects[i] == e)
			break;
	}
    Object ** newObjects = new Object*[m_num_objects--];
	for (int j = 0; j < m_num_objects; j++)
		newObjects[j] = m_objects[j];
	if (m_num_objects != i)
		newObjects[i] = m_objects[m_num_objects];
    delete [] m_objects;
    m_objects = newObjects;
}

bool Scene::checkOverlap(const Property* newproperty) {
    int x, y, sz_x, sz_y;
    newproperty->getXY(x, y);
    newproperty->getSize(sz_x, sz_y);
    for(int xx=x; xx<x+sz_x; xx++)
        for(int yy=y; yy<y+sz_y; yy++)
            if(getObjectAt(xx, yy) != nullptr) return true;
    return false;
}


void Scene::addProperty(int property, int x, int y) {
    Property* newProperty = nullptr;
    switch(property) {
    case FARMLAND:
        newProperty = new Farmland(x,y);
        break;
    case CATTLEFARM:
        newProperty = new Cattlefarm(x, y);
        break;
    }
    if (newProperty == nullptr) return;
    if (newProperty->getCost() > m_money || checkOverlap(newProperty)) {
        delete newProperty;
        return;
    }
    addObject(newProperty);
    m_money -= newProperty->getCost();
}


bool Scene::hire(Property* p, int employee) {
    Employee* newEmployee = nullptr;
    switch(employee){
    case EMPLOYEE:
        newEmployee = new Employee();
        break;
    case FARMER:
        newEmployee = new Farmer();
        break;
    case FEEDER:
        newEmployee = new Feeder();
        break;
    case COW:
        newEmployee = new Cow();
        break;
    }
    if (newEmployee == nullptr) return false;
    if (newEmployee->getCost() > m_money || ! p->assignEmployee(newEmployee)) {
        delete newEmployee;
        return false;
    }
    addObject(newEmployee);
    m_money -= newEmployee->getCost();
    return true;
}


Object* Scene::getObjectAt(int s_x, int s_y) const {
	int x, y, sz_x, sz_y;
    // If employee is at s_x, s_y, get employee
    // else, get property
    // otherwise return null
	for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::PROPERTY)
            continue;
		m_objects[i]->getXY(x,y);
        m_objects[i]->getSize(sz_x,sz_y);
        if ( s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
			return m_objects[i];
	}
	for (int i = 0; i < m_num_objects; i++) {
        if (m_objects[i]->getObjectType() == ObjectType::EMPLOYEE)
            continue;
		m_objects[i]->getXY(x,y);
        m_objects[i]->getSize(sz_x,sz_y);
        if ( s_x >= x && s_x < x + sz_x && s_y >= y && s_y < y + sz_y)
			return m_objects[i];
	}
	return nullptr;
}

//perform shallow copying
void Scene::addObject(Object* newobj) {
	Object** newobjects = new Object*[m_num_objects + 1];
	for (int i = 0; i < m_num_objects; i++)
		newobjects[i] = m_objects[i];
	newobjects[m_num_objects++] = newobj;
	if (m_num_objects != 1)
		delete [] m_objects;
	m_objects = newobjects;
}

void Scene::getConstObjects(const Object**& obj, int& count) const {
	count = m_num_objects;
	if (m_num_objects == 0) {
		obj =nullptr;
		return;
	}
	obj = new const Object*[m_num_objects];
	for (int i = 0; i < m_num_objects; i++)
		obj[i] = m_objects[i];
}

// TODO: Start to implement your code.

bool Scene::isGameOver() const {
	if (m_money < 0){
		return true;
	}
	return false;
}


void Scene::removeProperty(Property* p) {
	//If p = nullptr return
	if (p == nullptr)
		return;

	//If p does not exist in m_obj return
	if (!checkOverlap(p)){
		return;
	}

	//Find the employee in the property
	const Employee** list;
	p->getConstEmployeeList(list);



	//Make a new place for the rest of the m_obj
	//m_num_objects-(p->getNumEmployee())-1  is Total - num want to delete
	bool remainder = (m_num_objects-(p->getNumEmployee())-1 > 0);
	int r = m_num_objects-(p->getNumEmployee())-1;

	Object** new_obj = new Object*[m_num_objects-(p->getNumEmployee())-1];

	int k = 0;
	int p_i = -1;
	int num_empl = p->getNumEmployee();
	for (int i = 0; i < m_num_objects; ++i){

		//searching if m_object[i] is employee
		bool is_employee = false;

		for (int j = 0; j < num_empl; ++j){


			if (m_objects[i] == list[j]){
				is_employee = true;
			}
		}

		//delete employee
		if (is_employee){
			p->fireEmployee(dynamic_cast<Employee*>(m_objects[i]));
			m_objects[i] = nullptr;
		}

		//delete property
		else if (m_objects[i] == p){
			p_i = i;
		}

		//if not keep it
		else {
			if(remainder) {
				new_obj[k] = m_objects[i];
				m_objects[i] = nullptr;
				++k;
			}

		}
	}

	//delete property
	delete m_objects[p_i];
	m_objects[p_i] = nullptr;


	//delete the old one and assign to new one
	delete[] m_objects;
	m_objects = nullptr;
	m_num_objects = r;


	if (remainder){
		m_objects = new_obj;
		new_obj = nullptr;
	}
	else {
		delete[] new_obj;
		new_obj = nullptr;
		m_objects = nullptr;
	}

	delete[] list;
}

void Scene::nextRound() {
	if (m_objects == nullptr)
		return;

	int i_num_objects = m_num_objects;
	for (int i = 0; i < m_num_objects; ++i) {
		if (m_objects[i]->getObjectType() == ObjectType::PROPERTY) {
			Property* p = dynamic_cast<Property*>(m_objects[i]);
			m_money += p->makeMoney();
		}

		if (m_objects[i]->getObjectType() == ObjectType::EMPLOYEE) {
			Employee* e = dynamic_cast<Employee*>(m_objects[i]);
			m_money -= e->getSalary();

			e->updateWorkAge();
			e->updateState();
		}
	}

	//Removing the cow in m_objects
	for (int i = 0; i < m_num_objects; ++i) {
		if (m_objects[i]->getSymbol() == 'c'){
			Cow* cow = dynamic_cast<Cow*>(m_objects[i]);
			if (!cow->isAlive()){
				shallowRemoveEmployee(cow);
				--i;
			}
		}

	}


	//Remove the cow in employee list
	if (i_num_objects > m_num_objects){
		for (int i = 0; i < m_num_objects; ++i) {
			if (m_objects[i]->getSymbol() == 'C') {
					Cattlefarm* c = dynamic_cast<Cattlefarm*>(m_objects[i]);
					c->removeDiedCow();
			}
		}
	}



}


bool Scene::upgrade(Property* p) {
	if (p == nullptr)
		return false;

	p->upgrade();
	m_money -= p->getUpgradeCost();
	return true;

}


bool Scene::fire(Employee* e) {
	//If e = nullptr return
	if (e == nullptr)
		return false;

	//If e does not exist in m_obj return
	bool exist = false;
	for (int i = 0; i < m_num_objects; ++i){
		if (e == m_objects[i]){
			exist = true;
			break;
		}
	}
	if (!exist){
		return false;
	}

	//Find the position of and change its position
	int x = 0, y = 0;
	e->getXY(x,y);
	Object* emp = getObjectAt(x,y);
	emp->setXY(-1,-1);

	//Get the property object behind the employee
	//Object* p = getObjectAt(x,y);
	Property* prop = dynamic_cast<Property*>(getObjectAt(x,y));

	//modify m_objects and m_num_object
	Object** new_obj = new Object*[m_num_objects-1];
	int j = 0;
	for (int i = 0; i < m_num_objects; ++i){
		if (m_objects[i] == e){
			m_objects[i] = nullptr;
			continue;
		}
		new_obj[j] = m_objects[i];
		++j;
	}

	--m_num_objects;
	delete[] m_objects;
	m_objects = new_obj;
	new_obj = nullptr;


	//Fire employee (because we know the employee is fix inside the property)
	return prop->fireEmployee(e);
}


















