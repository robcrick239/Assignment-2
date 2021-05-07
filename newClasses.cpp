#include "Classes.h"
#include <sstream>

//GREENMONKEY CLASS DECLARATION
int GreenMonkey::getRandomNumber(int minimum, int maximum)
{
	unsigned value = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine gen(value);
	uniform_int_distribution<int> ran(minimum, maximum);
	return ran(gen);
}//end getRandomNumber for integer


float GreenMonkey::getRandomNumber(float minimum, float maximum)
{
	unsigned value = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine gen(value);
	uniform_real_distribution<double> ran(minimum, maximum);
	return ran(gen);
}//end getRandomNumber for float


GreenMonkey::GreenMonkey()
{

	int fl = 0, lc = 0;

	gender = 'F';
	name;
	weight;
	alive = true;
	mutant = false;
	injured = 0;

	ifstream pointer;
	GreenMonkey* ptr = NULL;
	int linetotal = 0;

	if (getRandomNumber(1, 100) > 50) // 50% chance assignment
	{
		gender = 'M';
	}//endif
	else
	{

		gender = 'F';
	}//endelse

	if (gender == 'M') //opens the file 
	{

		pointer.open("M_names.txt");
	}//endif

	else
	{
		pointer.open("F_names.txt");
	}//endif

	if (!pointer.is_open())
	{
		cerr << "Error" << endl;
		exit(1);
	}//endif

	while (getline(pointer, name))
	{
		linetotal = linetotal + 1;
	}//endwhile

	pointer.close(); //closes the file for reopening

	if (gender == 'M')//opens the file to get random name
		pointer.open("M_names.txt");
	else
		pointer.open("F_names.txt");

	if (!pointer.is_open())
	{
		cerr << "Error opening name file" << endl;
		exit(1);
	}//endif

	lc = getRandomNumber(1, linetotal);

	while (!pointer.eof() && fl != lc)
	{
		pointer >> name;
		fl = fl + 1;
	}//endwhile
	pointer.close();


	weight = getRandomNumber(minWeight, maxWeight);
	age = getRandomNumber(minAge, maxAge);


}//end GreenMonkey()


void GreenMonkey::print()
{
	cout << left << setw(17) << "Name --> " << name;
	cout << left << setw(17) << "Gender --> " << gender;
	cout << left << setw(17) << "Age --> " << age;
	cout << left << setw(17) << "Weight -->" << setprecision(3) << weight;
	if (alive)
	{
		cout << left << setw(17) << "Alive ";
	}//endif
	if (!alive)
	{
		cout << left << setw(17) << "Dead ";
	}//endif

	if (mutant)
	{
		cout << left << setw(17) << "Mutant ";
	}//endif

	if (!mutant)
	{
		cout << left << setw(17) << "Normal ";
	}//endif


	cout << left << setw(17) << "Injured --> " << injured;
	cout << endl;

}//end print() 

void GreenMonkey::eat()
{
	if (!mutant)
	{
		weight += weight * (getRandomNumber(minIncrease, maxIncrease)/100);
	}//endif

}//end eat()


void GreenMonkey::age_me()
{
	age = age + 1;
	int probmut = getRandomNumber(1, 100);
	if (probmut <= 2)
	{
		mutant = true;
	}//endif

	int probdeath = getRandomNumber(1, 100);

	if (probdeath <= round(weight) || injured > 3)
	{
		alive = false;
	}//endif
}// end age_me()


void GreenMonkey::fight(GreenMonkey* rival)
{
	float kilo = (weight / rival->get_weight()) * 50;

	float inspect = getRandomNumber(1, 100);

	if (inspect > kilo)
	{
		injured = injured + 1;
	}//endif

	if (kilo > inspect)
	{
		rival->set_injured(rival->get_injured() + 1);
	}//endif

}//end fight()


float GreenMonkey::get_weight()
{
	return weight;
}//end get_weight()

short int GreenMonkey::get_injured()
{
	return injured;
}//end get_injured()

