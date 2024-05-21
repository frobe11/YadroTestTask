#include <iostream>
import TapeEmulationController;
import KnowingMemoryCapacitySorter;
import ConfigReader;

int main(int argc, char** argv) {
    ConfigReader reader("../config/config.cfg");
    KnowingMemoryCapacitySorter sorter(reader);
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    sorter.sortTape(inputFile, outputFile);
    return 0;
}
