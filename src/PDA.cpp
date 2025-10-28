#include "../include/PDA.h"
#include "../json.hpp"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

using json = nlohmann::json;

PDA::PDA(const string &filename) {
    // JSON-bestand openen
    ifstream input(filename);
    if (!input.is_open()) {
        cerr << "Fout: kon bestand '" << filename << "' niet openen." << endl;
        return;
    }

    json j;
    input >> j;

    //States inlezen
    if (j.contains("States") && j["States"].is_array()) {
        for (const auto &state : j["States"]) States.push_back(state.get<string>());
    }

    //Alphabet inlezen
    if (j.contains("Alphabet") && j["Alphabet"].is_array()) {
        for (const auto &alphabet : j["Alphabet"]) Alphabet.push_back(alphabet.get<string>());
    }

    // StackAlphabet inlezen
    if (j.contains("StackAlphabet") && j["StackAlphabet"].is_array()) {
        for (const auto &stackAlphabet : j["StackAlphabet"]) StackAlphabet.push_back(stackAlphabet.get<string>());
    }

    //transities inlezen
    if (j.contains("Transitions") && j["Transitions"].is_array()) {
        for (const auto &trans : j["Transitions"]) {
            Transition _transition;
            _transition.from = trans["from"].get<string>();
            _transition.input =  trans["input"].get<string>();
            _transition.stacktop = trans["stacktop"].get<string>();
            _transition.to = trans["to"].get<string>();


            if (trans.contains("replacement") && trans["replacement"].is_array()) {
                for (const auto &repl : trans["replacement"]) {
                    _transition.replacement.push_back(repl.get<string>());
                }
            }
            Transitions.push_back(_transition) ;
        }
    }


    //StartState inlezen
    if (j.contains("StartState")) {
        StartState = j["StartState"].get<string>();
    }

    //StartStack inlezen
    if (j.contains("StartStack")) {
        StartStack = j["StartStack"].get<string>();
    }
}
