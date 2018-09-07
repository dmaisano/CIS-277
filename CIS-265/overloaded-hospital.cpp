#include <iostream>
using namespace std;

void validate(int *);
void validate(float *);
void charge(int, float, float, float);
void charge(float, float);

int main()
{
	int patientType, numDays;
	float rate, medCharge, services;

	cout << "Enter 1 for in-patient\nEnter 2 for out-patient\nEnter choice: ";
	cin >> patientType;

	while (patientType != 1 && patientType != 2)
	{
		cout << "Enter 1 for in-pati ent\nEnter 2 for out-patient\nEnter choice: ";
		cin >> patientType;
	}

	if (patientType == 1)
	{
		cout << "Enter the number of days spent in the hospital: ";
		cin >> numDays;
		while (numDays <= 0)
		{
			cout << "Days spent in hospital must be one or greater.\nEnter the number of days spent in the hospital: ";
			cin >> numDays;
		}

		cout << "Enter the amount for the daily rate: $";
		cin >> rate;
		validate(&rate);

		cout << "Enter the amount for the hospital medication charges: $";
		cin >> medCharge;
		validate(&medCharge);

		cout << "Enter the amount of charges for hospital services: $";
		cin >> services;
		validate(&services);

		charge(numDays, rate, medCharge, services);
	}

	else
	{
		cout << "Enter the amount of charges for hospital services: $";
		cin >> services;
		validate(&services);

		cout << "Enter the amount for the hospital medication charges: $";
		cin >> medCharge;
		validate(&medCharge);

		charge(services, medCharge);
	}

	return 0;
}

void charge(int numDays, float rate, float medCharge, float services)
{
	float total;

	total = (numDays * rate) + medCharge + services;

	cout << "\nTotal charge for hospital visit: $" << total;
}

void charge(float services, float medCharge)
{
	float total;

	total = medCharge + services;

	cout << "\nTotal charge for hospital visit: $" << total;
}

void validate(int *num)
{
	while (*num < 0)
	{
		cout << "Please enter positive values!\nEnter a number: ";
		cin >> *num;
	}
}

void validate(float *num)
{
	while (*num < 0)
	{
		cout << "Please enter positive values!\nEnter value: ";
		cin >> *num;
	}
}
