module;
#include <fstream>
#include <iostream>
#include <sstream>
#include "windows.h"
export module TapeEmulationController;

import ITapeController;
import ConfigReader;

export class TapeEmulationController : public ITapeController {
private:
    std::string _filename;
    const std::string _prefix;
    const long long _readDelay;
    const long long _writeDelay;
    const long long _moveDelay;
    size_t _position;
    size_t _size;
public:
    explicit TapeEmulationController(const std::string &filename, const ConfigReader &cfg)
            : _prefix("../tapes/"),
              _filename(std::move(filename)),
              _readDelay(cfg.getReadDelay()),
              _writeDelay(cfg.getWriteDelay()),
              _moveDelay(cfg.getMoveDelay())
              , _position(0), _size(0) {
        _filename = _prefix + _filename;
        std::fstream file(_filename, std::ios::in | std::ios::out);
        if (!file) {
            std::ofstream ofile(_filename);
            file.open(_filename, std::ios::in | std::ios::out);
        }
        std::string word;
        while (file >> word) {
            _size++;
        }
        file.close();

    };

    explicit TapeEmulationController(const TapeEmulationController& other, const std::string& filename) :
    _prefix(other._prefix), _filename(filename),
    _readDelay(other._readDelay),_writeDelay(other._writeDelay),
    _moveDelay(other._moveDelay), _position(other._position), _size(other._size)
    {
        _filename = _prefix + _filename;
        std::fstream file(_filename, std::ios::in | std::ios::out);
        if (!file) {
            std::ofstream ofile(_filename);
            file.open(_filename, std::ios::in | std::ios::out);
        }
        std::fstream otherFile(other._filename, std::ios::in | std::ios::out);
        file << otherFile.rdbuf();
        file.close();
    }

    ~TapeEmulationController() override = default;

    void prev() override {
        SleepEx(_moveDelay, false);
        if (_position == 0)
            return;
        _position--;
    }

    bool next() override {
        SleepEx(_moveDelay, false);
        if (_position + 1 > _size) {
            return false;
        }
        _position++;
        return true;
    }

    void nextAdd(long long val = 0) override {
        SleepEx(_moveDelay+_writeDelay, false);
        if (next()) {
            setCurrent(val);
            return;
        }
        _size++;
        _position++;
        std::fstream file(_filename, std::ios::app);
        if (_size == 1) {
            file << val;
        }
        else{
            file << " " << val;
        }
    }
    long long getCurrent() const override {
        SleepEx(_readDelay, false);
        long long res;
        std::fstream file(_filename, std::ios::in);
        for (size_t i = 0; i <= _position; i++) {
            file >> res;
        }
        return res;
    }

    void setCurrent(long long val) const override {
        SleepEx(_writeDelay, false);
        std::fstream file(_filename, std::ios::in | std::ios::out);
        std::stringstream newFile(std::stringstream::in | std::stringstream::out);
        long long temp;
        for (size_t i = 0; i < _size; i++) {
            file >> temp;
            if (i == _position) {
                temp = val;
            }
            newFile << temp << " ";
        }
        file.close();
        newFile.seekp(0);
        file.open(_filename, std::ios::in | std::ios::out);
        while (newFile >> temp) {
            file << temp << " ";
        }
        file.close();
    }

    size_t position() const override {
        return _position;
    }

    size_t size() const override {
        return _size;
    }
};