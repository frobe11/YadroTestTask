module;

#include <libconfig.h++>
#include <iostream>

export module ConfigReader;

export class ConfigReader {
private:
    long long _readDelay;
    long long _writeDelay;
    long long _moveDelay;
    size_t _memoryCapacity;
public:
    explicit ConfigReader(std::string configPath) {
        libconfig::Config cfg;
        cfg.readFile(configPath);
        try {
            _readDelay = _atoi64(cfg.lookup("readDelay"));

        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "No 'readDelay' setting in configuration file." << std::endl;
        }
        catch (const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                      << std::endl;
        } catch (const std::exception &ex) {
            std::cerr << "Exception: " << ex.what() << std::endl;
        }
        try {
            _writeDelay = _atoi64(cfg.lookup("writeDelay"));

        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "No 'writeDelay' setting in configuration file." << std::endl;
        }
        catch (const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                      << std::endl;
        } catch (const std::exception &ex) {
            std::cerr << "Exception: " << ex.what() << std::endl;
        }
        try {
            _moveDelay = _atoi64(cfg.lookup("moveDelay"));

        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "No 'moveDelay' setting in configuration file." << std::endl;
        }
        catch (const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                      << std::endl;
        } catch (const std::exception &ex) {
            std::cerr << "Exception: " << ex.what() << std::endl;
        }
        try {
            _memoryCapacity = _atoi64(cfg.lookup("memoryCapacity"));

        }
        catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "No 'memoryCapacity' setting in configuration file." << std::endl;
        }
        catch (const libconfig::ParseException &pex) {
            std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine() << " - " << pex.getError()
                      << std::endl;
        } catch (const std::exception &ex) {
            std::cerr << "Exception: " << ex.what() << std::endl;
        }
    }

    ~ConfigReader() = default;

    long long getReadDelay() const {
        return _readDelay;
    }

    long long getWriteDelay() const {
        return _writeDelay;
    }

    long long getMoveDelay() const {
        return _moveDelay;
    }

    size_t getMemoryCapacity() const {
        return _memoryCapacity;
    }
};