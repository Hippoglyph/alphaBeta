#include "player.hpp"
#include <cstdlib>
#include <iostream>
#include <limits>
#include <cmath>


namespace TICTACTOE3D
{
int Player::evaluate(const GameState &state){
	if(state.isXWin()) 
		return 77;
	else if(state.isOWin()) 
		return -77;
	else if (state.isDraw())
		return 0;
	else{
		int scoreX = 0;
		int scoreO = 0;
		//Row and column
		for(int p = 0; p<4;++p){
			for(int r = 0; r<4; ++r){
				int x = 0;
				int o = 0;
				for(int c = 0; c<4; ++c){
					if(state.at(r,c,p)&CELL_O){
						score++;
						break;
					}
				}
			}
			for(int c = 0; c<4; ++c){
				for(int r = 0; r<4; ++r){
					if(state.at(r,c,p)&CELL_O){
						score++;
						break;
					}
				}
			}
		}
		//plane
		for(int c = 0; c<4; ++c){
			for(int r = 0; r<4; ++r){
				for(int p = 0; p < 4;++p){
					if(state.at(r,c,p)&CELL_O){
						score++;
						break;
					}
				}
			}
		}
		//up diag
		for(int p = 0; p<4;++p){
			for(int i = 0; i<4;++i){
				if(state.at(i,i,p)&CELL_O){
						score++;
						break;
				}
			}
			for(int i = 0; i<4;++i){
				if(state.at(i,3-i,p)&CELL_O){
						score++;
						break;
				}
			}
		}
		//Side diag
		for(int r = 0; r<4;++r){
			for(int i = 0; i<4;++i){
				if(state.at(r,i,i)&CELL_O){
						score++;
						break;
				}
			}
			for(int i = 0; i<4;++i){
				if(state.at(r,3-i,i)&CELL_O){
						score++;
						break;
				}
			}
		}
		//Back diag
		for(int c = 0; c<4;++c){
			for(int i = 0; i<4;++i){
				if(state.at(i,c,i)&CELL_O){
						score++;
						break;
				}
			}
			for(int i = 0; i<4;++i){
				if(state.at(i,c,3-i)&CELL_O){
						score++;
						break;
				}
			}
		}
		//Main diag
		for(int i = 0; i < 4; ++i){
			if(state.at(i,i,i)&CELL_O){
						score++;
						break;
			}
		}

		for(int i = 0; i < 4; ++i){
			if(state.at(3-i,i,i)&CELL_O){
						score++;
						break;
			}
		}

		for(int i = 0; i < 4; ++i){
			if(state.at(i,3-i,i)&CELL_O){
						score++;
						break;
			}
		}

		for(int i = 0; i < 4; ++i){
			if(state.at(3-i,3-i,i)&CELL_O){
						score++;
						break;
			}
		}
		//std::cerr << "score " <<score <<std::endl;
		return 76-score;
	}
}
int Player::alphabeta(const GameState &state, int depth, int a, int b, bool pa,const Deadline &pDue){
	int v = 2;
	std::vector<GameState> nextStates;
	state.findPossibleMoves(nextStates);
	std::string stateKey = state.toMessage().substr(0,64);
	if(depth <= 0 || nextStates.size()==0||(pDue.getSeconds() - pDue.now().getSeconds())<0.1){
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
	
    int bestOption = std::numeric_limits<int>::min();
    int index = -1;
    for(int i = 0; i< lNextStates.size();++i){
		int newVal= alphabeta(lNextStates[i],1,std::numeric_limits<int>::min(),std::numeric_limits<int>::max(),false,pDue);
		if(std::max(bestOption,newVal)!=bestOption){
			index = i;
			bestOption = newVal;
		}
	}
	return lNextStates[index];
	
    
    //return lNextStates[rand() % lNextStates.size()];
}

/*namespace TICTACTOE3D*/ }
