/**
* \file jackieChan.cpp
* \brief Plik cpp modulu JackieChan.
*
* Tutaj znajduje sie kod zrodlowy funkcji odpowiedzialnych za stworzenie obiektu klasy typu CJackieChan, wyswietlanie rzeczy z nia zwiazanych (ataki, model) oraz funkcje odpowiedzialne za wywolywanie
* atakow wojownika.
*/

#include "jackieChan.h"

void CJackieChan::inicjujZmienne(int wx, int wy, string i, int z, int sz, int szer, int wys, int w, int s)
{
	this->x = wx;
	this->y = wy;
	this->imie = i;
	this->zdrowie = z;
	this->szybkosc = sz;
	this->szerokosc = szer;
	this->wysokosc = wys;
	this->wytrzymalosc = w;
	this->sila = s;

	this->cooldownAtakuPiescia = 60;
	this->czasDoAtakuPiescia = cooldownAtakuPiescia;

	this->cooldownKopniecia = 90;
	this->czasKopniecia = cooldownKopniecia;

	this->cooldownAtakuSpecjalnego = 200;
	this->czasDoAtakuSpecjalnego = cooldownAtakuSpecjalnego;

	this->czasTrwaniaCyklu = 240;
	this->czasObecnyCyklu = czasTrwaniaCyklu;

	this->czasTrwaniaCyklu = 240;
	this->czasObecnyCyklu = this->czasTrwaniaCyklu;

	this->trybSterowania = 0;
}

void CJackieChan::inicjujModel()
{
	this->model.setPosition(x, y);
	this->model.setFillColor(sf::Color(255, 172, 28));
	this->model.setSize(sf::Vector2f(szerokosc, wysokosc));
}

CJackieChan::CJackieChan(int wx, int wy, string i, int z, int sz, int szer, int wys, int w, int s)
{
	this->inicjujZmienne(wx, wy, i, z, sz, szer, wys, w, s);
	this->inicjujModel();
}

CJackieChan::~CJackieChan()
{

}

void CJackieChan::atakPiescia(bool wykonajAtak)
{
	if (wykonajAtak == 1 && this->czasDoAtakuPiescia >= this->cooldownAtakuPiescia)
	{
		sf::RectangleShape piesc;
		piesc.setFillColor(sf::Color::Green);
		piesc.setSize(sf::Vector2f(this->szerokosc / 2, this->szerokosc / 2));

		sf::Vector2f reka;
		if (xKierunek == 1 && yKierunek == 0)
			reka = sf::Vector2f(this->model.getPosition().x + this->szerokosc / 2, this->model.getPosition().y + this->wysokosc / 2);
		if (xKierunek == -1 && yKierunek == 0)
			reka = sf::Vector2f(this->model.getPosition().x, this->model.getPosition().y);
		if (xKierunek == 0 && yKierunek == -1)
			reka = sf::Vector2f(this->model.getPosition().x + this->szerokosc / 2, this->model.getPosition().y);
		if (xKierunek == 0 && yKierunek == 1)
			reka = sf::Vector2f(this->model.getPosition().x, this->model.getPosition().y + this->wysokosc / 2);

		if (wykonajAtak == 1 && this->czasDoAtakuPiescia >= this->cooldownAtakuPiescia);
		{
			if (piesci.size() == 0)
			{
				this->xKierunkiPiesci.push_back(this->xKierunek);
				this->yKierunkiPiesci.push_back(this->yKierunek);
				piesc.setPosition(reka);
				piesci.push_back(piesc);
			}
			else
			{
				this->xKierunkiPiesci.push_back(this->xKierunek);
				this->yKierunkiPiesci.push_back(this->yKierunek);
				this->piesci.erase(piesci.begin());
				piesc.setPosition(reka);
				this->piesci.push_back(piesc);
			}
		}
		this->czasDoAtakuPiescia = 0;
	}

}

