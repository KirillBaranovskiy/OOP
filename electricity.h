#pragma once
#include <iostream>
#include <string>

using namespace std;

class electricity
{
	double tariff; // тариф (стоимость к¬т/ч)
	short estimated_year = 0; // год учета
	int initial_indication = 0; // начальные показани€ счетчика
	static const short year = 12;
	int indications[year]{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}; // показани€ за каждый мес€ц года (массив)
	int calc_indications[year]{0}; // посчитанные показани€ со счетчика (массив)
	string month[year]{ "€нварь", "февраль", "март", "апрель", "май", "июнь", "июль", "август", "сент€брь", "окт€брь", "но€брь", "декабрь" };
	double payment[year]{0}; // начисленные платежи за каждый мес€ц года (массив)
	double sum_payments = 0; // сумма платежей за 12 мес€цев
	double avrg_energy = 0; // среднее потребление энергии в мес€ц
	double get_tariff() const; // тариф
	int get_initial_indication() const;
	void set_sum_payments(); // итогова€ сумма платежей
	void set_avrg_energy(); // среднее потребление энергии за 12 мес€цев
	double get_sum_payments() const;
	double get_avrg_energy() const;
	bool boolean = false; // дл€ print_summary_info()
public: // объ€вление методов:
	electricity(const double& tariff); // конструктор c параметром - тариф (стоимость к¬т/ч)
	~electricity(); // деструктор
	void set_estimated_year(const short& estimated_year); // установка года дл€ которого провод€тс€ расчеты
	void set_initial_indication(const int& initial_indications); // установка начальных показаний счетчика
	void set_indications(const short& month, const int& indications); // ввод показаний с параметрами : номер мес€ца и показани€, обновл€ет сводные параметры
	void print_summary_info() const; // вывод на консоль итоговой информации
};