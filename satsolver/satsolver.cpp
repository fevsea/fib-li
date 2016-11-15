#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

#define UNDEF -1
#define TRUE 1
#define FALSE 0

uint numVars;
uint numClauses;
vector<vector<int> > clauses;
vector<int> model;
vector<int> modelStack;
vector<int> occurrences;
vector<vector<vector<int>* > > positive_clauses;
vector<vector<vector<int>* > > negative_clauses;
uint indexOfNextLitToPropagate;
uint decisionLevel;

long long decisions;
long long propagations;
clock_t startTime;


void readClauses( ){
  // Skip comments
  char c = cin.get();
  while (c == 'c') {
    while (c != '\n') c = cin.get();
    c = cin.get();
  }
  // Read "cnf numVars numClauses"
  string aux;
  cin >> aux >> numVars >> numClauses;
  clauses.resize(numClauses);
  occurrences.resize(numVars+1, 0);
  positive_clauses.resize(numVars+1);
  negative_clauses.resize(numVars+1);
  // Read clauses
  for (uint i = 0; i < numClauses; ++i) {
    int lit;
    while (cin >> lit and lit != 0){
      clauses[i].push_back(lit);
      ++occurrences[abs(lit)];
      if(lit > 0){
        positive_clauses[abs(lit)].push_back(&clauses[i]);
      } else {
        negative_clauses[abs(lit)].push_back(&clauses[i]);
      }
    }
  }
}

int currentValueInModel(int lit){
  if (lit >= 0) return model[lit];
  else {
    if (model[-lit] == UNDEF) return UNDEF;
    else return 1 - model[-lit];
  }
}

void setLiteralToTrue(int lit){
  modelStack.push_back(lit);
  if (lit > 0) model[lit] = TRUE;
  else model[-lit] = FALSE;
}


bool propagateGivesConflict ( ) {
  while ( indexOfNextLitToPropagate < modelStack.size() ) {
    int lit = modelStack[indexOfNextLitToPropagate];
    vector< vector<int>* >& vec = lit > 0 ? negative_clauses[abs(lit)] : positive_clauses[abs(lit)];
    for (uint i = 0; i < vec.size(); ++i) {
      bool someLitTrue = false;
      int numUndefs = 0;
      int lastLitUndef = 0;
      for (uint k = 0; not someLitTrue and k < vec[i]->size(); ++k){
      	int val = currentValueInModel((*vec[i])[k]);
      	if (val == TRUE) someLitTrue = true;
      	else if (val == UNDEF){ ++numUndefs; lastLitUndef = (*vec[i])[k]; }
      }
      if (not someLitTrue and numUndefs == 0){
        ++occurrences[abs(lit)]; //avoid devil-choosed variable that usually provoque conflicts
        return true; // conflict! all lits false
      }
      else if (not someLitTrue and numUndefs == 1) setLiteralToTrue(lastLitUndef);
    }
    ++indexOfNextLitToPropagate;
    ++propagations;
  }
  return false;
}


void backtrack(){
  uint i = modelStack.size() -1;
  int lit = 0;
  while (modelStack[i] != 0){ // 0 is the DL mark
    lit = modelStack[i];
    model[abs(lit)] = UNDEF;
    modelStack.pop_back();
    --i;
  }
  // at this point, lit is the last decision
  modelStack.pop_back(); // remove the DL mark
  --decisionLevel;
  indexOfNextLitToPropagate = modelStack.size();
  setLiteralToTrue(-lit);  // reverse last decision
}


// Heuristic for finding the next decision literal:
int getNextDecisionLiteral(){
  int max = -1;
  uint max_pos;
  for (uint i = 1; i <= numVars; ++i){
    if (model[i] == UNDEF and occurrences[i] > max) {
        max = occurrences[i];
        max_pos = i;
      }
    }
  return max != -1 ? max_pos : 0;
}

void checkmodel(){
  for (int i = 0; i < numClauses; ++i){
    bool someTrue = false;
    for (int j = 0; not someTrue and j < clauses[i].size(); ++j)
      someTrue = (currentValueInModel(clauses[i][j]) == TRUE);
    if (not someTrue) {
      cout << "Error in model, clause is not satisfied:";
      for (int j = 0; j < clauses[i].size(); ++j) cout << clauses[i][j] << " ";
      cout << endl;
      exit(1);
    }
  }
}

void end(bool ok){
  double duration = (clock() - startTime)/CLOCKS_PER_SEC;
  cout << (ok ? "SATISFIABLE" : "UNSATISFIABLE") << " " << duration << " " << decisions << " " << propagations << endl;
  exit(ok ? 10 : 20);
}

int main(){
  decisions = propagations = 0;
  startTime = clock();
  readClauses(); // reads numVars, numClauses and clauses
  model.resize(numVars+1,UNDEF);
  indexOfNextLitToPropagate = 0;
  decisionLevel = 0;

  // Take care of initial unit clauses, if any
  for (uint i = 0; i < numClauses; ++i){
    if (clauses[i].size() == 1) {
      int lit = clauses[i][0];
      int val = currentValueInModel(lit);
      if (val == FALSE) {cout << "UNSATISFIABLE" << endl; return 10;}
      else if (val == UNDEF) setLiteralToTrue(lit);
    }
  }

  // DPLL algorithm
  while (true) {
    while ( propagateGivesConflict() ) {
      if ( decisionLevel == 0) {end(false); }
      backtrack();
    }
    int decisionLit = getNextDecisionLiteral();
    if (decisionLit == 0) { checkmodel(); end(true); }
    // start new decision level:
    modelStack.push_back(0);  // push mark indicating new DL
    ++indexOfNextLitToPropagate;
    ++decisionLevel;
    ++decisions;
    setLiteralToTrue(decisionLit);    // now push decisionLit on top of the mark
  }
}
