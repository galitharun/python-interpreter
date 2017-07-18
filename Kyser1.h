#include<iostream>
using namespace std;

class KyObject{
public:
	string type;
	KyObject()
	{

	}
	void setType(string Type)
	{
		type = Type;
	}
	string getType()
	{
		return type;
	}

};

class KyInt :public KyObject{
public:
	int kyint;
	KyInt(int value) :KyObject()
	{
		kyint = value;
		this->setType("int");
	}

};
class KyString :public KyObject{
public:
	string kystring;
	KyString(string str) :KyObject()
	{
		kystring = str;
		this->setType("string");
	}

};
class KyList :public KyObject{
public:
	KyObject *kylist [100];
	int length;
	KyList() :KyObject()
	{
		length = 0;
		this->setType("list");
	}
	void append(KyObject *kyob)
	{
		kylist[length++] = kyob;

	}

};
class KyDict :public KyObject{
public:
	KyObject *key[100];
	KyObject *value[100];
	int length;
	KyDict() :KyObject()
	{
		length = 0;
		this->setType("dict");
	}
	void set(KyObject *Value, KyObject *Key)
	{
		key[length] = Key;
		value[length] = Value;
		length++;
	}

};
class KyMarker :public KyObject{
public:
	KyMarker() :KyObject()
	{
		this->setType("marker");
	}
};
	