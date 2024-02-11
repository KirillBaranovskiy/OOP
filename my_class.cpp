#include "my_class.h"

my_class::my_class(const double& tariff) // конструктор с параметром - тариф (стоимость к¬/ч)
{
	if (tariff <= 0)
	{
		throw exception("“ариф не может быть меньше или равен нулю.");
	}
	else
	{
		this->tariff = tariff;
	}
}

my_class::~my_class() // деструктор на освобождение массивов
{
	delete[] data;
	data = nullptr;
	delete[] payment;
	payment = nullptr;
	delete[] month;
	month = nullptr;
}

double my_class::get_tariff() const // тариф
{
	return this->tariff;
}

double* my_class::set_data() const // заполнение показани€ми за каждый мес€ц года (массив)
{
	for (size_t i = 0; i < year; i++)
	{
		cout << "¬ведите показани€ за " << month[i] << ": ";
		cin >> data[i];
		if (data[i] <= 0 || data[i] > 9999)
		{
			throw exception("ѕоказани€ должны быть больше нул€ и не более 9999.");
		}
	}
	return data;
}

void my_class::set_payment()// начисленные платежи за каждый мес€ц года (массив)
{
	for (size_t i = 0; i < year; i++)
	{
		payment[i] += data[i] * this->tariff; // начисленные платежи за каждый мес€ц года (массив)
	}
}

double my_class::get_sum_payment() // сумма платежей за 12 мес€цев
{
	for (size_t i = 0; i < year; i++)
	{
		sum_payment += payment[i];
	}
	return sum_payment;
}

double my_class::get_avrg_energy() // стреднее потребление энергии в мес€ц
{
	short int count = 0;
	for (size_t i = 0; i < year; i++)
	{
		if (data[i]>0)
		{
			count++;
		}
	}
	if (count==year)
	{
		for (size_t i = 0; i < year; i++)
		{
			sum_energy += data[i];
		}
		avrg_energy = sum_energy / year;
		return avrg_energy;
	}
	else
	{
		throw exception("Ќельз€ получить среднее потребление энергии, т.к. не за каждый мес€ц внесены данные.");
	}
}

void my_class::update_data(const short int& month, const double& data) // ћетод ввода показаний с параметрами: номер мес€ца и показани€, обновл€ет сводные параметры
{
	if ((month >= 1 && month <= 12) && (data > 0 && data <= 9999))
	{
		for (size_t i = 0; i < year; i++) // обнуление массива платежей
		{
			payment[i] = 0;
		}
		this->data[month - 1] = data; // присвоение показаний в и-тый мес€ц
		my_class::set_payment();
		sum_payment = sum_energy = 0; // обнуление переменных накоплени€ суммы
		my_class::get_sum_payment();
		my_class::get_avrg_energy();
	}
	else
	{
		throw exception("ћес€ц длжен состо€ть из цифр от 1 до 12. ѕоказани€ должны быть больше нул€ и не более 9999.");
	}
}

void my_class::summary_info() const// вывод на консоль сводной информации
{
	cout << endl;
	cout << "“ариф (стоимость к¬т/ч) составл€ет: " << this->tariff << " руб." << endl << endl;
	for (size_t i = 0; i < year; i++)
	{
		cout << "«а " << month[i] << " израсходовано " << data[i] << " к¬/ч." << endl;
		cout << "«а " << month[i] << " начислено " << payment[i] << " руб." << endl;
		cout << endl;
	}
	cout << endl;
	cout << "¬сего за 12 мес€цев начислено " << sum_payment << " руб." << endl;
	cout << "—реднее потребление энергии в мес€ц составл€ет " << avrg_energy << " к¬/ч." << endl;
}
void my_class::run_all_meth()
{
	my_class::set_data();
	my_class::set_payment();
	my_class::get_sum_payment();
	my_class::get_avrg_energy();
	my_class::update_data(1, 100);
	my_class::summary_info();
}