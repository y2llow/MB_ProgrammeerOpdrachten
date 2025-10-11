#include "CFG.h"
#include <algorithm>
#include <sstream>
#include <iostream>

CFG::CFG() {
    // hardcoded voorbeeld
    V = {"BINDIGIT", "S"};
    T = {"0", "1", "a", "b"};
    S = "S";

    P["BINDIGIT"] = {{"0"}, {"1"}};
    P["S"] = { {}, {"a", "S", "b", "BINDIGIT"} };
}

void CFG::print() const {
    std::ostringstream out;

    // V
    out << "V = {";
    auto sortedV = V;
    std::sort(sortedV.begin(), sortedV.end());
    for (size_t i = 0; i < sortedV.size(); i++) {
        out << sortedV[i];
        if (i + 1 != sortedV.size()) out << ", ";
    }
    out << "}\n";

    // T
    out << "T = {";
    auto sortedT = T;
    std::sort(sortedT.begin(), sortedT.end());
    for (size_t i = 0; i < sortedT.size(); i++) {
        out << sortedT[i];
        if (i + 1 != sortedT.size()) out << ", ";
    }
    out << "}\n";

    // P
    out << "P = {\n";
    for (const auto &var : sortedV) { // alfabetisch per variabele
        if (P.count(var)) {
            for (const auto &body : P.at(var)) {
                out << "    " << var << " -> `";
                for (size_t j = 0; j < body.size(); j++) {
                    if (j > 0) out << " ";
                    out << body[j];
                }
                out << "`\n";
            }
        }
    }
    out << "}\n";

    // S
    out << "S = " << S;

    std::cout << out.str() << std::endl;
}