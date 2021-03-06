// GA2.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h> 
#include <crtdbg.h>  
#include "stdafx.h"
#include "Population.h"
#include <iostream>
#include "string"
#include <fstream>
#include <ctime>

void saveToFile(string, vector<int>, vector<int>, vector<int>, int, int, double, double, int, string);
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	srand(time(0));

	int POP_SIZE = 300;
	int GEN = 300;
	double P_X = 0.8;
	double P_M = 0.08;
	int TOUR = 10;
	string FILE_NAME;

	cout << "Parametry do algorytmu: " << endl;
	cout << endl << "popSize = ";
	cin >> POP_SIZE;
	cout << endl << "gen = ";
	cin >> GEN;
	cout << endl << "Px = ";
	cin >> P_X;
	cout << endl << "Pm = ";
	cin >> P_M;
	cout << endl << "Tour = ";
	cin >> TOUR;
	cout << endl << "Nazwa pliku = ";
	cin >> FILE_NAME;
	cout << endl;

		Population* pop = new Population(TOUR, POP_SIZE, P_M, P_X, FILE_NAME);
		vector<int> bestest;
		vector<int> worstest;
		vector<int> avarages;
		int generation = 0;

		while (generation < GEN) {
			cout << endl << "GNERACJA " << generation + 1 << endl;

			pop->evaluate();
			if (generation == 0) {
				cout << "Losowy: ";
				pop->getBest();
				cout << endl;
				cout << "Zachlanny ";
				pop->greedyAlghoritm();
				cout << endl;
				cout << "Wciśnij klawisz do kontynuowania algorytmu" << endl;
				int a;
				cin >> a;
			}
			bestest.push_back(pop->getBest());
			worstest.push_back(pop->getWorst());
			avarages.push_back(pop->getAvarage());

			pop->selection();
			pop->crossover();
			pop->mutation();

			generation++;
		}

		string CSV_FILE = "GA - " + to_string(POP_SIZE) + " - " + to_string(GEN) + " - " + to_string(P_M) + " - " + to_string(P_X) + ".csv";
		saveToFile(CSV_FILE, bestest, avarages, worstest, POP_SIZE, GEN, P_M, P_X, TOUR, FILE_NAME);
		if (pop) {
			delete pop;
		}
	system("pause");
	return 0;
}
void saveToFile(string csv, vector<int> data1, vector<int> data2, vector<int> data3, int pop_size, int gen, double Pm, double Px, int tour, string file_name) {
	ofstream myfile;
	myfile.open(csv);
	myfile << pop_size << ";" << gen << ";" << Pm << ";" << Px << ";" << tour << ";" << file_name<< endl;

	for (int i = 0; i < data1.size(); i++)
	{
		myfile << data1[i] << ";" << data2[i] << ";" << data3[i] << endl;
	}
	
	myfile.close();
}

