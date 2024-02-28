#include <iostream>
#include <string>
#include "template_Ielectricity.h"
#include "template_electricity.h"
#include "template_extra_electricity.h"

using namespace std;

int main()
{
	setlocale(0, "");
	template_extra_electricity<double> q;
	q.set_tariff(3);
	for (size_t i = 0; i <template_electricity<double>::YEAR; i++)
	{
		cout << "Enter month for indication: ";
		short month;
		cin >> month;
		cout << "Enter indication for this month: ";
		double indication;
		cin >> indication;
		q.set_indications(month - 1, indication);
	}
	q.set_initial_indication(0.5);
	q.set_estimated_year(2023);
	q.set_penalty(1, 20); 
	q.print_summary_info();
	q.print_summary_info(1);
	/*cout << "____operator [1] " << q[1] << endl;
	cout << "____operator << " << q << endl;
	cout << "____operator += " << endl;
	double w = 0;
	w += q;
	cout << "w += " << w << endl;
	template_electricity<double> arr[2];
	arr[0].print_summary_info();
	template_Ielectricity<double>* ptr_template_Ielectricity[2];
	template_electricity<double> _template_electricity;
	template_extra_electricity<double>* ptr_template_extra = new template_extra_electricity<double>;
	_template_electricity.set_tariff(3);
	ptr_template_extra->set_estimated_year(2023);
	ptr_template_Ielectricity[0] = &_template_electricity;
	ptr_template_Ielectricity[1] = ptr_template_extra;
	ptr_template_Ielectricity[0]->print_summary_info();
	ptr_template_Ielectricity[1]->print_summary_info();
	delete ptr_template_extra;*/

	return 0;
}