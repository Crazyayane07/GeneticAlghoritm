#include "stdafx.h"
#include "Population.h"
#include <fstream>
#include <iostream>

Population::Population(int tour, int popSize, double Pm, double Px, string fileName)
{
	this->tour = tour;
	this->pop_size = popSize;
	this->Px = Px;
	this->Pm = Pm;
	this->fileName = fileName;
	initFlowAndDistanceMatirixes();
	initPopulation();
}
void Population::initFlowAndDistanceMatirixes()
{
	fstream fs;
	fs.open(fileName, std::fstream::in);

	fs >> hadXX;

	int elem;

	for (int i = 0; i < hadXX; i++) 
	{
		vector<int> row;
		for (int j = 0; j < hadXX; j++) 
		{
			fs >> elem;
			row.push_back(elem);
		}
		distanceM.push_back(row);
	}

	for (int i = 0; i < hadXX; i++) 
	{
		vector<int> row;
		for (int j = 0; j < hadXX; j++) 
		{
			fs >> elem;
			row.push_back(elem);
		}
		flowM.push_back(row);
	}
}
void Population::initPopulation() 
{
	for (int i = 0; i < pop_size; i++) 
	{
		Member* m = new Member(hadXX);
		members.push_back(m);
	}
}

void Population::showPopulation() {
	for (int i = 0; i < members.size(); i++)
	{
		cout << "MEMBER nr." << i + 1 << " -> ";
		members.at(i)->showGenes();
		cout << endl;
	}
}
void Population::showMatingPool() 
{
	for (int i = 0; i < matingPool.size(); i++) {
		for (int j = 0; j < hadXX; j++) {
			cout << matingPool[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void Population::selection()
{
	clearMatingPool();
	if (tour > 0) {
		for (int i = 0; i < pop_size; i++)
		{
			tournament();
		}
	}
	else {
		for (int i = 0; i < pop_size; i++) {
			matingPool.push_back(members[i]->genes);
		}
	}
	shuffleMatingPool(pop_size/2);
}
void Population::tournament() {
	vector<int> myTournament;
	vector<int> tournamentScores;

	for (int i = 0; i < tour; i++) 
	{
		int participant = rand() % members.size();

		myTournament.push_back(participant);
		tournamentScores.push_back(members.at(participant)->getFitness());
		//cout << "Participant " << participant << " = " << members.at(participant)->getFitness() << endl;
		
	}
	int winnerIndex = myTournament.at(findIndexOfTournaentWinner(tournamentScores));
	//cout << "Winer = " << winnerIndex << endl << endl;
	//members.at(winnerIndex)->showGenes();
	//cout << endl << "11" << endl;
	matingPool.push_back(members.at(winnerIndex)->genes);
}
int Population::findIndexOfTournaentWinner(vector<int> scores) 
{
	int index = 0;
	int winScore = scores.at(0);
	for (int i = 0; i < scores.size(); i++) 
	{
		if (winScore > scores.at(i)) 
		{
			winScore = scores.at(i);
			index = i;
		}
	}
	return index;
}
int Population::getBest() 
{
	vector<int> fitnesses;
	for (int i = 0; i < members.size(); i++) 
	{
		fitnesses.push_back(members.at(i)->getFitness());
	}
	int indeXOfBest = findIndexOfTournaentWinner(fitnesses);
	cout << "BEST: " << endl;
	members.at(indeXOfBest)->showGenes();

	return members.at(indeXOfBest)->getFitness();
}
int Population::getAvarage() 
{
	int sum = 0;
	for (int i = 0; i < members.size(); i++) {

		sum += members.at(i)->getFitness();
	}
	return (int)sum / members.size();
}
int Population::findIndexOfWorst(vector<int> scores) 
{
	int index = 0;
	int winScore = scores.at(0);
	for (int i = 0; i < scores.size(); i++) 
	{
		if (winScore < scores.at(i)) 
		{
			winScore = scores.at(i);
			index = i;
		}
	}
	return index;
}
int Population::getWorst() 
{
	vector<int> fitnesses;
	for (int i = 0; i < members.size(); i++) 
	{
		fitnesses.push_back(members.at(i)->getFitness());
	}
	int indeXOfWorst = findIndexOfWorst(fitnesses);
	return members.at(indeXOfWorst)->getFitness();
}
void Population::crossover() 
{
	shuffleMembers(pop_size);
	for (int i = 0; i < matingPool.size(); i++) 
	{
		vector<int> ParentA = matingPool.at(i);
		int a = i;
		i++;
		int b = i;
		vector<int> ParentB = matingPool.at(i);

		double crossRate = doubleRand(0, 1);
		if (crossRate < Px) {
			//cout << endl << "XROS" << endl;
			int xCenter = rand() % hadXX;
			//cout << endl << "center = " << xCenter << endl;
			vector<int> genesA;
			vector<int> genesB;
			for (int j = 0; j < ParentA.size(); j++) 
			{
				if (j < xCenter) 
				{
					genesA.push_back(ParentA.at(j));
					genesB.push_back(ParentB.at(j));
				}
				else 
				{
					genesA.push_back(ParentB.at(j));
					genesB.push_back(ParentA.at(j));
				}
			}
			//cout << endl << "PRZED: " << endl;
			//members.at(a)->showGenes();
			//members.at(b)->showGenes();

			members.at(a)->clearAndSetMember(genesA);
			members.at(b)->clearAndSetMember(genesB);

			//cout << endl << "PO PRZED NAPRAWA: " << endl;
			//members.at(a)->showGenes();
			//members.at(b)->showGenes();

			if (!members.at(a)->isOk())
			{
				members.at(a)->repair();
			}
			if (!members.at(b)->isOk())
			{
				members.at(b)->repair();
			}

			//cout << endl << "PO NAPRAWA: " << endl;
			//members.at(a)->showGenes();
			//members.at(b)->showGenes();

		}
		else {
			//cout << endl << " NIEXROS PRZED: " << endl;
			//members.at(a)->showGenes();
			//members.at(b)->showGenes();

			members.at(a)->clearAndSetMember(ParentA);
			members.at(b)->clearAndSetMember(ParentB);

			//cout << endl << "PO: " << endl;
			//members.at(a)->showGenes();
			//members.at(b)->showGenes();
		}
	}
}
void Population::mutation() 
{
	for (int i = 0; i < members.size(); i++) {
		members.at(i)->mutationInside(Pm);
	}
}
void Population::evaluate() 
{
	for (int i = 0; i < members.size(); i++) 
	{
		members.at(i)->caculateAndSetFitness(distanceM, flowM);
	}
}
int Population::getTour() 
{
	return tour;
}
double Population::getPx()
{
	return Px;
}
double Population::getPm() 
{
	return Pm;
}
int Population::getPopSize() 
{
	return pop_size;
}
int Population::getHadXX() 
{
	return hadXX;
}
void Population::showMembersFitness() 
{
	for (int i = 0; i < members.size(); i++) 
	{
		cout << "Member at " << i << " " << members.at(i)->getFitness() << endl;
	}
}
void Population::clearMembers() 
{
	members.clear();
}
void Population::clearMatingPool() 
{
	matingPool.clear();
}
double Population::doubleRand(double dMin, double dMax)
{
	double d = (double)rand() / RAND_MAX;
	return dMin + d * (dMax - dMin);
}
void Population::greedyAlghoritm() {
	vector<int> greedyGenes;

	int firstGene = rand() % hadXX + 1;
	greedyGenes.push_back(firstGene);

	for (int i = 0; i < hadXX - 1; i++) {
		vector<int> temp = greedyGenes;
		int nextGene = 1;
		while (find(greedyGenes.begin(), greedyGenes.end(), nextGene) != greedyGenes.end()) {
			nextGene++;
		}
		temp.push_back(nextGene);
		int bestFitness = calcGreedyFitness(temp);
		temp.pop_back();
		//cout << endl << endl;
		for (int j = 1; j < hadXX + 1; j++) {
			if (!(find(greedyGenes.begin(), greedyGenes.end(), j) != greedyGenes.end())) {
				temp.push_back(j);
				int fitness = calcGreedyFitness(temp);
				//cout << "j = " << j << endl;
				//cout << fitness << endl;
				if (fitness < bestFitness) {
					bestFitness = fitness;
					nextGene = j;
				}
				temp.pop_back();
			}
		}	
		//cout << endl << "best = " << nextGene << endl;
		//cout << bestFitness << endl;
		temp.clear();
		greedyGenes.push_back(nextGene);
	}
	Member* m = new Member(hadXX, greedyGenes);
	m->caculateAndSetFitness(distanceM, flowM);
	m->showGenes();
	delete m;
}
int Population::calcGreedyFitness(vector<int> genes) {
	int fit = 0;
	for (int i = 0; i < genes.size(); i++)
	{
		for (int j = 0; j < genes.size(); j++)
		{
			int d = distanceM[i][j];
			int f = flowM[genes[i] - 1][genes[j] - 1];
			//cout << endl << d << " " << f << endl;
			fit += (f*d);
		}
	}
	return fit;
}
void Population::shuffleMatingPool(int rate) {

	for (int i = 0; i < rate; i++)
	{
		int mate_1 = rand() % pop_size;
		int mate_2 = rand() % pop_size;
		swap(matingPool[mate_1], matingPool[mate_2]);
	}
}
void Population::shuffleMembers(int rate) {

	for (int i = 0; i < rate; i++)
	{
		int mem_1 = rand() % pop_size;
		int mem_2 = rand() % pop_size;
		swap(members[mem_1], members[mem_2]);
	}
}
Population::~Population() 
{
	for (int i = 0; i < members.size(); i++) {
		delete members[i];
	}
	clearMatingPool();
	clearMembers();
	tour = 0;
	pop_size = 0;
	Px = 0;
	Pm = 0;
	hadXX = 0;
	fileName = "";
	flowM.clear();
	distanceM.clear();
	//cout << endl << "POPULATION IS DEAD" << endl;
}

