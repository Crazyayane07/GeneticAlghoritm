#pragma once
#include "Member.h"

class Population {
private:
	vector<Member*> members;
	vector<vector<int>> matingPool;
	vector<vector<int>> distanceM;
	vector<vector<int>> flowM;
	int tour;
	int pop_size;
	double Px;
	double Pm;
	int hadXX;
	string fileName;
public:
	Population(int, int, double, double, string);
	void initPopulation();
	void initFlowAndDistanceMatirixes();
	int getTour();
	double getPx();
	double getPm();
	int getPopSize();
	int getHadXX();
	void showPopulation();
	void selection();
	void crossover();
	void mutation();
	void tournament();
	void showMatingPool();
	int findIndexOfTournaentWinner(vector<int>);
	int findIndexOfWorst(vector<int>);
	void evaluate();
	void showMembersFitness();
	int getBest();
	int getWorst();
	void clearMembers();
	void clearMatingPool();
	int getAvarage();
	double doubleRand(double, double);
	void greedyAlghoritm();
	int calcGreedyFitness(vector<int>);
	void shuffleMatingPool(int);
	void shuffleMembers(int);
	~Population();
};
