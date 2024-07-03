#include <iostream>
using namespace std;

union data_type
{
	int value_int;
	char value_char;
};

enum type : char
{
	PLUS = '+',
	MINUS = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	OPEN_BRACKET = '(',
	CLOSE_BRACKET = ')',
	MIN = 'm',
	MAX = 'M',
	NAND = 'N',
	IF = 'I'
};

struct Node
{
	//If_int = 1 - liczba całkowita, If_int = 0 - operator
	int if_int = 0;
	data_type value;
	Node* previous = nullptr; //poprzednia gałąź do tylu
	Node* next = nullptr; //następna gałąź do przodu
};


class Stack
{
	Node* head;
	Node* tail;
	int size;

public:
	Stack();
	void push(char token);
	void push_from_stack_int(int token);
	int pop();
	int peek() const;
	int get_size() const;
	bool data_type() const;
	void clear();
	~Stack();

};

Stack::Stack()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

void Stack::push(char token)
{

	Node* create_node = new Node;
	switch (token) {
	case PLUS:
	case MINUS:
	case MULTIPLY:
	case DIVIDE:
	case OPEN_BRACKET:
	case CLOSE_BRACKET:
	case MIN:
	case MAX:
	case NAND:
	case IF:
		create_node->value.value_char = token;
		create_node->if_int = 0;
		break;
	default:
		create_node->value.value_int = int(token);
		create_node->if_int = 1;
		break;
	}

	create_node->next = nullptr;
	create_node->previous = nullptr;

	if (head == nullptr)
	{
		head = create_node;
		tail = create_node;
	}
	else
	{
		create_node->next = head;
		head->previous = create_node;
		head = create_node;
	}
	size++;
}




void Stack::push_from_stack_int(int token)
{

	Node* create_node = new Node;


	create_node->value.value_int = int(token);
	create_node->if_int = 1;


	create_node->next = nullptr;
	create_node->previous = nullptr;


	if (head == nullptr)
	{
		head = create_node;
		tail = create_node;
	}
	else
	{
		create_node->next = head;
		head->previous = create_node;
		head = create_node;
	}
	size++;
}


int Stack::pop()
{
	if (head == nullptr)
	{
		return -1;
	}
	else
	{
		Node* temp = head;
		head = head->next;
		if (temp->if_int == 1)
		{
			int r = temp->value.value_int;
			delete temp;
			size--;
			return r;
		}
		else
		{
			char r = temp->value.value_char;
			delete temp;
			size--;
			return r;
		}
	}
}


int Stack::peek() const
{
	if (head == NULL)
	{
		return -1;
	}
	else
	{
		if (head->if_int == 0)
		{
			switch (head->value.value_char)
			{
			case PLUS:
				return PLUS;
			case MINUS:
				return MINUS;
			case MULTIPLY:
				return MULTIPLY;
			case DIVIDE:
				return DIVIDE;
			case OPEN_BRACKET:
				return OPEN_BRACKET;
			case CLOSE_BRACKET:
				return CLOSE_BRACKET;
			case MIN:
				return MIN;
			case MAX:
				return MAX;
			case NAND:
				return NAND;
			case IF:
				return IF;
			default:
				return ' ';

			}
		}
		else
			return head->value.value_int;
	}
}


int Stack::get_size() const
{
	return size;
}

