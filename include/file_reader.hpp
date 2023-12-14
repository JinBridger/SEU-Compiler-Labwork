#pragma once

#include <fstream>
#include <string>
#include <utility>
#include <vector>

class file_reader {
public:
    // private:
    void read_file_to_string(std::string filename) {
        std::ifstream f(filename);
        std::string   tmp;
        while (std::getline(f, tmp)) {
            _lines.push_back(tmp);
        }
        f.close();
    }

    void split_sections() {
        int current_lines = 0;
        // split definitions
        while (_lines[current_lines] != "%%") {
            _definitions.push_back(_lines[current_lines++]);
        }
        current_lines++;
        while (_lines[current_lines] != "%%") {
            _rules.push_back(_lines[current_lines++]);
        }
        current_lines++;
        while (current_lines < _lines.size()) {
            _programs.push_back(_lines[current_lines++]);
        }
    }

    std::pair<std::string, std::string> parse_single_rule(std::string line) {
        auto div_pos = line.find("→");
        if (div_pos == std::string::npos) {
            return std::make_pair("", "");
        }
        std::string regexp = line.substr(0, div_pos);
        // "→" has a length of 3
        std::string action = line.substr(div_pos + 3);
        // filter end space in regexp
        int regexp_len = regexp.length();
        for (int i = regexp.length() - 1; i >= 0; --i) {
            if (regexp[i] == ' ') {
                regexp_len--;
            }
            else {
                break;
            }
        }
        std::string fin_regexp = regexp.substr(0, regexp_len);
        return std::make_pair(fin_regexp, action);
    }

    void parse_all_rules() {
        for (auto r : _rules) {
            auto res = parse_single_rule(r);
            if (res.first == "" && res.second == "") {
                continue;
            }
            _parsed_rules.push_back(res);
        }
    }

    void parse_definition_code() {
        int i = 0;
        while (i < _definitions.size()) {
            for (; i < _definitions.size(); ++i) {
                if (_definitions[i] == "%{") {
                    i++;
                    break;
                }
            }
            for (; i < _definitions.size(); ++i) {
                if (_definitions[i] == "%}") {
                    break;
                }
                _definitions_code.push_back(_definitions[i]);
            }
        }
    }

    std::vector<std::string> _lines;

    std::vector<std::string> _definitions;
    std::vector<std::string> _rules;
    std::vector<std::string> _programs;
    std::vector<std::string> _definitions_code;

    std::vector<std::pair<std::string, std::string>> _parsed_rules;
};