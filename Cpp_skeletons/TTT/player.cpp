#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cmath>

//Author Marcus Lignercrona & Jonathan Rinnarv
namespace TICTACTOE
{
int alphabeta(const GameState &state, int depth, int a, int b, bool pa){
	int v = 2;
	std::vector<GameState> nextStates;
	state.findPossibleMoves(nextStates);
	if(depth == 0 || nextStates.size()==0){
		if(state.isXWin()) 
			v = 1;
		else if(state.isOWin()) 
			v = -1;
		else
			v = 0;
	}
	else if(pa){
		v = std::numeric_limits<int>::min();
		for(int i = 0; i< nextStates.size();++i){
			v = std::max(v,alphabeta(nextStates[i],depth-1,a,b,false));
			a = std::max(a,v);
			if(b<=a)
				break;
		}
	}
	else{
		v = std::numeric_limits<int>::max();
		for(int i = 0; i< nextStates.size();++i){
			v = std::min(v,alphabeta(nextStates[i],depth-1,a,b,true));
			b = std::min(b,v);
			if(b<=a)
				break;
		}
	
	}
	return v;
}
GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::endl;

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    if (lNextStates.size() == 0) return GameState(pState, Move());
    int bestOption = std::numeric_limits<int>::min();
    int index = -1;
    for(int i = 0; i< lNextStates.size();++i){
		int newVal= alphabeta(lNextStates[i],20,std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),false);
		if(std::max(bestOption,newVal)!=bestOption){
			index = i;
			bestOption = newVal;
		}
	}
	return lNextStates[index];

    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE*/ }
