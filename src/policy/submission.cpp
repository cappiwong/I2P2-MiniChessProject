#include <cstdlib>

#include "../state/state.hpp"
#include "./submission.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

// AIplayer::get_move()


Move submission::get_move(State *state, int depth) {
    // Initial maximum value for comparison and best move holder
    int max_val;
    if(state->player == 0){
      max_val = -10000000;
    }
    else max_val = 10000000;
    Move best_move;

    // Get legal actions if not already available
    if (state->legal_actions.empty()) {
        state->get_legal_actions();
    }

    // Iterate over legal moves
    for (auto move : state->legal_actions) {
        // Create new child state for each move
        State* child_state = state->next_state(move);
        // Call the minimax function for the child state
        int value = minimax(child_state, depth - 1, state->player, -10000000, 10000000);
        // Delete the child_state once we are done with it
        delete child_state;

        // If the value returned by minimax is greater than max_val, update max_val and best_move
        if(state->player == 1 && value < max_val){
            max_val = value;
            best_move = move;
        }
        else if(state->player == 0 && value > max_val){
            max_val = value;
            best_move = move;
        }
        
    }
    // Return the best move found

    
    return best_move;
}

int submission::minimax(State* state, int depth, bool findmax, int alpha_prunning, int beta_prunning) {
  // Implement your own is_terminal() function here
  if(state->legal_actions.size() == 0){
    state->get_legal_actions();
  }

  if (state->legal_actions.size() == 0 || depth == 0) {
    return state->evaluate();
  }

  state->get_legal_actions();

  if (findmax) {
    int max_eval = -10000000;
    for (auto move : state->legal_actions) {
      State* child_state = state->next_state(move);
      int eval = minimax(child_state, depth - 1, false, alpha_prunning, beta_prunning);
      delete child_state; // Delete child_state after using it
      max_eval = std::max(max_eval, eval);
      alpha_prunning = std::max(alpha_prunning, eval);
      if (beta_prunning <= alpha_prunning) {
        break; // Beta cut-off
      }
    }
    return max_eval;
  } else {
    int min_eval = 10000000;
    for (auto move : state->legal_actions) {
      State* child_state = state->next_state(move);
      int eval = minimax(child_state, depth - 1, true, alpha_prunning, beta_prunning);
      delete child_state; // Delete child_state after using it
      min_eval = std::min(min_eval, eval);
      beta_prunning = std::min(beta_prunning, eval);
      if (beta_prunning <= alpha_prunning) {
        break; // Alpha cut-off
      }
    }
    return min_eval;
  }
}