void GreenMonkey::set_injured(short int hurt)
{
	injured = hurt;
}//end set_injured

void GreenMonkey::set_weight(float newton)
{
	weight = newton;
}//end set_weight

void GreenMonkey::set_age(short int elder)
{
	age = elder;
}//end set_age

void GreenMonkey::set_name(string n)
{
	name = n;
}//end set_name

void GreenMonkey::set_gender(char g)
{
	gender = g;
}//end set_gender

void GreenMonkey::set_alive(bool status)
{
	alive = status;
}// end set_alive

void GreenMonkey::set_mutant(bool mut)
{
	mutant = mut;
}//end set_mutant

void GreenMonkey::set_ID(int iden)
{
	ID = iden;
}//end set_ID

short int GreenMonkey::get_age()
{
	return age;
}//end get_age

string GreenMonkey::get_name()
{
	return name;
}//end get_name

char GreenMonkey::get_gender()
{
	return gender;
}//end get_gender

bool GreenMonkey::get_alive()
{
	return alive;
}//end get_alive

bool GreenMonkey::get_mutant()
{
	return mutant;
}//end get_mutant

int GreenMonkey::get_ID()
{
	return ID;
}//end get_ID

void GreenMonkey::set_next(GreenMonkey* increment)
{
	next = increment;
}//end set_next

GreenMonkey* GreenMonkey::get_next()
{
	return next;
}//end get_next

//GREENMONKEY_LINKEDLIST CLASS DECLARATIONS

GreenMonkey_LinkedList::GreenMonkey_LinkedList()
{
	head = NULL;
	idCount = 0;
}//endGreenMonkey_LinkedList()

void GreenMonkey_LinkedList::printList()
{
	GreenMonkey* temp = head;
	while (temp != NULL)
	{
		temp->print();

		temp = temp->get_next();
	}//endwhile

}//end printList()

void GreenMonkey_LinkedList::insert_at_start()
{
	GreenMonkey* newID = new GreenMonkey;
	newID->set_next(head);
	head = newID;
	set_idCount();
	newID->set_ID(idCount);
}//end insert_at_start

void GreenMonkey_LinkedList::deleteNode(int val)
{
	if (head->get_ID() == val)
	{
		GreenMonkey* found = head;
		head = head->get_next();
		delete found;
		return;
	}

	GreenMonkey* found = head;
	GreenMonkey* prev = NULL;

	while (found != NULL)
	{
		if (found->get_ID() == val)
		{
			prev->set_next(found->get_next());
			//found->set_next(found->get_next()->get_next());
			delete found;
			return;
		}//endif
		prev = found;
		found = found->get_next();
	}//endwhile
}//end deleteNode

void GreenMonkey_LinkedList::set_idCount()
{
	idCount = idCount + 1;
}//end set_idCount

int GreenMonkey_LinkedList::get_idCount()
{
	return idCount;
}//get_idCount

void GreenMonkey_LinkedList::update_id()
{
	int i = 1;
	GreenMonkey* temp = head;
	while (temp->get_next() != NULL)
	{
		temp->set_ID(i);
		i = i++;
		temp = temp->get_next();
	}//endwhile

	idCount = i;

}//end update_id()

GreenMonkey* GreenMonkey_LinkedList::get_Head()
{
	return head;
}//end get_Head()

GreenMonkey* GreenMonkey_LinkedList::get_Node(int num)
{
	GreenMonkey* temp = head;
	while (temp != NULL)
	{
		if (temp->get_ID() == num)
		{
			return temp;
		}//endif

		temp = temp->get_next();
	}//endwhile
}

//HABITAT CLASS DECLARATIONS

