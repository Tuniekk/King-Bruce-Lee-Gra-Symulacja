/**
* \file gra.cpp
* \brief Plik cpp modulu Gra.
*
* Tutaj znajduje sie kod zrodlowy funkcji odpowiedzialnych za stworzenie obiektu klasy typu CGra, jego aktualizowanie oraz funkcje zwiazane z wyswietlaniem rzeczy w oknie gry.
*/

#include "gra.h"

//Private
void CGra::inicjujZmienne()
{
	this->koniecGry = 0;
}

void CGra::inicjujOkno()
{
	this->videoMode = sf::VideoMode(this->szerokoscOkna, this->wysokoscOkna);
	this->okno = new sf::RenderWindow(this->videoMode, "King Bruce Lee", sf::Style::Close | sf::Style::Titlebar);
	this->okno->setFramerateLimit(60);
}

//Konstruktor i destruktor
CGra::CGra()
{
	this->inicjujZmienne();
	this->inicjujOkno();
}

CGra::~CGra()
{
	delete this->okno;
}

//Public
//Funkcje
const bool CGra::oknoOtwarte() const
{
	return this->okno->isOpen();
}

void CGra::dodajObiekty()
{
	this->obiekty.push_back(new CStol(50, 50, 300, 500));
	this->obiekty.push_back(new CStol(50, 50, 900, 400));
	this->obiekty.push_back(new CSkrzynia(60, 60, 400, 200));
	this->obiekty.push_back(new CSkrzynia(60, 60, 800, 200));
	this->obiekty.push_back(new CMur(30, 300, 600, 150));
}

void CGra::zabijWojownika()
{
	for (size_t i = 0; i < this->obiekty.size(); i++)
		if (this->obiekty[i]->zwrocZdrowie() <= 0)
		{
			this->obiekty.erase(this->obiekty.begin() + i);
		}
	for (size_t k = 0; k < this->wojownicy.size(); k++)
		if (this->wojownicy[k]->zwrocZdrowie() <= 0)
		{
			this->wojownicy.erase(this->wojownicy.begin() + k);
		}
}

void CGra::dodajWojownika(CWojownik* wojownik)
{
	this->obiekty.push_back(wojownik);
	this->wojownicy.push_back(wojownik);
}

void CGra::zakonczGre()
{
	if (wojownicy.size() <= 1)
	{
		this->koniecGry = 1;
	}
}

void CGra::sterowanie(CGracz gracz)
{
		if (sf::Keyboard::isKeyPressed(gracz.pKrokuWLewo))
		{
			gracz.postacGracza->chodzenie('l');
		}
		if (sf::Keyboard::isKeyPressed(gracz.pKrokuWPrawo))
		{
			gracz.postacGracza->chodzenie('p');
		}
		if (sf::Keyboard::isKeyPressed(gracz.pKrokuWDol))
		{
			gracz.postacGracza->chodzenie('d');
		}
		if (sf::Keyboard::isKeyPressed(gracz.pKrokuWGore))
		{
			gracz.postacGracza->chodzenie('g');
		}
		while (this->okno->pollEvent(this->eventGra))
		{
			if (this->eventGra.type == sf::Event::KeyReleased)
			{
				if (this->eventGra.key.code == gracz.pAtakuPiescia)
					gracz.postacGracza->atakPiescia(1);
				if (this->eventGra.key.code == gracz.pKopniecia)
					gracz.postacGracza->kopniecie(1);
				if (this->eventGra.key.code == gracz.pAtakuSpecjalnego)
					gracz.postacGracza->atakSpecjalny(1);
				if (this->eventGra.key.code == sf::Keyboard::Escape)
					this->okno->close();
			}
		}

		gracz.postacGracza->liczCzas();

		gracz.postacGracza->ruchPiescia(okno, obiekty);
		gracz.postacGracza->ruchKopniecia(okno, obiekty);
		gracz.postacGracza->ruchAtakuSpecjalnego(okno, obiekty);

		gracz.postacGracza->wykryjKolizjeZOknem(okno);
		gracz.postacGracza->wykryjKolizjeZObiektami(obiekty);
}

void CGra::pollEvents()
{
	while (this->okno->pollEvent(this->eventGra))
	{
		if (this->eventGra.type == sf::Event::KeyReleased)
		{
			if (this->eventGra.key.code == sf::Keyboard::Escape)
				this->okno->close();
		}
		if (this->eventGra.type == sf::Event::Closed)
			this->okno->close();
	}
}

void CGra::update()
{
	for (size_t i = 0; i < this->wojownicy.size(); i++)
	{
		this->wojownicy[i]->update(this->okno, this->obiekty);
	}
	this->pollEvents();
	this->zabijWojownika();
	this->zakonczGre();
}

void CGra::render()
{
	this->okno->clear(); // Czysci klatke
	//Renderuje klatke

	for (size_t i = 0; i < this->obiekty.size(); i++)
	{
		this->obiekty[i]->render(this->okno);
	}
	this->wyswietlKomunikat();
	this->okno->display();
}

void CGra::wyswietlKomunikat()
{
	if (this->koniecGry == 1)
	{
		sf::Text ogloszenieZwyciezcy;
		sf::Font czcionka;
		if (!czcionka.loadFromFile("fonts/arial.ttf"))
		{
			// W przypadku gdyby plik sie nie zaladowal
		}
		ogloszenieZwyciezcy.setFont(czcionka);
		ogloszenieZwyciezcy.setFillColor(sf::Color::White);
		ogloszenieZwyciezcy.setString(wojownicy[0]->zwrocImie() + " wygrywa!");
		ogloszenieZwyciezcy.setPosition(this->szerokoscOkna / 3, this->wysokoscOkna / 7);
		okno->draw(ogloszenieZwyciezcy);
	}
}