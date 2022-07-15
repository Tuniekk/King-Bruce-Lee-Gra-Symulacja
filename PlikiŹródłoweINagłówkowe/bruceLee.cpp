/**
* \file bruceLee.cpp
* \brief Plik cpp modulu BruceLee.
*
* Tutaj znajduje sie kod zrodlowy funkcji odpowiedzialnych za stworzenie obiektu klasy typu CBruceLee, wyswietlanie rzeczy z nia zwiazanych (ataki, model) oraz funkcje odpowiedzialne za wywolywanie
* atakow wojownika.
*/

#include "bruceLee.h"

void CBruceLee::inicjujZmienne(int wx, int wy, string i, int z, int sz, int szer, int wys, int w, int s)
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
	this->czasDoAtakuPiescia = this->cooldownAtakuPiescia;

	this->cooldownKopniecia = 120;
	this->czasKopniecia = this->cooldownKopniecia;

	this->cooldownAtakuSpecjalnego = 60;
	this->czasDoAtakuSpecjalnego = this->cooldownAtakuSpecjalnego;

	this->czasTrwaniaCyklu = 240;
	this->czasObecnyCyklu = czasTrwaniaCyklu;

	this->trybSterowania = 0;
}

void CBruceLee::inicjujModel()
{
	this->model.setPosition(x, y);
	this->model.setFillColor(sf::Color::Yellow);
	this->model.setSize(sf::Vector2f(this->szerokosc, this->wysokosc));
}

CBruceLee::CBruceLee(int wx, int wy, string i, int z, int sz, int szer, int wys, int w, int s)
{
	this->inicjujZmienne(wx, wy, i, z, sz, szer, wys, w, s);
	this->inicjujModel();
}

CBruceLee::~CBruceLee()
{

}
 
