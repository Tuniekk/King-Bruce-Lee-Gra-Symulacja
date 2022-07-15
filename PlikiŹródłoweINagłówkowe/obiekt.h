/**
* \file obiekt.h
* \brief Plik naglowkowy modulu Obiekt.
*/

#ifndef OBIEKT_H
#define OBIEKT_H

#pragma once

#include <iostream>
#include <string.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace std;

//Typ funkcji zwracajaca informacje o tym, czy jakis obiekt jest danej klasy. Uzywane glownie do sprawdzania, w co trafil jakis atak lub na co napotkala sie jakas postac.
template<typename Base, typename T>
inline bool instanceof(const T* ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}

/*
Klasa wirtualna posiadajaca podstawowe atrybuty oraz metody sluzace do utworzenia obiektu dowolnej klasy (wojownikow oraz przeszkod).
*/
class CObiekt {
protected:
	///Nazwa obiektu
	string imie;
	///Poczatkowa wspolrzedna X obiektu
	int x;
	///Poczatkowa wspolrzedna Y obiektu
	int y;
	///Ilosc obrazeñ blokowanych
	int wytrzymalosc;
	///Ilosc punktow zdrowia. Jezeli bedzie mniejsze lub rowne zero, to obiekt zostaje usuniety (obecnie tylko wojownicy traca zdrowie, jednak mozna stworzyc przeszkody, ktore bedzie mozna niszczyc)
	int zdrowie;
	///Szerokosc obiektu
	int szerokosc;
	///Wysokosc obiektu
	int wysokosc;
public:
	///Model obiektu
	sf::RectangleShape model;

	/** \brief //Wirtualna funkcja odpowiadajaca za wyswietlanie wszystkich rzeczy zwiazanych z obiektem (model, ataki itp.)
	* \param *target Okno, w ktorym zostaje wyswietlony obiekt oraz rzeczy z nim zwiazane.
	*/
	virtual void render(sf::RenderTarget* target) = 0;
	/** \brief //Wirtualna funkcja odpowiadajaca za zadawanie obrazen obiektowi (np. po dostaniu atakiem)
	* \param liczbaObrazen Liczba obrazen zadawanych przez np. atak (zazwyczaj sila wojownika pomnozona przez jakis wspolczynnik).
	*/
	virtual void przyjmijObrazenia(int liczbaObrazen) = 0;
	/** \brief //Funkcja zwracajaca imie obiektu
	*/
	string zwrocImie() { return imie; }
	/** \brief //Funkcja zwracajaca liczbe punktow zdrowia
	*/
	int zwrocZdrowie() { return zdrowie; }
	/** \brief //Funkcja zwracajaca szerokosc obiektu
	*/
	int zwrocSzerokosc() { return szerokosc; }
	/** \brief //Funkcja zwracajaca wysokosc obiektu
	*/
	int zwrocWysokosc() { return wysokosc; }
};

/*
Klasa wirtualna posiadajaca podstawowe atrybuty oraz metody sluzace do utworzenia dowolnego wojownika.
*/
class CWojownik :public CObiekt {
protected:

	/// Ilosc czasu jaka trzeba odczekac pomiedzy kolejnymi atakami piesciami
	int cooldownAtakuPiescia;
	/// Ilosc czasu, jaka minela od ostatniego ataku piescia (jezeli == cooldownAtakuPiescia to mozna ponownie zaatakowac piescia)
	int czasDoAtakuPiescia;

	/// Ilosc czasu jaka trzeba odczekac pomiedzy kolejnymi kopnieciami
	int cooldownKopniecia;
	/// Ilosc czasu, jaka minela od ostatniego kopniecia (jezeli == cooldownAtakuPiescia to mozna ponownie uzyc kopniecia)
	int czasKopniecia;

	/// Ilosc czasu jaka trzeba odczekac pomiedzy atakami specjalnymi
	int cooldownAtakuSpecjalnego;
	/// Ilosc czasu, jaka minela od ostatniego ataku specjalnego (jezeli == cooldownAtakuPiescia to mozna ponownie zaatakowac specjalnie)
	int czasDoAtakuSpecjalnego;

	//Parametry opisujace wojownika

