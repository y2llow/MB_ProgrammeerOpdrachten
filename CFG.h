#ifndef TEST_CFG_H
#define TEST_CFG_H

#include <utility>
#include <vector>
#include <map>
#include <string>

using namespace std;

class CFG {
public:
    vector<string> V;
    vector<string> T;
    map<string, vector<vector<string>>> P;
    string S;

    explicit CFG(const string &filename);

    void print() const;
};

#endif