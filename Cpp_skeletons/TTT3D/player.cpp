#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>


namespace TICTACTOE3D
{
void Player::mapping(std::map<std::string, int> &winconditions,int p,int r, int c){
	winconditions["pr"+std::to_string(p*10+r)]++;
	winconditions["pc"+std::to_string(p*10+c)]++;
	winconditions["rc"+std::to_string(r*10+c)]++;
	//std::cerr << "value after input "<<winconditions["pr"+std::to_string(p*10+r)] << std::endl;
	//TRUE DIAGONALS
	if(p==r&&r==c){
		winconditions["trudiag1"]++;
	}
	else if(r==c&&(3-c==p)){
		winconditions["trudiag2"]++;
	}

	else if(p==c&&(3-c==r)){
		winconditions["trudiag3"]++;
	}
	else if(p==r&&(3-r==c)){
		winconditions["trudiag4"]++;
	}
	//PLANE DIAGONALS
	if(p==c){
		winconditions["drr"+std::to_string(r)]++;
	}
	else if(p==3-c){
		winconditions["dir"+std::to_string(r)]++;
	}
	if(p==r){
		winconditions["drc"+std::to_string(c)]++;
	}
	else if(p==3-r){
		winconditions["dic"+std::to_string(c)]++;
	}
	if(r==c){
		winconditions["drp"+std::to_string(p)]++;
	}
	else if(r==3-c){
		winconditions["dip"+std::to_string(p)]++;
	}

/*
	winconditions.insert(std::make_pair(std::to_string(p*10+r),winconditions.find()));
	winconditions.insert(std::make_pair(std::to_string(p*10+c),r));
	winconditions.insert(std::make_pair(std::to_string(r*10+c),p));
	*/

}
int scoreing(int xp, int op){
	//Winning
	if(op == 0){
		if(xp == 4)
			return 100000;
		else if(xp == 3)
			return 1000;
		else if(xp == 2)
			return 100;
		else
			return 10;
	}
	//Blocking
	else if(xp > 0 && op > 0){
		if(op == 3)
			return 1500;
		else if(op == 2)
			return 50;
		else
			return 1;
	}
	//else
	return 0;
}
int Player::evaluate(const GameState &state){
	std::map<std::string, int> winconditionsX;
    std::map<std::string, int> winconditionsY;
	int score = 0;
	//Row and column
	for(int p = 0; p<4;++p){
		for(int r = 0; r<4;++r){
			for(int c = 0; c<4;++c){
				if(state.at(r,c,p)&CELL_X){
					mapping(winconditionsX,p,r,c);
				}
				else if(state.at(r,c,p)&CELL_O){
					mapping(winconditionsY,p,r,c);
				}
			}
		}
	}

	for(auto kv : winconditionsX) {
		if(winconditionsY.find(kv.first)==winconditionsY.end()){
			score+=scoreing(kv.second,0);
		}
		else{
			score+=scoreing(kv.second,winconditionsY[kv.first]);
		}
	}
	//std::cerr << "SCORE!!! " << score << std::endl;
	return score;

}
int Player::alphabeta(const GameState &state, int depth, int a, int b, bool pa,const Deadline &pDue){
	int v = 2;
	std::vector<GameState> nextStates;
	state.findPossibleMoves(nextStates);
	std::string stateKey = state.toMessage().substr(0,64);
	if(depth <= 0 || nextStates.size()==0||(pDue.getSeconds() - pDue.now().getSeconds())<0.05){
		if(stateValue.find(stateKey) != stateValue.end())
			return stateValue[stateKey];
		else
			v = evaluate(state);
	}
	else if(pa){
		v = std::numeric_limits<int>::min();
		for(int i = 0; i< nextStates.size();++i){
			v = std::max(v,alphabeta(nextStates[i],depth-1,a,b,false,pDue));
			a = std::max(a,v);
			if(b<=a)
				break;
		}
	}
	else{
		v = std::numeric_limits<int>::max();
		for(int i = 0; i< nextStates.size();++i){
			v = std::min(v,alphabeta(nextStates[i],depth-1,a,b,true,pDue));
			b = std::min(b,v);
			if(b<=a)
				break;
		}
	}
	stateValue[stateKey] = v;
	return v;
}

bool Player::sortHelper(const GameState & a, const GameState & b){
	std::string aS = a.toMessage().substr(0,64);
	std::string bS = b.toMessage().substr(0,64);
	int aVal = 0;
	int bVal = 0;
	if(stateValue.find(aS) != stateValue.end())
		aVal = stateValue[aS];
	else{
		aVal = evaluate(a);
		stateValue[aS] = aVal;
	}
	if(stateValue.find(bS) != stateValue.end())
		bVal = stateValue[bS];
	else{
		bVal = evaluate(b);
		stateValue[bS] = bVal;
	}
	return aVal > bVal;
}


void Player::sortStates(std::vector<GameState> & nextStates){
	std::sort(nextStates.begin(),nextStates.end(), 
		[this] (const GameState & a, const GameState & b) -> bool { return sortHelper(a,b); });
}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    if (lNextStates.size() == 0) return GameState(pState, Move());
    sortStates(lNextStates);

	int dl = pState.cSquares;
    for (int i = 0; i < pState.cSquares; ++i)
	{
		if (pState.at(i) & CELL_X)
			--dl;
		else if (pState.at(i) & CELL_O)
			--dl;
	}

	int d = -1;
	int sum = dl;
	int T = 2394;
	while(sum < T){
		sum *= --dl;
		d++;
	}
	//std::cerr << "D= " << d << std::endl;
	
    int bestOption = std::numeric_limits<int>::min();
    int index = -1;
    for(int i = 0; i< lNextStates.size();++i){
		int newVal= alphabeta(lNextStates[i],d,std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),false,pDue);
		if(std::max(bestOption,newVal)!=bestOption){
			index = i;
			bestOption = newVal;
		}
	}
	//std::cerr << "Hash size : " << stateValue.size() << std::endl;
	return lNextStates[index];
	
    
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE3D*/ }
