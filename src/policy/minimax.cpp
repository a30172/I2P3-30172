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
Move Minimax::get_move(State *state, int depth ,int selfplayer){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  Move actions = *(state->legal_actions.begin());
  Move tmp;
  State* newone ;
  if(state->player==selfplayer)
    state->value=-1e9;
  else 
    state->value=1e9;
    
  for( auto it = state->legal_actions.begin() ; it!=state->legal_actions.end() ; ++it){
    tmp = *it ;
    newone = state->next_state(tmp);

    if(!depth) newone->value=newone->evaluate();
    else get_move(newone,depth-1,selfplayer);

    if(state->player==selfplayer && newone->value>=state->value){
      state->value=newone->value;
      actions = tmp ;
    }
    else if(state->player!=selfplayer && newone->value<=state->value){
      state->value=newone->value;
      actions = tmp ;
    }
  }

  for( auto flag = state->legal_actions.begin() ; flag!=state->legal_actions.end() ; ++flag){
    tmp = *flag ;
    if(actions==tmp)
      return actions;
  }

  return *(state->legal_actions.begin());
}