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
Move Minimax::get_move(State *state, int depth ,int selfplyer){
  if(!state->legal_actions.size())
    state->get_legal_actions();
  
  Move actions = *(state->legal_actions.begin());
  State* newone ;
  state->value=-1e9;
  for( auto it = state->legal_actions.begin() ; it!=state->legal_actions.end() ; ++it){
    newone = state->next_state(*it);
    
    if(!newone->legal_actions.size())
    newone->get_legal_actions();
  
    Move nextactions = *(newone->legal_actions.begin());
    State* nextone ;
    newone->value=+1e9;
    for( auto is = newone->legal_actions.begin() ; is!=newone->legal_actions.end() ; ++is){
      nextone = state->next_state(*is);
      nextone->value = newone->evaluate(selfplyer);
      if(nextone->value<newone->value){
      newone->value=nextone->value;
      nextactions = *is ;
      }
    }


    if(newone->value>state->value){
      state->value=newone->value;
      actions = *it ;
    }
  }
  /*Move newmove = *(state->legal_actions.begin());
  State* newone ;
  auto legel = state->legal_actions;

  if(state->player==selfplyer){
    state->value=-1e9;
    for( auto it = legel.begin() ; it!=legel.end() ; ++it){
      newmove = *it ;
      newone = state->next_state(newmove);
      if(depth==1) newone->value = newone->evaluate(selfplyer);
      else newone->value = newone->next_state(get_move(newone,depth-1,selfplyer))->value;

      if(newone->value>state->value){
        state->value=newone->value;
        actions = *it ;
      }
    }
  }
  else{
    state->value=1e9;
    for( auto it = legel.begin() ; it!=legel.end() ; it++){
      newmove = *it ;
      newone = state->next_state(newmove);
      if(depth==1) newone->value = newone->evaluate(selfplyer);
      else newone->value = newone->next_state(get_move(newone,depth-1,selfplyer))->value;

      if(newone->value<state->value){
        state->value=newone->value;
        actions = *it ;
      }
    }
  }*/
  
  return actions;
}