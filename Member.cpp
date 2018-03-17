#include "stdafx.h"
#include "Member.h"
#include <iostream>

Member::Member(int hadXX) 
{
	this->hadXX = hadXX;
	fitness = 0;
	initMember();
}
Member::Member(int hadXX, vector<int> newGenes) 
{
	this->hadXX = hadXX;
	fitness = 0;
	genes.clear();
	initChild(newGenes);
}
void Member::initChild(vector<int> newGenes) 
{
	genes.clear();
	for (int i = 0; i < newGenes.size(); i++) 
	{
		genes.push_back(newGenes.at(i));
	}
}
int Member::getHadXX() 
{
	return hadXX;
}
void Member::initMember() 
{
	for (int i = 1; i <= hadXX; i++) 
	{
		genes.push_back(i);
	}
	randomShuffle(hadXX);
}
void Member::randomShuffle(int randScale)
{
	for (int i = 0; i < randScale; i++) 
	{
		int gene_1 = rand() % hadXX;
		int gene_2 = rand() % hadXX;
		swap(genes[gene_1], genes[gene_2]);
	}
}
void Member::showGenes() 
{
	for (int i = 0; i < genes.size(); i++) 
	{
		cout << genes.at(i) << " ";
	}
	cout << "	F: " << fitness;
}
void Member::mutationInside(double Pm) 
{
	for (int i = 0; i < genes.size(); i++) 
	{
		double mutationRate = doubleRand(0, 1);
		if (mutationRate < Pm) {
			int genetoSwap = rand() % hadXX;
			swap(genes[i], genes[genetoSwap]);
		}
	}
}
bool Member::isOk() 
{
	bool ok = true;
	vector<int> elements;
	for (int i = 0; i < genes.size() && ok; i++) 
	{
		if (hasDoubles(elements, genes.at(i))) 
		{
			ok = false;
		}
		else 
		{
			elements.push_back(genes.at(i));
		}
	}
	return ok;
}
void Member::repair() 
{
	vector<int> elements;
	for (int i = 0; i < genes.size(); i++) 
	{
		bool doubles;
		if (hasDoubles(elements, genes.at(i))) 
		{
			doubles = true;
			int gene = rand() % hadXX + 1;
			while (doubles) {
				if (hasDoubles(elements, gene)) 
				{
					gene = rand() % hadXX + 1;
				}
				else 
				{
					doubles = false;
					elements.push_back(gene);
					genes.at(i) = gene;
				}
			}
		}
		else {
			elements.push_back(genes.at(i));
		}
	}
}
bool Member::hasDoubles(vector<int> elements, int elem) 
{
	return find(elements.begin(), elements.end(), elem) != elements.end();
}
void Member::caculateAndSetFitness(vector<vector<int>> distanceM, vector<vector<int>> flowM) 
{
	int fit = 0;
	for (int i = 0; i < genes.size(); i++) 
	{
		for (int j = 0; j < genes.size(); j++) 
		{
			int d = distanceM[i][j];
			int f = flowM[genes[i] - 1][genes[j] - 1];
			fit += (f*d);
		}
	}
	fitness = fit;
}
int Member::getFitness() 
{
	return fitness;
}
double Member::doubleRand(double dMin, double dMax)
{
	double d = (double)rand() / RAND_MAX;
	return dMin + d * (dMax - dMin);
}
void Member::clearAndSetMember(vector<int> newGenes) {
	fitness = 0;
	genes.clear();
	initChild(newGenes);
	newGenes.clear();
}
Member::~Member() {
	genes.clear();
	hadXX = 0;
	fitness = 0;
}
