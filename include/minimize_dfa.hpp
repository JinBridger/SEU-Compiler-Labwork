#pragma once

#include "fa.hpp"

#include <set>
#include <tuple>
#include <utility>
#include <vector>

class minimize_dfa {
public:
    static fa convert(fa dfa) {
        auto init_split_group = init_split(dfa);
        auto final_group      = split_group(dfa, init_split_group);

        final_group = move_forward_zero(final_group);
        fa new_dfa(final_group.size());

        std::set<std::tuple<int, int, char>> add_buffer;

        for (int from = 0; from < final_group.size(); ++from) {
            for (auto state : final_group[from]) {
                for (int i = dfa._head[state]; i != -1; i = dfa._edge[i]._next) {
                    int dst = in_which_group(final_group, dfa._edge[i]._to);
                    int ch  = dfa._edge[i]._ch;
                    add_buffer.insert(std::tuple<int, int, char>(from, dst, ch));
                }
            }
        }

        for (auto param : add_buffer) {
            new_dfa.add_edge(std::get<0>(param), std::get<1>(param), std::get<2>(param));
        }

        for (auto i : dfa._accept_status)
            new_dfa._accept_status[in_which_group(final_group, i.first)] = i.second;
        return new_dfa;
    }

private:
    static std::vector<std::vector<int>> init_split(fa dfa) {
        // split accept & non-accept
        auto result              = std::vector<std::vector<int>>();
        auto total_accept_status = std::set<int>();
        for (int i = 0; i < dfa._total_status; ++i) {
            total_accept_status.insert(dfa._accept_status[i]);
        }
        for (auto accept_status : total_accept_status) {
            std::vector<int> tmp_group;
            for (int i = 0; i < dfa._total_status; ++i) {
                if (dfa._accept_status[i] == accept_status) {
                    tmp_group.push_back(i);
                }
            }
            result.push_back(tmp_group);
        }
        return result;
    }

    static std::vector<std::vector<int>> split_group(fa dfa, std::vector<std::vector<int>> input) {
        std::vector<std::vector<int>> result;
        std::vector<std::vector<int>> last_result;
        std::vector<std::vector<int>> this_result;
        do {
            last_result = this_result;
            this_result.clear();
            for (char ch : dfa._symbols) {
                for (auto group : input) {
                    std::vector<int> dest_groups;
                    for (auto state : group) {
                        int dest_state = -1;
                        int dest_group = -1;
                        for (int i = dfa._head[state]; i != -1; i = dfa._edge[i]._next) {
                            if (dfa._edge[i]._ch == ch) {
                                dest_state = dfa._edge[i]._to;
                                break;
                            }
                        }
                        if (dest_state != -1) {
                            for (auto i = 0; i < input.size(); ++i)
                                for (auto j : input[i])
                                    if (dest_state == j)
                                        dest_group = i;
                        }
                        dest_groups.push_back(dest_group);
                    }
                    // split
                    std::set<int> dests(dest_groups.begin(), dest_groups.end());
                    for (auto dest : dests) {
                        std::vector<int> tmp_group;
                        for (int i = 0; i < dest_groups.size(); ++i) {
                            if (dest_groups[i] == dest) {
                                tmp_group.push_back(group[i]);
                            }
                        }
                        this_result.push_back(tmp_group);
                    }
                }
                input = this_result;
                this_result.clear();
            }
            this_result = input;
        } while (this_result != last_result);
        return input;
    }

    static int in_which_group(std::vector<std::vector<int>> groups, int state) {
        for (int i = 0; i < groups.size(); ++i) {
            for (auto e : groups[i]) {
                if (e == state)
                    return i;
            }
        }
        return -1;
    }

    static std::vector<std::vector<int>> move_forward_zero(std::vector<std::vector<int>> groups) {
        int i = 0;
        for (; i < groups.size(); ++i) {
            for (auto state : groups[i])
                if (state == 0)
                    goto find_zero;
        }
    find_zero:
        std::swap(groups[0], groups[i]);
        return groups;
    }
};