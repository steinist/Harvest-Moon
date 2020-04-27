/*
 * File Created: Sun Mar 15 2020
 * Author:
 * SID:
*/

#ifndef CATTLEFARM_H_
#define CATTLEFARM_H_

#include "Property.h"
extern const int CATTLEFARM_SIZE_X;
extern const int CATTLEFARM_SIZE_Y;

// HINT: You may seek help from Property::fireEmployee()
//       when you implement your Cattlefarm::removeDiedCow().
// TODO: Start to implement your code.

class Cattlefarm : public Property {
public:
	Cattlefarm(int x, int y);
	virtual bool checkEmployee(Employee*) const;
	virtual void upgrade();
	virtual int makeMoney() const;
	void removeDiedCow();
	string getName() const override;
	char getSymbol() const override;
};
#endif /*CATTLEFARM_H_*/
