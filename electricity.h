#pragma once
#include <iostream>
#include <string>

using namespace std;

class electricity
{
	double tariff; // тариф (стоимость к¬т/ч)
	short estimated_year = 0; // год учета
	int initial_indication = 0; // начальные показани€ счетчика
	static const short YEAR = 3;  // 12
	int indications[YEAR]{-1, -1, -1}; // показани€ за каждый мес€ц года (массив) , -1, -1, -1, -1, -1, -1, -1, -1, -1
	int calc_indications[YEAR]{0}; // посчитанные показани€ со счетчика (массив)
	string month[YEAR]{ "€нварь", "февраль", "март"}; //, "апрель", "май", "июнь", "июль", "август", "сент€брь", "окт€брь", "но€брь", "декабрь" 
	double payment[YEAR]{0}; // начисленные платежи за каждый мес€ц года (массив)
	double sum_payments = 0; // сумма платежей за 12 мес€цев
	double avrg_energy = 0; // среднее потребление энергии в мес€ц
	double get_tariff() const; // тариф
	int get_initial_indication() const;
	void set_sum_payments(); // итогова€ сумма платежей
	void set_avrg_energy(); // среднее потребление энергии за 12 мес€цев
	bool is_initial_indication_set = false; // дл€ set_sum_payments() set_avrg_energy()
	bool is_sum_avrg_set = false; // dlya optimizasii (4tobi ne delat' kajdiy raz cikl proverki)
public: // объ€вление методов:
	electricity(const double& tariff); // конструктор c параметром - тариф (стоимость к¬т/ч)
	~electricity(); // деструктор
	void set_estimated_year(const short& estimated_year); // установка года дл€ которого провод€тс€ расчеты
	void set_initial_indication(const int& initial_indications); // установка начальных показаний счетчика
	void set_indications(const short& month, const int& indications); // ввод показаний с параметрами : номер мес€ца и показани€, обновл€ет сводные параметры
	double get_sum_payments() const;
	double get_avrg_energy() const;
	bool year_calculation_done() const;
	void print_summary_info() const; // вывод на консоль итоговой информации
	void print_summary_info(const short month) const; // перегрузка метода вывода с вводом номера мес€ца и отображени€ информации по нему
	double operator [] (const short month) const; // перегрузка оператора [] дл€ получени€ размера платежа за текущий мес€ц
	friend ostream& operator << (ostream& os, const electricity& obj); // перегрузка оператора << дл€ вывода только сводной информации(без информации по мес€цам)
	friend double& operator += (double& sum, const electricity& obj); // перегрузка оператора += вне класса дл€ получени€ суммированного значени€ средних показаний за все года
};