void CJackieChan::ruchPiescia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele)
{
	if (!cele.empty() && !this->piesci.empty())
	{
		for (size_t i = 0; i < this->piesci.size(); i++)
		{
			this->piesci[i].move(this->predkoscPiesci * this->xKierunkiPiesci[i] * this->szybkosc, this->predkoscPiesci * this->yKierunkiPiesci[i] * this->szybkosc);

			if (this->piesci[i].getPosition().y < 0 || this->piesci[i].getPosition().y > okno->getSize().y || this->piesci[i].getPosition().x < 0 || this->piesci[i].getPosition().x > okno->getSize().x || !this->piesci[i].getGlobalBounds().intersects(this->model.getGlobalBounds()))
			{
				this->xKierunkiPiesci.erase(this->xKierunkiPiesci.begin() + i);
				this->yKierunkiPiesci.erase(this->yKierunkiPiesci.begin() + i);
				this->piesci.erase(this->piesci.begin() + i);
			}
		}
		for (size_t i = 0; i < cele.size(); i++)
		{
			for (size_t k = 0; k < this->piesci.size(); k++)
				if (this->piesci[k].getGlobalBounds().intersects(cele[i]->model.getGlobalBounds()))
				{
					if (instanceof<CPrzeszkoda>(cele[i]))
					{
						this->piesci.erase(this->piesci.begin() + k);
						this->xKierunkiPiesci.erase(this->xKierunkiPiesci.begin() + k);
						this->yKierunkiPiesci.erase(this->yKierunkiPiesci.begin() + k);
						break;
					}
					if (instanceof<CWojownik>(cele[i]) && !instanceof<CJackieChan>(cele[i]))
					{
						cele[i]->przyjmijObrazenia(this->sila);

						this->piesci.erase(this->piesci.begin() + k);
						this->xKierunkiPiesci.erase(this->xKierunkiPiesci.begin() + k);
						this->yKierunkiPiesci.erase(this->yKierunkiPiesci.begin() + k);
						cout << cele[i]->zwrocZdrowie() << " " << cele[i]->zwrocImie() << endl;
						break;
					}
				}
		}
	}
}

void CJackieChan::kopniecie(bool wykonajAtak)
{
	if (wykonajAtak == 1 && this->czasKopniecia >= this->cooldownKopniecia)
	{
		sf::RectangleShape noga;
		noga.setFillColor(sf::Color::White);

		sf::Vector2f biodro;
		if (this->xKierunek == 1 && this->yKierunek == 0)
		{
			biodro = sf::Vector2f(this->model.getPosition().x + this->szerokosc / 2, this->model.getPosition().y);
			noga.setSize(sf::Vector2f(this->szerokosc / 1.5, this->wysokosc / 2));
		}
		if (this->xKierunek == -1 && this->yKierunek == 0)
		{
			biodro = sf::Vector2f(this->model.getPosition().x, this->model.getPosition().y + this->wysokosc / 2);
			noga.setSize(sf::Vector2f(this->szerokosc / 1.5, this->wysokosc / 2));
		}
		if (this->xKierunek == 0 && this->yKierunek == -1)
		{
			biodro = sf::Vector2f(this->model.getPosition().x, this->model.getPosition().y);
			noga.setSize(sf::Vector2f(this->szerokosc / 2, this->wysokosc / 1.5));
		}
		if (this->xKierunek == 0 && this->yKierunek == 1)
		{
			biodro = sf::Vector2f(this->model.getPosition().x + this->szerokosc / 2, this->model.getPosition().y + this->wysokosc / 2);
			noga.setSize(sf::Vector2f(this->szerokosc / 2, this->wysokosc / 1.5));
		}

		if (wykonajAtak == 1 && this->czasKopniecia >= this->cooldownKopniecia)
		{
			if (this->nogi.size() == 0)
			{
				this->xKierunkiNog.push_back(this->xKierunek);
				this->yKierunkiNog.push_back(this->yKierunek);
				noga.setPosition(biodro);
				this->nogi.push_back(noga);
			}
			else
			{
				this->xKierunkiNog.push_back(this->xKierunek);
				this->yKierunkiNog.push_back(this->yKierunek);
				this->nogi.erase(nogi.begin());
				noga.setPosition(biodro);
				this->nogi.push_back(noga);
			}
		}
		this->czasKopniecia = 0;
	}
}

