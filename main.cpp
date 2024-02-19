#include <iostream>
#include <string>
#include "electricity.h"
#include "extra_electricity.h"
using namespace std;

int main()
{
	setlocale(0, "");
	
	extra_electricity q(3);
	q.set_initial_indication(0);
	for (size_t i = 0; i < 3; i++)
	{
		cout << "введите номер мес€ца за который нужно ввести показание: ";
		short month;
		cin >> month;
		cout << "введите показание счетчика за этот мес€ц целым числом: ";
		int indications;
		cin >> indications;
		q.set_indications(month - 1, indications);
	}
	q.set_penalty(0, 100);
	//q.print_summary_info();
	//q.print_summary_info(0);
	cout << "q[0] = " << q[0] << endl;
	//cout << "<< q " << endl << q << endl;
	
	


	return 0;
}