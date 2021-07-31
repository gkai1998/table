#ifndef PREDEFINED_H
#define PREDEFINED_H

#include <string.h>

namespace bpt {

/* predefined B+ info */
#define BP_ORDER 20

/* key/value type */

typedef off64_t value_t;
struct key_t {
    int64_t k;

    key_t(int64_t kk=0)
    {
        k=kk;
    }

    operator bool() const {
        return (k==0);
    }
};

inline int keycmp(const key_t &a, const key_t &b) {
    int x = a.k-b.k;
    return x;
}

#define OPERATOR_KEYCMP(type) \
    bool operator< (const key_t &l, const type &r) {\
        return keycmp(l, r.key) < 0;\
    }\
    bool operator< (const type &l, const key_t &r) {\
        return keycmp(l.key, r) < 0;\
    }\
    bool operator== (const key_t &l, const type &r) {\
        return keycmp(l, r.key) == 0;\
    }\
    bool operator== (const type &l, const key_t &r) {\
        return keycmp(l.key, r) == 0;\
    }

}

#endif /* end of PREDEFINED_H */
