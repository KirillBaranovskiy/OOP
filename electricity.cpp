#include "electricity.h"

electricity::electricity(const double& tariff) // конструктор с параметром - тариф (стоимость кВ/ч)
{
	//cout << "constructor base parameter" << endl;
	if (tariff > 0)
	{
		this->tariff = tariff;
	}
	else
	{
		throw exception("Тариф не может быть меньше или равен нулю.");
	}
}

electricity::~electricity() { /*cout << "destructor base" << endl;*/ } // деструктор на освобождение массивов

double electricity::get_tariff() const // тариф
{
	return tariff;
}

int electricity::get_initial_indication() const
{
	return initial_indication;
}

void electricity::set_estimated_year(const short estimated_year) // установка года для которого проводятся расчеты
{
	if (estimated_year >= 1872)
	{
		this->estimated_year = estimated_year;
	}
	else
	{
		throw exception("Расчетный год не может быть меньше 1872 т.к. до этого еще не существовало счетчика электричества.");
	}
}

void electricity::set_initial_indication(const int& initial_indication) // установка начальных показаний счетчика
{
	if (initial_indication >= 0)
	{
		this->initial_indication = initial_indication;
		is_initial_indication_set = true; // для set_indications()
	}
	else
	{
		throw exception("Начальные показания счетчика не могут быть меньше нуля.");
	}
}

void electricity::set_indications(const short month, const int& indications) // ввод показаний с параметрами : номер месяца и показания, обновляет сводные параметры
{
	if ((month >= 0 && month < YEAR) && (indications >= 0 && indications <= 9999))
	{
		this->indications[month] = indications; // присвоение показаний в и-тый месяц массива
	}
	else
	{
		throw exception("Месяц должен быть от 0 до 11. Показания должны быть равны или больше нуля и не более 9999.");
	}
	short count = 0;
	for (size_t i = 0; i < YEAR; i++)
	{
		if (this->indications[i] >= 0)
		{
			count++;
		}
		if (count == YEAR && is_initial_indication_set)
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

void electricity::set_sum_payments() // итоговая сумма платежей
{
	sum_payments = (indications[YEAR -1] - initial_indication) * tariff;
}

double electricity::get_sum_payments() const
{
	return sum_payments;
}

void electricity::set_avrg_energy()
{
	avrg_energy = (indications[YEAR - 1] - initial_indication) / YEAR;
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
	cout << "Ваш тариф (стоимость кВт/ч): " << get_tariff() << " кВ/ч." << endl;
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

