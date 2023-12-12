#pragma once

#include <set>
#include <stack>
#include <string>

// convert to postfix expr
class regexpr {
public:
    static std::string convert(std::string regexpr) {
        return convert_to_postfix(add_connect_operator(regexpr));
    }

    static std::set<char> get_all_character(std::string regexpr) {
        std::set<char> result;
        for (auto ch : regexpr)
            if (!is_regexpr_operator(ch))
                result.insert(ch);
        return result;
    }

private:
    // operator priority: * > | > @
    static std::string add_connect_operator(std::string regexpr) {
        std::string new_regexpr = "";
        new_regexpr += regexpr[0];
        for (int i = 1; i < regexpr.length(); ++i) {
            bool add_connect = false;

            char curr_char = regexpr[i];
            char last_char = new_regexpr[new_regexpr.length() - 1];

            // case 1: add between 2 non-operator character
            if (!is_regexpr_operator(last_char) && !is_regexpr_operator(curr_char))
                add_connect = true;

            // case 2: add between non-operator and '('
            if (!is_regexpr_operator(last_char) && curr_char == '(')
                add_connect = true;

            // case 3: add between ')' and non-operator
            if (last_char == ')' && !is_regexpr_operator(curr_char))
                add_connect = true;

            // case 4: add between '*' and non-operator
            if (last_char == '*' && !is_regexpr_operator(curr_char))
                add_connect = true;

            // case 5: add between '*' and '('
            if (last_char == '*' && curr_char == '(')
                add_connect = true;

            if (add_connect)
                new_regexpr += '@';

            new_regexpr += curr_char;
        }
        return new_regexpr;
    }

    static std::string convert_to_postfix(std::string regexpr) {
        std::stack<char> operator_stack;
        std::stack<char> intermediate_stack;
        for (int i = 0; i < regexpr.length(); ++i) {
            // non-operator
            if (!is_regexpr_operator(regexpr[i])) {
                intermediate_stack.push(regexpr[i]);
                continue;
            }

            // left parenthese
            if (regexpr[i] == '(') {
                operator_stack.push(regexpr[i]);
                continue;
            }

            // right parenthese
            if (regexpr[i] == ')') {
                while (operator_stack.top() != '(') {
                    intermediate_stack.push(operator_stack.top());
                    operator_stack.pop();
                }
                operator_stack.pop();
                continue;
            }

            // other operators
            while (!operator_stack.empty() && operator_stack.top() != '('
                   && !compare_priority(regexpr[i], operator_stack.top())) {
                intermediate_stack.push(operator_stack.top());
                operator_stack.pop();
            }

            operator_stack.push(regexpr[i]);
        }
        while (!operator_stack.empty()) {
            intermediate_stack.push(operator_stack.top());
            operator_stack.pop();
        }

        std::stack<char> revert_stack;
        while (!intermediate_stack.empty()) {
            revert_stack.push(intermediate_stack.top());
            intermediate_stack.pop();
        }

        std::string new_regexpr = "";
        while (!revert_stack.empty()) {
            new_regexpr += revert_stack.top();
            revert_stack.pop();
        }

        return new_regexpr;
    }

    static bool is_regexpr_operator(char c) {
        if (c == '*' || c == '|' || c == '(' || c == ')' || c == '@')
            return true;
        return false;
    }

    // return true when a has higher priority than b
    static bool compare_priority(char a, char b) {
        auto convert_int = [](char a) -> int {
            switch (a) {
            case '(':
                return 0;
            case '*':
                return -1;
            case '|':
                return -2;
            case '@':
                return -3;
            }
            return 1;
        };

        return convert_int(a) > convert_int(b);
    }
};