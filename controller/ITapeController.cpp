export module ITapeController;

export class ITapeController {
protected:
    ITapeController() = default;

    virtual ~ITapeController() = default;

public:
    virtual bool next() {
        return false;
    };

    virtual void nextAdd(long long val = 0) {

    };

    virtual void prev() {

    };

    virtual long long getCurrent() const {
        return 0;
    };

    virtual void setCurrent(long long val) const {
    };

    virtual size_t position() const {
        return 0;
    };

    virtual size_t size() const {
        return 0;
    };
};