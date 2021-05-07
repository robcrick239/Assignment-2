#pragma once
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include<iomanip>
#define minAge 1
#define maxAge 4
#define minWeight 0.5f
#define maxWeight 3.5f
#define minIncrease 0.1f
#define maxIncrease 1.0f
using namespace std;
/****************************************************************************/
	/*GREENMONKEY CLASS FUNCTION PROTOYPES AND DATA MEMBERS STARTS HERE*/
/****************************************************************************/
class GreenMonkey
{
public:
	GreenMonkey();
	static int getRandomNumber(int, int);
	static float getRandomNumber(float, float);
	string getCurrentDateTime();
	void print();
	void eat();
	void age_me();
	void fight(GreenMonkey*);
	void set_weight(float);
	void set_age(short int);
	void set_name(string);
	void set_gender(char);
	void set_alive(bool);
	void set_mutant(bool);
	void set_injured(short int);
	void set_ID(int);
	float get_weight();
	short int get_age();
	string get_name();
	char get_gender();
	bool get_alive();
	bool get_mutant();
	short int get_injured();
	int get_ID();
	void set_next(GreenMonkey*);
	GreenMonkey* get_next();

private:
	int ID;
	float weight;
	short int age;
	string name;
	char gender;
	bool alive;
	bool mutant;
	int injured;
	GreenMonkey* next;
};
/****************************************************************************************/
	/*GREENMONKEY_LINKEDLIST CLASS FUNCTION PROTOYPES AND DATA MEMBERS STARTS HERE*/
/****************************************************************************************/
const int mutantFactor(2);
const int fightRatioMultiplier(50);
const int injuredDeathFactor(3);
class GreenMonkey_LinkedList {
private:
	GreenMonkey* head;
	int idCount;
public:
	GreenMonkey_LinkedList();
	void printList();
	void insert_at_start();
	void deleteNode(int);
	void set_idCount();  //sets the next ID of node that will be added to the list
	int get_idCount();   //gets the next ID of node that will be added to the list
	void update_id(); //resets the ID of all the nodes in the list
	GreenMonkey* get_Head();
	GreenMonkey* get_Node(int);
};

/****************************************************************************************/
	/*HABITAT CLASS FUNCTION PROTOYPES AND DATA MEMBERS STARTS HERE*/
/****************************************************************************************/
class Habitat
{
private:
	static const int RowCol = 10;
	GreenMonkey_LinkedList grid[RowCol][RowCol] = {};//creates a 10 X 10 grid, each grid cell will have an empty GreenMonkey Linked linked
public:
	vector<string> getEmptyCells();
	void intialization(int);
	void showGrid();
	void invasion(int);
	void impact(GreenMonkey_LinkedList&, GreenMonkey*); //picks a random GreenMonkey from the Linked List in the 1st parameter and engage with the GreenMonkey which is the second parameter.
	void ageAll();
	void feedAll();
	void printAll();
	void getStatistics();
};
