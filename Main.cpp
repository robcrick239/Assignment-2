#include "Classes.h"

int main()
{

	GreenMonkey_LinkedList test;
	Habitat t;
	test.insert_at_start();
	test.insert_at_start();
	test.insert_at_start();
	test.update_id();
	cout << test.get_idCount();

	t.intialization(5);
	t.invasion(3);
	t.printAll();

	
	

}//endmain