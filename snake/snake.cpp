// snake.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>

#include "Map.h"
#include "MapBuilder.h"

class Player
{
public:
	Player() {}


};



/*
ostream &operator << (ostream & os, const MapHandler& mh)
{
	for (const auto & row : MapHandler.m_map)
	{
		os << row;

	}
	return os;
}*/

int main()
{
	Map<char> map{ 10, 20, '='};
	std::cout << map << "\n";
	MapBuilder::generateMap<Map<char>, char>(map);

	std::cout << map << "\n";
	//mh.generateMapBorders('=', ' ');
//	mh.generateMap();
	//std::cout << map << std::endl;
}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
