#pragma once

#include "fa.hpp"
#include "regexpr.hpp"

#include <stack>
#include <string>
#include <vector>

// convert regexpr to nfa
class nfa {
public:
    static fa convert(reg_string regexpr, int target_enum) {
        std::stack<fa> stk;
        for (int i = 0; i < regexpr._value.size(); ++i) {
            if (!regexpr._value[i]._is_operator)
                stk.push(create_nfa(regexpr._value[i]._value));

            if (regexpr._value[i]._is_operator && regexpr._value[i]._value == '@') {
                fa b = stk.top();
                stk.pop();
                fa a = stk.top();
                stk.pop();
                stk.push(joint_nfa(a, b));
            }
            if (regexpr._value[i]._is_operator && regexpr._value[i]._value == '|') {
                fa b = stk.top();
                stk.pop();
                fa a = stk.top();
                stk.pop();
                stk.push(union_nfa(a, b));
            }
            if (regexpr._value[i]._is_operator && regexpr._value[i]._value == '*') {
                fa a = stk.top();
                stk.pop();
                stk.push(kleene_nfa(a));
            }
        }
        auto result     = stk.top();
        result._symbols = regexpr::get_all_character(regexpr);

        result._accept_status[result._total_status - 1] = target_enum;
        return result;
    }

    static fa combine_nfas(std::vector<fa> nfas) {
        int total_states = 0;
        for (auto nfa : nfas)
            total_states += nfa._total_status;
        fa  new_nfa(total_states + 1);
        int offset = 1;
        for (auto nfa : nfas) {
            int state_in_nfa = 0;
            for (; state_in_nfa < nfa._total_status; ++state_in_nfa)
                for (int i = nfa._head[state_in_nfa]; i != -1; i = nfa._edge[i]._next) {
                    new_nfa.add_edge(state_in_nfa + offset, nfa._edge[i]._to + offset, nfa._edge[i]._ch);
                }
            for (auto i : nfa._accept_status) {
                new_nfa._accept_status[i.first + offset] = i.second;
            }
            new_nfa.add_edge(0, offset, '@');
            for (auto symbol : nfa._symbols)
                new_nfa._symbols.insert(symbol);
            offset += nfa._total_status;
        }
        return new_nfa;
    }

private:
    // create nfa for each character
    static fa create_nfa(char c) {
        fa new_nfa(2);
        new_nfa.add_edge(0, 1, c);
        return new_nfa;
    }

    static fa union_nfa(fa a, fa b) {
        fa new_nfa(a._total_status + b._total_status + 2);

        // a node: [1, a._total_status]
        // b node: [a._total_status + 1, a._total_status + b._total_status]
        // now combine a:
        int offset_a = 1;
        new_nfa.add_edge(0, 1, '@');
        for (int i = 0; i < a._total_status; ++i)
            for (int idx = a._head[i]; idx != -1; idx = a._edge[idx]._next)
                new_nfa.add_edge(i + offset_a, a._edge[idx]._to + offset_a, a._edge[idx]._ch);
        new_nfa.add_edge(a._total_status - 1 + offset_a, a._total_status + b._total_status + 1, '@');
        // now combine b:
        int offset_b = a._total_status + 1;
        new_nfa.add_edge(0, 0 + offset_b, '@');
        for (int i = 0; i < b._total_status; ++i)
            for (int idx = b._head[i]; idx != -1; idx = b._edge[idx]._next)
                new_nfa.add_edge(i + offset_b, b._edge[idx]._to + offset_b, b._edge[idx]._ch);
        new_nfa.add_edge(b._total_status - 1 + offset_b, a._total_status + b._total_status + 1, '@');

        return new_nfa;
    }

    static fa joint_nfa(fa a, fa b) {
        fa new_nfa(a._total_status + b._total_status - 1);

        // a node: [0, a._total_status - 1]
        // b node: [a._total_status - 1, a._total_status + b._total_status - 2]
        // now joint a:
        int offset_a = 0;
        for (int i = 0; i < a._total_status; ++i)
            for (int idx = a._head[i]; idx != -1; idx = a._edge[idx]._next)
                new_nfa.add_edge(i + offset_a, a._edge[idx]._to + offset_a, a._edge[idx]._ch);
        // now joint b:
        int offset_b = a._total_status - 1;
        for (int i = 0; i < b._total_status; ++i)
            for (int idx = b._head[i]; idx != -1; idx = b._edge[idx]._next)
                new_nfa.add_edge(i + offset_b, b._edge[idx]._to + offset_b, b._edge[idx]._ch);

        return new_nfa;
    }

    static fa kleene_nfa(fa a) {
        fa new_nfa(a._total_status + 3);

        // a node: [2, a._total_status + 1]
        int offset_a = 2;
        new_nfa.add_edge(0, 1, '@');
        new_nfa.add_edge(1, 2, '@');
        for (int i = 0; i < a._total_status; ++i)
            for (int idx = a._head[i]; idx != -1; idx = a._edge[idx]._next)
                new_nfa.add_edge(i + offset_a, a._edge[idx]._to + offset_a, a._edge[idx]._ch);
        new_nfa.add_edge(a._total_status - 1 + offset_a, 1, '@');
        new_nfa.add_edge(1, a._total_status + 2, '@');

        return new_nfa;
    }
};
