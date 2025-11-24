#include <iostream>                                                                     

using namespace std;

double Length1;
double Length2;
double Length3;

void Print_result() {
    double sumShortSides = (Length1 * Length1) + (Length2 * Length2);
    double squareHypotenuse = (Length3 * Length3);
    if (sumShortSides == squareHypotenuse) {
        cout << "This is a right angled triangle" << endl;
    } else {
        cout << "This is not a right angled triangle" << endl;
    }
}

int main() {
    cout << "Enter three side lengths (numbers):" << endl;

    cout << "length of first side: ";
    if (!(cin >> Length1)) return 0;

    cout << "length of second side: ";
    if (!(cin >> Length2)) return 0;

    cout << "length of third side: ";
    if (!(cin >> Length3)) return 0;

    if (Length1 <= 0 || Length2 <= 0 || Length3 <= 0) {
        cout << "Invalid input: Side lengths must be positive numbers." << endl;
        return 0;
    }

    if (Length1 + Length2 <= Length3 || Length1 + Length3 <= Length2 || Length2 + Length3 <= Length1) {
        cout << "Not a valid triangle." << endl;
        return 0;
    }

    if (Length1 > Length3) {
        double tmp = Length1;
        Length1 = Length3;
        Length3 = tmp;
    }
    if (Length2 > Length3) {
        double tmp = Length2;
        Length2 = Length3;
        Length3 = tmp;
    }
    Print_result();
    return 0;
}