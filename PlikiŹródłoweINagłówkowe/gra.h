/**
* \file gra.h
* \brief Plik naglowkowy modulu Gra.
*/

#ifndef GRA_H
#define GRA_H

#pragma once

#include <iostream>
#include <vector>

#include "obiekt.h" //Zawiera definicje klas CObiekt, CWojownik oraz CPrzeszkoda
#include "menu.h" //Zawiera definicje klasy CMenu
#include "gracz.h" //Zawiera definicje klasy CGracz
#include "bruceLee.h" //Zawiera definicje klasy CBruceLee
#include "karateKid.h" //Zawiera definicje klasy CKarateKid
#include "jackieChan.h" //Zawiera definicje klasy CJackieChan
#include "stol.h" //Zawiera definicje klasy CStol
#include "mur.h" //Zawiera definicje klasy CMur
#include "skrzynia.h" //Zawiera definicje klasy CSkrzynia

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class CGra {
private:
	///Zmienna przechowywujaca szerokosc okna gry
	float szerokoscOkna = 1280; 
	///Zmienna przechowywujaca wysokosc okna gry
	float wysokoscOkna = 720;
	///Info o oknie
	sf::VideoMode videoMode;
	///Definicja wydarzen (wcisniecie klawisza itp)
	sf::Event eventGra;

	/** \brief Funkcja przypisujaca wartosci atrybutom zwiazanych z gra
	*/
	void inicjujZmienne();
	/** \brief Funkcja tworzaca okno do gry (szerokosc, wysokosc, tytul okna oraz liczba klatek na sekunde)
	*/
	void inicjujOkno();
public:
	/// Wskaznik na okno, w ktorym bedzie wyswietlana gra lub symulacja
	sf::RenderWindow* okno;

	/// Zmienna przechowywujaca informacje o stanie gry, jezeli jest rowna jeden to gra powinna byc zakonczona
	bool koniecGry;
	/// Obiekt klasy CBruceLee reprezentujacy wojownika tej klasy w trybie gry oraz symulacji
	CBruceLee bruceLee;
	/// Obiekt klasy CKarateKid reprezentujacy wojownika tej klasy w trybie gry oraz symulacji
	CKarateKid karateKid; 
	/// Obiekt klasy CJackieChan reprezentujacy wojownika tej klasy w trybie gry oraz symulacji
	CJackieChan jackieChan;
	/// Obiekt klasy CGracz pozwalajacy na przypisanie wojownika graczowi podczas trybu gry
	CGracz gracz1;

	///Wektor przechowywujacy wszystkie obiekty (przeszkody oraz wojownicy)
	std::vector<CObiekt*> obiekty;
	///Wektor przechowywujacy tylko wojownikow
	std::vector<CWojownik*> wojownicy;

	//Konstruktor i destruktor
	CGra();
	~CGra();

	/** \brief Funkcja zwracajaca informacje o tym, czy okno jest otwarte
	*/
	const bool oknoOtwarte() const;

	/** \brief Funkcja dodajaca wojownikow do listy wojownicy oraz dodajaca obiekty i liste wojownicy do listy obiekty.
	*/
	void dodajObiekty();

	/** \brief Funkcja usuwajaca z list obiekty oraz wojownicy wojownikow, ktorzy maja zdrowie mniejsze lub rowne zero.
	*/
	void zabijWojownika();

	/** \brief Funkcja dodajaca do list obiekty oraz wojownicy wybranego wojownika.
	*/
	void dodajWojownika(CWojownik *wojownik);

	/** \brief Funkcja zmieniajaca bool koniecGry na jeden, jezeli zyje co najwyzej jeden wojownik.
	*/
	void zakonczGre();

	/** \brief Funckja odpowiadajaca za wywolywanie funkcji wojownika (ataki, poruszanie sie) po kliknieciu odpowiedniego przycisku.
	* \param gracz Obiekt trybu gracz, ktorego przyciski wywoluja poszczegolne akcje (ataki, chodzenie).
	*/
	void sterowanie(CGracz gracz);
	/** \brief Funckja odpowiadajaca za odpowiadanie na zdarzenia (klikniecie klawisza, klikniecie przycisku X w pasku itp.).
	*/
	void pollEvents();
	/** \brief Funkcja odpowiadajaca za aktualizowanie obiektow, sprawdzanie warunkow.
	*/
	void update();
	/** \brief  Funkcja wyswietlajaca wszystkie rzeczy w oknie.
	*/
	void render();
	/** \brief  Funkcja wyswietlajaca komunikat o zwyciestwie ostatniego wojownika.
	*/
	void wyswietlKomunikat();
};

#endif //GRA_H