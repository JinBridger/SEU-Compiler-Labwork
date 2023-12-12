#pragma once

#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <vector>

// actually, it is a graph
// use '@' for epsilon
struct fa {
    fa(int total_status) : _total_status(total_status), _head(std::vector<int>(total_status, -1)) {}

    int _total_status = 0;
    // start status is default 0
    // for nfa, accept status is total status - 1
    // for dfa, accept status is _accept_status

    struct edge {
        int  _to, _next;
        char _ch;
    };
    std::vector<int>  _head;
    std::vector<edge> _edge;

    std::set<char> _symbols;
    std::set<int>  _accept_status;

    void add_edge(int from, int to, char c) {
        _edge.push_back(edge());
        _edge[_edge.size() - 1]._to   = to;
        _edge[_edge.size() - 1]._ch   = c;
        _edge[_edge.size() - 1]._next = _head[from];
        _head[from]                   = _edge.size() - 1;
    }

    void print() {
        for (int i = 0; i < _total_status; ++i) {
            if (_head[i] == -1)
                continue;
            std::cout << "Status " + std::to_string(i) << std::endl;
            for (int idx = _head[i]; idx != -1; idx = _edge[idx]._next)
                std::cout << "    --" << _edge[idx]._ch << "--> " << std::to_string(_edge[idx]._to) << std::endl;
        }
        std::cout << "Accept states: ";
        for (auto i : _accept_status)
            std::cout << i << " ";
        std::cout << std::endl;
    }
};