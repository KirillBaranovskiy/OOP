#pragma once
#include "template_Ielectricity.h"
template<class T>
class template_electricity : public template_Ielectricity<T>
{
public:
	template_electricity();
	template_electricity(const double& tariff);
	virtual ~template_electricity();
	static const short YEAR = 12;
	virtual void set_tariff(const double& tariff);
	virtual void set_estimated_year(const short estimated_year);
	virtual void set_initial_indication(const T initial_indication) override;
	virtual void set_indications(const short month, const T indications) override;
	virtual double get_tariff() const;
	virtual T get_initial_indication() const;
	virtual double get_sum_payments() const;
	virtual double get_avrg_energy() const;
	virtual bool is_calc_done() const;
	virtual void print_summary_info() const override;
	virtual void print_summary_info(const short month) const override;
	virtual double operator [] (const short month) const override;
	virtual short get_initial_month() const;
protected:
	double tariff = 0;
	short estimated_year = 0;
	T initial_indication = 0;
	T indications[YEAR]{ -1, -1, -1 , -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	double calc_indications[YEAR]{ 0 };
	string month[YEAR]{ "€нварь", "февраль", "март" , "апрель", "май", "июнь", "июль", "август", "сент€брь", "окт€брь", "но€брь", "декабрь" };
	double payments[YEAR]{ 0 };
	double sum_payments = 0;
	double avrg_energy = 0;
	void set_sum_payments();
	void set_avrg_energy();
	bool is_initial_indication_set = false;
	bool is_sum_avrg_set = false;
	bool is_tariff_set = false;
	inline friend ostream& operator << (ostream& os, const template_electricity& obj)
	{
		if (obj.is_sum_avrg_set)
		{
			os << "¬сего за 12 мес€цев начислено " << obj.sum_payments << " руб." << endl;
			os << "—реднее потребление энергии в мес€ц составл€ет " << obj.avrg_energy << " к¬/ч.";
			return os;
		}
		else
		{
			os << "Ќевозможно получить сводные данные т.к. недостаточно данных." << endl;
			return os;
		}
	}
	inline friend double& operator += (double& sum, const template_electricity& obj)
	{
		if (obj.is_sum_avrg_set)
		{
			sum += obj.avrg_energy;
			return sum;
		}
		else return sum = 0;
	}
	const short initial_month = 0;
};