	/// Szybkosc, z jaka wojownik porusza sie po planszy
	int szybkosc;
	/// Ilosc obrazen, jakie sa zadawane atakami (wartosci moga byc dzielone lub mnozone w zaleznosci od ataku)
	int sila;
	
	/// Kierunek w osi X, w jaka jest odwrocony wojownik (=-1 jesli wojownik jest odwrocony w lewo, =1 jesli w prawo)
	float xKierunek = 0;
	/// Kierunek w osi Y, w jaka jest odwrocony wojownik (=-1 jesli wojownik jest odwrocony w gore, =1 jesli w dol)
	float yKierunek = 1;

	/// Predkosc, z jaka porusza sie piesc wojownika
	float predkoscPiesci = 0.3;

	/// Predkosc, z jaka porusza sie noga wojownika
	float predkoscNogi = 0.3;

	//Wektory przechowywujace ataki postaci

	/// Wektor przechowywujacy wszystkie piesci 
	std::vector<sf::RectangleShape> piesci; 
	/// Wektor przechowywujacy wszystkie nogi 
	std::vector<sf::RectangleShape> nogi;

	//Wektory przechowywujace kierunki ruchu piesci postaci

	/// Wektor kierunkow w osi X, w jaka sa odwrocone piesci
	vector<float> xKierunkiPiesci;
	/// Wektor kierunkow w osi Y, w jaka sa odwrocone piesci
	vector<float> yKierunkiPiesci;

	//Wektory przechowywujace kierunki nog piesci postaci

	/// Wektor kierunkow w osi X, w jaka sa odwrocone nogi
	vector<float> xKierunkiNog;
	/// Wektor kierunkow w osi Y, w jaka sa odwrocone nog
	vector<float> yKierunkiNog;

	//Funkcje odpowiadajace za operacje wykonywane w tle (odliczanie czasu, wykrywanie kolizji itp)

	/** \brief Funkcja liczaca dystans miedzy wojownikiem, a danym obiektem.
	* \param wojownik Wspolrzedne wojownika, od ktorych liczony jest dystans.
	* \param obiekt Wspolrzedne obiektu do ktorego liczony jest dystans.
	*/
	virtual float obliczDystans(sf::FloatRect wojownik, sf::FloatRect obiekt) = 0;

public:
	/** \brief Funkcja odliczajaca czas od ostatniego uzycia poszczegolnych atakow. Odliczanie zatrzymuje sie na wartosciach rowncyh cooldownom poszczegolnych atakow, co oznacza, ze dane ataki mozna ponownie wykonac.
	*/
	virtual void liczCzas() = 0;
	/** \brief Funkcja wykrywajaca kolizje z ramammi okna.
	* \param *okno Okno (plansza), z jaka jest wykrywana kolizja.
	*/
	virtual void wykryjKolizjeZOknem(const sf::RenderTarget* okno) = 0;
	/** \brief Funkcja wykrywajaca kolizje z innymi obiektami na planszy.
	* \param obiekty Lista obiektow, z ktorymi jest wykrywana kolizja.
	*/
	virtual void wykryjKolizjeZObiektami(std::vector<CObiekt*> obiekty) = 0;

	//Funkcje odpowiadajace za akcje postaci wywolywane wcisnieciem klawiszy (ataki, poruszanie sie)

