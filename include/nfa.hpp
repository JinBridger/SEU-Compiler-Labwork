#pragma once

#include "fa.hpp"

#include <stack>
#include <string>
#include <vector>

// convert regexpr to nfa
class nfa {
public:
    static nfa_item convert(std::string regexpr) {
        std::stack<nfa_item> stk;
        for (int i = 0; i < regexpr.length(); ++i) {
            if (regexpr[i] != '@' && regexpr[i] != '|' && regexpr[i] != '*')
                stk.push(create_nfa(regexpr[i]));

            if (regexpr[i] == '@') {
                nfa_item b = stk.top();
                stk.pop();
                nfa_item a = stk.top();
                stk.pop();
                stk.push(joint_nfa(a, b));
            }
            if (regexpr[i] == '|') {
                nfa_item b = stk.top();
                stk.pop();
                nfa_item a = stk.top();
                stk.pop();
                stk.push(union_nfa(a, b));
            }
            if (regexpr[i] == '*') {
                nfa_item a = stk.top();
                stk.pop();
                stk.push(kleene_nfa(a));
            }
        }
        return stk.top();
    }

private:
    // create nfa for each character
    static nfa_item create_nfa(char c) {
        nfa_item new_nfa(2);
        new_nfa.add_edge(0, 1, c);
        return new_nfa;
    }

    static nfa_item union_nfa(nfa_item a, nfa_item b) {
        nfa_item new_nfa(a._total_status + b._total_status + 2);

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

    static nfa_item joint_nfa(nfa_item a, nfa_item b) {
        nfa_item new_nfa(a._total_status + b._total_status - 1);

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

    static nfa_item kleene_nfa(nfa_item a) {
        nfa_item new_nfa(a._total_status + 3);

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
