#include "electricity.h"

electricity::electricity() // add constructor default for arr[]
{
}

electricity::electricity(const double& tariff) 
{
	if (tariff > 0)
	{
		this->tariff = tariff;
		is_tariff_set = true; // add is_tariff_set
	}
	else
	{
		throw exception("must be tariff > 0");
	}
}

electricity::~electricity() { }

void electricity::set_tariff(const double& tariff) 
{
	if (tariff > 0)
	{
		this->tariff = tariff;
		is_tariff_set = true; // add is_tariff_set
		short count = 0; // add check
		for (size_t i = 0; i < YEAR; i++)
		{
			if (this->indications[i] >= 0)
			{
				count++;
			}
			if (count == YEAR && is_initial_indication_set && is_tariff_set) // add && is_tariff_set
			{
				electricity::set_sum_payments();
				electricity::set_avrg_energy();
				int temp_initial_indications = initial_indication;
				for (size_t i = 0; i < YEAR; i++)
				{
					calc_indications[i] = this->indications[i] - temp_initial_indications;
					temp_initial_indications = this->indications[i];
				}
				for (size_t i = 0; i < YEAR; i++)
				{
					payments[i] = calc_indications[i] * tariff;
				}
				is_sum_avrg_set = true;
			}
		}

	}
	else
	{
		throw exception("must be tariff > 0");
	}
}

void electricity::set_estimated_year(const short estimated_year)
{
	if (estimated_year >= 1872)
	{
		this->estimated_year = estimated_year;
	}
	else
	{
		throw exception("must be estimated_year >= 1872");
	}
}

void electricity::set_initial_indication(const int initial_indication)
{
	if (initial_indication >= 0)
	{
		this->initial_indication = initial_indication;
		is_initial_indication_set = true;
		short count = 0;
		for (size_t i = 0; i < YEAR; i++)
		{
			if (this->indications[i] >= 0)
			{
				count++;
			}
			if (count == YEAR && is_initial_indication_set && tariff) // add && tariff
			{
				electricity::set_sum_payments();
				electricity::set_avrg_energy();
				int temp_initial_indications = initial_indication;
				for (size_t i = 0; i < YEAR; i++)
				{
					calc_indications[i] = this->indications[i] - temp_initial_indications;
					temp_initial_indications = this->indications[i];
				}
				for (size_t i = 0; i < YEAR; i++)
				{
					payments[i] = calc_indications[i] * tariff;
				}
				is_sum_avrg_set = true;
			}
		}
	}
	else
	{
		throw exception("must be initial_indication >= 0");
	}
}

void electricity::set_indications(const short month, const int indications)
{
	if ((month >= 0 && month < YEAR) && (indications >= 0 && indications <= 9999))
	{
		this->indications[month] = indications;
	}
	else
	{
		throw exception("must be (month >= 0 && month < YEAR) && (indications >= 0 && indications <= 9999)");
	}
	short count = 0;
	for (size_t i = 0; i < YEAR; i++)
	{
		if (this->indications[i] >= 0)
		{
			count++;
		}
		if (count == YEAR && is_initial_indication_set && tariff) // add && tariff
		{
			electricity::set_sum_payments();
			electricity::set_avrg_energy();
			int temp_initial_indications = initial_indication;
			for (size_t i = 0; i < YEAR; i++)
			{
				calc_indications[i] = this->indications[i] - temp_initial_indications;
				temp_initial_indications = this->indications[i];
			}
			for (size_t i = 0; i < YEAR; i++)
			{
				payments[i] = calc_indications[i] * tariff;
			}
			is_sum_avrg_set = true;
		}
	}
}

void electricity::set_sum_payments()
{
	sum_payments = (indications[YEAR - 1] - initial_indication) * tariff;
}

void electricity::set_avrg_energy()
{
	avrg_energy = (indications[YEAR - 1] - initial_indication) / YEAR;
}

double electricity::get_tariff() const
{
	return tariff;
}

int electricity::get_initial_indication() const
{
	return initial_indication;
}

