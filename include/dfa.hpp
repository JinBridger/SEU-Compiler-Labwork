#pragma once

#include "lexical_rules.hpp"

#include <string>
#include <vector>

class dfa {
public:
    dfa(const std::vector<lexical_rule>& rules,
        const std::vector<status>&       accept_status)
        : _is_failed(false), _current_status(0), _accept_status(accept_status),
          _rules(100) {
        for (auto& rule : rules) {
            _rules[rule.init_status].push_back(rule);
        }
    }

    bool verify(const std::string& str) {
        _is_failed      = false;
        _current_status = 0;
        for (auto& character : str) {
            move(character);
            if (_is_failed)
                return false;
        }
        return true;
    }

private:
    void move(char c) {
        auto& rule_set = _rules[_current_status];
        for (auto& rule : rule_set) {
            if (rule.move_char == c) {
                _current_status = rule.target_status;
                return;
            }
        }
        _is_failed = true;
    }

    typedef std::vector<lexical_rule> rule_set;

    bool                  _is_failed;
    status                _current_status;
    std::vector<status>   _accept_status;
    std::vector<rule_set> _rules;
};