#include <iostream>
#include <string>
#include "electricity.h"

using namespace std;

int main()
{
	setlocale(0, "");
	cout << "Ёто класс дл€ информации о годовых показани€х и платежах за электроэнергию." << endl;
	cout << "¬ведите тариф (стоимость к¬т/ч): ";
	double tariff;
	cin >> tariff;
	electricity q(tariff);
	cout << "¬ведите расчетный год: ";
	short estimated_year;
	cin >> estimated_year;
	q.set_estimated_year(estimated_year);
	cout << "¬ведите начальное показание счетчика целым числом: ";
	int initial_indications;
	cin >> initial_indications;
	q.set_initial_indication(initial_indications);
	for (size_t i = 0; i < 12; i++)
	{
		cout << "¬ведите номер мес€ца за который нужно ввести показание: ";
		short month;
		cin >> month;
		cout << "¬ведите показание счетчика за этот мес€ц целым числом: ";
		int indications;
		cin >> indications;
		q.set_indications(month - 1, indications);
	}
	//q.print_summary_info();
	return 0;
}
	