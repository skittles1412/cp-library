#ifndef CP_LIBRARY_TEMPLATE_H
#define CP_LIBRARY_TEMPLATE_H

#include "bits/extc++.h"

using namespace std;

#ifdef DEBUG
#define dbg(...)                                           \
    cerr << "L" << __LINE__ << " [" << #__VA_ARGS__ << "]" \
         << ": ";                                          \
    [](const auto& __a, const auto&... __b) -> void {      \
        cerr << __a;                                       \
        ((cerr << " | " << __b), ...);                     \
        cerr << endl;                                      \
    }(__VA_ARGS__);
#else
#define cerr   \
    if (false) \
    cerr
#define dbg(...)
#endif

using u32 = uint32_t;
using u64 = uint64_t;
using ld = long double;

#define endl "\n"
#define long int64_t
#define sz(x) int(std::size(x))

#endif  // CP_LIBRARY_TEMPLATE_H
