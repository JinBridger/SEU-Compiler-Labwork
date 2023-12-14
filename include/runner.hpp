#pragma once
#include "fa.hpp"

#include <functional>
#include <map>

struct runnable_fa {
    runnable_fa(fa f) : _fa(f), _current_state(0) {}
    fa  _fa;
    int _current_state;
    // return value:
    // false: failed, true: find
    bool input(char ch) {
        for (int i = _fa._head[_current_state]; i != -1; i = _fa._edge[i]._next) {
            if (_fa._edge[i]._ch == ch) {
                _current_state = _fa._edge[i]._to;
                return true;
            }
        }
        return false;
    }

    void reset() {
        _current_state = 0;
    }
};

class runner {
public:
    // return value:
    // -1: failed, 0: eof
    static int run(fa f, std::string s, std::map<int, std::function<void(void)>> table) {
        int  pos     = 0;
        auto exec    = runnable_fa(f);
        bool reseted = true;
        while (pos < s.length()) {
            bool can_we_put_it_in = exec.input(s[pos]);

            if (can_we_put_it_in == false) {
                // time to check current state
                int result = exec._fa._accept_status[exec._current_state];
                if (result == -1) {
                    // looks like it failed :(
                    if (reseted)
                        return -1;
                    else {
                        exec.reset();
                        reseted = true;
                        continue;
                    }
                }
                // ok, match, reset it and retry!
                table[result]();
                exec.reset();
                reseted = true;
                continue;
            }

            if (pos == s.length() - 1) {
                int result = exec._fa._accept_status[exec._current_state];
                if (result == -1) {
                    return -1;
                }
                table[result]();
            }

            pos++;
            reseted = false;
        }
        return 0;
    }
};