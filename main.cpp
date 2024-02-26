#include <iostream>
#include <string>
#include "electricity.h"
#include "extra_electricity.h"
#include "Ielectricity.h"

using namespace std;

class abonent
{
public:
	void set_initial_indication(Ielectricity& electricity, int initial_indication)
	{
		electricity.set_initial_indication(initial_indication);
	}
	void set_indication(Ielectricity & electricity, short month, const int indication)
	{
		electricity.set_indications(month - 1, indication);
	}
	void print_summary_info(Ielectricity& electricity)
	{
		electricity.print_summary_info();
	}
	void print_summary_info(Ielectricity& electricity, const short month)
	{
		electricity.print_summary_info(month);
	}
};
int main()
{
	setlocale(0, "");
	/*electricity arr[2];
	abonent first_abonent;
	for (size_t i = 0; i < electricity::YEAR; i++)
	{
		cout << "Enter month for indication: ";
		short month;
		cin >> month;
		cout << "Enter indication for this month: ";
		double indication;
		cin >> indication;
		first_abonent.set_indication(arr[0], month, indication);
	}
	cout << "Enter initial indication: ";
	int initial_indication;
	cin >> initial_indication;
	first_abonent.set_initial_indication(arr[0], initial_indication);
	cout << "Enter tariff: ";
	double tariff;
	cin >> tariff;
	arr[0].set_tariff(tariff);
	first_abonent.print_summary_info(arr[0]);
	cout << "Enter month number for information: ";
	short month;
	cin >> month;
	first_abonent.print_summary_info(arr[0], month - 1);*/
	Ielectricity* ptr_Ielectricity[2];
	electricity _electricity;
	extra_electricity* ptr_extra_electricity = new extra_electricity;
	ptr_Ielectricity[0] = &_electricity;
	ptr_Ielectricity[1] = ptr_extra_electricity;
	ptr_Ielectricity[0]->print_summary_info(); // ok
	ptr_Ielectricity[1]->print_summary_info(); // ok
	delete ptr_extra_electricity;
	//delete[] ptr_Ielectricity; // Kak pravilno delete?? error
	return 0;
}