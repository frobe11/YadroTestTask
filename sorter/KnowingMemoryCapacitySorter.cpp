module;

#include <fstream>
#include <vector>
#include <algorithm>
#include <libconfig.h++>
#include <iostream>
#include <filesystem>
#include <system_error>

export module KnowingMemoryCapacitySorter;

import TapeEmulationController;
import TapeMerger;
import ConfigReader;

export class KnowingMemoryCapacitySorter {
private:
    size_t _memoryCapacity;
    std::vector<TapeEmulationController> _tapes;
    const ConfigReader _cfg;
    void clearFile(std::string filename){
        std::ofstream ofs;
        ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
    }
public:
    explicit KnowingMemoryCapacitySorter(const ConfigReader &cfg) :
            _memoryCapacity(cfg.getMemoryCapacity()), _tapes(), _cfg(cfg) {
        _memoryCapacity = (long long) _memoryCapacity / 8;
    }

    ~KnowingMemoryCapacitySorter() = default;

    void sortTape(std::string input, std::string output) {
        clearFile("../tapes/" + output);
        TapeEmulationController inputController(input, _cfg);
        TapeEmulationController outputController(output, _cfg);
        std::vector<long long> buffer(_memoryCapacity, 0);
        size_t i = 0;
        bool timeToStop = false;
        int iteration = 0;
        while (!timeToStop) {
            for (i = 0; i < _memoryCapacity; i++) {
                long long temp = inputController.getCurrent();
                buffer[i] = temp;
                if (!inputController.next()) {
                    timeToStop = true;
                    break;
                }
            }

            for (size_t j = i; j < _memoryCapacity; j++) {
                buffer[j] = std::numeric_limits<long long>::max();
            }
            std::sort(buffer.begin(), buffer.end());
            clearFile("../tapes/temp/" + std::to_string(iteration) + "-" + std::to_string(_tapes.size()));
            TapeEmulationController temp("temp/" + std::to_string(iteration) + "-" + std::to_string(_tapes.size()),
                                         _cfg);
            _tapes.push_back(temp);
            for (size_t j = 0; j < i; j++) {
                _tapes[_tapes.size() - 1].nextAdd(buffer[j]);
            }
        }
        std::vector<TapeEmulationController> tempTapes;
        while (_tapes.size() + tempTapes.size() > 2) {
            iteration++;
            if (iteration % 2 == 1) {
                for (int i = _tapes.size() - 1; i >= 0; i -= 2) {
                    if (i == 0) {
                        clearFile("../tapes/temp/" + std::to_string(iteration) + "-" + std::to_string(tempTapes.size()));
                        TapeEmulationController copyTape(_tapes[i], "temp/" + std::to_string(iteration) + "-" +
                                                                     std::to_string(tempTapes.size()));
                        tempTapes.push_back(copyTape);
                        break;
                    }
                    clearFile("../tapes/temp/" + std::to_string(iteration) + "-" + std::to_string(tempTapes.size()));
                    TapeEmulationController newTape(
                            "temp/" + std::to_string(iteration) + "-" + std::to_string(tempTapes.size()), _cfg);
                    TapeMerger::merge(_tapes[i - 1], _tapes[i], newTape);
                    tempTapes.push_back(newTape);
                }
                _tapes.clear();
            } else {
                for (int i = tempTapes.size() - 1; i >= 0; i -= 2) {
                    if (i == 0) {
                        clearFile("../tapes/temp/" + std::to_string(iteration) + "-" + std::to_string(_tapes.size()));
                        TapeEmulationController copyTape(tempTapes[i], "temp/" + std::to_string(iteration) + "-" +
                                                                       std::to_string(_tapes.size()));
                        _tapes.push_back(copyTape);
                        break;
                    }
                    clearFile("../tapes/temp/" + std::to_string(iteration) + "-" + std::to_string(_tapes.size()));
                    TapeEmulationController newTape(
                            "temp/" + std::to_string(iteration) + "-" + std::to_string(_tapes.size()), _cfg);
                    TapeMerger::merge(tempTapes[i - 1], tempTapes[i], newTape);
                    _tapes.push_back(newTape);
                }
                tempTapes.clear();
            }
        }
        if (iteration % 2 == 1) {
            TapeMerger::merge(tempTapes[0], tempTapes[1], outputController);
        } else {
            TapeMerger::merge(_tapes[0], _tapes[1], outputController);
        }
    }
};