module;

#include <fstream>

export module TapeMerger;

import ITapeController;

export class TapeMerger {
public:
    //tapes should be sorted
    static void merge(ITapeController &first, ITapeController &second, ITapeController &result) {
        while (first.position() > 0) {
            first.prev();
        }
        while (second.position() > 0) {
            second.prev();
        }
        while (result.position() > 0) {
            result.prev();
        }
        while (first.position() < first.size() && second.position() < second.size()) {
            if (first.getCurrent() < second.getCurrent()) {
                if (result.size() != 0 && result.position() == 0) {
                    result.setCurrent(first.getCurrent());
                    first.next();
                    continue;
                }
                result.nextAdd(first.getCurrent());
                first.next();
            } else {
                if (result.size() != 0 && result.position() == 0) {
                    result.setCurrent(second.getCurrent());
                    second.next();
                    continue;
                }
                result.nextAdd(second.getCurrent());
                second.next();
            }
        }
        while (first.position() < first.size()) {
            if (result.size() != 0 && result.position() == 0) {
                result.setCurrent(first.getCurrent());
                first.next();
                continue;
            }
            result.nextAdd(first.getCurrent());
            first.next();
        }
        while (second.position() < second.size()) {
            if (result.size() != 0 && result.position() == 0) {
                result.setCurrent(second.getCurrent());
                second.next();
                continue;
            }
            result.nextAdd(second.getCurrent());
            second.next();
        }
        while (first.position() > 0) {
            first.prev();
        }
        while (second.position() > 0) {
            second.prev();
        }
        while (result.position() > 0) {
            result.prev();
        }
    }
};