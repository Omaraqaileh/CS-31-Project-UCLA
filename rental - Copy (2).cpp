#include <iostream>
#include <string>
using namespace std;

int main() {


	int startodo;
	int endodo;
	int days_rental;
	string customer_name;
	char luxury_car;
	int starting_month;



	cout << "Odometer at start: ";
	cin >> startodo;
	cout << "Odometer at end: ";
	cin >> endodo;
	cout << "Rental days: ";
	cin >> days_rental;
	cout << "Customer name: ";
	cin.ignore();
	getline(cin, customer_name);
	cout << "Luxury car? (y/n): ";
	cin >> luxury_car;
	cout << "Starting month (1=Jan, 2=Feb, etc.): ";
	cin >> starting_month;

	int base_charge = 45;
	double per_mile = 0.33;
	double per_mile2 = 0;
	double per_mile3 = 0;
	double total_miles_driven = endodo - startodo;


	if (total_miles_driven > 600) {
		per_mile3 = 0.21;
	}



	switch (starting_month) {
	case 12:
		if (total_miles_driven > 100 && total_miles_driven <= 500) {
			per_mile2 = 0.33;
		}
		break;
	case 1:
		if (total_miles_driven > 100 && total_miles_driven <= 500) {
			per_mile2 = 0.33;
		}
		break;
	case 2:
		if (total_miles_driven > 100 && total_miles_driven <= 500) {
			per_mile2 = 0.33;
		}
		break;
	case 3:
		if (total_miles_driven > 100 && total_miles_driven <= 500) {
			per_mile2 = 0.33;
		}
		break;
	case 4:
		per_mile2 = 0.27;
		break;
	case 5:
		per_mile2 = 0.27;
		break;
	case 6:
		per_mile2 = 0.27;
		break;
	case 7:
		per_mile2 = 0.27;
		break;
	case 8:
		per_mile2 = 0.27;
		break;
	case 9:
		per_mile2 = 0.27;
		break;
	case 10:
		per_mile2 = 0.27;
		break;
	case 11:
		per_mile2 = 0.27;
		break;
	default:
		break;
	}

	double end_money;




	if (luxury_car == 'y') {
		base_charge = 75;
	}

	if (startodo < 0) {
		cout << "---" << endl;
		cout << "The starting odometer reading must not be negative.";
	}
	else if (total_miles_driven < 0) {
		cout << "---" << endl;
		cout << "The ending odometer reading must be at least as large as the starting reading.";
	}
	else if (days_rental <= 0) {
		cout << "---" << endl;
		cout << "The number of rental days must be positive.";
	}
	else if (customer_name.length() == 0) {
		cout << "---" << endl;
		cout << "You must enter a customer name.";

	}
	else if (luxury_car != 'y' && luxury_car != 'n') {
		cout << "---" << endl;
		cout << "You must enter y or n.";

	}
	else if (starting_month > 12 || starting_month < 1) {
		cout << "---" << endl;
		cout << "The month number must be in the range 1 through 12.";

	}


	else if (total_miles_driven <= 100 && total_miles_driven > 0) {
		end_money = base_charge * days_rental + per_mile * (endodo - startodo);
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "---" << endl;
		cout << "The rental charge for " << customer_name << " is $" << end_money;
	}
	else if (total_miles_driven > 100 && total_miles_driven <= 600) {
		end_money = base_charge * days_rental + per_mile * 100 + per_mile2 * (total_miles_driven - 100);
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "---" << endl;
		cout << "The rental charge for " << customer_name << " is $" << end_money;

	}
	else if (total_miles_driven > 600) {
		end_money = base_charge * days_rental + per_mile * 100 + per_mile2 * 500 + per_mile3 * (total_miles_driven - 600);
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << "---" << endl;
		cout << "The rental charge for " << customer_name << " is $" << end_money;

	}
}