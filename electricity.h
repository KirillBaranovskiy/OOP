#pragma once
#include <iostream>
#include <string>
#include "Ielectricity.h"
using namespace std;
class electricity : public Ielectricity
{
public:
	electricity();
	electricity(const double& tariff);
	virtual ~electricity();
	virtual void set_tariff(const double& tariff);
	virtual void set_estimated_year(const short estimated_year);
	virtual void set_initial_indication(const int initial_indication) override;
	virtual void set_indications(const short month, const int indications) override;
	
	virtual void print_summary_info() const override;
	virtual void print_summary_info(const short month) const override;
	virtual double operator [] (const short month) const override;
	friend ostream& operator << (ostream& os, const electricity& obj);
	friend double& operator += (double& sum, const electricity& obj);
protected:
	virtual double get_tariff() const;
	virtual int get_initial_indication() const;
	virtual double get_sum_payments() const;
	virtual double get_avrg_energy() const;
	virtual bool is_calc_done() const;
	static const int YEAR = 12;
	double tariff = 0;
	int estimated_year = 0;
	int initial_indication = 0;
	int indications[YEAR]{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
	int calc_indications[YEAR]{ 0 };
	string month[YEAR]{ "€нварь", "февраль", "март", "апрель", "май", "июнь", "июль",
"август", "сент€брь", "окт€брь", "но€брь", "декабрь" };
	double payments[YEAR]{ 0 };
	double sum_payments = 0;
	double avrg_energy = 0;
	void set_sum_payments();
	void set_avrg_energy();
	bool is_initial_indication_set = false;
	bool is_sum_avrg_set = false;
	bool is_tariff_set = false;
};