#include <iostream>
#include <iomanip>
#include <conio.h>
#include <string>
#include <cmath>
#include <windows.h>
#include <fstream>

using namespace std;

class Rating {
	double** mark;
	int* competences;
	int m, n;
public:
	Rating() : mark(NULL), competences(NULL), m(3), n(4) {}

	Rating(int m, int n) : m(m), n(n) {
		mark = new double*[m];
		for (int i = 0; i < m; i++)
			mark[i] = new double[n];

		competences = new int[m];
	}

	~Rating() { 
		for (int k = 0; k < m; k++) delete[] mark[k];
		delete[] mark;
		delete[] competences; 
	}

	void setMatrix() {
		double sum = 0; // =1
		int errorCounter = 0;
		cout << "������� ���-�� ���������: ";
		cin >> m;
		cout << "������� ���-�� �������: ";
		cin >> n;

		mark = new double* [m];
		for (int i = 0; i < m; i++)
			mark[i] = new double[n];

		competences = new int[m];

		cout << endl << "������� ������� ����� ����� (�� 0 �� 1 �� ������������) (������� n - 1 �������� � ������): " << endl;
		for (int i = 0; i < m; i++) {
			cout << endl << "�������_" << i + 1 << ":" << endl;
			for (;;) {
				for (int j = 0; j < n - 1; j++) {
					cout << "Z" << j + 1 << ": ";
					cin >> mark[i][j]; 
					if (mark[i][j] < 0) errorCounter++;
					sum += mark[i][j];
				}
				if (sum >= 1 || errorCounter) {
					cout << "������� �������� ��������, ��������� �������" << endl;
					errorCounter = 0;
					sum = 0;
					continue;
				}
				else {
					mark[i][n - 1] = (double)1 - sum;
					cout << "Z" << n << ": " << mark[i][n - 1];
					errorCounter = 0;
					sum = 0;
					break;
				}
			}
			cout << endl;
		}
	}

	void getData() {
		system("cls");
		cout << "������� ����� �����: " << endl << endl;
		for (int j = 0; j < n; j++) cout << setw(7) << "Z" << j + 1;
		cout << endl << endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << setw(8) << mark[i][j];
			}
			cout << "\t �������_" << i + 1 << endl;
		}


		cout << endl << endl << "�������������� ���������: " << endl << endl;
		for (int i = 0; i < m; i++) {
			cout << "�������_" << i + 1 << ": ";
			cout << competences[i] << endl;
		}
	}

	void setCompetence() {
		cout << endl << "������� ������ �������������� ��������� (1-10):" << endl;
		for (int i = 0; i < m; i++) {
			cout << "�������_" << i + 1 << ": ";
			cin >> competences[i];
			if (competences[i] < 1 || competences[i] > 10) {
				cout << "������� �������� ��������. ��������� �������" << endl;
				i--;
			}
		}
	}

	void solveProblem() {
		ofstream f;
		f.open("saipis_3.txt");
		double* wages = new double[n];
		int sum = 0;
		double wage = 0;
		double* rel;
		rel = new double[m];
		for (int i = 0; i < m; i++) sum += competences[i];
		cout << endl << endl << "������������� ������ ��������������: " << endl << endl;
		for (int i = 0; i < m; i++) {
			rel[i] = (double)competences[i] / (double)sum;
			cout << "�������_" << i + 1 << ": ";
			cout << round(rel[i] * 100) / 100 << endl;
		}

		cout << endl << "���� �����: " << endl << endl;
		for (int j = 0; j < n; j++) {
			wages[j] = 0;
			for (int i = 0; i < m; i++) {
				wages[j] += round(((round(rel[i] * 100) / 100) * mark[i][j]) * 100) / 100;
			}
			cout << "Omega_Z" << j + 1 << ": " << wages[j] << endl;
		}

		double max = wages[0];
		int solution = 1;
		for (int k = 0; k < n; k++)
			if (max < wages[k]) {
				max = wages[k];
				solution = k + 1;
			}

		cout << endl << "�����: �������� ������� ���� ����� " << solution << endl;

		if (f.is_open()) {
			f << "������� ����� �����: " << endl << endl;
			for (int j = 0; j < n; j++) f << setw(7) << "Z" << j + 1;
			f << endl << endl;
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					f << setw(8) << mark[i][j];
				}
				f << "\t �������_" << i + 1 << endl;
			}

			f << endl << endl << "�������������� ���������: " << endl << endl;
			for (int i = 0; i < m; i++) {
				f << "�������_" << i + 1 << ": ";
				f << competences[i] << endl;
			}

			f << endl << endl << "������������� ������ ��������������: " << endl << endl;
			for (int i = 0; i < m; i++) {
				f << "�������_" << i + 1 << ": ";
				f << round(rel[i] * 100) / 100 << endl;
			}

			f << endl << "���� �����: " << endl << endl;
			for (int j = 0; j < n; j++) {
				f << "Omega_Z" << j + 1 << ": " << wages[j] << endl;
			}

			f << endl << "�����: �������� ������� ���� ����� " << solution << endl;

			cout << endl << endl << "������ �������� � ���� saipis_3.txt!" << endl;
		}

		f.close();
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Rating var_8;
	var_8.setMatrix();
	var_8.setCompetence();
	var_8.getData();

	cout << endl << "������� �� ����� �������, ����� ������ ������. . .\t";
	if (_getch()) {}

	var_8.solveProblem();
}