	/** \brief Funkcja dodajaca piesc do wektora piesci.
	* \param wykonajAtak zmienna, ktora wywoluje sie funkcje (dla == 1 funkcja zostaje wywolana).
	*/
	virtual void atakPiescia(bool wykonajAtak) = 0;
	/** \brief Funkcja odpowiadajaca za poruszanie sie piesci oraz wykrywanie ich kolizji z innymi obiektami.
	* \param *okno miejsce, gdzie atak piescia ma miejsce (plansza).
	* \param cele lista obiektow, z ktorymi piesci wykrywaja kolizje (lista obiektow na planszy).
	*/
	virtual void ruchPiescia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele) = 0; 
	/** \brief Funkcja dodajaca noge do wektora nogi.
	* \param wykonajAtak zmienna, ktora wywoluje sie funkcje (dla == 1 funkcja zostaje wywolana).
	*/
	virtual void kopniecie(bool wykonajAtak) = 0;
	/** \brief Funkcja odpowiadajaca za poruszanie sie nog oraz wykrywanie ich kolizji z innymi obiektami.
	* \param *okno miejsce, gdzie kopniecie ma miejsce (plansza).
	* \param cele lista obiektow, z ktorymi nogi wykrywaja kolizje (lista obiektow na planszy).
	*/
	virtual void ruchKopniecia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele) = 0;
	/** \brief Funkcja wywolujaca atak specjalny (np. rzut szurikenem lub rozpoczecie czasu premii).
	* \param wykonajAtak zmienna, ktora wywoluje sie funkcje (dla == 1 funkcja zostaje wywolana).
	*/
	virtual void atakSpecjalny(bool wykonajAtak) = 0;
	/** \brief Funkcja odpowiadajaca za poruszanie sie atakow specjalnych lub odliczanie czasu ich trwania.
	* \param *okno miejsce, gdzie atak specjalny ma miejsce (plansza).
	* \param cele lista obiektow, z ktorymi ataki specjalne wykrywaja kolizje (lista obiektow na planszy).
	*/
	virtual void ruchAtakuSpecjalnego(const sf::RenderTarget* okno, std::vector<CObiekt*> cele) = 0;
	/** \brief Funkcja odpowiadajaca za poruszanie sie postaci oraz jej atakow.
	* \param stronaRuchu Zmienna uzywana w intrukcji switch wewnatrz funkcji, w zaleznosci od podanej wartosci postac oraz ataki ruszaja sie w jedna z czterech stron.
	*/
	virtual void chodzenie(char stronaRuchu) = 0; 

	/** \brief Funkcja odpowiadajaca za samodzielne zachowywanie sie wojownika.
	* \param *okno Plansza, na ktorej zachodzi aktualizacja wojownika (np. poruszanie sie).
	* \param obiekty Lista obiektow, z ktorymi wojownikyou moze wchodzic w interakcje (blokowowac sie o nie, atakowac itp.).
	*/
	virtual void update(const sf::RenderTarget* okno, std::vector<CObiekt*> obiekty) = 0;

	/** \brief Wyswietlanie ataku piescia wojownika.
	* \param *okno miejsce, gdzie jest wyswietlany atak piescia.
	*/
	virtual void renderAtakPiescia(sf::RenderTarget* okno) = 0;
	/** \brief Wyswietlanie kopniecia wojownika.
	* \param *okno miejsce, gdzie jest wyswietlane kopniecie.
	*/
	virtual void renderKopniecie(sf::RenderTarget* okno) = 0;
	/** \brief //Wirtualna funkcja odpowiadajaca za zadawanie obrazen wojownikowi (np. po dostaniu atakiem)
	* \param liczbaObrazen Liczba obrazen zadawanych przez np. atak (zazwyczaj sila wojownika pomnozona przez jakis wspolczynnik).
	*/
	virtual void przyjmijObrazenia(int liczbaObrazen) = 0;
	/** \brief Wyswietlanie wszystkich rzeczy zwiazanych z wojownikiem (ataki, model itp).
	* \param *okno miejsce, gdzie sa wyswietlane rzeczy zwiazane z wojownikiem.
	*/
	virtual void render(sf::RenderTarget* target) = 0;
};

/*
Klasa wirtualna posiadajaca podstawowe atrybuty oraz metody sluzace do utworzenia dowolnej przeszkody.
*/
class CPrzeszkoda :public CObiekt {

public:
	/** \brief Wyswietlanie wszystkich rzeczy zwiazanych z przeszkoda (model itp).
	* \param *okno miejsce, gdzie sa wyswietlane rzeczy zwiazane z przeszkoda.
	*/
	virtual void render(sf::RenderTarget* target) = 0;
	/** \brief //Wirtualna funkcja odpowiadajaca za zadawanie obrazen przeszkodzie (np. po dostaniu atakiem)
	* \param liczbaObrazen Liczba obrazen zadawanych przez np. atak (zazwyczaj sila wojownika pomnozona przez jakis wspolczynnik).
	*/
	virtual void przyjmijObrazenia(int liczbaObrazen) = 0;
};

#endif //GRACZ_H
