#pragma once

#include <set>
#include <stack>
#include <string>
#include <vector>

struct reg_char {
    reg_char(char v, bool is_op) : _value(v), _is_operator(is_op) {}
    char _value;
    bool _is_operator;
};

struct reg_string {
    std::vector<reg_char> _value;
};

// convert to postfix expr
class regexpr {
public:
    static reg_string convert(std::string regexpr) {
        return convert_to_postfix(add_connect_operator(convert_reg_string(replace_keyword(regexpr))));
    }

    static std::set<char> get_all_character(reg_string regexpr) {
        std::set<char> result;
        for (auto ch : regexpr._value)
            if (!ch._is_operator)
                result.insert(ch._value);
        return result;
    }

private:
    static std::string replace_keyword(std::string regexpr) {
        // replace a-z
        while (true) {
            auto pos = regexpr.find("a-z");
            if (pos == std::string::npos) {
                break;
            }
            regexpr.replace(pos, 3, "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z");
        }
        // replace A-Z
        while (true) {
            auto pos = regexpr.find("A-Z");
            if (pos == std::string::npos) {
                break;
            }
            regexpr.replace(pos, 3, "A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z");
        }
        // replace 0-9
        while (true) {
            auto pos = regexpr.find("0-9");
            if (pos == std::string::npos) {
                break;
            }
            regexpr.replace(pos, 3, "0|1|2|3|4|5|6|7|8|9");
        }
        return regexpr;
    }

    static reg_string convert_reg_string(std::string regexpr) {
        reg_string result;
        for (int i = 0; i < regexpr.length(); ++i) {
            if (regexpr[i] == '\\') {
                i++;
                result._value.push_back(reg_char(regexpr[i], false));
                continue;
            }
            if (is_regexpr_operator(regexpr[i])) {
                result._value.push_back(reg_char(regexpr[i], true));
            }
            else {
                result._value.push_back(reg_char(regexpr[i], false));
            }
        }
        return result;
    }

    // operator priority: * > | > @
    static reg_string add_connect_operator(reg_string regexpr) {
        reg_string new_regexpr;
        new_regexpr._value.push_back(regexpr._value[0]);
        for (int i = 1; i < regexpr._value.size(); ++i) {
            bool add_connect = false;

            auto curr_char = regexpr._value[i];
            auto last_char = new_regexpr._value[new_regexpr._value.size() - 1];

            // case 1: add between 2 non-operator character
            if (!last_char._is_operator && !curr_char._is_operator)
                add_connect = true;

            // case 2: add between non-operator and '('
            if (!last_char._is_operator && curr_char._is_operator && curr_char._value == '(')
                add_connect = true;

            // case 3: add between ')' and non-operator
            if (last_char._is_operator && last_char._value == ')' && !curr_char._is_operator)
                add_connect = true;

            // case 4: add between '*' and non-operator
            if (last_char._is_operator && last_char._value == '*' && !curr_char._is_operator)
                add_connect = true;

            // case 5: add between '*' and '('
            if (last_char._is_operator && last_char._value == '*' && curr_char._is_operator && curr_char._value == '(')
                add_connect = true;

            if (add_connect)
                new_regexpr._value.push_back(reg_char('@', true));

            new_regexpr._value.push_back(curr_char);
        }
        return new_regexpr;
    }

    static reg_string convert_to_postfix(reg_string regexpr) {
        std::stack<reg_char> operator_stack;
        std::stack<reg_char> intermediate_stack;
        for (int i = 0; i < regexpr._value.size(); ++i) {
            // non-operator
            if (!regexpr._value[i]._is_operator) {
                intermediate_stack.push(regexpr._value[i]);
                continue;
            }

            // left parenthese
            if (regexpr._value[i]._is_operator && regexpr._value[i]._value == '(') {
                operator_stack.push(regexpr._value[i]);
                continue;
            }

            // right parenthese
            if (regexpr._value[i]._is_operator && regexpr._value[i]._value == ')') {
                while (!(operator_stack.top()._value == '(' && operator_stack.top()._is_operator)) {
                    intermediate_stack.push(operator_stack.top());
                    operator_stack.pop();
                }
                operator_stack.pop();
                continue;
            }

            // other operators
            while (!operator_stack.empty() && !(operator_stack.top()._value == '(' && operator_stack.top()._is_operator)
                   && !compare_priority(regexpr._value[i]._value, operator_stack.top()._value)) {
                intermediate_stack.push(operator_stack.top());
                operator_stack.pop();
            }

            operator_stack.push(regexpr._value[i]);
        }
        while (!operator_stack.empty()) {
            intermediate_stack.push(operator_stack.top());
            operator_stack.pop();
        }

        std::stack<reg_char> revert_stack;
        while (!intermediate_stack.empty()) {
            revert_stack.push(intermediate_stack.top());
            intermediate_stack.pop();
        }

        reg_string new_regexpr;
        while (!revert_stack.empty()) {
            new_regexpr._value.push_back(revert_stack.top());
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