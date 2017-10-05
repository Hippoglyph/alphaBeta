 #ifndef _TICTACTOE3D_PLAYER_HPP_
#define _TICTACTOE3D_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>
#include <map>
#include <string>

namespace TICTACTOE3D
{

class Player
{
public:
    std::map<std::string, int> stateValue;
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    GameState play(const GameState &pState, const Deadline &pDue);
    int alphabeta(const GameState &state, int depth, int a, int b, bool pa,const Deadline &pDue);
    int evaluate(const GameState &state);
};

/*namespace TICTACTOE3D*/ }

#endif
