#ifndef TEST_CFG_H
#define TEST_CFG_H

#include <utility>
#include <vector>
#include <map>
#include <string>

using namespace std;

class CFG {
public:
    std::vector<string> V;
    std::vector<string> T;
    std::map<string, vector <vector <string>>> P;
    string S;

    CFG();
    void print() const;
};


#endif //TEST_CFG_H
