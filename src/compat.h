#pragma once

#define C99 199901L
#define C11 201112L
#define C17 201710L
#define C23 202311L

#if __STDC_VERSION__ < C23
#define constexpr static const
#define static_assert _Static_assert
#endif
