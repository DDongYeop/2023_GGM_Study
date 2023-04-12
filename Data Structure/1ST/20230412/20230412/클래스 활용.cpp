#include <iostream>
using namespace std;

class Student
{
	string name;
	string clubName;
};

class Grade : Student
{
	int classNum;
	int studentNum;
	void StudyDataStruct()
	{

	}
};

class Art : Grade
{
	void StudyArt()
	{

	}
};

class Design : Grade
{
	void StudyDesign()
	{

	}
};

class Programming
{
	void StudyGameprogramming()
	{

	}
}