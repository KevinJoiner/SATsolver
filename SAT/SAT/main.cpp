#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <sstream>
#include <math.h>
using namespace std;
/*
Author: Kevin Joiner
Date: 9/23/2016

*/

class Clause {
public:
	vector<int> clause;
	Clause(vector<string>StrClause) {
		for (int i = 0; i < StrClause.size(); i++) {
			clause.push_back(stoi(StrClause[i]));
		}
	}
};

class TruthModel {
public:
	int VaribleNumber;
	int ClauseNumber;
	//stores the state of the varibles
	vector<bool> Vars;
	// stores a vector of the different clauses
	vector<Clause> Clauses;
	TruthModel() {
		VaribleNumber=0;
		ClauseNumber=0;
	}
	// Allocates the coreect size for the varible vector
	void SetSize( int VarNum, int ClaNum) {
		VaribleNumber = VarNum;
		ClauseNumber = ClaNum;
		for (int i = 0; i < VarNum; i++) {
			Vars.push_back(true);
		}
	}

	// adds a cluase to the model
	void InsertClause(vector<string> StrClause) {
		Clause clause(StrClause);
		Clauses.push_back(clause);
	}
	
	void SetVarValue(int var, bool value) {
		Vars[var - 1] == value;
	}
	
	//Check to see how many clauses are correct
	int Get_fitness(){
		int Cvalue = 0;
		//For each clause
		for (int i = 0; i < Clauses.size(); i++) {
			bool state;
			if (Clauses[i].clause[0] < 0) {
				state = !Vars[Clauses[i].clause[0]*-1 - 1];
			}
			else {
				state = Vars[Clauses[i].clause[0] - 1];
			}

			//For each value varible in a clause evaluate it with the previous
			for (int j = 1; j < Clauses[i].clause.size(); j++) {

				//If varible is not set then go to the next clause
				if (2== !Vars[abs(Clauses[i].clause[j]) - 1]){
					state = false;
					break;
				}
				if (Clauses[i].clause[j] < 0) 
					state = !Vars[Clauses[i].clause[j]*-1 - 1] || state;
				else
					state = Vars[Clauses[i].clause[j] - 1] || state;
			}
			if (state == true) {
				Cvalue++;
			}
				
		}
		return Cvalue;
	}
	// Checks to see if the model is true
	bool is_True() {
		if (Get_fitness() == ClauseNumber) {
			return true;
		}
		return false;
	}
		
		
};




main() {

	// Finds all files with the extension .cnf and stores the filenames into a vector
	//http://stackoverflow.com/questions/35424519/list-all-text-files-in-directory-in-c
	const char* file = "*.cnf";
	WIN32_FIND_DATA FindFileData;
	vector<string> vs;
	HANDLE hFind;
	hFind = FindFirstFile(file, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			vs.push_back(FindFileData.cFileName);
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}


	std::cout << "count:" << vs.size() << "\n";
	for (auto item : vs) {
		bool started = false;
		ifstream infile(item);
		string line;
		TruthModel model;
		while (getline(infile, line)) {
			if (started) {
				vector<string> StrClause;
				int pos;
				string varible;

				//parsing throught the line adding values to a vector of strings that will be the cluse
				while ((pos = line.find(" ")) != std::string::npos) {
					varible = line.substr(0, pos);
					line.erase(0, pos + 1);
					StrClause.push_back(varible);
				}
			}
			// shows that the file started 
			if (line.find("cnf") != string::npos) {
				int VarNum = stoi(line.substr(line.find("cnf") + 4, 2));
				int ClaNum = stoi(line.substr(line.find("cnf") + 7, 2));
				model.SetSize(VarNum,ClaNum);
				started = true;
			}

		}

		std::cout << item << "\n";
	}
}