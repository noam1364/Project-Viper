#pragma once
class Type
{
public:
	Type();
	~Type();
	bool _isTemp;
	virtual string toString()=0;
	virtual bool isPrintable() = 0;
	virtual string getType() = 0;
	virtual int len();
	virtual void add(Type* t);
	virtual void subtract(Type* t);
	virtual void mulltiply(Type* t);
	virtual void divide(Type* t);
};

