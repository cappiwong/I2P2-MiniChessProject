#include <cstdlib>

#include "../state/state.hpp"
#include "./AIplayer.hpp"


/**
 * @brief Randomly get a legal action
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */
Move AIplayer::get_move(State *state, int depth) {
    if(!state->legal_actions.size()) 
        state->get_legal_actions();

    std::vector<Move> actions = state->legal_actions;

    int bestValue = -10000000; // Initialize to very small number
    Move bestMove;

    // Alpha-beta values initialization
    int alpha = -10000000;
    int beta = 10000000;

    for(auto move : actions) {
        State* child_state = state->next_state(move);
        int value = minimax(child_state, depth, false, alpha, beta); // False because we're considering opponent's best move
        //delete child_state; // Delete child_state after using it

        if(value > bestValue) {
            bestValue = value;
            bestMove = move;
        }
    }

    return bestMove;
}


/*int AIpolicy::minimax(State* state, int depth, bool maximizingPlayer) {
    // Implement your own is_terminal() function here
    if (depth == 0 || is_terminal(state)) {
        return state->evaluate();
    }

    std::vector<Move> legal_actions = state->legal_actions;

    if (maximizingPlayer) {
        int max_eval = -10000000; // starting with negative infinity
        for(auto move : legal_actions) {
            State* child_state = state->next_state(move);
            int eval = minimax(child_state, depth - 1, false);
            delete child_state;
            max_eval = std::max(max_eval, eval);
        }
        return max_eval;
    } else {
        int min_eval = 10000000; // starting with positive infinityt
        for(auto move : legal_actions) {
            State* child_state = state->next_state(move);
            int eval = minimax(child_state, depth - 1, true);
            delete child_state;
            min_eval = std::min(min_eval, eval);
        }
        return min_eval;
    }
}*/

int AIplayer::minimax(State* state, int depth, bool maximizingPlayer, int alpha, int beta) {
    // Implement your own is_terminal() function here
    if (depth == 0 ) {
        return state->evaluate();
    }

    std::vector<Move> legal_actions = state->legal_actions; // use the stored legal actions

    if (maximizingPlayer) {
        int max_eval = -10000000; // starting with negative infinity concept
        for(auto move : legal_actions) {
            State* child_state = state->next_state(move);
            int eval = minimax(child_state, depth - 1, false, alpha, beta);
            //delete child_state; // You should delete it if you're done using it
            max_eval = std::max(max_eval, eval);
            alpha = std::max(alpha, eval);
            if(beta <= alpha){
                break; // beta cut-off
            }
        }
        return max_eval;
    } else {
        int min_eval = 10000000; // starting with positive infinity concept
        for(auto move : legal_actions) {
            State* child_state = state->next_state(move);
            int eval = minimax(child_state, depth - 1, true, alpha, beta);
            //delete child_state; // You should delete it if you're done using it
            min_eval = std::min(min_eval, eval);
            beta = std::min(beta, eval);
            if(beta <= alpha){
                break; // alpha cut-off
            }
        }
        return min_eval;
    }
}