void CJackieChan::ruchKopniecia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele)
{
	for (size_t i = 0; i < nogi.size(); i++)
	{
		this->nogi[i].move(this->predkoscNogi * this->xKierunkiNog[i] * this->szybkosc, this->predkoscNogi * this->yKierunkiNog[i] * this->szybkosc);

		if (this->nogi[i].getPosition().y < 0 || this->nogi[i].getPosition().y > okno->getSize().y || this->nogi[i].getPosition().x < 0 || this->nogi[i].getPosition().x > okno->getSize().x || !this->nogi[i].getGlobalBounds().intersects(this->model.getGlobalBounds()))
		{
			this->xKierunkiNog.erase(this->xKierunkiNog.begin() + i);
			this->yKierunkiNog.erase(this->yKierunkiNog.begin() + i);
			this->nogi.erase(this->nogi.begin() + i);
		}
	}
	if (!cele.empty() && !this->nogi.empty())
	{
		for (size_t i = 0; i < cele.size(); i++)
		{
			for (size_t k = 0; k < this->nogi.size(); k++)
				if (this->nogi[k].getGlobalBounds().intersects(cele[i]->model.getGlobalBounds()))
				{
					if (instanceof<CPrzeszkoda>(cele[i]))
					{
						this->nogi.erase(this->nogi.begin() + k);
						this->xKierunkiNog.erase(this->xKierunkiNog.begin() + k);
						this->yKierunkiNog.erase(this->yKierunkiNog.begin() + k);
						break;
					}
					if (instanceof<CWojownik>(cele[i]) && !instanceof<CJackieChan>(cele[i]))
					{
						cele[i]->przyjmijObrazenia(1.2 * this->sila);

						this->nogi.erase(this->nogi.begin() + k);
						this->xKierunkiNog.erase(this->xKierunkiNog.begin() + k);
						this->yKierunkiNog.erase(this->yKierunkiNog.begin() + k);
						cout << cele[i]->zwrocZdrowie() << " " << cele[i]->zwrocImie() << endl;
						break;
					}
				}
		}
	}
}

void CJackieChan::atakSpecjalny(bool wykonajAtak)
{
	if (wykonajAtak == 1 && this->czasDoAtakuSpecjalnego >= this->cooldownAtakuSpecjalnego)
	{
		sf::RectangleShape atakSpecjalny;
		atakSpecjalny.setFillColor(sf::Color::Magenta);
		atakSpecjalny.setSize(sf::Vector2f(this->szerokosc / 1.25, this->szerokosc / 1.25));

		sf::Vector2f reka;
		if (xKierunek == 1 && yKierunek == 0)
			reka = sf::Vector2f(this->model.getPosition().x + this->szerokosc / 2, this->model.getPosition().y + this->wysokosc / 2);
		if (xKierunek == -1 && yKierunek == 0)
			reka = sf::Vector2f(this->model.getPosition().x, this->model.getPosition().y);
		if (xKierunek == 0 && yKierunek == -1)
			reka = sf::Vector2f(this->model.getPosition().x + this->szerokosc / 2, this->model.getPosition().y);
		if (xKierunek == 0 && yKierunek == 1)
			reka = sf::Vector2f(this->model.getPosition().x, this->model.getPosition().y + this->wysokosc / 2);

		if (wykonajAtak == 1 && this->czasDoAtakuSpecjalnego >= this->cooldownAtakuSpecjalnego);
		{
			if (atakiSpecjalne.size() == 0)
			{
				this->xKierunkiAtakowSpecjalnych.push_back(this->xKierunek);
				this->yKierunkiAtakowSpecjalnych.push_back(this->yKierunek);
				atakSpecjalny.setPosition(reka);
				this->atakiSpecjalne.push_back(atakSpecjalny);
			}
			else
			{
				this->xKierunkiAtakowSpecjalnych.push_back(this->xKierunek);
				this->yKierunkiAtakowSpecjalnych.push_back(this->yKierunek);
				this->piesci.erase(piesci.begin());
				atakSpecjalny.setPosition(reka);
				this->atakiSpecjalne.push_back(atakSpecjalny);
			}
		}
		this->czasDoAtakuSpecjalnego = 0;
	}
}

