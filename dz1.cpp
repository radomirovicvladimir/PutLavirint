#include<iostream>
#include<cstdlib>
using namespace std;
void obrisi(int ** matrica, int &n)
{
	if (n != 0)
	{
		for (int i = 0; i < n; i++)
		{
			delete[] matrica[i];
		}
		delete[] matrica;
		n = 0;
	}
}
void kreiraj(int ***matrica, int &n) {
	while (1) {
		cout << "\nUnesite broj cvorova grafa: "; cin >> n;
		if (n > 0 && n <= 4000)
		{
			int **mat = new int*[n];
			for (int i = 0; i < n; i++)
			{
				mat[i] = new int[n];
				for (int j = 0; j < n; j++)
					mat[i][j] = 0;
			}
			*matrica = mat;
			break;
		}
		else {
			cout << "Broj cvorova nije u predvidjenom dosegu";
			continue;
		}
	}
}
int** dodajCvor(int **matrica, int &n) {
	if (n == 4000) {
		cout << "Dostigli ste maksimum cvorova";
		return matrica;
	}
	n = n + 1;
	int **mat = new int*[n];
	for (int i = 0; i < n; i++)
	{
		mat[i] = new int[n];
		for (int j = 0; j < n; j++)
			mat[i][j] = 0;
	}
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - 1; j++)
			mat[i][j] = matrica[i][j];
	return mat;
}
int** ukloniCvor(int **matrica, int &n) {
	if (n == 0) {
		cout << "Nema cvorova u matrici";
		return matrica;
	}
	int **mat;
	int c = 0;
	while (1) {
		cout << "\nUnesite koji cvor zelite da obrisete? "; cin >> c;
		if (c < n && c >= 0)
		{
			--n;
			mat = new int*[n];
			for (int i = 0; i < n; i++)
			{
				mat[i] = new int[n];
				for (int j = 0; j < n; j++)
					mat[i][j] = 0;
			}
			for (int i = 0; i < n+1; i++) {
				for (int j = 0; j < n+1; j++) {
					if (i < c && j < c)
						mat[i][j] = matrica[i][j];
					else if (i<c && j>c)
						mat[i][j - 1] = matrica[i][j];
					else if (i > c && j < c)
						mat[i - 1][j] = matrica[i][j];
					else if (i > c && j > c)
						mat[i - 1][j - 1] = matrica[i][j];
				}
			}break;
		}
		else {
			cout << "Uneli ste neispravan cvor " << endl;
			continue;
		}
	}
	int t = n + 1;
	obrisi(matrica, t);
	return mat;
}
int** dodajGranu(int **matrica, int n) {
	int i = 0, j = 0;
	while (1) {
		cout << "\nUnesite dva cvora izmedju kojih zelite da bude dodata grana: "; cin >> i >> j;
		if ((i >= 0 && i < n) && (j >= 0 && j < n)) {
			if (matrica[i][j] != 1)
			{
				matrica[i][j] = 1;
				matrica[j][i] = 1;
			}
			else cout << "Grana vec postoji";
			break;
		}
		else {
			cout << "Cvorovi nisu u opsegu";
			continue;
		}
	}
	return matrica;
}
int** ukloniGranu(int **matrica, int n) {
	int i = 0, j = 0;
	while (1) {
		cout << "\nUnesite dva cvora izmedju kojih zelite da bude uklonjena grana: "; cin >> i >> j;
		if ((i >= 0 && i < n) && (j >= 0 && j < n)) {
			if (matrica[i][j] == 1)
			{
				matrica[i][j] = 0;
				matrica[j][i] = 0;
			}
			else cout << "Ne postoji grana izmedju ova dva cvora";
			break;
		}
		else {
			cout << "Cvorovi nisu u opsegu";
			continue;
		}
	}
	return matrica;
}
void ispis(int **matrica, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << matrica[i][j] << "\t";
		cout << endl;
	}
}
int main()
{
	int** matrica=0;
	int n = 0;
	int i=0, j=0;
	bool kraj = false;
	while (!kraj) {
		cout << "\n1. Kreiraj reprezentaciju graf\n"
			"2. Dodaj cvor\n"
			"3. Ukloni cvor\n"
			"4. Dodaj granu\n"
			"5. Ukloni granu\n"
			"6. Ispisi reprezentaciju grafa\n"
			"7. Izbrisi reprezentaciju grafa\n"
			"0. Kraj programa\n\n";
		int izbor; cin >> izbor;
		switch (izbor) {
		case 1:kreiraj(&matrica, n); break;
		case 2:matrica = dodajCvor(matrica, n); break;
		case 3:matrica = ukloniCvor(matrica, n); break;
		case 4:matrica = dodajGranu(matrica, n); break;
		case 5:matrica = ukloniGranu(matrica, n); break;
		case 6:ispis(matrica, n); break;
		case 7:obrisi(matrica, n); break;
		case 0:default:kraj = true; break;
		}
	}
	system("pause");
}