 #ifndef _TICTACTOE3D_PLAYER_HPP_
#define _TICTACTOE3D_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>
#include <unordered_map>
#include <string>
#include <map>

namespace TICTACTOE3D
{

class Player
{
public:
    std::unordered_map<std::string, int> stateValue;
    bool sortHelper(const GameState & a, const GameState & b);
    void sortStates(std::vector<GameState> & nextStates);
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    GameState play(const GameState &pState, const Deadline &pDue);
    int alphabeta(const GameState &state, int depth, int a, int b, bool pa,const Deadline &pDue);
    int evaluate(const GameState &state);
    void mapping(std::map<std::string,int>&,int,int,int);
};

/*namespace TICTACTOE3D*/ }

#endif
