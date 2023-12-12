#pragma once

#include "fa.hpp"

#include <algorithm>
#include <iterator>
#include <map>
#include <queue>
#include <set>
#include <vector>

struct dfa_item {
    dfa_item(int id, bool acceptable, std::set<int> states) : _id(id), _is_acceptable(acceptable), _states(states) {}
    int  _id;
    bool _is_acceptable;

    std::set<int> _states;
};

class dfa {
public:
    static fa convert(fa nfa) {
        auto dfa_states            = std::vector<dfa_item>();
        int  total_states          = 0;
        auto start_epsilon_closure = find_epsilon_closure(nfa, 0);
        start_epsilon_closure.insert(0);

        std::vector<std::map<char, int>> table;

        dfa_states.push_back(
            dfa_item(total_states++, is_acceptable(nfa, start_epsilon_closure), start_epsilon_closure));
        int current_state = 0;
        // fill in table
        do {
            table.push_back(std::map<char, int>());
            for (char ch : nfa._symbols) {
                table[current_state][ch] = -1;
            }
            for (char ch : nfa._symbols) {
                auto closure = find_char_closure(nfa, dfa_states[current_state]._states, ch);
                if (closure.size() == 0)
                    continue;
                for (auto state : dfa_states) {
                    if (state._states == closure) {
                        table[current_state][ch] = state._id;
                        goto next_char;
                    }
                }
                // new state
                dfa_states.push_back(dfa_item(total_states++, is_acceptable(nfa, closure), closure));
                table[current_state][ch] = total_states - 1;
            next_char:
                continue;
            }
            current_state++;
        } while (current_state != total_states);

        // construct new dfa according to table
        fa new_dfa(total_states);
        for (int from = 0; from < table.size(); ++from)
            for (char ch : nfa._symbols)
                if (table[from][ch] != -1)
                    new_dfa.add_edge(from, table[from][ch], ch);

        // add accept states
        for (auto it : dfa_states)
            if (it._is_acceptable)
                new_dfa._accept_status.insert(it._id);

        new_dfa._symbols = nfa._symbols;
        return new_dfa;
    }

private:
    static std::set<int> find_epsilon_closure(fa nfa, int start) {
        std::set<int>    result;
        std::queue<int>  tmp;
        std::vector<int> visited(nfa._total_status, 0);
        tmp.push(start);
        while (!tmp.empty()) {
            int start = tmp.front();
            tmp.pop();
            if (!visited[start]) {
                for (int i = nfa._head[start]; i != -1; i = nfa._edge[i]._next) {
                    if (nfa._edge[i]._ch == '@') {
                        result.insert(nfa._edge[i]._to);
                        tmp.push(nfa._edge[i]._to);
                    }
                }
                visited[start] = 1;
            }
        }
        return result;
    }

    static std::set<int> find_char_closure(fa nfa, std::set<int> start, char ch) {
        // first get epsilon start
        std::set<int> epsilon_closure_start;
        for (int pt : start)
            for (int i = nfa._head[pt]; i != -1; i = nfa._edge[i]._next)
                if (nfa._edge[i]._ch == ch)
                    epsilon_closure_start.insert(nfa._edge[i]._to);

        // get epsilon closure
        std::set<int> result = epsilon_closure_start;
        for (int pt : epsilon_closure_start) {
            auto          tmp       = find_epsilon_closure(nfa, pt);
            auto          union_tmp = result;
            std::set<int> tmp_result;
            std::set_union(tmp.begin(), tmp.end(), union_tmp.begin(), union_tmp.end(),
                           std::inserter(tmp_result, tmp_result.begin()));
            result = tmp_result;
        }

        return result;
    }

    static bool is_acceptable(fa nfa, std::set<int> states) {
        for (auto state : states)
            if (state == nfa._total_status - 1)
                return true;
        return false;
    }
};