void CJackieChan::ruchAtakuSpecjalnego(const sf::RenderTarget* okno, std::vector<CObiekt*> cele)
{
	if (!cele.empty() && !this->atakiSpecjalne.empty())
	{
		for (size_t i = 0; i < this->atakiSpecjalne.size(); i++)
		{
			this->atakiSpecjalne[i].move(this->predkoscPiesci * this->xKierunkiAtakowSpecjalnych[i] * this->szybkosc, this->predkoscPiesci * this->yKierunkiAtakowSpecjalnych[i] * this->szybkosc);

			if (this->atakiSpecjalne[i].getPosition().y < 0 || this->atakiSpecjalne[i].getPosition().y > okno->getSize().y || this->atakiSpecjalne[i].getPosition().x < 0 || this->atakiSpecjalne[i].getPosition().x > okno->getSize().x || !this->atakiSpecjalne[i].getGlobalBounds().intersects(this->model.getGlobalBounds()))
			{
				this->xKierunkiAtakowSpecjalnych.erase(this->xKierunkiAtakowSpecjalnych.begin() + i);
				this->yKierunkiAtakowSpecjalnych.erase(this->yKierunkiAtakowSpecjalnych.begin() + i);
				this->atakiSpecjalne.erase(this->atakiSpecjalne.begin() + i);
			}
		}
		for (size_t i = 0; i < cele.size(); i++)
		{
			for (size_t k = 0; k < this->atakiSpecjalne.size(); k++)
				if (this->atakiSpecjalne[k].getGlobalBounds().intersects(cele[i]->model.getGlobalBounds()))
				{
					if (instanceof<CPrzeszkoda>(cele[i]))
					{
						this->atakiSpecjalne.erase(this->atakiSpecjalne.begin() + k);
						this->xKierunkiAtakowSpecjalnych.erase(this->xKierunkiAtakowSpecjalnych.begin() + k);
						this->yKierunkiAtakowSpecjalnych.erase(this->yKierunkiAtakowSpecjalnych.begin() + k);
						break;
					}
					if (instanceof<CWojownik>(cele[i]) && !instanceof<CJackieChan>(cele[i]))
					{
						cele[i]->przyjmijObrazenia(this->sila);

						this->atakiSpecjalne.erase(this->atakiSpecjalne.begin() + k);
						this->xKierunkiAtakowSpecjalnych.erase(this->xKierunkiAtakowSpecjalnych.begin() + k);
						this->yKierunkiAtakowSpecjalnych.erase(this->yKierunkiAtakowSpecjalnych.begin() + k);
						cout << cele[i]->zwrocZdrowie() << " " << cele[i]->zwrocImie() << endl;
						break;
					}
				}
		}
	}
}

