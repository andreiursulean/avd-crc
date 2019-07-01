#include <iostream>

#define DEBUG true

int xor_function(int a, int b)
{
	return (a || b) && (!(a && b));
}

void copy_array(int* source, int* destination, int n)
{
	for (int i = 0; i < n; i++)
		destination[i] = source[i];
}

void print_array(int* a, int n)
{
	for (int i = 0; i < n; i++)
		std::cout << a[i] << ' ';
}

int main()
{
	int info[100], control[100], old_control[100], poly[100];
	int n, c, old_feedback = 0;

	// initialize control bits size and generating polynomial
	c = 4;
	poly[0] = 1;
	poly[1] = 0;
	poly[2] = 1;
	poly[3] = 1;

	if (DEBUG == true)
	{
		n = 6;
		info[0] = 1;
		info[1] = 0;
		info[2] = 1;
		info[3] = 1;
		info[4] = 1;
		info[5] = 0;
	}
	else
	{
		// get information and control size
		std::cout << "n = ";
		std::cin >> n;

		// read information
		std::cout << "info = ";
		for (int i = 0; i < n; i++)
			std::cin >> info[i];

	}
	// initialize control bits to 0
	for (int i = 0; i < c; i++)
		old_control[i] = 0;

	// calculate CRC
	for (int i = 1; i <= n; i++)
	{
		int feedback = xor_function(info[i - 1], old_control[0]);
		control[c - 1] = feedback;

		for (int j = c - 2; j >= 0; j--)
		{
			if (poly[j] == 1)
				control[j] = xor_function(old_control[j + 1], feedback);
			else
				control[j] = old_control[j + 1];
		}

		copy_array(control, old_control, c);


		if (DEBUG)
		{
			std::cout << info[i - 1] << "  ";
			print_array(old_control, c);
			std::cout << "  " << feedback << std::endl;
			
		}
	}

	std::cout << std::endl;
	print_array(info, n);
	std::cout << std::endl;
	print_array(control, c);
	std::cout << std::endl;
}
