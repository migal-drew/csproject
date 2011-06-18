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

enum argType {none, func, var, any};

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

slot opponent[256], proponent[256];

field* (*functions[15])(field* args[3]);
argType argsType[15][3];

/*CARDS FUNCTION*/

field* func_I(field* args[3]);
field* func_zero(field* args[3]);
field* func_succ(field* args[3]);
field* func_dbl(field* args[3]);
field* func_get(field* args[3]);
field* func_put(field* args[3]);
field* func_S(field* args[3]);
field* func_K(field* args[3]);
field* func_inc(field* args[3]);
field* func_dec(field* args[3]);
field* func_attack(field* args[3]);
field* func_help(field* args[3]);
field* func_copy(field* args[3]);
field* func_revive(field* args[3]);
field* func_zombie(field* args[3]);

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

field* Execute(cards card, field* args[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (!(
		(argsType[card][i] == none && args[i] == NULL) || 
		(args[i] != NULL && (
			(argsType[card][i] == any) ||
			(argsType[card][i] == func && args[i] -> m_keyIsFunction) || 
			(argsType[card][i] == var && !args[i] -> m_keyIsFunction)))))
			return NULL;
	}
	return functions[card](args);
}

void Calculate(field* f)
{
	int i = -1;
	while (i < 2 && f -> m_args[++i] != NULL)
	{
		if (f->m_keyIsFunction)
		{
			Calculate(f -> m_args[i]);
			field* newF = Execute(f -> m_function, f -> m_args);
			//if f==NULL then we can't execute;
			if (f != NULL)
			{
				DeleteField(f);
				f = newF;
			}
		}
	}
}

void CommitState(slot slots[], turn t)
{
	field* f = InitField(t.m_card);
	if (t.m_choice == ctos)
	{
		f -> m_args[0] = slots[t.m_slot].m_field;
		slots[t.m_slot].m_field = f -> m_args[0];
	}
	else
	{
		int i = -1;
		while (i < 2 && slots[t.m_slot].m_field -> m_args[++i] != NULL);
		if (i < 3)
			slots[t.m_slot].m_field[i].m_args[i] = f;
	}
	Calculate(slots[t.m_slot].m_field);
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
	CommitState(opponent, ans);
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
	CommitState(proponent, t);
}

void InitSlot(slot &s)
{
	s.m_isAlive = true;
	s.m_vitality = 10000;
	s.m_field = InitField(I);
}

void Init()
{
	//Init all slots
	for (int i = 0; i < 256; i++)
	{
		InitSlot(opponent[i]);
		InitSlot(proponent[i]);
	}
	//Init card functions
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
	functions[] = func_;
	argsType[][1] = ;
	argsType[][2] = ;
	argsType[][3] = ;
	/////////////////////
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

