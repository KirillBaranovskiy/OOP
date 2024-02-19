#include <iostream>
#include <string>
#include "electricity.h"

using namespace std;

int main()
{
	setlocale(0, "");
	//cout << "Ёто класс дл€ информации о годовых показани€х и платежах за электроэнергию." << endl;
	//cout << "¬ведите тариф (стоимость к¬т/ч): ";
	//double tariff;
	//cin >> tariff;
	//electricity q(tariff);
	//cout << "¬ведите расчетный год: ";
	//short estimated_year;
	//cin >> estimated_year;
	//q.set_estimated_year(estimated_year);
	//cout << "¬ведите начальное показание счетчика целым числом: ";
	//int initial_indications;
	//cin >> initial_indications;
	//q.set_initial_indication(initial_indications);
	electricity q(3);
	q.set_initial_indication(0);
	for (size_t i = 0; i < 3; i++)
	{
		cout << "введите номер мес€ца за который нужно ввести показание: ";
		short month;
		cin >> month;
		cout << "введите показание счетчика за этот мес€ц целым числом: ";
		int indications;
		cin >> indications;
		q.set_indications(month - 1, indications);
	}
	//cout << "=======================================1" << endl;
	//cout << "year_calculation_done = " << q.is_calc_done() << endl;
	//cout << "=======================================2" << endl;
	//q.print_summary_info();
	//cout << "=======================================3" << endl;
	//q.print_summary_info(1); // перегрузка 1
	//cout << "=======================================4" << endl;
	//cout << "q[i] =  " << q[1] << endl; // перегрузка 2
	//cout << "=======================================5" << endl;
	//cout << "q = " << q << endl; // перегрузка 3
	//cout << "=======================================6" << endl;
	//double e = 0;
	//e += q; // перегрузка 4
	//cout << "e = " << e << endl;
	//q.print_summary_info();
	penalty w(q);
	w.set_penalty(0, 100);
	w.calc_sum_penalty();
	w.print_summary_info();

	return 0;
}
	