bool Stack::data_type() const
{
	if (head == NULL)
	{
		printf("Stack is empty\n");
	}
	else
	{
		if (head->if_int == 1)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	return 0;
}

//czyści zawartość stosu
void Stack::clear()
{
	while (head != NULL)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
	size = 0;
}


Stack::~Stack()
{
	while (head != NULL)
	{
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}

//sprawdza czy token jest operatorem
bool if_operand(char token)
{
	switch (token)
	{
	case OPEN_BRACKET:
	case CLOSE_BRACKET:
	case PLUS:
	case MINUS:
	case MULTIPLY:
	case DIVIDE:
	case MIN:
	case MAX:
	case NAND:
	case IF:
		return true;
	default:
		return false;
	}
}


//kolejność wykonywania działań
int priority(char token)
{
	switch (token)
	{
	case PLUS:
	case MINUS:
		return 2;
	case MULTIPLY:
	case DIVIDE:
		return 3;
	case MIN:
	case MAX:
		return 4;
	case NAND:
		return 5;
	default:
		return 1;
	}
}


int do_calculations(char token, Stack& help_onp, Stack& stack)
{
	if (token == MIN)
	{

		if (stack.peek() == 1)
		{
			stack.pop();
			return help_onp.pop();
		}
		else {
			int a = help_onp.pop();

			int counter = stack.pop();
			for (int i = 0; i < counter - 1; i++) {
				if (a < help_onp.peek())
				{
					help_onp.pop();
				}
				else
				{
					a = help_onp.pop();
				}
			}
			return a;
		}
	}
	else if (token == MAX) {

		if (stack.peek() == 1)
		{
			stack.pop();
			return help_onp.pop();
		}
		else {
			int a = help_onp.pop();

			int counter = stack.pop();
			for (int i = 0; i < counter - 1; i++) {
				if (a > help_onp.peek())
				{
					help_onp.pop();
				}
				else
				{
					a = help_onp.pop();
				}

			}
			return a;
		}
	}
	else if (token == IF) {

		int c = help_onp.pop();
		int b = help_onp.pop();
		int a = help_onp.pop();
		if (a > 0)
		{
			return b;
		}
		else
		{
			return c;
		}
	}
	else
	{

		if (token == NAND)
		{
			int a = help_onp.pop();
			return -a;
		}
		else {
			int a = help_onp.pop();
			int b = help_onp.pop();
			switch (token)
			{
			case PLUS:
				return a + b;
			case MINUS:
				return b - a;
			case MULTIPLY:
				return a * b;
			case DIVIDE:
				if (a != 0)
					return b / a;
				else
					return INT_MIN;
			default:
				return -1;
			}
		}
	}
}

void rotation(Stack& onp, Stack& stack)
{
	while (onp.get_size() > 0)
	{
		if (onp.data_type() == 1)
		{
			int p = onp.peek();
			stack.push_from_stack_int(p);
			onp.pop();
		}
		else
		{
			char p = char(onp.peek());
			stack.push(p);
			onp.pop();
		}
	}
}

void close_bracket_function(Stack& stack, Stack& onp, Stack& count)
{
	while (stack.peek() != '(' && stack.get_size() != 0)
	{
		onp.push(char(stack.peek()));
		stack.pop();


	}
	stack.pop(); //usuwamy nawias otwierający
	if (stack.peek() == IF || stack.peek() == NAND) { //jeśli na stosie jest IF lub NAND to dodajemy je do stosu ONP
		onp.push(char(stack.peek()));
		stack.pop();

	}

	//dodatkowy warunek dla min i max ze względu na liczenie argumentów
	if ((stack.peek() == MIN || stack.peek() == MAX) && count.get_size() > 0 && count.peek() != -1)
	{
		onp.push(char(stack.pop()));
		onp.push_from_stack_int(count.pop());

	}
	else if (count.get_size() > 0 && count.peek() == -1) //jeśli na stosie jest -1 to usuwamy go ( -1 pomaga nam tylko zobaczyc czy to jest nawias otwierający do liczenia min i max)
	{
		count.pop();
	}
}

void comma_function(Stack& stack, Stack& onp, Stack& count)
{
	while (stack.peek() != '(' && stack.peek() != ',' && stack.get_size() != 0) //dodawanie przecinka do stosu
	{
		onp.push(char(stack.peek()));
		stack.pop();
	}
	if (stack.peek() == ',') //jeśli na stosie jest przecinek to go usuwamy
		stack.pop();

	if (count.get_size() > 0 && count.peek() != -1) //count licznik do min i max , jeśli jest -1 to nie dodajemy ( -1 sygnalizuje naiwas otwierający - wyedy program wie że musi zacząć liczbyć od nowa)
	{
		int s = count.pop();
		s++;
		count.push(char(s)); //dodawana jest wartość zlicconej ilości argumentów dla min lub max
	}

}

void convert_char_to_int(char* input, Stack& onp)
{
	int num = 0;
	int j = 0;
	while (input[j] != '\0') {
		num *= 10;
		num += (input[j] - '0');
		j++;
	}
	onp.push_from_stack_int(num);

}

void find_operator(char* input, Stack& stack, Stack& onp, Stack& count)
{
	if (input[0] == '(')
	{
		if (count.get_size() > 0)
		{
			count.push(-1);
		}
		stack.push(input[0]);


	}
	else if (input[0] == ')') //jeśli nawias zamykający to usuwamy wszystko ze stosu do napotkania nawiasu otwierającego
	{
		close_bracket_function(stack, onp, count);
	}
	else if (input[0] == 'I' && input[1] == 'F')
	{
		stack.push(IF);

	}
	else if (input[1] == 'I')
	{
		stack.push(MIN);
		cin >> input[0];
		stack.push(input[0]);
		count.push(1);
	}
	else if (input[1] == 'A')
	{
		stack.push(MAX);
		cin >> input[0];
		stack.push(input[0]);
		count.push(1);
	}
	else if (input[0] == 'N' && stack.peek() == 'N') //gdyby było 2 razy negacja
	{
		stack.push(char(input[0]));

	}
	else if (priority(char(input[0])) > priority(char(stack.peek())))
	{
		stack.push(input[0]);

	}
	else if (priority(char(input[0])) <= priority(char(stack.peek())))
	{
		while (priority(char(input[0])) <= priority(char(stack.peek())) && stack.get_size() > 0)
		{
			onp.push(char(stack.peek()));
			stack.pop();

		}
		stack.push(input[0]);
	}
}

void onp_creator(char* input, Stack& stack, Stack& onp, Stack& count) {
	while (input[0] != '.')
	{
		cin >> input;

		if (input[0] == '.') //usuwanie zawartości stosu na koniec
		{
			while (stack.get_size() > 0)
			{
				onp.push(char(stack.peek()));
				stack.pop();
			}
			break;
		}
		else if (input[0] == ',')
		{
			comma_function(stack, onp, count);
		}
		else if (if_operand(input[0]) == false) //sprawdza czy to liczba, jak tak to konwertuje znak po znaku z tablicy char na int i dodaje wynik do stosu
		{
			convert_char_to_int(input, onp);

		}
		else //jeśli to operator
		{
			find_operator(input, stack, onp, count);
		}
	}
}

void calculator_onp(Stack& stack, Stack& help_onp, int& result)
{
	char token = ' ';
	while (stack.get_size() > 0)
	{
		if (stack.data_type() == false)
		{
			token = char(stack.pop());

			result = (do_calculations(token, help_onp, stack));
			if (result == INT_MIN && token == DIVIDE)
			{
				printf("ERROR\n");
				break;
			}
			else
			{
				help_onp.push_from_stack_int(result);
			}

		}
		else
		{
			help_onp.push_from_stack_int(stack.peek());
			stack.pop();
		}
	}
}


int main()
{
	int result = INT_MIN;
	int invoke;
	cin >> invoke;
	Stack stack;
	Stack onp;
	Stack count;
	Stack help_onp; //do wyswietlenia np.  - 6 11 -400
	char* input = new char[10];
	for (int i = 0; i < invoke; i++)
	{
		input[0] = ' ';
		onp_creator(input, stack, onp, count);

		stack.clear();

		//odwracanie stosu ONP
		rotation(onp, stack);


		//obliczanie wyrażenia ONP
		calculator_onp(stack, help_onp, result);

		//wyswietlanie wyniku
		if (result != INT_MIN)
			printf("%d\n", result);

		onp.clear();
		stack.clear();
		help_onp.clear();

	}
	delete[] input;
	return 0;
}