void CJackieChan::chodzenie(char stronaRuchu)
{
	switch (stronaRuchu)
	{
		//Ruch w lewo
	case 'l':
	{
		this->model.move(-this->szybkosc, 0.f);
		this->xKierunek = -1;
		this->yKierunek = 0;
		for (size_t i = 0; i < piesci.size(); i++)
		{
			if (this->xKierunkiPiesci[i] == -1);
			this->piesci[i].move(this->xKierunkiPiesci[i] * (this->szybkosc + this->predkoscPiesci), 0.f);
		}
		for (size_t i = 0; i < nogi.size(); i++)
		{
			if (this->xKierunkiNog[i] == -1);
			this->nogi[i].move(this->xKierunkiNog[i] * (this->szybkosc + this->predkoscNogi), 0.f);
		}
		for (size_t i = 0; i < atakiSpecjalne.size(); i++)
		{
			if (this->xKierunkiAtakowSpecjalnych[i] == -1);
			this->atakiSpecjalne[i].move(this->xKierunkiAtakowSpecjalnych[i] * (this->szybkosc + this->predkoscPiesci), 0.f);
		}
		break;
	}
	//Ruch w prawo
	case 'p':
	{
		this->model.move(this->szybkosc, 0.f);
		this->xKierunek = 1;
		this->yKierunek = 0;
		for (size_t i = 0; i < this->piesci.size(); i++)
		{
			if (this->xKierunkiPiesci[i] == 1);
			this->piesci[i].move(this->xKierunkiPiesci[i] * (this->szybkosc + this->predkoscPiesci), 0.f);
		}
		for (size_t i = 0; i < this->nogi.size(); i++)
		{
			if (this->xKierunkiNog[i] == 1);
			this->nogi[i].move(this->xKierunkiNog[i] * (this->szybkosc + this->predkoscNogi), 0.f);
		}
		for (size_t i = 0; i < atakiSpecjalne.size(); i++)
		{
			if (this->xKierunkiAtakowSpecjalnych[i] == 1);
			this->atakiSpecjalne[i].move(this->xKierunkiAtakowSpecjalnych[i] * (this->szybkosc + this->predkoscPiesci), 0.f);
		}
		break;
	}
	case 'g':
		//Ruch w gore
	{
		this->model.move(0.f, -this->szybkosc);
		this->yKierunek = -1;
		this->xKierunek = 0;
		for (size_t i = 0; i < piesci.size(); i++)
		{
			if (this->yKierunkiPiesci[i] == -1);
			this->piesci[i].move(0.f, this->yKierunkiPiesci[i] * (this->szybkosc + this->predkoscPiesci));
		}
		for (size_t i = 0; i < nogi.size(); i++)
		{
			if (this->yKierunkiNog[i] == -1);
			this->nogi[i].move(0.f, this->yKierunkiNog[i] * (this->szybkosc + this->predkoscNogi));
		}
		for (size_t i = 0; i < atakiSpecjalne.size(); i++)
		{
			if (this->yKierunkiAtakowSpecjalnych[i] == -1);
			this->atakiSpecjalne[i].move(0.f, this->yKierunkiAtakowSpecjalnych[i] * (this->szybkosc + this->predkoscPiesci));
		}
		break;
	}
	//Ruch w dol
	case 'd':
	{
		this->model.move(0.f, this->szybkosc);
		this->yKierunek = 1;
		this->xKierunek = 0;
		for (size_t i = 0; i < piesci.size(); i++)
		{
			if (yKierunkiPiesci[i] == 1);
			this->piesci[i].move(0.f, this->yKierunkiPiesci[i] * (this->szybkosc + this->predkoscPiesci));
		}
		for (size_t i = 0; i < nogi.size(); i++)
		{
			if (yKierunkiNog[i] == 1);
			this->nogi[i].move(0.f, this->yKierunkiNog[i] * (this->szybkosc + this->predkoscNogi));
		}
		for (size_t i = 0; i < atakiSpecjalne.size(); i++)
		{
			if (this->yKierunkiAtakowSpecjalnych[i] == 1);
			this->atakiSpecjalne[i].move(0.f, this->yKierunkiAtakowSpecjalnych[i] * (this->szybkosc + this->predkoscPiesci));
		}
		break;
	}
	}
}

float CJackieChan::obliczDystans(sf::FloatRect wojownik, sf::FloatRect obiekt)
{
	return sqrtf((wojownik.left - obiekt.left) * (wojownik.left - obiekt.left) + (wojownik.top - obiekt.top) * (wojownik.top - obiekt.top));
}

void CJackieChan::liczCzas()
{
	if (this->czasDoAtakuPiescia < this->cooldownAtakuPiescia)
		this->czasDoAtakuPiescia++;
	if (this->czasKopniecia < this->cooldownKopniecia)
		this->czasKopniecia++;
	if (this->czasDoAtakuSpecjalnego < this->cooldownAtakuSpecjalnego)
		this->czasDoAtakuSpecjalnego++;
	if (this->czasObecnyCyklu < this->czasTrwaniaCyklu)
		this->czasObecnyCyklu++;
	if (this->czasObecnyCyklu >= this->czasTrwaniaCyklu)
		this->czasObecnyCyklu = 0;
}

