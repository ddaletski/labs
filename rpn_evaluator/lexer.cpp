#include "lexer.hpp"

#include <iostream>
#include <set>

std::vector<TokenPtr> Lexer::tokenize(const std::string &s) {
    std::vector<TokenPtr> v;

    std::set<int> active; // active rules (currently match)
    std::set<int> matches;  // matched but stopped match

    int start, end;
    std::string substr;

    for(start = 0, end = 1; start < end && end <= s.size(); end++) {
        substr = s.substr(start, end - start);

        int current = 0;
        for (auto rule: rules) {
            bool matched = std::regex_match(substr, rule.first);

            if (active.count(current) == 0 && matched) {
                active.insert(current);
            } else if (active.count(current) && !matched) {
                active.erase(active.find(current));
                matches.insert(current);
            }
            current++;
        }

        switch (matches.size()) {
            case 0:
                break;
            case 1:
                if (active.size() == 0) {
                    v.push_back(rules[*matches.begin()].second(s.substr(start, end - start - 1)));
                    start = end = end - 1;
                }
                matches.clear();
                break;
            default:
                throw "ambiguous case";
                break;
        }
    }

    if (active.size() == 1) {
        v.push_back(rules[*active.begin()].second(s.substr(start, end - start)));
    } else if (active.size() > 1) {
        throw "ambiguous case";
    }

    return v;
}

void Lexer::addRule(const std::regex& re, const Lexer::tokenFactory& factory) {
    rules.push_back(std::make_pair(re, factory));
}
