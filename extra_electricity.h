#pragma once
#include <iostream>
#include <string>
#include "electricity.h"
using namespace std;
class extra_electricity : public electricity
{
protected:
	double penalties[YEAR]{ 0 };
	double sum_penalty = 0;
public:
	extra_electricity() {};
	extra_electricity(const double& tariff);
	virtual ~extra_electricity() override;
	virtual void set_penalty(const short month, const double& penalty);
	virtual double get_sum_penalty() const;
	virtual void print_summary_info() const override;
	virtual void print_summary_info(const short month) const override;
	virtual double operator [] (const short month) const override;
	friend ostream& operator << (ostream& os, const extra_electricity& obj);
	virtual double get_total_sum() const;
};
