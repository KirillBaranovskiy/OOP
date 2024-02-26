#include <iostream>
#include <string>
#include "electricity.h"
#include "extra_electricity.h"
#include "IFelectricity.h"

using namespace std;

class abonent
{
public:
	void set_initial_indication(IFelectricity& electricity, int initial_indication)
	{
		electricity.set_initial_indication(initial_indication);
	}
	void set_indication(IFelectricity & electricity, short month, double& indication)
	{
		electricity.set_indications(month - 1, indication);
	}
	void print_summary_info(IFelectricity& electricity)
	{
		electricity.print_summary_info();
	}
	void print_summary_info(IFelectricity& electricity, const short month)
	{
		electricity.print_summary_info(month);
	}
protected:
	short month = 0;
};
int main()
{
	setlocale(0, "");
	electricity arr[2];
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
	first_abonent.print_summary_info(arr[0], month - 1);


	return 0;
}