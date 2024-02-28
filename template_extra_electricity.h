#pragma once
#include "template_electricity.h"

template<class T>
class template_extra_electricity : public template_electricity<T>
{
protected:
	double penalties[template_electricity<T>::YEAR]{ 0 };
	double sum_penalty = 0;
public:
	template_extra_electricity();
	template_extra_electricity(const double& tariff);
	virtual ~template_extra_electricity();
	virtual void set_penalty(const short month, const double& penalty);
	virtual double get_sum_penalty() const;
	virtual void print_summary_info() const override;
	virtual void print_summary_info(const short month) const override;
	virtual double operator [] (const short month) const override;
	inline friend ostream& operator << (ostream& os, const template_extra_electricity& obj)
	{
		if (obj.is_sum_avrg_set)
		{
			os << "Всего за 12 месяцев начислено " << obj.sum_payments << " руб." << endl;
			os << "Среднее потребление энергии в месяц составляет " << obj.avrg_energy << " кВ/ч." << endl;
			os << "Сумма пени за год составляет " << obj.sum_penalty << " руб." << endl;
			os << "Итоговая сумма включая пени соствляет " << obj.sum_payments + obj.sum_penalty << " руб." << endl;
			return os;
		}
		else
		{
			os << "Невозможно получить сводные данные т.к. недостаточно данных." << endl;
			return os;
		}
	}
	virtual double get_total_sum() const;
};