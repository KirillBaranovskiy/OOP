#pragma once
#include <iostream>
#include <string>

using namespace std;

class penalty;

class electricity
{
protected:
	double tariff; // тариф (стоимость к¬т/ч)
	short estimated_year = 0; // год учета
	int initial_indication = 0; // начальные показани€ счетчика
	static const short YEAR = 3;  // 12
	int indications[YEAR]{-1, -1, -1}; // показани€ за каждый мес€ц года (массив) , -1, -1, -1, -1, -1, -1, -1, -1, -1
	int calc_indications[YEAR]{ 0 }; // посчитанные показани€ со счетчика (массив)
	string month[YEAR]{ "€нварь", "февраль", "март"}; //, "апрель", "май", "июнь", "июль", "август", "сент€брь", "окт€брь", "но€брь", "декабрь" 
	double payments[YEAR]{ 0 }; // начисленные платежи за каждый мес€ц года (массив)
	double sum_payments = 0; // сумма платежей за 12 мес€цев
	double avrg_energy = 0; // среднее потребление энергии в мес€ц
	void set_sum_payments(); // итогова€ сумма платежей
	void set_avrg_energy(); // среднее потребление энергии за 12 мес€цев
	bool is_initial_indication_set = false; // дл€ set_sum_payments() set_avrg_energy()
	bool is_sum_avrg_set = false;
public: // объ€вление методов:
	electricity();
	~electricity(); // деструктор
	electricity(const double& tariff); // конструктор c параметром - тариф (стоимость к¬т/ч)
	void set_estimated_year(const short estimated_year); // установка года дл€ которого провод€тс€ расчеты
	void set_initial_indication(const int& initial_indications); // установка начальных показаний счетчика
	void set_indications(const short month, const int& indications); // ввод показаний с параметрами : номер мес€ца и показани€, обновл€ет сводные параметры
	double get_tariff() const; // тариф
	int get_initial_indication() const;
	double get_sum_payments() const;
	double get_avrg_energy() const;
	virtual bool is_calc_done() const;
	virtual void print_summary_info() const; // вывод на консоль итоговой информации
	void print_summary_info(const short month) const; // перегрузка метода вывода с вводом номера мес€ца и отображени€ информации по нему
	double operator [] (const short month) const; // перегрузка оператора [] дл€ получени€ размера платежа за текущий мес€ц
	friend ostream& operator << (ostream& os, const electricity& obj); // перегрузка оператора << дл€ вывода только сводной информации(без информации по мес€цам)
	friend double& operator += (double& sum, const electricity& obj);
	friend class penalty;
};

class penalty : electricity
{
	electricity obj;
	double penalties[YEAR]{ 0 };
	double sum_penalty = 0;
	bool is_sum_calc_done = false;

public:
	penalty(electricity& obj);
	void set_penalty(const short month, const double& penalty);
	void calc_sum_penalty();
	double get_sum_penalty() const;
	bool is_calc_done() const override;
	void print_summary_info() const override;
};