vector<string> Habitat::getEmptyCells()
{
	vector<string> confusion;
	int x, y, z;
	int i = 48, j = 48;

	string pos = "";
	for (x = 0; x < RowCol;x++)
	{
		j = 48;
		for (y = 0;y < RowCol;y++)
		{
			if (grid[x][y].get_Head() == NULL)
			{
				pos += char(i);
				pos += " : ";
				pos += char(j);
				confusion.push_back(pos);
				pos = "";
			}//endif
			j++;
		}//endfor
		i++;
	}//endfor

	/*for (z = 0; z< confusion.size();z++)
	{
		cout << confusion.at(z) << endl;
	}//endfor
	*/
	return confusion;
}//end getEmptyCells()

void Habitat::intialization(int bob)
{
	int i;
	int count = 0, found = 0;
	string pos1, pos2, position;
	vector<string> confusion = getEmptyCells();

	for (i = 0;i < bob; i++)
	{
		found = 0;

		while (found == 0 && count < confusion.size())
		{
			GreenMonkey monke;
			vector<string> confusion = getEmptyCells();
			int p1 = monke.getRandomNumber(0, RowCol - 1);
			int p2 = monke.getRandomNumber(0, RowCol - 1);
			stringstream s1, s2;
			s1 << p1;
			s1 >> pos1;
			s2 << p2;
			s2 >> pos2;
			position = pos1 + " : " + pos2;
			for (int j = 0;j < confusion.size();j++)
			{
				if (position == confusion.at(j))
				{
					found = 1;
					/*cout << position << endl;
					cout << confusion.at(j) << endl;*/
					grid[p1][p2].insert_at_start();
					/*grid[p1][p2].get_Head()->print();*/
					count++;
				}//endif
			}//endfor
		}//endwhile


	}//endfor

}//end initialization

void Habitat::showGrid()
{
	int x, y;

	for (x = 0; x < RowCol;x++)
	{
		cout << left << setw(10) << x;

		for (y = 0; y < RowCol;y++)
		{
			if (grid[x][y].get_Head() != NULL)
			{
				cout <<left<< "[" << grid[x][y].get_Head()->get_gender() << setw(5) << "]";
				continue;
			}//endif
			else
				cout << left << "[ " << setw(5) << "] ";
		}//endfor
		cout << endl;
	}//endfor
}//end showGrid

void Habitat::invasion(int val)
{
	int i, x, y;
	for (i = 0; i < val; i++)
	{
		GreenMonkey monke;
		x = monke.getRandomNumber(0, RowCol - 1);
		y = monke.getRandomNumber(0, RowCol - 1);

		if (grid[x][y].get_Head() == NULL)
		{
			grid[x][y].insert_at_start();
		}//endif
		else
		{
			grid[x][y].insert_at_start();
			impact(grid[x][y], grid[x][y].get_Head());
		}//endelse
	}//endfor
}//end invasion()

void Habitat::impact(GreenMonkey_LinkedList& link, GreenMonkey* monke)
{
	int location = monke->getRandomNumber(1, link.get_idCount());

	if (!link.get_Node(location)->get_alive())
	{
		return;
	}//endif

	else
	{
		if (link.get_Node(location)->get_gender() == monke->get_gender())
		{
			monke->fight(link.get_Node(location));
		}//endif
		else
		{
			link.insert_at_start();
		}//endelse
	}//endelse
}//end impact()

void Habitat::ageAll()
{
	int x, y;
	for (x = 0; x < RowCol;x++)
	{
		for (y = 0; y < RowCol;y++)
		{
			if (grid[x][y].get_Head() != NULL)
			{
				GreenMonkey* temp = grid[x][y].get_Head();
				while (temp->get_next() != NULL)
				{
					temp->age_me();

					temp = temp->get_next();
				}//endwhile
				continue;
			}//endif
		}//endfor
	}//endfor
}//end ageAll()

void Habitat::feedAll()
{
	int x, y;
	for (x = 0; x < RowCol;x++)
	{
		for (y = 0; y < RowCol;y++)
		{
			if (grid[x][y].get_Head() != NULL)
			{
				GreenMonkey* temp = grid[x][y].get_Head();
				while (temp->get_next() != NULL)
				{
					temp->eat();

					temp = temp->get_next();
				}//endwhile
				continue;
			}//endif
		}//endfor
	}//endfor
}//end feedAll()

