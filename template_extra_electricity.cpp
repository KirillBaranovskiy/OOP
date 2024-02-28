#include "template_extra_electricity.h"
#include "template_electricity.h"

template class template_extra_electricity<int>; // without this, error LNK2019 LNK1120
template class template_extra_electricity<double>; // without this, error LNK2019 LNK1120

template<class T>
template_extra_electricity<T>::template_extra_electricity()
{
	cout << "__constructor default template_extra_electricity__" << endl;
}

template<class T>
template_extra_electricity<T>::template_extra_electricity(const double& tariff)
{
	cout << "__constructor with parameter template_extra_electricity__" << endl;
}

template<class T>
template_extra_electricity<T>::~template_extra_electricity()
{
	cout << "__destructor emplate_extra_electricity__" << endl;
}

template<class T>
void template_extra_electricity<T>::set_penalty(const short month, const double& penalty)
{
	if ((month >= 0 && month < template_electricity<T>::YEAR) && (penalty > 0 && penalty <= 9999))
	{
		penalties[month] = penalty;
		sum_penalty = 0;
		for (size_t i = 0; i < template_electricity<T>::YEAR; i++)
		{
			sum_penalty += penalties[i];
		}
	}
	else throw exception("must be (month >= 0 && month < 12) && (penalty > 0 && penalty <= 9999)");
}

template<class T>
double template_extra_electricity<T>::get_sum_penalty() const
{
	return sum_penalty;
}

template<class T>
void template_extra_electricity<T>::print_summary_info() const
{
	cout << endl;
	template_electricity<T>::print_summary_info();
	cout << endl;
	for (size_t i = 0; i < template_electricity<T>::YEAR; i++)
	{
		cout << "Пеня за " << template_electricity<T>::month[i] << " составляет " << penalties[i] << " руб." << endl;
	}
	cout << "Сумма пени за год составляет " << sum_penalty << " руб." << endl;
	if (template_electricity<T>::is_sum_avrg_set)
	{
		cout << "Итоговая сумма включая пени соствляет " << fixed << template_electricity<T>::sum_payments + sum_penalty << " руб." << endl;
	}
	cout << "=======================================================" << endl;
}

template<class T>
void template_extra_electricity<T>::print_summary_info(const short month) const
{
	template_electricity<T>::print_summary_info(month);
	cout << "Пеня за " << template_electricity<T>::month[month] << " составляет " << penalties[month] << " руб." << endl;
}

template<class T>
double template_extra_electricity<T>::operator[](const short month) const
{
	return template_electricity<T>::operator[](month) + penalties[month];
}

template<class T>
double template_extra_electricity<T>::get_total_sum() const
{
	if (template_electricity<T>::is_sum_avrg_set)
	{
		return template_electricity<T>::sum_payments + sum_penalty;
	}
	else { throw exception("Нельзя получить total_sum. Недостаточно данных"); }
}