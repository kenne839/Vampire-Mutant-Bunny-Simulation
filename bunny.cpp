// Beginner Graduation (vampire bunnies).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

//Write a program that creates a linked list of 'bunny' objects
//Each bunny must have: sex: male,female(50/50 chance)
//						color: white, brown, black, spotted
//						Name: randomly chosen from list of bunny names
//						age (0-10)
//						radioactive_mutant_vampire_bunny: true/false (decided at time of bunny creation (2% change))

//Graduation Psuedo-code
//Bunny Class:
//Data members: sex, color, name, age, radioactive
//constructor: declareborn(), randomly choose name,age,color,sex, radioactiveness


int randAge(void);
int randColor(void);
int randSex(void);
bool randRadioactive();
string randName(vector<string>& bunnyNames);

enum bunnyColor {WHITE, BROWN, BLACK, SPOTTED}; //possible bunny colors
enum bunnySex { MALE, FEMALE };
enum radioactive { nRADIOACTIVE, RADIOACTIVE};
vector<string> bunnyNames = { "Darth Maul", "Filthy Wabbit", "Julies Ceasar", "Ezio Auditore", "Medjay", "Babbit Brook", "Bilbo Hoppins" };

class Bunny
{
public:
	//Bunny();
	Bunny(int age = randAge(), int color = randColor()); //debug
	int GetAge();
	void SetAge(int age);
	int GetColor();
	bool GetRadioactive();
	int GetSex();
	void SetNext(Bunny *Bunny);
	void PrintInfo();
	Bunny* GetNext();
	string GetName();
	void SetRadioactive();
private:
	int m_Age;
	int m_Sex;
	string m_Name;
	bool m_Radioactive;
	int m_Color;
	Bunny* m_pNext;
};
Bunny::Bunny(int age, int color)
{

	//m_Age = randAge();
	//m_Color = randColor();
	m_Age = age;
	m_Color = color;

	m_Sex = randSex();
	m_Radioactive = randRadioactive();
	m_Name = randName(bunnyNames);
	m_pNext = NULL;

	/*if (m_Radioactive)
	{
		cout << "Radioactive Mutant Vampire ";
	}
	cout << "Bunny " << m_Name << " was born." << endl;*/
	//cout << endl << "My name is " << m_Name << " and I am " << m_Age << " years old." << endl;
	//cout << "Radioactive: " << m_Radioactive << endl;
	//cout << "Color: " << m_Color << endl;
	//cout << "Sex: " << m_Sex << endl;
}
int Bunny::GetAge()
{
	return m_Age;
}
int Bunny::GetSex()
{
	return m_Sex;
}
bool Bunny::GetRadioactive()
{
	return m_Radioactive;
}
int Bunny::GetColor()
{
	return m_Color;
}
void Bunny::SetAge(int age)
{
	m_Age = age;
}
void Bunny::SetNext(Bunny *Bunny)
{
	m_pNext = Bunny;
}
Bunny* Bunny::GetNext()
{
	return m_pNext;
}
string Bunny::GetName()
{
	return m_Name;
}
void Bunny::PrintInfo()
{
	cout << "Name: " << GetName() << ", Age: " << GetAge() << ", Color: ";
	switch (m_Color)
	{
	case WHITE:
		cout << "White";
		break;
	case BLACK:
		cout << "Black";
		break;
	case BROWN:
		cout << "Brown";
		break;
	case SPOTTED:
		cout << "Spotted";
		break;
	default:
		cout << "Rainbow?";
		break;
	}
	cout << ", Radioactive: ";
	m_Radioactive == RADIOACTIVE ? (cout << "y") : (cout << "n");
	cout << ", Sex: ";
	m_Sex == MALE ? (cout << "Male") : (cout << "Female");
	cout << endl;
}
void Bunny::SetRadioactive()
{
	m_Radioactive = RADIOACTIVE;
}

class Colony
{
public:
	Colony(int size = 0);
	void AddBunny(int age = randAge(), int color = randColor());
	void KillBunny(Bunny* bunny);
	Bunny* ReturnTail();
	void PrintTail();
	void PrintColony();
	Bunny* ReturnHead();
	void SortColony(Bunny *pHead, Bunny *pPrev); //sort colony by age
	int GetColonySize();
	void AgeBunnies();
	void BreedColony();
	void CullColony();
	void AddRadio();
	int m_Peak_Size;
	int m_CullCount;
private:
	int m_Colony_Size;
	int m_Females;
	int m_Males;
	int m_Radioactive;

