#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <cassert>

#define ASSERT_THROW(statement, exception)                                     \
    try {                                                                      \
        statement;                                                             \
        assert(0 && "did not throw");                                          \
    } catch (const exception &ex) {                                            \
        (void)ex;                                                              \
    } catch (...) {                                                            \
        assert(0 && "threw something else");                                   \
    }

#endif
