#include <cstdlib>

#include "../state/state.hpp"
#include "./minimax.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Minimax::get_move(State *state, int depth ){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  Move actions = *(state->legal_actions.begin());
  State* newone ;
  state->value=-1e9;
  for( auto it = state->legal_actions.begin() ; it!=state->legal_actions.end() ; ++it){
    newone = state->next_state(*it);

    if(newone->value>state->value){
      state->value=newone->value;
      actions = *it ;
    }
  }
  
  return actions;
}