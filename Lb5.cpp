// Lb5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double startPoint, endPoint, h, numberOfPoint, a, b, x0, xi, xi1, diff,rootNewton, rootDichotomy;
double eps = 1;
int counter,counterDich;
//�������� �������
double transcendentalFunction(double x) {
	return log10(1.0+2.0*x)-2.0+x;
}
//������ �����������
double difFunction(double x, double h) {
	return ((transcendentalFunction(x + h) - transcendentalFunction(x - h)) / (2.0 * h));
}
//������ �����������
double diff2Function(double x, double h) {
	return (difFunction((x + h),h) - difFunction((x - h),h)) / (2.0 * h);
}
//�������� ���������� ������ �����������
bool savingCheck(double a, double b, double h) {
	while (a <= b) {
		if ((difFunction(a, h) * difFunction(a + h, h) > 0) && ((diff2Function(a, h) * diff2Function(a + h, h)) > 0)) {
			return true;
		}
		a = a + h;
	}
	return false;
}
//�������� ������� ���������� f(x0)*f``(x0)>0
bool check(double a, double b, double h) {
	while (a <= b) {
		if (transcendentalFunction(a) * diff2Function(a, h) > 0) {
			return true;
		}
		a = a + h;
	}
	return false;
}

//���������� ����������� � ����������� �������� �������
//��� ����������� �������� ���������
double stoppingCriterion(double a, double b, double h) {
	double M, m;
	M = diff2Function(a, h); m = difFunction(a, h);
	do
	{
		a += h;
		if (diff2Function(a,h) > M) M =diff2Function(a,h);
		if (difFunction(a,h) < m) m = difFunction(a,h);

	} while (a != b);
	return M / (2.0 * m);
}
//����������� ������ ������� � �������������� ������ ����������� � ��������� ����� �����������
double ModifiedNewton(double a,double b, double h, double eps) {
	//����� ���������� �����������
	if (transcendentalFunction(a) > 0) {
		xi = a;
	}
	else if (transcendentalFunction(b)>0) {
		xi = b;
	}
	diff = difFunction(xi, h);
	xi1 = xi - transcendentalFunction(xi) / diff;
	counter = 1;
	while (((xi1 - xi) * (xi1 - xi) * stoppingCriterion(a, b, h)) > eps) {
		counter += 1;
		xi = xi1;
		xi1 = xi - transcendentalFunction(xi) / diff;
	}
	return xi1;
}
//����� ���������
double dichotomy(double a, double b, double h, double eps) {
	double c;
	c = (a + b) / 2;
	counterDich = 1;
	while (fabs(b - a) > eps) {
		counterDich += 1;
		c = (a + b) / 2;
		if ((transcendentalFunction(a) * transcendentalFunction(c)) < 0) b = c;
		else a = c;
	}
	return c;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "������� ��������� ������� ���������: ";
	cin >> startPoint;
	cout << "������� �������� ������� ���������: ";
	cin >> endPoint;
	cout << "������� ���������� ����� ���������: ";
	cin >> numberOfPoint;
	h = (endPoint - startPoint) / numberOfPoint; //���, � ������� ����� ������������
												 //� ��������� ������� ��������� ��������
	a = startPoint;
	b = a + h;
	//����� ��������� �������� ������ f(a)*f(b)<0
	while (b <= endPoint) {
		b = a + h;
		if ((((transcendentalFunction(a) * transcendentalFunction(b)) < 0)) && check(a,b,h)&& savingCheck(a,b,h)) {
			cout << "�������� �������� �����: " << "[" << a << "," << b << "]"<<endl;
			cout<<setw(10)<<left<<"Eps"<<" " << setw(25) << left << "�������� �-��� �����.������" <<" " << setw(15) << left << "���-�� ��������" <<" " << setw(25) << left << "�������� �-��� ���������" <<" " << setw(15) << left << "���-�� ��������" << endl;
			for (int i = 1;i < 7;i++) {
				eps = eps / 10.0;
				rootNewton = ModifiedNewton(a,b, h, eps);
				rootDichotomy = dichotomy(a, b, h, eps);
				cout << setw(10) << left << eps <<"  " << setw(25) << left << rootNewton <<"  " << setw(15) << left << counter <<"  " << setw(25) << left << rootDichotomy <<" " << setw(15) << left << counterDich << endl;
			}
		}

		a = b;
	}
	cout << endl;
	system("DrawFunctionproject.exe");
	return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