void CJackieChan::wykryjKolizjeZObiektami(std::vector<CObiekt*> obiekty)
{
	for (size_t i = 0; i < obiekty.size(); i++)
	{
		sf::FloatRect granicePostaci = this->model.getGlobalBounds();
		sf::FloatRect graniceObiektu = obiekty[i]->model.getGlobalBounds();

		if (!instanceof<CSkrzynia>(obiekty[i]))
			if (graniceObiektu.intersects(granicePostaci))
			{
				//Prawa strona
				if (granicePostaci.left < graniceObiektu.left && granicePostaci.left + this->szerokosc < graniceObiektu.left + obiekty[i]->zwrocSzerokosc()
					&& granicePostaci.top < graniceObiektu.top + obiekty[i]->zwrocWysokosc() && granicePostaci.top + this->wysokosc > graniceObiektu.top)
				{
					this->model.setPosition(graniceObiektu.left - this->szerokosc, granicePostaci.top);
				}
				//Lewa strona
				else if (granicePostaci.left > graniceObiektu.left && granicePostaci.left + this->szerokosc > graniceObiektu.left + obiekty[i]->zwrocSzerokosc()
					&& granicePostaci.top < graniceObiektu.top + obiekty[i]->zwrocWysokosc() && granicePostaci.top + this->wysokosc > graniceObiektu.top)
				{
					this->model.setPosition(graniceObiektu.left + obiekty[i]->zwrocSzerokosc() , granicePostaci.top);
				}
				//Gorna strona
				else if (granicePostaci.top > graniceObiektu.top && granicePostaci.top + this->wysokosc > graniceObiektu.top + obiekty[i]->zwrocWysokosc()
					&& granicePostaci.left < graniceObiektu.left + obiekty[i]->zwrocSzerokosc() && granicePostaci.left + this->szerokosc > graniceObiektu.left)
				{
					this->model.setPosition(granicePostaci.left, graniceObiektu.top + obiekty[i]->zwrocWysokosc());
				}
				//Dolna strona
				else if (granicePostaci.top < graniceObiektu.top && granicePostaci.top + this->wysokosc < graniceObiektu.top + obiekty[i]->zwrocWysokosc()
					&& granicePostaci.left < graniceObiektu.left + obiekty[i]->zwrocSzerokosc() && granicePostaci.left + this->szerokosc > graniceObiektu.left)
				{
					this->model.setPosition(granicePostaci.left, graniceObiektu.top - this->wysokosc);
				}
			}
	}
}

void CJackieChan::wykryjKolizjeZOknem(const sf::RenderTarget* okno)
{
	//Lewa strona okna
	if (this->model.getGlobalBounds().left <= 0.f)
		this->model.setPosition(0.f, this->model.getGlobalBounds().top);
	//Prawa strona okna
	if (this->model.getGlobalBounds().left + szerokosc >= okno->getSize().x)
		this->model.setPosition(okno->getSize().x - szerokosc, this->model.getGlobalBounds().top);
	//Gorna strona okna
	if (this->model.getGlobalBounds().top <= 0.f)
		this->model.setPosition(this->model.getGlobalBounds().left, 0.f);
	//Dolna strona okna
	if (this->model.getGlobalBounds().top + wysokosc >= okno->getSize().y)
		this->model.setPosition(this->model.getGlobalBounds().left, okno->getSize().y - wysokosc);
}

