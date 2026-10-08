#include <iostream>
#include <string>
#include "Ielectricity.h"
#include "electricity.h"
#include "extra_electricity.h"
#include "template_Ielectricity.h"
#include "template_electricity.h"
#include "template_extra_electricity.h"

int main()
{
	//примерный алгоритм работы с классом extra_electricity
	setlocale(0, "");
	extra_electricity w;
	cout << "Введите ваш тариф (стоимость кВ/ч): ";
	double tariff = 0;
	cin >> tariff;
	w.set_tariff(tariff);
	cout << "Введите начальные показания счетчика целым числом: ";
	int initialIndication = 0;
	cin >> initialIndication;
	string month[12]{ "январь", "февраль", "март", "апрель", "май", "июнь", "июль", "август", "сентябрь", "октябрь", "ноябрь", "декабрь" };
	w.set_initial_indication(initialIndication);
	for (size_t i = 0; i < 12; i++)
	{
		cout << "Введите показания за " << month[i] << " целым числом: ";
		int indication = 0;
		cin >> indication;
		w.set_indications(i, indication);
		cout<< "Введите пеню за " << month[i] << ", (если не было введите 0): ";
		double penalty = 0;
		cin >> penalty;
		w.set_penalty(i, penalty);
	}
	w.print_summary_info();
}

