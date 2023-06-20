#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"

int alphabeta(State *state, int depth , int alp , int be , int selfplayer){

    if(!state->legal_actions.size())
    state->get_legal_actions();

    Move tmp;
    State* newone ;
    int alpha=alp , beta=be;

    if(state->player==selfplayer){

      int value = -1e9 ;
      int t;
      for( auto it = state->legal_actions.begin() ; it!=state->legal_actions.end() ; ++it){
        tmp = *it;
        newone = state->next_state(tmp);

        if(!depth) value = newone->evaluate() ;
        else {
          t = alphabeta(newone, depth-1 , alpha , beta , selfplayer);
          if(t>value)
            value = t ;
        }

        if(alpha<value){
          alpha = value ;
        }

        if(alpha >= beta) break ;
      }

      return value ;
    }
    else{
      int value = 1e9 ;
      int t;
      for( auto it = state->legal_actions.begin() ; it!=state->legal_actions.end() ; ++it){
        tmp = *it;
        newone = state->next_state(tmp);

        if(!depth) value = newone->evaluate() ;
        else {
          t = alphabeta(newone, depth-1 , alpha , beta , selfplayer);
          if(t<value)
            value = t ;
        }

        if(beta>value){
          beta = value ;
        }

        if(alpha >= beta) break ;
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
Move Submission::get_move(State *state, int depth , int selfplayer){
  if(!state->legal_actions.size())
    state->get_legal_actions();

  Move actions=*(state->legal_actions.begin());
  Move tmp ;
  State* newone;
  int alp = -1e9;
  for( auto it = state->legal_actions.begin() ; it!=state->legal_actions.end() ; ++it){
    tmp = *it;
    newone = state->next_state(tmp) ;

    int value = alphabeta(newone, depth-1 , -1e9 , 1e9 , selfplayer);
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