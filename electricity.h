#pragma once
#include <iostream>
#include <string>

using namespace std;

class electricity
{
public: // объ€вление методов:
	electricity(const double& tariff); // конструктор c параметром - тариф (стоимость к¬т/ч)
	~electricity(); // деструктор
	static const short YEAR = 12; // 12
	virtual void set_estimated_year(const short estimated_year); // установка года дл€ которого провод€тс€ расчеты
	virtual void set_initial_indication(const int initial_indications); // установка начальных показаний счетчика
	virtual void set_indications(const short month, const int indications); // ввод показаний с параметрами : номер мес€ца и показани€, обновл€ет сводные параметры
	virtual double get_tariff() const; // тариф
	virtual int get_initial_indication() const;
	virtual double get_sum_payments() const;
	virtual double get_avrg_energy() const;
	virtual bool is_calc_done() const;
	virtual void print_summary_info() const; // вывод на консоль итоговой информации
	virtual void print_summary_info(const short month) const; // перегрузка метода вывода с вводом номера мес€ца и отображени€ информации по нему
	virtual double operator [] (const short month) const; // перегрузка оператора [] дл€ получени€ размера платежа за текущий мес€ц
	friend ostream& operator << (ostream& os, const electricity& obj); // перегрузка оператора << дл€ вывода только сводной информации(без информации по мес€цам)
	friend double& operator += (double& sum, const electricity& obj);
protected:
	double tariff; // тариф (стоимость к¬т/ч)
	short estimated_year = 0; // год учета
	int initial_indication = 0; // начальные показани€ счетчика
	int indications[YEAR]{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 }; // , -1, -1, -1, -1, -1, -1, -1, -1, -1
	int calc_indications[YEAR]{ 0 }; // посчитанные показани€ со счетчика (массив)
	string month[YEAR]{ "€нварь", "февраль", "март", "апрель", "май", "июнь", "июль", "август", "сент€брь", "окт€брь", "но€брь", "декабрь" }; //, "апрель", "май", "июнь", "июль", "август", "сент€брь", "окт€брь", "но€брь", "декабрь" 
	double payments[YEAR]{ 0 }; // начисленные платежи за каждый мес€ц года (массив)
	double sum_payments = 0; // сумма платежей за 12 мес€цев
	double avrg_energy = 0; // среднее потребление энергии в мес€ц
	void set_sum_payments(); // итогова€ сумма платежей
	void set_avrg_energy(); // среднее потребление энергии за 12 мес€цев
	bool is_initial_indication_set = false; // дл€ set_sum_payments() set_avrg_energy()
	bool is_sum_avrg_set = false;
};