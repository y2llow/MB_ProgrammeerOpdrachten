#include "../include/CFG.h"
#include "../json.hpp"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

CFG::CFG(const string &filename) {
    // JSON-bestand openen
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Fout: kon bestand '" << filename << "' niet openen." << endl;
        return;
    }

    json j;
    input >> j;

    // Variabelen en terminals inlezen
    if (j.contains("Variables") && j["Variables"].is_array()) {
        for (const auto &v : j["Variables"]) V.push_back(v.get<string>());
    }

    if (j.contains("Terminals") && j["Terminals"].is_array()) {
        for (const auto &t : j["Terminals"]) T.push_back(t.get<string>());
    }

    // Producties inlezen
    if (j.contains("Productions") && j["Productions"].is_array()) {
        for (const auto &prod : j["Productions"]) {
            string head = prod["head"].get<string>();
            vector<string> body;

            if (prod.contains("body") && prod["body"].is_array()) {
                for (const auto &sym : prod["body"]) {
                    body.push_back(sym.get<string>());
                }
            }

            // Voeg toe aan producties
            P[head].push_back(body);
        }
    }

    // Startsymbool
    if (j.contains("Start")) {
        S = j["Start"].get<string>();
    }
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

// sorteer producties per variabele in ASCII-volgorde
    for (const auto &var : sortedV) {
        if (P.count(var)) {
            auto bodies = P.at(var);
            std::sort(bodies.begin(), bodies.end(), [](const vector<string> &a, const vector<string> &b) {
                for (size_t i = 0; i < min(a.size(), b.size()); ++i) {
                    if (a[i] != b[i])
                        return a[i] < b[i];
                }
                return a.size() < b.size();
            });

            //Producties printen
            for (const auto &body : bodies) {
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
