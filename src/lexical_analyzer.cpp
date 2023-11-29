#include "dfa.hpp"
#include "lexical_rules.hpp"

#include <iostream>
#include <string>

int main() {
    std::string id;
    std::cin >> id;
    std::cout << "id: " + id << std::endl;

    auto test = dfa(identifier_rules, identifier_accept_status);

    std::string result = test.verify(id) ? "true" : "false";
    std::cout << "result: " + result;
}