	Bunny* m_pHead;
	Bunny* m_pTail;
};
Colony::Colony(int size)
{
	m_Colony_Size = size;
	m_Males = 0;
	m_Females = 0;
	m_Radioactive = 0;
	m_pHead = NULL;
	m_pTail = NULL;
	m_Peak_Size = 0;
	m_CullCount = 0;
}

void Colony::AddBunny(int age, int color)
{
	Bunny* pNewBunny = new Bunny(age, color);
	if (m_pHead == NULL)
	{
		m_pHead = pNewBunny;
		m_pTail = m_pHead;
	}
	else
	{
		m_pTail->SetNext(pNewBunny);
		m_pTail = pNewBunny;
	}

	//update colony counters
	pNewBunny->GetSex() == MALE ? m_Males++ : m_Females++;
	if (pNewBunny->GetRadioactive() == RADIOACTIVE) m_Radioactive++;
	m_Colony_Size = m_Males + m_Females;
}
void Colony::KillBunny(Bunny *deadBunny)
{
	Bunny* pTemp = m_pHead;
	Bunny* pOldBunny = NULL;
	string Name = deadBunny->GetName();

	//decrement colony counters if not empty
	if (m_pHead != NULL)
	{
		deadBunny->GetSex() == MALE ? m_Males-- : m_Females--;
		if (deadBunny->GetRadioactive() == RADIOACTIVE) m_Radioactive--;
		m_Colony_Size = m_Males + m_Females;
		//cout << "Bunny " << Name << " has died!" << endl;
	}
	//empty list do nothing
	if (m_pHead == NULL)
	{
		cout << "Empty List, can't delete anything" << endl;
	}
	//remove head from a list greater than 1 bunny
	else if (deadBunny == m_pHead && deadBunny != m_pTail)
	{
		m_pHead = m_pHead->GetNext();
		delete deadBunny;
	}
	//remove tail from a list greater than 1 bunny
	else if (deadBunny == m_pTail && deadBunny != m_pHead)
	{

		for (; pTemp != deadBunny; pTemp = pTemp->GetNext())
		{
			if ((pTemp->GetNext()) == deadBunny)
			{
				pOldBunny = pTemp;
			}
		}
		m_pTail = pOldBunny;
		pOldBunny->SetNext(NULL);
		delete deadBunny;
	}
	//delete last member of list
	else if (deadBunny == m_pHead && deadBunny == m_pTail)
	{
		delete deadBunny;
		m_pHead = NULL;
		m_pTail = NULL;
	}
	else
	{
		for (; pTemp != deadBunny; pTemp = pTemp->GetNext())
		{
			if ((pTemp->GetNext()) == deadBunny)
			{
				pOldBunny = pTemp;
			}
		}
		//m_pTail = pOldBunny;
		pOldBunny->SetNext(deadBunny->GetNext());
		delete deadBunny;
	}
	
}
Bunny* Colony::ReturnTail() //debug
{
	return m_pTail;
}
Bunny* Colony::ReturnHead() //debug
{
	return m_pHead;
}
void Colony::PrintTail() //debug 
{
	cout << endl << "You are killing: ";
	cout << m_pTail->GetName() << endl;
}
void Colony::PrintColony()
{
	Bunny *pTemp = m_pHead;

	cout << endl << "This colony has " << m_Colony_Size << " bunnie(s) in it. ";
	cout << "There are " << m_Females << " female(s) and " << m_Males << " males." << endl;
	cout << "Here are their stats: " << endl;
	if (m_pHead != NULL ) //if not empty list
	{
		while (pTemp->GetNext() != NULL) //print info until you get to tail
		{
			pTemp->PrintInfo();
			pTemp = pTemp->GetNext();
		}
		//cout << "Printing Tail" << endl;
		pTemp->PrintInfo(); //print tail
		cout << endl;
	}
	else
	{
		cout << "Actually, this colony is empty" << endl;
	}

}
void Colony::SortColony(Bunny *pHead, Bunny *pPrev)
{
	//PrintColony();
	Bunny *tempNode = NULL;
	Bunny *pTemp = NULL;
	Bunny *pTempHead = NULL;
	Bunny *pPrevTemp = NULL;

	//If at the end of the list, return
	if (pHead->GetNext() == NULL)
	{
		//cout << endl << "End of list return" << endl;
		return;
	}

	//move to next node
	pPrevTemp = pHead; //maintain previous entry
	tempNode = pHead->GetNext();
	//cout << endl << "Calling SortColony with pHead: " << tempNode->GetName() << " and pPrev: " << pPrevTemp->GetName() << endl;
	SortColony(tempNode, pPrevTemp);
	tempNode = pHead->GetNext();
	//cout << endl << "Returned to call with pHead: " << pHead->GetName() << " and tempNode: " << tempNode->GetName() << " and pPrev: " << pPrev->GetName() << endl;
	//cout << "tempNode is pointing to: " << tempNode->GetNext() << endl;
	//cout << "pHead address is: " << pHead << endl;
	if (tempNode->GetAge() < pHead->GetAge())
	{

		pTemp = pHead; //get address of pHead
		//if (tempNode->GetNext() == NULL) cout << "TempNode->GetNext() == NULL!" << endl;
		pHead->SetNext(tempNode->GetNext()); //set to what node ahead is pointing to

		if (tempNode->GetNext() == NULL) m_pTail = pHead;
		//cout << "m_pTail is now pointing to: " << m_pTail->GetName() << endl;
		if (pHead == m_pHead)
		{
			m_pHead = tempNode;
			//cout << endl << "CHANGING HEAD TO: " << m_pHead->GetName() << endl;
			//cout << endl << "pHead->GetNext(): " << pHead->GetNext() << endl;
		}
		tempNode->SetNext(pHead);
		//cout << endl << "tempNode->GetNext(): " << tempNode->GetNext() << endl;
		//cout << "pPrev is: " << pPrev->GetName() << endl;
		//cout << "pPrev is now pointing to: " << tempNode->GetName() << endl;
		if (pPrev != pHead)
		{
			pPrev->SetNext(tempNode);
		}

		//cout << endl << "End of swap. Calling SortColony with pHead: " << pHead->GetName() << " and pPrev: " << tempNode->GetName() << endl;
		SortColony(pHead, tempNode);
	}

	return;
}
int Colony::GetColonySize()
{
	return m_Colony_Size;
}
void Colony::AgeBunnies()
{
	Bunny *pTemp = m_pHead;
	Bunny *pDeleteTemp = NULL;
	while (pTemp->GetNext() != NULL) //go to end of Bunnies linked list
	{	
		pDeleteTemp = pTemp->GetNext();
		pTemp->SetAge(pTemp->GetAge() + 1);
		if ((pTemp->GetRadioactive() != RADIOACTIVE) && (pTemp->GetAge() >= 10))
		{
			KillBunny(pTemp);
		}
		else if ((pTemp->GetRadioactive() == RADIOACTIVE) && (pTemp->GetAge() >= 50))
		{
			KillBunny(pTemp);
		}
		pTemp = pDeleteTemp;
	}

	if (pTemp->GetNext() == NULL)
	{
		pTemp->SetAge(pTemp->GetAge() + 1);
		if (pTemp->GetAge() >= 10)
		{
			KillBunny(pTemp);
		}
	}	
}
void Colony::BreedColony()
{
	Bunny *pTemp = m_pHead;

	bool breedAvail = false;
	int breedNum = 0;
	while (pTemp != NULL)
	{
		if (pTemp->GetSex() == MALE && pTemp->GetAge() >= 2 && pTemp->GetRadioactive() != RADIOACTIVE) //found any male that is 2 or older
		{
			breedAvail = true;
			break;
		}
		if (pTemp == m_pTail)
		{
			break;
		}
		pTemp = pTemp->GetNext();
	}

	pTemp = m_pHead;
	while (pTemp != NULL)
	{
		if (pTemp->GetSex() == FEMALE && pTemp->GetRadioactive() != RADIOACTIVE)
		{
			breedNum++;
		}
		if (pTemp == m_pTail)
		{
			break;
		}
		pTemp = pTemp->GetNext();
	}

	pTemp = m_pHead;
	while (pTemp != NULL)
	{
		while (breedNum != 0) //while females left to breed
		{
			if (pTemp->GetSex() == FEMALE && pTemp->GetRadioactive() != RADIOACTIVE)
			{
				AddBunny(0, pTemp->GetColor()); //zero years old, same color as mother
				breedNum--;
			}
			if (pTemp == m_pTail)
			{
				break;
			}
			pTemp = pTemp->GetNext();
		}
		if (breedNum == 0)
		{
			break;
		}
	}
}

