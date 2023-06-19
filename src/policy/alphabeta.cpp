#include <cstdlib>

#include "../state/state.hpp"
#include "./alphabeta.hpp"

int alpbe(State *state, int depth , int alp , int be , int selfplayer){

    if(!state->legal_actions.size())
    state->get_legal_actions();

    Move tmp;
    State* newone ;

    if(state->player==selfplayer){
        int value = -1e9 ;
        for( auto it = state->legal_actions.begin() ; it!=state->legal_actions.end() ; ++it){
            tmp = *it;
            newone = state->next_state(tmp);

            if(!depth) value = newone->evaluate() ;
            else value = std::max(value,alpbe(newone, depth-1 , alp , be , selfplayer)) ;
            alp = std::max(value,alp) ;
            if(alp >= be) break ;
        }
        return value ;
    }
    else{
      int value = 1e9 ;
        for( auto it = state->legal_actions.begin() ; it!=state->legal_actions.end() ; ++it){
            tmp = *it;
            newone = state->next_state(tmp);

            if(!depth) value = newone->evaluate() ;
            else value = std::min(value,alpbe(newone, depth-1 , alp , be , selfplayer)) ;
            be = std::min(value,be) ;
            if(alp >= be) break ;
        }
        return value ;
    }
}


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move Alphabeta::get_move(State *state, int depth , int selfplayer){
  if(!state->legal_actions.size())
    state->get_legal_actions();

  Move actions=*(state->legal_actions.begin());
  Move tmp ;
  int alp = -1e9;
  for( auto it = state->legal_actions.begin() ; it!=state->legal_actions.end() ; ++it){
    tmp = *it;

    int value = alpbe(state->next_state(tmp), depth-1 , -1e9 , 1e9 , selfplayer);
    if(value>=alp){
        alp = value ;
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