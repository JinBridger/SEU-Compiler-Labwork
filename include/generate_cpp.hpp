#pragma once

#include <fstream>
#include <string>
#include <utility>
#include <vector>

class generate_cpp {
public:
    void load_source(std::string source_path = "./res/source.cpp") {
        std::ifstream f(source_path);
        std::string   tmp;
        while (std::getline(f, tmp)) {
            _sources.push_back(tmp);
        }
        f.close();
    }

    void find_insert_rule_pos() {
        int i = 0;
        for (; i < _sources.size(); ++i) {
            if (_sources[i].find("// INSERT RULE HERE") != std::string::npos) {
                break;
            }
        }
        _insert_rule_pos = i;
    }

    void insert_parsed_rule(std::pair<std::string, std::string> r) {
        auto regexp = r.first;
        auto action = r.second;

        // build insert statement
        std::string insert_statement = "lexer.add_regexpr(\n";
        // regexpr
        insert_statement += ("\"" + regexp + "\",\n");
        // lambda
        insert_statement += ("[]()\n" + action + "\n");
        // end
        insert_statement += (");\n");

        // insert it!
        // first get iterator
        auto insert_iter = _sources.begin() + _insert_rule_pos + 1;
        _sources.insert(insert_iter, insert_statement);
        _insert_rule_pos++;
    }

    void output_cpp_file(std::string path) {
        std::ofstream of(path, std::fstream::out);
        for (auto statement : _sources) {
            of << statement << std::endl;
        }
        of.close();
    }

    void insert_end_program(std::vector<std::string> vec) {
        for (auto prog : vec)
            _sources.push_back(prog);
    }

    void insert_begin_program(std::vector<std::string> vec) {
        std::string insert_str = "";
        for (auto prog : vec)
            insert_str += (prog + "\n");
        _sources.insert(_sources.begin(), insert_str);
    }

    int _insert_rule_pos;

    std::vector<std::string> _sources;
};