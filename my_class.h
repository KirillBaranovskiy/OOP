#pragma once
#include <iostream>
#include <string>

using namespace std;

class my_class
{
	double tariff; // тариф (стоимость к¬т/ч)
	const short int year = 12;
	double* data = new double[year]{0}; // показани€ за каждый мес€ц года (массив)
	const string* month = new string[year]{ "€нварь", "февраль", "март", "апрель", "май", "июнь", "июль", "август", "сент€брь", "окт€брь", "но€брь", "декабрь" };
	double* payment = new double[year]{0}; // начисленные платежи за каждый мес€ц года (массив)
	double sum_payment = 0; // сумма платежей за 12 мес€цев
	double sum_energy = 0; // временна€ переменна€
	double avrg_energy = 0; // среднее потребление энергии в мес€ц
public: // объ€вление методов:
	my_class(const double& tariff); // конструктор c параметром - тариф (стоимость к¬т/ч)
	~my_class(); // деструктор
	double get_tariff() const; // тариф
	double* set_data() const; // заполнение показани€ми за каждый мес€ц года (массив)
	void set_payment(); // начисленные платежи за каждый мес€ц года (массив)
	double get_sum_payment(); // сумма платежей за 12 мес€цев
	double get_avrg_energy(); // среднее потребление энергии в мес€ц
	void update_data(const short int& month, const double& data); // ввод показаний с параметрами: номер мес€ца и показани€, обновл€ет сводные параметры
	void summary_info() const; // вывод на консоль сводной информации
	void run_all_meth(); // все методы в одном
};