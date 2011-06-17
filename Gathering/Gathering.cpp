// Gathering.cpp : Defines the entry point for the console application.
//
#include <iostream>
using namespace std;

/*CONSTANTS*/

const char CARDS_COUNT = 15;
char* CARDS_NAME[CARDS_COUNT] = {"I", "zero", "succ", "dbl", "get", "put", "S", "K", "inc", "dec", "attack", "help", "copy", "revive", "zombie"};

/*TYPES*/
enum cards {I, zero, succ, dbl, get, put, S, K, inc, dec, attack, help, copy, revive, zombie};

enum choice {ctos = 1, stoc = 2}; //ctos == Card to slot. stoc == Slot to card

struct field
{
	bool m_keyIsFunction;
	union 
	{
		unsigned int m_value;
		cards m_function;
	};
	field* m_args[3];
};

struct slot
{
	bool m_isAlive;
	unsigned int m_vitality;
	field* m_field;
};

struct turn
{
	choice m_choice;
	cards m_card;
	unsigned char m_slot;
};

/*GLOBAL VARIABLES*/

slot m_opponent[256], m_proponent[256];

void(*m_functions)(field* args[3])[15];
bool *m_args[15][3];

/*FUNCTIONS*/

cards StringToCards(char* s);
char* CardsToString(cards card);
field* InitField(cards card);
void DeleteFieldArgs(field* f);
void DeleteField(field* f);
bool Execute(cards card, field* args[3]);
void Calculate(field* f);
void CommitState(slot slots[], turn t);
turn ReadStep();
void WriteStep(turn t);
void InitSlot(slot &s);
void Init();
turn Logic();

cards StringToCards(char* s)
{
	char i = -1;
	while (++i < CARDS_COUNT && strcmpi(CARDS_NAME[i], s) != 0);
	if (i >= CARDS_COUNT)
		return I;
	return (cards)i;
}

char* CardsToString(cards card)
{
	return CARDS_NAME[card];
}

field* InitField(cards card)
{
	field* f = new field;
	f -> m_keyIsFunction = true;
	f -> m_function = card;
	for (int i = 0; i < 3; i++)
		f -> m_args[i] = NULL;
	return f;
}

void DeleteFieldArgs(field* f)
{
	if (f == NULL)
		return;
	for (int i = 0; i < 3; i++)
		DeleteField(f -> m_args[i]);
}

void DeleteField(field* f)
{
	DeleteFieldArgs(f);
	delete f;
}

bool Execute(cards card, field* args[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (m_args[card][i] != NULL && args[i] != NULL)
		{
			if ((*m_args[card][i]) != args[i] -> m_keyIsFunction)
				return false;
		}
		else
		{
			if (m_args != NULL || m_args != NULL) 
				return false;
		}
	}
	m_functions[card](args);
	return true;
}

void Calculate(field* f)
{
	int i = -1;
	while (i < 2 && f -> m_args[++i] != NULL)
	{
		if (f.m_keyIsFunction)
		{
			Calculate(f -> m_args[i]);
			if (Execute(f -> m_function, m_args))
			{
				DeleteFieldArgs(f);
			}
		}
	}
}

void CommitState(slot slots[], turn t)
{
	field* f = InitField(t.m_card)
	if (t.m_choice == ctos)
	{
		f.m_args[0] = slots[t.m_slot].m_field;
		slots[t.m_slot].m_field = f.m_args[0];
	}
	else
	{
		int i = -1;
		while (i < 2 && slots[t.m_slot].m_field[++i] != NULL);
		if (i < 3)
			slots[t.m_slot].m_field[i] = f;
	}
	Calculate(&slots[t.m_slot].m_field);
}

turn ReadStep()
{
	turn ans;
	int ch;
	cin>>ch;
	char s[10];
	ans.m_choice = (choice) ch;
	if (ans.m_choice == ctos)
	{
		cin>>s;
		cin>>ans.m_slot;
	}
	else
	{
		cin>>ans.m_slot;
		cin>>s;
	}
	ans.m_card = StringToCards(s);
	CommitState(m_opponent, ans);
	return ans;
}

void WriteStep(turn t)
{
	cout<<t.m_choice<<"\n";
	if (t.m_choice == ctos)
	{
		cout<<CardsToString(t.m_card)<<"\n";
		cout<<t.m_slot<<"\n";
	}
	else
	{
		cout<<t.m_slot<<"\n";
		cout<<CardsToString(t.m_card)<<"\n";
	}
	CommitState(m_proponent, t);
}

void InitSlot(slot &s)
{
	s.m_isAlive = true;
	s.m_vitality = 10000;
	s.m_field = InitField(I);
}

void Init()
{
	for (int i = 0; i < 256; i++)
	{
		InitSlot(m_opponent[i]);
		InitSlot(m_proponent[i]);
	}
}

turn Logic()
{
}

int main(int argc, char* argv[])
{
	if (argc!=2)
		return 1;
	Init();
	turn CurrentTurn;
	if (atoi(argv[1])==1)
	{
		CurrentTurn = ReadStep();
	}
	while (true)
	{
		CurrentTurn = Logic();
		WriteStep(CurrentTurn);
		CurrentTurn = ReadStep();
	}
	return 0;
}

