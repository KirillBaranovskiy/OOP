#include "template_electricity.h"
#include <iomanip>

template class template_electricity<int>; // without this, error LNK2019 LNK1120
template class template_electricity<double>; // without this, error LNK2019 LNK1120

template<class T>
template_electricity<T>::template_electricity()
{
	cout << "__constructor default template_electricity__" << endl;
}

template<class T>
template_electricity<T>::template_electricity(const double& tariff)
{
	cout << "__constructor with parameter template_electricity__" << endl;
	if (tariff > 0)
	{
		this->tariff = tariff;
		is_tariff_set = true;
	}
	else
	{
		throw exception("must be tariff > 0");
	}
}

template<class T>
template_electricity<T>::~template_electricity()
{
	cout << "__destructor template_electricity__" << endl;
}

template<class T>
void template_electricity<T>::set_tariff(const double& tariff)
{
	if (tariff > 0)
	{
		this->tariff = tariff;
		is_tariff_set = true;
		short count = 0;
		for (size_t i = 0; i < YEAR; i++)
		{
			if (this->indications[i] >= 0)
			{
				count++;
			}
			if (count == YEAR && is_initial_indication_set && is_tariff_set) // add && is_tariff_set
			{
				get_sum_payments();
				set_avrg_energy();
				double temp_initial_indications = initial_indication;
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

template<class T>
void template_electricity<T>::set_estimated_year(const short estimated_year)
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

template<class T>
void template_electricity<T>::set_initial_indication(const T initial_indication)
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
			if (count == YEAR && is_initial_indication_set && is_tariff_set) // add && is_tariff_set
			{
				template_electricity::set_sum_payments();
				template_electricity::set_avrg_energy();
				double temp_initial_indications = initial_indication;
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

template<class T>
void template_electricity<T>::set_indications(const short month, const T indications)
{
	if ((month >= 0 && month < YEAR) && (indications >= 0 && indications <= 9999))
	{
		this->indications[month] = indications;
		short count = 0;
		for (size_t i = 0; i < YEAR; i++)
		{
			if (this->indications[i] >= 0)
			{
				count++;
			}
			if (count == YEAR && is_initial_indication_set && is_tariff_set) // add && is_tariff_set
			{
				template_electricity::set_sum_payments();
				template_electricity::set_avrg_energy();
				double temp_initial_indications = initial_indication;
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
		throw exception("must be (month >= 0 && month < 12) && (indications >= 0 && indications <= 9999)");
	}
}

template<class T>
double template_electricity<T>::get_tariff() const
{
	return tariff;
}

template<class T>
T template_electricity<T>::get_initial_indication() const
{
	return T(initial_indication);
}

template<class T>
double template_electricity<T>::get_sum_payments() const
{
	return sum_payments;
}

template<class T>
double template_electricity<T>::get_avrg_energy() const
{
	return avrg_energy;
}

template<class T>
bool template_electricity<T>::is_calc_done() const
{
	if (is_sum_avrg_set) return true;
	else return false;
}

template<class T>
void template_electricity<T>::print_summary_info() const
{
	cout << endl;
	cout << "Ваш тариф (стоимость кВт/ч): " << tariff << " кВ/ч." << endl;
	if (estimated_year > 0) { cout << "Расчетный год: " << estimated_year << endl; }
	else { cout << "Расчетный год: данные не введены." << endl; }
	if (is_initial_indication_set) { cout << "Начальное показание счетчика: " << initial_indication << " кВ/ч." << endl; }
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
		cout << "Всего за год начислено " << sum_payments << " руб." << endl;
		cout << "Среднее потребление энергии в месяц составляет " << fixed << setprecision(2) << avrg_energy << " кВ/ч." << endl;
		cout << "=======================================================" << endl;
	}
}

template<class T>
void template_electricity<T>::print_summary_info(const short month) const
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
	else { throw exception("Must be month >= 0 && month < 12"); }
}

template<class T>
double template_electricity<T>::operator[](const short month) const
{
	if (month >= 0 && month < YEAR)
	{
		if (is_sum_avrg_set)
		{
			return payments[month];
		}
		else return 0;
	}
	else { throw exception("Must be (month >= 0 && month < 12"); }
}

template<class T>
short template_electricity<T>::get_initial_month() const
{
	return initial_month;
}

template<class T>
void template_electricity<T>::set_sum_payments()
{
	sum_payments = (indications[YEAR - 1] - initial_indication) * tariff;
}

template<class T>
void template_electricity<T>::set_avrg_energy()
{
	avrg_energy = (indications[YEAR - 1] - initial_indication) / YEAR;
}
