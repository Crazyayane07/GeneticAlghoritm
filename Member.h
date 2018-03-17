#pragma once
#include <vector>
using namespace std;

class Member
{
private:
	int hadXX;
	int fitness;
public:
	Member(int);
	Member(int, vector<int>);
	vector<int> genes;
	void initChild(vector<int>);
	int getHadXX();
	void initMember();
	void randomShuffle(int);
	void showGenes();
	void mutationInside(double);
	bool isOk();
	void repair();
	bool hasDoubles(vector<int>, int);
	void caculateAndSetFitness(vector<vector<int>>, vector<vector<int>>);
	int getFitness();
	double doubleRand(double, double);
	void clearAndSetMember(vector<int>);
	~Member();
};