void CJackieChan::update(const sf::RenderTarget* okno, std::vector<CObiekt*> obiekty)
{
	if (trybSterowania != 1)
	{
		int zasieg = 500;
		sf::FloatRect granicePostaci = this->model.getGlobalBounds();
		sf::FloatRect srodekPostaci;
		srodekPostaci.left = granicePostaci.left + this->szerokosc / 2;
		srodekPostaci.top = granicePostaci.top + this->wysokosc / 2;

		for (size_t i = 0; i < obiekty.size(); i++)
		{
			sf::FloatRect graniceObiektu = obiekty[i]->model.getGlobalBounds();
			sf::FloatRect srodekObiektu;
			{
				srodekObiektu.left = graniceObiektu.left + obiekty[i]->zwrocSzerokosc() / 2;
				srodekObiektu.top = graniceObiektu.top + obiekty[i]->zwrocWysokosc() / 2;
			}

			if (!instanceof<CJackieChan>(obiekty[i]))
			{
				if (instanceof<CWojownik>(obiekty[i]))
				{
					if (obliczDystans(srodekObiektu, srodekPostaci) > zasieg)
					{
						if (czasObecnyCyklu >= 0 && czasObecnyCyklu < 50)
							chodzenie('l');
						else if (czasObecnyCyklu >= 50 && czasObecnyCyklu < 110)
							chodzenie('d');
						else if (czasObecnyCyklu >= 130 && czasObecnyCyklu < 165)
							chodzenie('p');
						else if (czasObecnyCyklu >= 165 && czasObecnyCyklu < czasTrwaniaCyklu)
							chodzenie('g');
					}
					else if (obliczDystans(srodekPostaci, srodekObiektu) <= zasieg && czasDoAtakuSpecjalnego > cooldownAtakuSpecjalnego / 2)
					{
						{
							{
								if (srodekObiektu.left > srodekPostaci.left + this->szerokosc / 2)
									chodzenie('p');
								if (srodekObiektu.left + obiekty[i]->zwrocSzerokosc() / 2 < srodekPostaci.left)
									chodzenie('l');
								if (srodekObiektu.top + obiekty[i]->zwrocWysokosc() / 2 < srodekPostaci.top)
									chodzenie('g');
								if (srodekObiektu.top > srodekPostaci.top + this->wysokosc / 2)
									chodzenie('d');
							}
						}

					}
					else if (obliczDystans(srodekPostaci, srodekObiektu) <= zasieg && czasDoAtakuSpecjalnego <= cooldownAtakuSpecjalnego / 2)
					{
						if (srodekObiektu.left > srodekPostaci.left + this->szerokosc / 2)
							chodzenie('l');
						if (srodekObiektu.left + obiekty[i]->zwrocSzerokosc() / 2 < srodekPostaci.left)
							chodzenie('p');
						if (srodekObiektu.top + obiekty[i]->zwrocWysokosc() / 2 < srodekPostaci.top)
							chodzenie('d');
						if (srodekObiektu.top > srodekPostaci.top + this->wysokosc / 2)
							chodzenie('g');
					}
					if (obliczDystans(srodekPostaci, srodekObiektu) < obiekty[i]->zwrocSzerokosc() + this->szerokosc)
					{
						this->atakSpecjalny(1);
						this->atakPiescia(1);
						if (this->czasDoAtakuPiescia < this->cooldownAtakuPiescia)
							this->kopniecie(1);
					}
				}
			}
		}
	}

	this->ruchPiescia(okno, obiekty);
	this->ruchKopniecia(okno, obiekty);
	this->ruchAtakuSpecjalnego(okno, obiekty);
	this->liczCzas();
	this->wykryjKolizjeZOknem(okno);
	this->wykryjKolizjeZObiektami(obiekty);
}

void CJackieChan::przyjmijObrazenia(int liczbaObrazen)
{
	if (liczbaObrazen - this->wytrzymalosc <= 0)
		this->zdrowie = (this->zdrowie - 1);
	else
		this->zdrowie = (this->zdrowie - liczbaObrazen + this->wytrzymalosc);
}

void CJackieChan::renderAtakPiescia(sf::RenderTarget* okno)
{
	for (size_t i = 0; i < this->piesci.size(); i++)
	{
		okno->draw(this->piesci[i]);
	}
}

void CJackieChan::renderKopniecie(sf::RenderTarget* okno)
{
	for (size_t i = 0; i < this->nogi.size(); i++)
	{
		okno->draw(this->nogi[i]);
	}
}

void CJackieChan::renderAtakSpecjalny(sf::RenderTarget* okno)
{
	for (size_t i = 0; i < this->atakiSpecjalne.size(); i++)
	{
		okno->draw(this->atakiSpecjalne[i]);
	}
}

void CJackieChan::render(sf::RenderTarget* target)
{
	target->draw(this->model);
	this->renderAtakPiescia(target);
	this->renderKopniecie(target);
	this->renderAtakSpecjalny(target);
}