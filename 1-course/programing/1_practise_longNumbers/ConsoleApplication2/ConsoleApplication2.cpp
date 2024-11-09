

#include <iostream>


struct Number
{
	//creating class Number for too long numbers
	int  m_counter = 0; //shows the length of number
	bool m_isNegative = false; // if number < 0, true; else false
	int m_numbersActions[200]={ 0 }; // array with numbers
};

bool zeroCheck(Number a) // check if number is 0
{
	bool check = true;

	for (int i = 0; i < a.m_counter; i++)
		if (a.m_numbersActions[i] != 0)
			check = false;

	return check;
}

void output(Number a)
{
	if (zeroCheck(a))
		std::cout << 0;
	else
	{
		int newCounter = 0;

		while (a.m_numbersActions[newCounter] == 0)//if number == 1200 we will output only 12e2, not 120e1 or 1200
			newCounter++;

		//print as 1.2341e5
		if (a.m_isNegative)
			std::cout << "-";

		std::cout << a.m_numbersActions[a.m_counter - 1]<<".";

		for (int i = a.m_counter - 2; i >= newCounter; i--)
			std::cout << a.m_numbersActions[i];

		std::cout << "e" << a.m_counter - 1 << "\n";

		//print as 123410
		if (a.m_isNegative) std::cout << "-";

		for (int i = 0; i < a.m_counter; i++)
			std::cout << a.m_numbersActions[a.m_counter - 1 - i];
	}
	std::cout << "\n";
}

Number input()
{
	Number a={};

	std::cout << "Enter number(r to confirm):\n";

	char m_numbers[200] = { '0' };
	char n = '0';

	a.m_counter = 0;
	a.m_isNegative = false;

	std::cin >> n;

	a.m_isNegative = (n == '-');
	// if first char is "-", we make is_negative true and dont fill the "-" to the array, input again to start
	if (a.m_isNegative)
	{
		std::cin >> n;

		while (n != 'r')
		{
			m_numbers[a.m_counter] = n;
			a.m_counter++;

			std::cin >> n;
		}
	}

	else
	{
		while (n != 'r')
		{
			m_numbers[a.m_counter] = n;
			a.m_counter++;

			std::cin >> n;
		}
	}

	for (int i = 0; i < a.m_counter; i++)//1234 ->4321 in order to make +, * easier 
		a.m_numbersActions[i] = m_numbers[a.m_counter - i - 1] - '0';
	return a;
}

Number sum(Number a, Number b)
{
	int lB = b.m_counter;
	int lA = a.m_counter;

	int add = 0;
	Number Temp = a;

	if (lA - lB < 0)// we will add smaller to the bigger one
	{
		a = b;
		b = Temp;
	}

	//refresh information
	lB = b.m_counter;
	lA = a.m_counter;

	int is_na = a.m_isNegative;
	int is_nb = b.m_isNegative;

	if ((!is_na && !is_nb) || (is_na && is_nb))
	{
		for (int i = 0; i < lA; i++)
		{
			int Na = a.m_numbersActions[i];
			int Nb = b.m_numbersActions[i];
			int sum = Na + Nb;

			if (sum >= 10)
			{
				a.m_numbersActions[i + 1] += (sum/10);
				sum %= 10;
				add = i;
			}

			a.m_numbersActions[i] = sum;
		}
		if (add == lA - 1)
			a.m_counter++;

		return a;
	}
	else
	{
		for (int i = 0; i < lA; i++)
		{
			int Na = a.m_numbersActions[i];
			int Nb = b.m_numbersActions[i];
			int sum = Na - Nb;

			if (sum < 0)
			{
				add = i;
				a.m_numbersActions[i+1]--;
				sum += 10;
			}

			a.m_numbersActions[i] = sum;
		}
		if (add == lA - 2)
			a.m_counter--;

		return a;
	}
	
}

Number mul(Number a, Number b)
{
	
	int lB = b.m_counter;
	int lA = a.m_counter;
	
	int add2 = 0;
	int add = 0;
	Number Temp = a;

	if (lA - lB < 0)
	{
		a = b;
		b = Temp;
	}

	lB = b.m_counter;
	lA = a.m_counter;

	int is_na = a.m_isNegative;
	int is_nb = b.m_isNegative;

	Number res = { a.m_counter, false, {0} };

	if ((!is_na && !is_nb) || (is_na && is_nb))
		res.m_isNegative = false;
	else
		res.m_isNegative = true;

	for (int i = 0; i < lA; i++)
	{
		for (int j = 0; j < res.m_counter; j++)
		{
			res.m_numbersActions[j+i] += a.m_numbersActions[j] * b.m_numbersActions[i];

			if (res.m_numbersActions[j+i] >= 10)
			{
				res.m_numbersActions[j + 1+i] += res.m_numbersActions[j+i] / 10;
				res.m_numbersActions[j+i] %= 10;

				add = j;
				add2 = i;
			}
		}
		if (add == res.m_counter-1)
			res.m_counter++;
	}
	if (add2 == lA-1)
		res.m_counter++;

	return res;

}

int main()
{

	while (true)
	{
		Number A = input();
		Number B = input();

		std::cout << "\nMul: \n";
		output(mul(A,B));

		std::cout << "\nSum: \n";
		output(sum(A,B));

	}
}