#pragma once
#include <iostream>
#include <string>
using namespace std;
class Ielectricity
{
public:
	Ielectricity() {}
	virtual ~Ielectricity() {};
	virtual void set_initial_indication(const int initial_indications) = 0;
	virtual void set_indications(const short month, const int indications) = 0;
	virtual void print_summary_info() const = 0;
	virtual void print_summary_info(const short month) const = 0;
	virtual double operator [] (const short month) const = 0;
};