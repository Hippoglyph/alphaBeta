#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cmath>

namespace TICTACTOE3D
{
int alphabeta(const GameState &state, int depth, int a, int b, bool pa){
	int v = 2;
	std::vector<GameState> nextStates;
	state.findPossibleMoves(nextStates);
	if(depth <= 0 || nextStates.size()==0){
		if(state.isXWin()) 
			v = 1;
		else if(state.isOWin()) 
			v = -1;
		else //if (state.isDraw())
			v = 0;
		/*else{
			int score = 0;
			for(int r = 0; r<4; ++r){
				for(int c = 0; c<4; ++c){
					if(r==c)
						if(state.at(r,c)=='X')
							score++;
						else if(state.at(r,c)=='O')
							score--;
					if(3-r==c)
						if(state.at(r,c)=='X')
							score++;
						else if(state.at(r,c)=='O')
							score--;
					if(state.at(r,c)=='X')
						score+=2;
					else if(state.at(r,c)=='O')
						score-=2;
				}
			}
			if(score == 0)
				v = 0;
			else if(score>0)
				v = 1;
			else 
				v = -1;
		}*/
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
		int newVal= alphabeta(lNextStates[i],1,std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),false);
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

/*namespace TICTACTOE3D*/ }
