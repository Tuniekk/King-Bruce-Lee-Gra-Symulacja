/**
* \file karateKid.h
* \brief Plik naglowkowy modulu KarateKid.
*/

#ifndef KARATEKID_H
#define KARATEKID_H

#pragma once

#include "obiekt.h"
#include "mur.h"

#include <iostream>
#include <string.h>


/*
Wojownik Karate Kid:
-Atak piescia oraz kopniecie standardowe.
-Atak specjalny - przez okreslony czas wojownik otrzymuje premie do szybkosci. W tym czasie moze rowniez czesciej atakowac piescia oraz uzywac kopniecia.

-Wojownik ten jest w stanie przechodzic przez mury. Inne przeszkody oraz wojownicy blokuja postac.
*/

class CKarateKid :public CWojownik {
private:
	///Dlugosc jednego cyklu poruszania sie
	int czasTrwaniaCyklu;
	///Ilosc czasu jaka minela od skoñczenia ostatniego cyklu (lub ilosc czasu, jaka trwa obecny cykl poruszania sie) 
	int czasObecnyCyklu; 

	///Zmienna przechowywujaca wartosc szybkosci postaci (szybkosc ta na skutek uzycia ataku specjalnego moze sie chwilowo zmieniac, po skoñczeniu tego ataku wartosc wraca do podanej w tej zmiennej
	int oryginalnaSzybkosc; 
	///Zmienna przechowywujaca wartosc cooldownu ataku piescia postaci (cooldown ten na skutek uzycia ataku specjalnego moze sie chwilowo zmieniac, po skoñczeniu tego ataku wartosc wraca do podanej w tej zmiennej
	int oryginalnyCooldownAtakuPiescia; 
	///Zmienna przechowywujaca wartosc cooldownu kopniecia postaci (cooldown ten na skutek uzycia ataku specjalnego moze sie chwilowo zmieniac, po skoñczeniu tego ataku wartosc wraca do podanej
	int oryginalnyCooldownKopniecia; 

	///Zmienna informujaca o tym, czy premia ataku specjalnego jest aktywna (== 1 oznacza, ze premia jest aktywna)
	bool premiaAktywna;

	void inicjujZmienne(int wx, int wy, string i, int z, int sz, int szer, int wys, int w, int s);
	void inicjujModel();

public:
	///Zmienna przechowywujaca informacje o tym, czy postac jest sterowana przez gracza
	bool trybSterowania;

	//Konstruktor i destruktor
	CKarateKid(int wx = 800, int wy = 300, string i = "Karate Kid", int z = 50, int sz = 8, int szer = 70, int wys = 70, int w = 3, int s = 10);
	~CKarateKid();

	void atakPiescia(bool wykonajAtak);
	void ruchPiescia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele);
	void kopniecie(bool wykonajAtak);
	void ruchKopniecia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele);
	void atakSpecjalny(bool wykonajAtak);
	void ruchAtakuSpecjalnego(const sf::RenderTarget* okno, std::vector<CObiekt*> cele);
	void chodzenie(char stronaRuchu);

	float obliczDystans(sf::FloatRect wojownik, sf::FloatRect obiekt);
	void liczCzas();
	void wykryjKolizjeZOknem(const sf::RenderTarget* okno);
	void wykryjKolizjeZObiektami(std::vector<CObiekt*> obiekty);
	void update(const sf::RenderTarget* okno, std::vector<CObiekt*> obiekty);
	void przyjmijObrazenia(int liczbaObrazen);

	void renderAtakPiescia(sf::RenderTarget* okno);
	void renderKopniecie(sf::RenderTarget* okno);
	void render(sf::RenderTarget* target);
};

#endif //KARATEKID_H