void Habitat::printAll()
{
	int x, y;
	for (x = 0; x < RowCol;x++)
	{
		for (y = 0; y < RowCol;y++)
		{
			if (grid[x][y].get_Head() != NULL)
			{
				cout << "Cell -> " << x << ":" << y << " has " << grid[x][y].get_idCount() << " monkeys." << endl;

				cout << left << setw(15) << "Name" << setw(15) << "Age" << setw(15) << "Weight" << setw(15) << "Gender"
					<< setw(15) << "Status" <<setw(15)<< "Genes" << setw(15) << "Injured" << endl;

				/*cout << setw(5) << "Weight" <<setw(5) << "Gender";
				cout << setw(5) << "Status" << "Genes";
				cout <<setw(5)<< "Injured";*/

				for (int i = 0; i < 90; i++)
				{
					cout << "=";
				}//endfor
				cout << endl;

				GreenMonkey* temp = grid[x][y].get_Head();
				while (temp->get_next() != NULL)
				{
					temp->print();
					temp = temp->get_next();
				}//endwhile
				continue;
			}//endif
		}//endfor
	}//endfor
}//end printAll()

void Habitat::getStatistics()
{
	int monktot = 0;
	int malemonktot = 0;
	int fmalemonktot = 0;
	int totalive = 0;
	int totdead = 0;
	int mut = 0;
	int norm = 0;
	float avgweight = 0;
	float avgage = 0;
	float avginj = 0;

	int x, y;
	for (x = 0; x < RowCol;x++)
	{
		for (y = 0; y < RowCol;y++)
		{
			if (grid[x][y].get_Head() != NULL)
			{
				GreenMonkey* temp = grid[x][y].get_Head();
				while (temp->get_next() != NULL)
				{
					monktot++;

					if (temp->get_gender() == 'M')
					{
						malemonktot++;
					}//endif
					else
					{
						fmalemonktot++;
					}//endelse
					if (temp->get_alive())
					{
						avgweight += temp->get_weight();
						avgage += temp->get_age();
						avginj += temp->get_injured();
						totalive++;
					}//endif
					else
					{
						totdead++;
					}//endelse
					if (temp->get_mutant())
					{
						mut++;
					}//endif
					else
					{
						norm++;
					}//endelse

					temp = temp->get_next();
				}//endwhile
				continue;
			}//endif
		}//endfor
	}//endfor
	avgweight = avgweight / totalive;
	avgage = avgage / totalive;
	avginj = avginj / totalive;
	for (int i = 0; i < 90; i++)
	{
		cout << "=";
	}//endfor
	cout << endl;

	cout << left << setw(80) << "Description" << "Value" << endl;


	for (int i = 0; i < 90; i++)
	{
		cout << "=";
	}//endfor
	cout << endl;

	cout << left << setw(82) << "Total monkeys in the habitat" << monktot << endl;
	cout << left << setw(82) << "Total male monkeys in the habitat" << malemonktot << endl;
	cout << left << setw(82) << "Total female monkeys in the habitat" << totalive << endl;
	cout << left << setw(82) << "Total alive monkeys in the habitat" << totdead << endl;
	cout << left << setw(82) << "Total dead monkeys in the habitat" << totdead << endl;
	cout << left << setw(82) << "Total mutant monkeys in the habitat" << mut << endl;
	cout << left << setw(82) << "Total normal monkeys in the habitat" << norm << endl;
	cout << left << setw(82) << "Average weight of all alive monkeys in the habitat" << setprecision(3) << avgweight << endl;
	cout << left << setw(82) << "Average age of all alive monkeys in the habitat" << setprecision(3) << avgage << endl;
	cout << left << setw(82) << "Average injuries of all alive monkeys in the habitat" << setprecision(3) << avginj << endl;

	for (int i = 0; i < 90; i++)
	{
		cout << "=";
	}//endfor
	cout << endl;

}//end getStatistics()
