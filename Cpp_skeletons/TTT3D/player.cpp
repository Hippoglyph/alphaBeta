#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cmath>


namespace TICTACTOE3D
{
int Player::evaluate(const GameState &state){
	if(state.isXWin()) 
		return 1217;
	else if(state.isOWin()) 
		return -1217;
	else if (state.isDraw())
		return 0;
	else{
		int score = 0;
		//Row and column
		for(int p = 0; p<4;++p){
			for(int r = 0; r<4; ++r){
				int x = 0;
				int o = 0;
				for(int c = 0; c<4; ++c){
					if(state.at(r,c,p)&CELL_X)
						++x;
					if(state.at(r,c,p)&CELL_O)
						++o;
				}
				score += std::pow(2,x);
				score -= std::pow(2,o);
			}
			for(int c = 0; c<4; ++c){
				int x = 0;
				int o = 0;
				for(int r = 0; r<4; ++r){	
					if(state.at(r,c,p)&CELL_X)
						++x;
					if(state.at(r,c,p)&CELL_O)
						++o;
				}
				score += std::pow(2,x);
				score -= std::pow(2,o);
			}
		}
		//plane
		for(int c = 0; c<4; ++c){
			for(int r = 0; r<4; ++r){
				int x = 0;
				int o = 0;
				for(int p = 0; p < 4;++p){	
					if(state.at(r,c,p)&CELL_X)
						++x;
					if(state.at(r,c,p)&CELL_O)
						++o;
				}
				score += std::pow(2,x);
				score -= std::pow(2,o);
			}
		}
		//up diag
		for(int p = 0; p<4;++p){
			int x = 0;
			int o = 0;
			int x2 = 0;
			int o2 = 0;
			for(int i = 0; i<4;++i){
				if(state.at(i,i,p)&CELL_X)
					++x;
				if(state.at(i,i,p)&CELL_O)
					++o;
				if(state.at(i,3-i,p)&CELL_X)
					++x2;
				if(state.at(i,3-i,p)&CELL_O)
					++o2;
			}
			score += std::pow(2,x);
			score -= std::pow(2,o);
			score += std::pow(2,x2);
			score -= std::pow(2,o2);
		}
		//Side diag
		for(int r = 0; r<4;++r){
			int x = 0;
			int o = 0;
			int x2 = 0;
			int o2 = 0;
			for(int i = 0; i<4;++i){
				if(state.at(r,i,i)&CELL_X)
					++x;
				if(state.at(r,i,i)&CELL_O)
					++o;
				if(state.at(r,3-i,i)&CELL_X)
					++x2;
				if(state.at(r,3-i,i)&CELL_O)
					++o2;
			}
			score += std::pow(2,x);
			score -= std::pow(2,o);
			score += std::pow(2,x2);
			score -= std::pow(2,o2);
		}
		//Back diag
		for(int c = 0; c<4;++c){
			int x = 0;
			int o = 0;
			int x2 = 0;
			int o2 = 0;
			for(int i = 0; i<4;++i){
				if(state.at(i,c,i)&CELL_X)
					++x;
				if(state.at(i,c,i)&CELL_O)
					++o;
				if(state.at(i,c,3-i)&CELL_X)
					++x;
				if(state.at(i,c,3-i)&CELL_O)
					++o;
			}
			score += std::pow(2,x);
			score -= std::pow(2,o);
			score += std::pow(2,x2);
			score -= std::pow(2,o2);
		}
		//Main diag
		int x = 0;
		int o = 0;
		int x2 = 0;
		int o2 = 0;
		int x3 = 0;
		int o3 = 0;
		int x4 = 0;
		int o4 = 0;
		for(int i = 0; i < 4; ++i){
			if(state.at(i,i,i)&CELL_X)
				++x;
			if(state.at(i,i,i)&CELL_O)
				++o;
			if(state.at(3-i,i,i)&CELL_X)
				++x2;
			if(state.at(3-i,i,i)&CELL_O)
				++o2;
			if(state.at(i,3-i,i)&CELL_X)
				++x3;
			if(state.at(i,3-i,i)&CELL_O)
				++o3;
			if(state.at(i,i,3-i)&CELL_X)
				++x4;
			if(state.at(i,i,3-i)&CELL_O)
				++o4;
		}
		score += std::pow(2,x);
		score -= std::pow(2,o);
		score += std::pow(2,x2);
		score -= std::pow(2,o2);
		score += std::pow(2,x3);
		score -= std::pow(2,o3);
		score += std::pow(2,x4);
		score -= std::pow(2,o4);
		return score;
	}
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
GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;
	
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
	
    if (lNextStates.size() == 0) return GameState(pState, Move());

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
