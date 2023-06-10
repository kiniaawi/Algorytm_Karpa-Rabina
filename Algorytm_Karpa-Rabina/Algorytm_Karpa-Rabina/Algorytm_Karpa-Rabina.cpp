//Algorytm Karpa-Rabina Kinga Wieloch
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <limits>

using namespace std;

void algorytmKarpaRabina(string wzorzec, string tekst);

int main()
{
	int liczbaPrzypadkow;
	std::cout << "Podaj liczbe przypadkow: ";
	std::cin >> liczbaPrzypadkow;

	if (liczbaPrzypadkow <= 0)
	{
		std::cout << "Niepoprawna liczba przypadkow" << endl;
	}

	for (int i = 0; i < liczbaPrzypadkow; i++)
	{
		string nazwaPliku;
		string wzorzec;
		string tekst;

	std:cout << "Podaj nazwe pliku: "; //np KR-biblia.txt
		std::cin >> nazwaPliku;
		cin.ignore(numeric_limits < streamsize >::max(), '\n');
		std::cout << "Podaj wzorzec: ";
		getline(cin, wzorzec);

		ifstream plik(nazwaPliku.c_str(), ios::in);
		if (plik.good())
		{
			getline(plik, tekst);
		}
		else
		{
			std::cout << "Nie znaleziono pliku" << endl;
		}
		plik.close();

		algorytmKarpaRabina(wzorzec, tekst);
	}

	return 0;
}

void algorytmKarpaRabina(string wzorzec, string tekst)
{
	int dlugoscWzorca = wzorzec.length();
	int dlugoscTekstu = tekst.length();

	int hashWzorca = 0;
	int hashTekstu = 0;

	if (dlugoscWzorca == 0)
	{
		std::cout << "Nie podano wzorca" << endl;
	}
	else if (dlugoscWzorca == 1)
	{
		hashWzorca = ((wzorzec[0] % 151)) % 151;
		hashTekstu = ((tekst[0] % 151)) % 151;
	}
	else if (dlugoscWzorca == 2)
	{
		hashWzorca = ((((wzorzec[0] % 151)) * (256 % 151)) + (wzorzec[1]) % 151) % 151;
		hashTekstu = ((((tekst[0] % 151)) * (256 % 151)) + (tekst[1]) % 151) % 151;
	}
	else if (dlugoscWzorca > 2)
	{
		int x = ((((wzorzec[0] % 151)) * (256 % 151)) + (wzorzec[1]) % 151) % 151;
		int y = ((((tekst[0] % 151)) * (256 % 151)) + (tekst[1]) % 151) % 151;
		for (int h = 2; h < dlugoscWzorca; h++)
		{
			hashWzorca = ((x * (256 % 151)) % 151 + (wzorzec[h] % 151)) % 151;
			hashTekstu = ((y * (256 % 151)) % 151 + (tekst[h] % 151)) % 151;
			x = hashWzorca;
			y = hashTekstu;
		}
	}

	if (hashWzorca < 0)
	{
		hashWzorca += 151;
	}
	if (hashTekstu < 0)
	{
		hashTekstu += 151;
	}

	int flaga;
	int x;
	int h = 0;

	int powDl = 1;
	for (int i = 0; i < dlugoscWzorca - 1; i++)
	{
		powDl = (powDl * 256) % 151;
	}

	while (h <= (dlugoscTekstu - dlugoscWzorca))
	{
		if (hashWzorca == hashTekstu)
		{
			flaga = 1;
			for (int j = 0; j < dlugoscWzorca; j++)
			{
				if (wzorzec[j] == tekst[h + j]) {
					continue;
				}
				else
				{
					flaga = 0;
					break;
				}
			}

			if (flaga == 1) std::cout << h << " ";
		}

		if (h < dlugoscTekstu - dlugoscWzorca)
		{
			x = hashTekstu;
			hashTekstu = (((x - ((tekst[h]) * powDl))) * (256 % 151) + (tekst[h + dlugoscWzorca])) % 151;

			if (hashTekstu < 0)
			{
				hashTekstu += 151;
			}
		}

		h++;
	}

	cout << endl;
}
