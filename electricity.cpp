#include "electricity.h"

electricity::electricity(const double& tariff) // конструктор с параметром - тариф (стоимость кВ/ч)
{
	if (tariff > 0)
	{
		this->tariff = tariff;
	}
	else
	{
		throw exception("Тариф не может быть меньше или равен нулю.");
	}
}

electricity::~electricity() // деструктор на освобождение массивов
{
	// *удаляю статический массив*
}

double electricity::get_tariff() const // тариф
{
	return tariff;
}

int electricity::get_initial_indication() const
{
	return initial_indication;
}

void electricity::set_estimated_year(const short& estimated_year) // установка года для которого проводятся расчеты
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
		boolean = true;
	}
	else
	{
		throw exception("Начальные показания счетчика не могут быть меньше нуля.");
	}
}
// зашил в метод set_indications выполнение функций set_sum_payments, set_avrg_energy, print_summary_info
// при выполнении условий ввода начального показания счетчика и наличия показаний за весь год
// сеттеры и геттеры для sum_payments и avrg_energy разместил в private поле (ексепшены не убирал,
// но вообще теперь они нужны). Теперь сторонний программист не сможет использовать класс неправильно
void electricity::set_indications(const short& month, const int& indications) // ввод показаний с параметрами : номер месяца и показания, обновляет сводные параметры
{
	if ((month >= 0 && month <= 11) && (indications >= 0 && indications <= 9999))
	{
		this->indications[month] = indications; // присвоение показаний в и-тый месяц массива
	}
	else
	{
		throw exception("Месяц должен состоять из цифр от 1 до 12. Показания должны быть равны или больше нуля и не более 9999.");
	}
	short count = 0;
	for (size_t i = 0; i < year; i++)
	{
		if (this->indications[i] >= 0)
		{
			count++;
		}
		if (count == year)
		{
			electricity::set_sum_payments();
			electricity::set_avrg_energy();
			int temp_initial_indications = initial_indication;
			for (size_t i = 0; i < year; i++)
			{
				calc_indications[i] = this->indications[i] - temp_initial_indications;
				temp_initial_indications = this->indications[i];
			}
			electricity::print_summary_info();
		}
	}
}

void electricity::set_sum_payments() // итоговая сумма платежей
{
	sum_payments = (indications[year-1] - initial_indication) * tariff;
}

double electricity::get_sum_payments() const
{
	return sum_payments;
}

void electricity::set_avrg_energy()
{
	avrg_energy = (indications[year - 1] - initial_indication) / year;
}

double electricity::get_avrg_energy() const
{
	return avrg_energy;
}
/*в print_summary_info() логика такая что, если введены не все показания (не за каждый месяц или начальное
показание счетчика), сработает только вывод информации о фактических показаниях счетчика. если введены 
все показания и введено начальное показание счетчика, сработает вывод информации о фактических показаниях,
подсчет расхода, суммы платежа и итоговой информации
*/
void electricity::print_summary_info() const
{
	cout << endl;
	cout << "Ваш тариф (стоимость кВт/ч): " << get_tariff() << " кВ/ч." << endl;
	if (estimated_year > 0)
	{
		cout << "Расчетный год: " << estimated_year << endl;
	}
	else
	{
		cout << "Расчетный год: данные не введены." << endl;
	}
	if (boolean)
	{
		cout << "Начальное показание счетчика: " << get_initial_indication() << " кВ/ч." << endl;
	}
	else
	{
		cout << "Начальное показание счетчика: данные не введены." << endl;
	}
	cout << endl;
	short count = 0;
	for (size_t i = 0; i < year; i++)
	{
		if (indications[i] == -1)
		{
			++count;
		}
	}
	if (count > 0 && count <= year)
	{
		for (size_t i = 0; i < year; i++)
		{
			if (indications[i] != -1)
			{
				cout << "показание счетчика за " << month[i] << ": " << indications[i] << " кВ/ч." << endl;
			}
			if (indications[i] == -1)
			{
				cout << "показание счетчика за " << month[i] << ": " << "данные не введены." << endl;
			}
		}
	}
	if (count == 0 && boolean == true)
	{
		for (size_t i = 0; i < year; i++)
		{
			cout << "показание счетчика за " << month[i] << ": " << indications[i] << " кВ/ч." << endl;
			cout << "За " << month[i] << " израсходовано " << calc_indications[i] << " кВ/ч." << endl;
			cout << "За " << month[i] << " начислено " << calc_indications[i] * tariff << " руб." << endl;
			cout << endl;
		}
		cout << endl;
		cout << "Всего за 12 месяцев начислено " << get_sum_payments() << " руб." << endl;
		cout << "Среднее потребление энергии в месяц составляет " << get_avrg_energy() << " кВ/ч." << endl;
	}
	if (count == 0 && boolean == false)
	{
		for (size_t i = 0; i < year; i++)
		{
			cout << "показание счетчика за " << month[i] << ": " << indications[i] << " кВ/ч." << endl;
		}
	}
}