void Colony::CullColony()
{
	int randKill = 500;
	int killIter = 0;
	Bunny *pTemp = m_pHead;
	Bunny *pKillTemp = NULL;

	while (randKill > 0)
	{
		pKillTemp = pTemp->GetNext();
		if (pKillTemp->GetNext() == NULL)
			cout << "NEXT IS NULL" << endl;
		if (rand() % 2)
		{
			randKill--;
			KillBunny(pTemp);
		}
		pTemp = pKillTemp;
		if (pTemp->GetNext() == NULL) //cycle back around if there are more kills to do
		{
			pTemp = m_pHead;
		}
	}
}

void Colony::AddRadio()
{

	Bunny *pTemp = m_pHead;
	int rACount = 0;

	pTemp = m_pHead;
	while (rACount < m_Radioactive && (rACount + m_Radioactive) != m_Colony_Size)
	{
		if (pTemp->GetRadioactive() != RADIOACTIVE)
		{
			pTemp->SetRadioactive();
			rACount++;
		}
		if (pTemp == m_pTail)
		{
			pTemp = m_pHead;
		}
		else
		{
			pTemp = pTemp->GetNext();
		}
	}
	if (rACount + m_Radioactive < m_Colony_Size)
	{
		m_Radioactive += m_Radioactive;
	}
	else
	{
		m_Radioactive = m_Colony_Size;
	}

}

