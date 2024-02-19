#pragma once
#include <iostream>
#include <string>

using namespace std;

class extra_electricity : public electricity
{
protected:
	double penalties[YEAR]{ 0 };
	double sum_penalty = 0;
	bool is_sum_calc_done = false;
public:
	extra_electricity(const double& tariff);
	~extra_electricity();
	void set_penalty(const short month, const double& penalty);
	double get_sum_penalty() const;
	void print_summary_info() const override;
	void print_summary_info(const short month) const override;
	double operator [] (const short month) const override;
	friend ostream& operator << (ostream& os, const extra_electricity& obj);
};