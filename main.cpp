#include <iostream>
// #include "CFG.h"
#include "PDA.h"
using namespace std;

int main() {
    PDA pda("input-pda2cfg1.json");
    pda.toCFG().print();
    return 0;
}

// using namespace std;
// int main() {
//     CFG cfg("/home/y2llow/CLionProjects/MB_ProgrammeerOpdrachten/CFG.json");
//     cfg.print();
//     return 0;
// }