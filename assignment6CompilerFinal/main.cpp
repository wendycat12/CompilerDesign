// Wendy Catalan
// Assignment 6 Final Project Compiler Design Phase 1
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SLRParser {
private:
    vector<vector<string>> action_table;
    vector<vector<int>> goto_table;

public:
    SLRParser() {
        // Initialize action table (12 states × 6 terminals)
        action_table = {
            {"s5", "",   "",   "s4", "",   ""  },  // State 0
            {"",   "s6", "",   "",   "",   "acc"},  // State 1
            {"",   "r2", "s7", "",   "r2", "r2"},  // State 2
            {"",   "r4", "r4", "",   "r4", "r4"},  // State 3
            {"s5", "",   "",   "s4", "",   ""  },  // State 4
            {"",   "r6", "r6", "",   "r6", "r6"},  // State 5
            {"s5", "",   "",   "s4", "",   ""  },  // State 6
            {"s5", "",   "",   "s4", "",   ""  },  // State 7
            {"",   "s6", "",   "",   "s11", ""  }, // State 8
            {"",   "r1", "s7", "",   "r1", "r1"},  // State 9
            {"",   "r3", "r3", "",   "r3", "r3"},  // State 10
            {"",   "r5", "r5", "",   "r5", "r5"}   // State 11
        };

        // Initialize goto table (12 states × 3 non-terminals)
        goto_table = {
            {1, 2, 3},  // State 0
            {0, 0, 0},  // State 1
            {0, 0, 0},  // State 2
            {0, 0, 0},  // State 3
            {8, 2, 3},  // State 4
            {0, 0, 0},  // State 5
            {0, 9, 3},  // State 6
            {0, 0, 10}, // State 7
            {0, 0, 0},  // State 8
            {0, 0, 0},  // State 9
            {0, 0, 0},  // State 10
            {0, 0, 0}   // State 11
        };
    }

    int get_column(char c) {
        switch(c) {
            case 'i': return 0;  // id
            case '+': return 1;
            case '*': return 2;
            case '(': return 3;
            case ')': return 4;
            case '$': return 5;
            default: return -1;
        }
    }

    void print_tables() {
        cout << "SLR Parsing Tables:\n\n";
        cout << "STATE |         ACTION          | GOTO\n";
        cout << "      | id  +   *   (   )   $   | E  T  F\n";
        cout << "-----------------------------------------\n";

        for (int i = 0; i < 12; i++) {
            printf("%-5d | ", i);

            // Print action table
            for (const string& action : action_table[i]) {
                printf("%-3s ", action.c_str());
            }
            cout << "| ";

            // Print goto table
            for (int goto_val : goto_table[i]) {
                if (goto_val != 0) {
                    printf("%-2d ", goto_val);
                } else {
                    printf("   ");
                }
            }
            cout << "\n";
        }
    }

    bool parse(string input) {
        vector<int> state_stack;
        state_stack.push_back(0);  // Start state
        input += "$";
        int pos = 0;

        while (true) {
            int current_state = state_stack.back();
            char current_symbol = input[pos];
            
            if (current_symbol == 'd') {
                pos++;
                continue;  // Skip 'd' in "id"
            }
            
            int col = get_column(current_symbol);
            if (col == -1) {
                cout << "Invalid input symbol at position " << pos << "\n";
                return false;
            }

            string action = action_table[current_state][col];
            
            if (action.empty()) {
                cout << "Error at state " << current_state << " with symbol " << current_symbol << "\n";
                return false;
            }

            if (action == "acc") {
                return true;
            }

            char action_type = action[0];
            int action_value = stoi(action.substr(1));

            if (action_type == 's') {
                state_stack.push_back(action_value);
                pos++;
                if (current_symbol == 'i') pos++;  // Skip 'd' in "id"
            }
            else if (action_type == 'r') {
                // Number of symbols to pop for each reduction rule
                vector<int> rule_length = {1, 3, 1, 3, 1, 3, 1};  // Rule 0 is added for indexing
                // Non-terminal produced by each rule (0=E, 1=T, 2=F)
                vector<int> rule_nonterminal = {0, 0, 0, 1, 1, 2, 2};
                
                // Pop states according to rule length
                int pop_count = rule_length[action_value];
                for (int i = 0; i < pop_count; i++) {
                    state_stack.pop_back();
                }

                // Get goto state
                int goto_state = state_stack.back();
                int non_terminal = rule_nonterminal[action_value];
                
                int next_state = goto_table[goto_state][non_terminal];
                if (next_state != 0) {
                    state_stack.push_back(next_state);
                } else {
                    cout << "Error: Invalid goto state for state " << goto_state
                         << " and non-terminal " << non_terminal << "\n";
                    return false;
                }
            }
        }
    }
};

int main() {
    SLRParser parser;
    parser.print_tables();
    
    string test_input = "id+id*id";
    cout << "\n\nTesting input '" << test_input << "': ";
    if (parser.parse(test_input)) {
        cout << "Accepted!\n\n";
    } else {
        cout << "Rejected.\n\n";
    }
    
    return 0;
}