void CBruceLee::atakPiescia(bool wykonajAtak)
{
	if (wykonajAtak == 1 && this->czasDoAtakuPiescia >= this->cooldownAtakuPiescia)
	{
		sf::RectangleShape piesc;
		piesc.setFillColor(sf::Color::Green);
		piesc.setSize(sf::Vector2f(this->szerokosc / 2, this->szerokosc / 2));

		sf::Vector2f reka;
		if (this->xKierunek == 1 && this->yKierunek == 0)
			reka = sf::Vector2f(this->model.getPosition().x + this->szerokosc / 2, this->model.getPosition().y + this->wysokosc / 2);
		if (this->xKierunek == -1 && this->yKierunek == 0)
			reka = sf::Vector2f(this->model.getPosition().x, this->model.getPosition().y);
		if (this->xKierunek == 0 && this->yKierunek == -1)
			reka = sf::Vector2f(this->model.getPosition().x + this->szerokosc / 2, this->model.getPosition().y);
		if (this->xKierunek == 0 && this->yKierunek == 1)
			reka = sf::Vector2f(this->model.getPosition().x, this->model.getPosition().y + this->wysokosc / 2);

		if (wykonajAtak == 1 && this->czasDoAtakuPiescia >= this->cooldownAtakuPiescia);
		{
			if (this->piesci.size() == 0)
			{
				this->xKierunkiPiesci.push_back(this->xKierunek);
				this->yKierunkiPiesci.push_back(this->yKierunek);
				piesc.setPosition(reka);
				this->piesci.push_back(piesc);
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

void CBruceLee::ruchPiescia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele)
{
	for (size_t i = 0; i < piesci.size(); i++)
	{
		this->piesci[i].move(this->predkoscPiesci * this->xKierunkiPiesci[i] * this->szybkosc, this->predkoscPiesci * this->yKierunkiPiesci[i] * this->szybkosc);

		if (this->piesci[i].getPosition().y < 0 || this->piesci[i].getPosition().y > okno->getSize().y || this->piesci[i].getPosition().x < 0 || this->piesci[i].getPosition().x > okno->getSize().x || !this->piesci[i].getGlobalBounds().intersects(this->model.getGlobalBounds()))
		{
			this->xKierunkiPiesci.erase(this->xKierunkiPiesci.begin() + i);
			this->yKierunkiPiesci.erase(this->yKierunkiPiesci.begin() + i);
			this->piesci.erase(this->piesci.begin() + i);
		}
	}
	if (!cele.empty() && !this->piesci.empty())
	{
		for (size_t i = 0; i < cele.size(); i++)
		{
			for (size_t k = 0; k < piesci.size(); k++)
				if (this->piesci[k].getGlobalBounds().intersects(cele[i]->model.getGlobalBounds()))
				{
					if (instanceof<CPrzeszkoda>(cele[i]))
					{
						this->piesci.erase(this->piesci.begin() + k);
						this->xKierunkiPiesci.erase(this->xKierunkiPiesci.begin() + k);
						this->yKierunkiPiesci.erase(this->yKierunkiPiesci.begin() + k);
						break;
					}
					if (instanceof<CWojownik>(cele[i]) && !instanceof<CBruceLee>(cele[i]))
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

void CBruceLee::kopniecie(bool wykonajAtak)
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

void CBruceLee::ruchKopniecia(const sf::RenderTarget* okno, std::vector<CObiekt*> cele)
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
					if (instanceof<CWojownik>(cele[i]) && !instanceof<CBruceLee>(cele[i]))
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

void CBruceLee::atakSpecjalny(bool wykonajAtak)
{
	if (wykonajAtak == 1 && czasDoAtakuSpecjalnego >= cooldownAtakuSpecjalnego)
	{
		sf::CircleShape szuriken;
		szuriken.setFillColor(sf::Color::Magenta);
		szuriken.setRadius(this->szerokosc / 4);

		sf::Vector2f srodekPostaci = sf::Vector2f(this->model.getPosition().x + this->szerokosc / 4, this->model.getPosition().y + this->wysokosc / 4);
	
		if (wykonajAtak == 1 && this->czasDoAtakuSpecjalnego >= this->cooldownAtakuSpecjalnego)
		{
			this->xKierunkiAtakowSpecjalnych.push_back(this->xKierunek);
			this->yKierunkiAtakowSpecjalnych.push_back(this->yKierunek);
			szuriken.setPosition(srodekPostaci);
			this->szurikeny.push_back(szuriken);
		}
;		this->czasDoAtakuSpecjalnego = 0;
	}
}

void CBruceLee::ruchAtakuSpecjalnego(const sf::RenderTarget* okno, std::vector<CObiekt*> cele)
{
		for (size_t i = 0; i < this->szurikeny.size(); i++)
		{
			this->szurikeny[i].move(this->xKierunkiAtakowSpecjalnych[i] * 1.5 * this->szybkosc, this->yKierunkiAtakowSpecjalnych[i] * 1.5 * this->szybkosc);

			if (this->szurikeny[i].getPosition().y < 0 || this->szurikeny[i].getPosition().y > okno->getSize().y || this->szurikeny[i].getPosition().x < 0 || this->szurikeny[i].getPosition().x > okno->getSize().x)
			{
				this->szurikeny.erase(this->szurikeny.begin() + i);
				this->xKierunkiAtakowSpecjalnych.erase(this->xKierunkiAtakowSpecjalnych.begin() + i);
				this->yKierunkiAtakowSpecjalnych.erase(this->yKierunkiAtakowSpecjalnych.begin() + i);
			}
		}
		if (!cele.empty() && !this->szurikeny.empty())
		{
			for (size_t i = 0; i < cele.size(); i++)
			{
				for (size_t k = 0; k < this->szurikeny.size(); k++)
					if (this->szurikeny[k].getGlobalBounds().intersects(cele[i]->model.getGlobalBounds()))
					{
						if (instanceof<CPrzeszkoda>(cele[i]))
						{
							this->szurikeny.erase(szurikeny.begin() + k);
							this->xKierunkiAtakowSpecjalnych.erase(this->xKierunkiAtakowSpecjalnych.begin() + k);
							this->yKierunkiAtakowSpecjalnych.erase(this->yKierunkiAtakowSpecjalnych.begin() + k);
							break;
						}
						if (instanceof<CWojownik>(cele[i]) && !instanceof<CBruceLee>(cele[i]))
						{
							cele[i]->przyjmijObrazenia(this->sila / 4);

							this->szurikeny.erase(this->szurikeny.begin() + k);
							this->xKierunkiAtakowSpecjalnych.erase(this->xKierunkiAtakowSpecjalnych.begin() + k);
							this->yKierunkiAtakowSpecjalnych.erase(this->yKierunkiAtakowSpecjalnych.begin() + k);
							cout << cele[i]->zwrocZdrowie() << " " << cele[i]->zwrocImie() << endl;
							break;

						}
					}
			}
		}
}

void CBruceLee::chodzenie(char stronaRuchu)
{
	switch (stronaRuchu)
	{
	//Ruch w lewo
	case 'l':
		{
			this->model.move(-this->szybkosc, 0.f);
			this->xKierunek = -1;
			this->yKierunek = 0;
			for (size_t i = 0; i < this->piesci.size(); i++)
			{
				if (this->xKierunkiPiesci[i] == -1 && this->yKierunkiPiesci[i] == 0);
				this->piesci[i].move(xKierunkiPiesci[i] * (this->szybkosc + this->predkoscPiesci), 0.f);
			}
			for (size_t i = 0; i < nogi.size(); i++)
			{
				if (this->xKierunkiNog[i] == -1);
				this->nogi[i].move(this->xKierunkiNog[i] * (this->szybkosc + this->predkoscNogi), 0.f);
			}
			break;
		}
		//Ruch w prawo
	case 'p':
		{
			this->model.move(this->szybkosc, 0.f);
			this->xKierunek = 1;
			this->yKierunek = 0;
			for (size_t i = 0; i < piesci.size(); i++)
			{
				if (this->xKierunkiPiesci[i] == 1 && this->yKierunkiPiesci[i] == 0);
				this->piesci[i].move(xKierunkiPiesci[i] * (this->szybkosc + this->predkoscPiesci), 0.f);;
			}
			for (size_t i = 0; i < nogi.size(); i++)
			{
				if (this->xKierunkiNog[i] == 1);
				this->nogi[i].move(this->xKierunkiNog[i] * (this->szybkosc + this->predkoscNogi), 0.f);
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
				if (this->yKierunkiPiesci[i] == -1 && this->xKierunkiPiesci[i] == 0);
				this->piesci[i].move(0.f, this->yKierunkiPiesci[i] * (this->szybkosc + this->predkoscPiesci));
			}
			for (size_t i = 0; i < nogi.size(); i++)
			{
				if (this->yKierunkiNog[i] == -1);
				this->nogi[i].move(0.f, this->yKierunkiNog[i] * (this->szybkosc + this->predkoscNogi));
			}
			break;
		}
		//Ruch w dol
	case 'd':
		{
			this->model.move(0.f, this->szybkosc);
			this->yKierunek = 1;
			this->xKierunek = 0;
			for (size_t i = 0; i < this->piesci.size(); i++)
			{
				if (this->yKierunkiPiesci[i] == 1 && this->xKierunkiPiesci[i] == 0);
				this->piesci[i].move(0.f, this->yKierunkiPiesci[i] * (this->szybkosc + this->predkoscPiesci));
			}
			for (size_t i = 0; i < nogi.size(); i++)
			{
				if (this->yKierunkiNog[i] == 1);
				this->nogi[i].move(0.f, this->yKierunkiNog[i] * (this->szybkosc + this->predkoscNogi));
			}
			break;
		}
	}
}

float CBruceLee::obliczDystans(sf::FloatRect wojownik, sf::FloatRect obiekt)
{
	return sqrtf((wojownik.left - obiekt.left) * (wojownik.left - obiekt.left) + (wojownik.top - obiekt.top) * (wojownik.top - obiekt.top));
}

void CBruceLee::liczCzas()
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

void CBruceLee::wykryjKolizjeZOknem(const sf::RenderTarget* okno)
{
	//Lewa strona okna
	if (this->model.getGlobalBounds().left <= 0)
		this->model.setPosition(0.f, this->model.getGlobalBounds().top);
	//Prawa strona okna
	if (this->model.getGlobalBounds().left + this->szerokosc >= okno->getSize().x)
		this->model.setPosition(okno->getSize().x - this->szerokosc, this->model.getGlobalBounds().top);
	//Gorna strona okna
	if (this->model.getGlobalBounds().top <= 0.f)
		this->model.setPosition(this->model.getGlobalBounds().left, 0.f);
	//Dolna strona okna
	if (this->model.getGlobalBounds().top + this->wysokosc >= okno->getSize().y)
		this->model.setPosition(this->model.getGlobalBounds().left, okno->getSize().y - this->wysokosc);
}

void CBruceLee::wykryjKolizjeZObiektami(std::vector<CObiekt*> obiekty)
{
	for (size_t i = 0; i < obiekty.size(); i++)
	{
		sf::FloatRect granicePostaci = this->model.getGlobalBounds();
		sf::FloatRect graniceObiektu = obiekty[i]->model.getGlobalBounds();

		if(!instanceof<CStol>(obiekty[i]))
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
				this->model.setPosition(graniceObiektu.left + obiekty[i]->zwrocSzerokosc(), granicePostaci.top);
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

void CBruceLee::update(const sf::RenderTarget* okno, std::vector<CObiekt*> obiekty)
{
	if (this->trybSterowania != 1)
	{
		int zasieg = 600;
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

			if (!instanceof<CBruceLee>(obiekty[i]))
			{
				if (instanceof<CWojownik>(obiekty[i]))
				{
					if (obliczDystans(srodekObiektu, srodekPostaci) > zasieg)
					{
						if (this->czasObecnyCyklu >= 0 && this->czasObecnyCyklu < 40)
							chodzenie('l');
						else if (this->czasObecnyCyklu >= 40 && this->czasObecnyCyklu < 110)
							chodzenie('d');
						else if (this->czasObecnyCyklu >= 110 && this->czasObecnyCyklu < 180)
							chodzenie('p');
						else if (this->czasObecnyCyklu >= 180 && this->czasObecnyCyklu < this->czasTrwaniaCyklu)
							chodzenie('g');
					}
					else if (obliczDystans(srodekPostaci, srodekObiektu) <= zasieg)
					{
						if (this->czasDoAtakuPiescia >= this->cooldownAtakuPiescia / 2 || this->czasKopniecia >= this->cooldownKopniecia / 2)
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
						else if (this->czasDoAtakuPiescia < this->cooldownAtakuPiescia / 2 || this->czasKopniecia < this->cooldownKopniecia / 2)
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
					}
					if (obliczDystans(srodekPostaci, srodekObiektu) < obiekty[i]->zwrocSzerokosc() + this->szerokosc)
					{
						this->atakPiescia(1);
						if (this->czasDoAtakuPiescia > this->cooldownAtakuPiescia / 1.5)
							kopniecie(1);
					}
					if (obliczDystans(srodekPostaci, srodekObiektu) >= zasieg / 2)
					{
						this->atakSpecjalny(1);
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
}

void CBruceLee::przyjmijObrazenia(int liczbaObrazen)
{
	if (liczbaObrazen - this->wytrzymalosc <= 0)
		this->zdrowie = (this->zdrowie - 1);
	else
		this->zdrowie = (this->zdrowie - liczbaObrazen + this->wytrzymalosc);
}

void CBruceLee::renderSzurikeny(sf::RenderTarget* okno)
{
	for (size_t i = 0; i < this->szurikeny.size(); i++)
	{
		okno->draw(this->szurikeny[i]);
	}
}

void CBruceLee::renderAtakPiescia(sf::RenderTarget* okno)
{
	for (size_t i = 0; i < this->piesci.size(); i++)
	{
		okno->draw(this->piesci[i]);
	}
}

void CBruceLee::renderKopniecie(sf::RenderTarget* okno)
{
	for (size_t i = 0; i < this->nogi.size(); i++)
	{
		okno->draw(this->nogi[i]);
	}
}

void CBruceLee::render(sf::RenderTarget* target)
{
	target->draw(this->model);
	renderSzurikeny(target);
	renderAtakPiescia(target);
	renderKopniecie(target);
}
