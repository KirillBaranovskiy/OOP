#include "electricity.h"
#include "extra_electricity.h"
extra_electricity::extra_electricity(const double& tariff) : electricity::electricity(tariff)
{
}
extra_electricity::~extra_electricity()
{
}
void extra_electricity::set_penalty(const short month, const double& penalty)
{
	if ((month >= 0 && month < YEAR) && (penalty > 0 && penalty <= 99999))
	{
		penalties[month] = penalty;
		sum_penalty = 0;
		for (size_t i = 0; i < YEAR; i++)
		{
			sum_penalty += penalties[i];
		}
	}
	else throw exception("must be (month >= 0 && month < YEAR) && (penalty > 0 && penalty <= 99999)");
}
double extra_electricity::get_sum_penalty() const
{
	return sum_penalty;
}
void extra_electricity::print_summary_info() const
{
	cout << endl;
	electricity::print_summary_info();
	cout << endl;
	for (size_t i = 0; i < YEAR; i++)
	{
		cout << "Пеня за " << month[i] << " составляет " << penalties[i] << " руб." << endl;
	}
	cout << "Сумма пени за год составляет " << sum_penalty << " руб." << endl;
	if (is_sum_avrg_set)
	{
		cout << "Итоговая сумма включая пени соствляет " << sum_payments + sum_penalty << " руб." << endl;
	}
	cout << "=======================================================" << endl;
}
void extra_electricity::print_summary_info(const short month) const
{
	electricity::print_summary_info(month);
	cout << "Пеня за " << this->month[month] << " составляет " << penalties[month] << " руб." << endl;
}
double extra_electricity::operator[](const short month) const
{
	return electricity::operator[](month) + penalties[month];
}
ostream& operator<<(ostream& os, const extra_electricity& obj)
{
	if (obj.is_sum_avrg_set)
	{
		os << "Всего за 12 месяцев начислено " << obj.sum_payments << " руб." << endl;
		os << "Среднее потребление энергии в месяц составляет " << obj.avrg_energy << " кВ/ч." << endl;
		os << "Сумма пени за год составляет " << obj.sum_penalty << " руб." << endl;
		os << "Итоговая сумма включая пени соствляет " << obj.sum_payments + obj.sum_penalty << " руб." << endl;
		return os;
	}
	else
	{
		os << "Невозможно получить сводные данные т.к. недостаточно данных." << endl;
		return os;
	}
}
double extra_electricity::get_total_sum() const
{
	if (is_sum_avrg_set)
	{
		return sum_payments + sum_penalty;
	}
	else { throw exception("Can't get total_sum. Not enough data"); }
}
