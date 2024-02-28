#pragma once
#include <iostream>
#include <string>

using namespace std;

template<class T>
class template_Ielectricity
{
public:
	template_Ielectricity()
	{
		cout << "__constructor template_I__" << endl;
	}
	virtual ~template_Ielectricity() { cout << "__destructor template_I__" << endl; };
	virtual void set_initial_indication(const T initial_indication) = 0;
	virtual void set_indications(const short month, const T indications) = 0;
	virtual void print_summary_info() const = 0;
	virtual void print_summary_info(const short month) const = 0;
	virtual double operator [] (const short month) const = 0;
};