double electricity::get_sum_payments() const
{
	return sum_payments;
}

double electricity::get_avrg_energy() const
{
	return avrg_energy;
}

bool electricity::is_calc_done() const
{
	if (is_sum_avrg_set) return true; 
	else return false;
}

void electricity::print_summary_info() const
{
	cout << endl;
	cout << "Ваш тариф (стоимость кВт/ч): " << tariff << " кВ/ч." << endl;
	if (estimated_year > 0) { cout << "Расчетный год: " << estimated_year << endl; }
	else { cout << "Расчетный год: данные не введены." << endl; }
	if (is_initial_indication_set) { cout << "Начальное показание счетчика: " << get_initial_indication() << " кВ/ч." << endl; }
	else { cout << "Начальное показание счетчика: данные не введены." << endl; }
	cout << endl;
	if (!is_sum_avrg_set)
	{
		for (size_t i = 0; i < YEAR; i++)
		{
			if (indications[i] != -1)
			{
				cout << "Показание счетчика за " << month[i] << ": " << indications[i] << " кВ/ч." << endl;
			}
			if (indications[i] == -1)
			{
				cout << "Показание счетчика за " << month[i] << ": " << "данные не введены." << endl;
			}
		}
		cout << "Сумма платежей и среднее потребление электричества: недостаточно данных." << endl;
 		cout << "=======================================================" << endl;
	}
	if (is_sum_avrg_set)
	{
		for (size_t i = 0; i < YEAR; i++)
		{
			cout << "Показание счетчика за " << month[i] << ": " << indications[i] << " кВ/ч." << endl;
			cout << "За " << month[i] << " израсходовано " << calc_indications[i] << " кВ/ч." << endl;
			cout << "За " << month[i] << " начислено " << payments[i] << " руб." << endl;
			cout << endl;
		}
		cout << endl;
		cout << "Всего за год начислено " << sum_payments  << " руб." << endl;
		cout << "Среднее потребление энергии в месяц составляет " << avrg_energy << " кВ/ч." << endl;
		cout << "=======================================================" << endl;
	}
}

void electricity::print_summary_info(const short month) const
{
	if (month >= 0 && month < YEAR)
	{
		if (!is_sum_avrg_set)
		{
			if (indications[month] != -1)
			{
				cout << "Показание счетчика за " << this->month[month] << ": " << indications[month] << " кВ/ч." << endl;
			}
			if (indications[month] == -1)
			{
				cout << "Показание счетчика за " << this->month[month] << ": " << "данные не введены." << endl;
			}
		}
		if (is_sum_avrg_set)
		{
			cout << "Показание счетчика за " << this->month[month] << ": " << indications[month] << " кВ/ч." << endl;
			cout << "За " << this->month[month] << " израсходовано " << calc_indications[month] << " кВ/ч." << endl;
			cout << "За " << this->month[month] << " начислено " << payments[month] << " руб." << endl;
		}
	}
	else { throw exception("Номер месяца должен состоять из цифр от 0 до 11."); }
}

double electricity::operator[](const short month) const
{
	if (month >= 0 && month < YEAR)
	{
		if (is_sum_avrg_set)
		{
			return payments[month];
		}
		else return 0;
	}
	else { throw exception("Номер месяца должен состоять из цифр от 0 до 11."); }
}

ostream& operator<<(ostream& os, const electricity& obj)
{
	if (obj.is_sum_avrg_set)
	{
		os << "Всего за 12 месяцев начислено " << obj.sum_payments << " руб." << endl;
		os << "Среднее потребление энергии в месяц составляет " << obj.avrg_energy << " кВ/ч.";
		return os;
	}
	else
	{
		os << "Невозможно получить сводные данные т.к. недостаточно данных." << endl;
		return os;
	}
}

double& operator+=(double& sum, const electricity& obj)
{
	if (obj.is_sum_avrg_set)
	{
		sum += obj.avrg_energy;
		return sum;
	}
	else return sum = 0; 
}

