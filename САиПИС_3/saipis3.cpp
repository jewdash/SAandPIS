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
		cout << "Ââåäèòå êîë-âî ýêñïåðòîâ: ";
		cin >> m;
		cout << "Ââåäèòå êîë-âî ðåøåíèé: ";
		cin >> n;

		mark = new double* [m];
		for (int i = 0; i < m; i++)
			mark[i] = new double[n];

		competences = new int[m];

		cout << endl << "Ââåäèòå ìàòðèöó âåñîâ öåëåé (îò 0 äî 1 ÍÅ âêëþ÷èòåëüíî) (Ââîäèòå n - 1 çíà÷åíèé â ñòðîêå): " << endl;
		for (int i = 0; i < m; i++) {
			cout << endl << "Ýêñïåðò_" << i + 1 << ":" << endl;
			for (;;) {
				for (int j = 0; j < n - 1; j++) {
					cout << "Z" << j + 1 << ": ";
					cin >> mark[i][j]; 
					if (mark[i][j] < 0) errorCounter++;
					sum += mark[i][j];
				}
				if (sum >= 1 || errorCounter) {
					cout << "Ââåäåíû íåâåðíûå çíà÷åíèÿ, ïîâòîðèòå ïîïûòêó" << endl;
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
		cout << "ÌÀÒÐÈÖÀ ÂÅÑÎÂ ÖÅËÅÉ: " << endl << endl;
		for (int j = 0; j < n; j++) cout << setw(7) << "Z" << j + 1;
		cout << endl << endl;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				cout << setw(8) << mark[i][j];
			}
			cout << "\t Ýêñïåðò_" << i + 1 << endl;
		}


		cout << endl << endl << "ÊÎÌÏÅÒÅÍÒÍÎÑÒÜ ÝÊÑÏÅÐÒÎÂ: " << endl << endl;
		for (int i = 0; i < m; i++) {
			cout << "Ýêñïåðò_" << i + 1 << ": ";
			cout << competences[i] << endl;
		}
	}

	void setCompetence() {
		cout << endl << "Ââåäèòå îöåíêè êîìïåòåíòíîñòè ýêñïåðòîâ (1-10):" << endl;
		for (int i = 0; i < m; i++) {
			cout << "Ýêñïåðò_" << i + 1 << ": ";
			cin >> competences[i];
			if (competences[i] < 1 || competences[i] > 10) {
				cout << "Ââåäåíî íåâåðíîå çíà÷åíèå. Ïîâòîðèòå ïîïûòêó" << endl;
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
		cout << endl << endl << "ÎÒÍÎÑÈÒÅËÜÍÛÅ ÎÖÅÍÊÈ ÊÎÌÏÅÒÅÍÒÍÎÑÒÈ: " << endl << endl;
		for (int i = 0; i < m; i++) {
			rel[i] = (double)competences[i] / (double)sum;
			cout << "Ýêñïåðò_" << i + 1 << ": ";
			cout << round(rel[i] * 100) / 100 << endl;
		}

		cout << endl << "ÂÅÑÀ ÖÅËÅÉ: " << endl << endl;
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

		cout << endl << "ÎÒÂÅÒ: ÍÀÈÁÎËÅÅ ÂÛÃÎÄÅÍ ÏËÀÍ ÍÎÌÅÐ " << solution << endl;

		if (f.is_open()) {
			f << "ÌÀÒÐÈÖÀ ÂÅÑÎÂ ÖÅËÅÉ: " << endl << endl;
			for (int j = 0; j < n; j++) f << setw(7) << "Z" << j + 1;
			f << endl << endl;
			for (int i = 0; i < m; i++) {
				for (int j = 0; j < n; j++) {
					f << setw(8) << mark[i][j];
				}
				f << "\t Ýêñïåðò_" << i + 1 << endl;
			}

			f << endl << endl << "ÊÎÌÏÅÒÅÍÒÍÎÑÒÜ ÝÊÑÏÅÐÒÎÂ: " << endl << endl;
			for (int i = 0; i < m; i++) {
				f << "Ýêñïåðò_" << i + 1 << ": ";
				f << competences[i] << endl;
			}

			f << endl << endl << "ÎÒÍÎÑÈÒÅËÜÍÛÅ ÎÖÅÍÊÈ ÊÎÌÏÅÒÅÍÒÍÎÑÒÈ: " << endl << endl;
			for (int i = 0; i < m; i++) {
				f << "Ýêñïåðò_" << i + 1 << ": ";
				f << round(rel[i] * 100) / 100 << endl;
			}

			f << endl << "ÂÅÑÀ ÖÅËÅÉ: " << endl << endl;
			for (int j = 0; j < n; j++) {
				f << "Omega_Z" << j + 1 << ": " << wages[j] << endl;
			}

			f << endl << "ÎÒÂÅÒ: ÍÀÈÁÎËÅÅ ÂÛÃÎÄÅÍ ÏËÀÍ ÍÎÌÅÐ " << solution << endl;

			cout << endl << endl << "Äàííûå çàïèñàíû â ôàéë saipis_3.txt!" << endl;
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

	cout << endl << "Íàæìèòå íà ëþáóþ êëàâèøó, ÷òîáû ðåøèòü çàäà÷ó. . .\t";
	if (_getch()) {}

	var_8.solveProblem();
}