int main()
{
	int numTurns = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	Colony myColony;

	//Test cases
	
	//Starts with 5 Bunnies
	myColony.AddBunny();
	myColony.AddBunny();
	myColony.AddBunny();
	myColony.AddBunny();
	myColony.AddBunny();
	myColony.AddBunny(0, WHITE);
	myColony.SortColony(myColony.ReturnHead(), myColony.ReturnHead());


	myColony.PrintColony();


	while (myColony.GetColonySize() != 0) //while bunnies left
	{
		numTurns++;
		if (myColony.GetColonySize() > myColony.m_Peak_Size)
		{
			myColony.m_Peak_Size = myColony.GetColonySize();
		}
		//Bunnies age 1 year
		//myColony.SortColony(myColony.ReturnHead(), myColony.ReturnHead());
		myColony.AgeBunnies(); //Kills old bunnies and ages the rest
		//myColony.PrintColony();
		if (myColony.GetColonySize() == 0)
			break;
		myColony.BreedColony();
		myColony.AddRadio();
		//myColony.SortColony(myColony.ReturnHead(), myColony.ReturnHead());

		if (myColony.GetColonySize() >= 1500)
		{
			myColony.CullColony();
			cout << "COLONY CULLED" << endl;
			myColony.m_CullCount++;
		}

		//If at least 1 male (two years or older), for each female bunny in the list age 2 or older, a new bunny is created each turn
		//New bunnies should be the same color as their mother. (0 years old)

		//For each radioactive bunny, exactly one other non-radioactive bunny turns into radioactive bunny
		//Radioactive bunnies to not breed

		//print colony info, sorted by age
		//terminate when all bunnies die

		//program should write all screen output to a file

		//If the bunny exceeds 1000, a food shortage must occur killing exactly half of the bunnies
	}

	cout << endl << "All the rabbits are dead!" << endl;
	cout << "The max size of the colony was: " << myColony.m_Peak_Size << endl;
	cout << "Number of culls: " << myColony.m_CullCount << endl;
	cout << "Number of turns: " << numTurns;

	getchar();
    return 0;
}

//Generate random bunny age from zero to 10
int randAge(void)
{
	int age = rand() % 11; 
	return age;
}

//Generate random bunny color between 4 choices, enumerated globally
int randColor(void)
{
	int color = rand() % 4; //gives 0-3
	return color;
}

//Generate random sex between MALE and FEMALE
int randSex(void)
{
	int sex = rand() % 2;
	return sex;
}

//If random number from 0-99 is 2 of them, (2% chance, the bunny is radioactive)
bool randRadioactive()
{
	int rA = rand() % 100;
	bool rAb = false; //radioactive?
	if (rA == 42) //randomly chosen 
		rAb = true;
	
	return rAb;
}

string randName(vector<string>& bunnyNames)
{
	int bunnyVectorSize = 0;
	int randName;
	string name;
	vector<string>::const_iterator iter = bunnyNames.begin();

	for (vector<string>::const_iterator iter = bunnyNames.begin(); iter != bunnyNames.end(); ++iter)
	{
		bunnyVectorSize++;
	}
	//cout << "Vector Size: " << bunnyVectorSize << endl;
	randName = rand() % (bunnyVectorSize); //should give a number between 0 and end of vector
	iter += randName;
	name = *iter;

	return name;
}
