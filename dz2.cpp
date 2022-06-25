#include<iostream>
using namespace std;
//1 8 8 0 3 6 7 2 1 3 2 1 2 2 1 1 2 2 1 2 3 1 2 4 1 2 5 1 2 6 1 2 6 2 2 6 3 2 6 4 2 6 5 2 6 6 2 2 3 2 3 3 2 4 3 2 4 4 2 4 5 2 4 6 2 3 5 2 2 5 2 2 4
//1 9 9 0 1 0 7 2 1 1 2 1 2 2 1 3 2 2 3 2 3 3 2 3 1 2 4 3 2 5 3 2 5 2 2 5 1 2 6 1 2 7 1 2 7 2 2 7 3 2 6 3 2 6 4 2 6 5 2 7 5 2 7 6 2 7 7 2 6 7 2 5 7 2 4 7 2 4 6 2 4 5 2 3 5 2 2 5 2 1 5 2 1 6 2 1 7 2 2 7 2 3 7
struct Cvor {
	int vrsta;
	int kolona;
	char vrednost;
	
};
class Red {
	
	int *niz,kap, duz, prvi, posl;
public:
	explicit Red(int k = 4000) {
		niz = new int[kap = k];
		duz = prvi = posl = 0;
	}
	void stavi(int b) {
		if (duz == kap)cout << "Red je pun";
		niz[posl++] = b;
		if (posl == kap)prvi = 0;
		duz++;
	}
	int uzmi() {
		if (duz == 0)cout << "Red nema vise elemenata";
		int b = niz[prvi++];
		if (prvi == kap)prvi = 0;
		duz--;
		return b;
	}
	bool prazan() const { return duz == 0; }
	bool pun() const { return duz == kap; }
};
int resi(Cvor **mat, int brojVrsta, int brojKolona, Cvor ulaz, Cvor izlaz) {
	//INICIJALIZUJEMO PROMENLJIVE
	char c = (char)178;
	//pravimo dva reda u koja cemo da smestamo cvorove,dva su zato sto nam je lakse da pretrazujemo
	Red *redVrsta = new Red((brojVrsta - 2)*(brojKolona - 2));
	Red *redKolona = new Red((brojVrsta - 2)*(brojKolona - 2));
	//Promenljive koje sluze da prate koliko nam je koraka potrebno
	int korak = 0;
	int cvorUtek = 1;
	int cvorUsled = 0;
	//Promenljiva za kraj
	bool kraj = false;
	//Matrica posecenosti da pratimo da li su poseceni
	bool **posecen = new bool*[brojVrsta];
	int** pretVrsta = new int*[brojVrsta];
	int** pretKolona = new int*[brojVrsta];
	for (int i = 0; i < brojVrsta; i++) {
		posecen[i] = new bool[brojKolona];
		pretVrsta[i] = new int[brojKolona];
		pretKolona[i] = new int[brojKolona];
		for (int j = 0; j < brojKolona; j++)
		{
			pretVrsta[i][j] = -1;
			pretKolona[i][j] = -1;
			posecen[i][j] = false;
		}
	}
	//Gore dole desno levo
	int smerVrsta[4] = { -1,1,0,0 };
	int smerKolona[4] = { 0,0,1,-1 };
	//POCETAK RESAVANJA
	redVrsta->stavi(ulaz.vrsta);
	redKolona->stavi(ulaz.kolona);
	posecen[ulaz.vrsta][ulaz.kolona] = true;
	while (!redVrsta->prazan() && !redKolona->prazan()) 
	{
		int v = redVrsta->uzmi();
		int k = redKolona->uzmi();
		if (mat[v][k].vrednost == 'x') {
			kraj = true;
			break;
		}
		//OBILAZIMO SUSEDNE CVOROVE
		for (int i = 0; i < 4; i++)
		{
			int vv = v + smerVrsta[i];
			int kk = k + smerKolona[i];

			//Ispitujemo granice
			if (vv < 0 || kk < 0)continue;
			if (vv >= brojVrsta || kk >= brojKolona)continue;

			//Preskacemo zidove i posecene
			if (posecen[vv][kk] == true)continue;
			if (mat[vv][kk].vrednost == c)continue;

			redVrsta->stavi(vv);
			redKolona->stavi(kk);
			posecen[vv][kk] = true;
			pretVrsta[vv][kk] = v;
			pretKolona[vv][kk] = k;
			cvorUsled++;
		}
		cvorUtek--;
		if (cvorUtek == 0) {
			cvorUtek = cvorUsled;
			cvorUsled = 0;
			korak++;
		}
	}
	int* putVrsta = new int[brojVrsta*brojKolona];
	int* putKolona = new int[brojVrsta*brojKolona];
	int brojPut = 0;
	int pv = izlaz.vrsta, pk = izlaz.kolona;
	while (pretVrsta[pv][pk] != -1 && pretKolona[pv][pk] != -1) {
		putVrsta[brojPut] = pretVrsta[pv][pk];
		putKolona[brojPut] = pretKolona[pv][pk];
		pv = putVrsta[brojPut];
		pk = putKolona[brojPut];
		brojPut++;
	}
	if (putVrsta[brojPut - 1] == ulaz.vrsta && putKolona[brojPut - 1] == ulaz.kolona) {
		for (int k = brojPut - 1; k >= 0; k--) {
			cout << "(" << putVrsta[k] << "," << putKolona[k] << ")" << " -> ";
		}
		cout << "(" << izlaz.vrsta << "," << izlaz.kolona << ")" << endl;
	}
	else {
		cout << "Ne postoji put do kraja";
		return -1;
	}
	/*Cvor* put = new Cvor[(brojVrsta - 2)*(brojKolona - 2)];
	int brojPuta = 0, pretVrsta = izlaz.vrsta, pretKolona = izlaz.kolona;
	while (matCvorova[pretVrsta][pretKolona].vrednost != '1' && matCvorova[pretVrsta][pretKolona].vrednost != '1') {
		put[brojPuta].vrsta = matCvorova[pretVrsta][pretKolona].vrsta;
		put[brojPuta].kolona = matCvorova[pretVrsta][pretKolona].kolona;
		pretVrsta = put[brojPuta].vrsta;
		pretKolona = put[brojPuta].kolona;
		brojPuta++;
	}
	if (put[brojPuta - 1].vrsta = ulaz.vrsta && put[brojPuta - 1].kolona == ulaz.kolona) {
		for (int k = brojPuta - 1; k >= 0; k--) {
			cout << "(" << put[k].vrsta << "," << put[k].kolona << ")" << "->" << endl;
		}
		cout << "(" << izlaz.vrsta << "," << izlaz.kolona << ")" << endl;
	}
	else {
		cout << "Ne postoji put do kraja";
		return -1;
	}*/


	cout << "\nBroj koraka potrebnih od ulaza do izlaza je ";
	if (kraj) return korak;
	else return -1;
}
void napravi_lavirint(Cvor ***matrica, int &brojVrsta, int &brojKolona, Cvor &ulaz, Cvor &izlaz) {
	while (1) {
		cout << "\nUnesite dimenzije lavirinta: "; cin >> brojVrsta >> brojKolona;
		if ((brojVrsta>=0 && brojVrsta<=80)&&(brojKolona>=0 && brojKolona<=50))
		{
			//MATRICA CVOROVA
			Cvor **mat = new Cvor*[brojVrsta];
			for (int i = 0; i < brojVrsta; i++)
			{
				mat[i] = new Cvor[brojKolona];
				for (int j = 0; j < brojKolona; j++) {
					mat[i][j].vrednost = (char)178;
					mat[i][j].vrsta = i;
					mat[i][j].kolona = j;
				}
			}
			//ULAZ
			while (1) {
				cout << "\nPostaviti ulaz na kordinatama: ";
				cin >> ulaz.vrsta >> ulaz.kolona;
				if ((ulaz.vrsta == 0 && ulaz.kolona >= 0 && ulaz.kolona < brojKolona) || (ulaz.vrsta == (brojVrsta - 1) && ulaz.kolona >= 0 && ulaz.kolona < brojKolona) || (ulaz.kolona == 0 && ulaz.vrsta >= 0 && ulaz.vrsta < brojVrsta) || (ulaz.kolona == (brojKolona - 1) && ulaz.vrsta >= 0 && ulaz.vrsta < brojVrsta)) { mat[ulaz.vrsta][ulaz.kolona].vrednost = 'o'; break; }
				else {
					cout << "Ulaz je moguce postaviti samo na ivicama lavirinta";
					continue;
				}
			}
			//IZLAZ
			while (1) {
				cout << "\nPostaviti izlaz na kordinatama: ";
				cin >> izlaz.vrsta >> izlaz.kolona;
				if ((izlaz.vrsta == 0 && izlaz.kolona >= 0 && izlaz.kolona < brojKolona) || (izlaz.vrsta == (brojVrsta - 1) && izlaz.kolona >= 0 && izlaz.kolona < brojKolona) || (izlaz.kolona == 0 && izlaz.vrsta >= 0 && izlaz.vrsta < brojVrsta) || (izlaz.kolona == (brojKolona - 1) && izlaz.vrsta >= 0 && izlaz.vrsta < brojVrsta)) { 
					if (mat[izlaz.vrsta][izlaz.kolona].vrednost == 'o') {
						cout << "Ne mozete postaviti izlaz na ulazu";
						continue;
					}
					else {
						mat[izlaz.vrsta][izlaz.kolona].vrednost = 'x'; break;
					}
				}
				else {
					cout << "Izlaz je moguce postaviti samo na ivicama lavirinta";
					continue;
				}
			}
			*matrica = mat;
			break;
		}
		else {
			cout << "Dimenzije lavirinta nisu validne";
			continue;
		}
	}
}
void ispis(Cvor **matrica, int brojVrsta, int brojKolona) {
	for (int i = 0; i < brojVrsta; i++) {
		for (int j = 0; j < brojKolona; j++)
			cout << matrica[i][j].vrednost;
		cout << endl;
	}
}
void brisi(Cvor **matrica, int &brojVrsta, int &brojKolona) {
	if (brojVrsta != 0 && brojKolona!=0)
	{
		for (int i = 0; i < brojVrsta; i++)
		{
			delete[] matrica[i];
		}
		delete[] matrica;
		brojVrsta = 0;
		brojKolona = 0;
	}
}
Cvor** dodajPut(Cvor **matrica, int brojVrsta, int brojKolona)
{
	Cvor novi;
	while (1) 
	{
		cout << "\nUnesite kordinate cvora gde zelite da dodate put: "; 
		cin >> novi.vrsta >> novi.kolona;
		if ((novi.vrsta == 0 && novi.kolona >= 0 && novi.kolona < brojKolona) || (novi.vrsta == (brojVrsta - 1) && novi.kolona >= 0 && novi.kolona < brojKolona) || (novi.kolona == 0 && novi.vrsta >= 0 && novi.vrsta < brojVrsta) || (novi.kolona == (brojKolona - 1) && novi.vrsta >= 0 && novi.vrsta < brojVrsta))
		{
			cout << "Ne mozete dodati put na ivicama lavirinta";
			continue;
		}
		else if ((novi.vrsta < 0 || novi.vrsta >= brojVrsta) || (novi.kolona < 0 || novi.kolona >= brojKolona))
		{

			cout << "Kordinate izvan dosega matrice";
			continue;
		}
		else 
		{
			if (matrica[novi.vrsta][novi.kolona].vrednost == ' ')
				cout << "Postoji put na tim kordinatama";
			else matrica[novi.vrsta][novi.kolona].vrednost = ' ';
			break;
		}
	}
	return matrica;
}
Cvor** ukloniPut(Cvor **matrica, int brojVrsta, int brojKolona) {
	Cvor novi;
	char c = (char)178;
	while (1)
	{
		cout << "\nUnesite kordinate cvora gde zelite da uklonite put i postavite zid: ";
		cin >> novi.vrsta >> novi.kolona;
		if ((novi.vrsta < 0 || novi.vrsta >= brojVrsta) || (novi.kolona < 0 || novi.kolona >= brojKolona))
		{
			cout << "Kordinate izvan dosega matrice";
			continue;
		}
		if ((novi.vrsta == 0 && novi.kolona >= 0 && novi.kolona < brojKolona) || (novi.vrsta == (brojVrsta - 1) && novi.kolona >= 0 && novi.kolona < brojKolona) || (novi.kolona == 0 && novi.vrsta >= 0 && novi.vrsta < brojVrsta) || (novi.kolona == (brojKolona - 1) && novi.vrsta >= 0 && novi.vrsta < brojVrsta))
		{
			cout << "Ne mozete uklanjati put na ivicama lavirinta";
			continue;
		}
		if (matrica[novi.vrsta][novi.kolona].vrednost == c) cout << "Na datim kordinatama postoji zid";
		else matrica[novi.vrsta][novi.kolona].vrednost = c;
		break;
	}
	return matrica;
}
int main()
{
	Cvor** matrica = nullptr;
	int brojVrsta = 0, brojKolona = 0;
	Cvor ulaz, izlaz;
	bool kraj = false;
	while (!kraj) {
		cout << "\n1. Kreiraj lavirint \n"
			"2. Dodaj put\n"
			"3. Ukloni put\n"
			"4. Ispisi lavirint\n"
			"5. Izbrisi lavirint\n"
			"6. Resi\n"
			"0. Kraj programa\n\n";
		int izbor; cin >> izbor;
		switch (izbor) {
		case 1:napravi_lavirint(&matrica, brojVrsta, brojKolona, ulaz, izlaz); break;
		case 2:matrica = dodajPut(matrica, brojVrsta, brojKolona); break;
		case 3:matrica = ukloniPut(matrica, brojVrsta,brojKolona); break;
		case 4: ispis(matrica, brojVrsta, brojKolona); break;
		case 5: brisi(matrica, brojVrsta, brojKolona); break;
		case 6:cout << resi(matrica, brojVrsta, brojKolona, ulaz, izlaz); break;
		case 0:default:kraj = true; break;
		}
	}
	system("pause");
}