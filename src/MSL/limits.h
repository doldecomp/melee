#ifndef _STD_LIMITS_H
#define _STD_LIMITS_H

#ifdef __cplusplus
extern "C" {
#endif

#define CHAR_BIT 8

#define SCHAR_MIN (-0x7F - 1)
#define SCHAR_MAX 0x7F
#define UCHAR_MAX 0xFF

#define CHAR_MIN 0
#define CHAR_MAX SCHAR_MAX

#define SHRT_MIN (-0x7FFF - 1)
#define SHRT_MAX 0x7FFF
#define USHRT_MAX 0xFFFF

#define INT_MIN (-0x7FFFFFFF - 1)
#define INT_MAX 0x7FFFFFFF
#define UINT_MAX 0xFFFFFFFF

#define LONG_MIN (-0x7FFFFFFFL - 1)
#define LONG_MAX 0x7FFFFFFFL
#define ULONG_MAX 0xFFFFFFFFUL

#define LLONG_MIN (-0x7FFFFFFFFFFFFFFFLL - 1)
#define LLONG_MAX 0x7FFFFFFFFFFFFFFFLL
#define ULLONG_MAX 0xFFFFFFFFFFFFFFFFULL

#ifdef __cplusplus
}

namespace std {
    template <typename T> class numeric_limits {
    public:
        static inline T min();
        static inline T max();
    };

    template <> class numeric_limits<char> {
    public:
        static inline char min()
        {
            return -0x80;
        }
        static inline char max()
        {
            return 0x7F;
        }
    };

    template <> class numeric_limits<short> {
    public:
        static inline short min()
        {
            return -0x8000;
        }
        static inline short max()
        {
            return 0x7FFF;
        }
    };

    template <> class numeric_limits<int> {
    public:
        static inline int min()
        {
            return -0x80000000;
        }
        static inline int max()
        {
            return 0x7FFFFFFF;
        }
    };

    template <> class numeric_limits<long> {
    public:
        static inline long min()
        {
            return -0x80000000;
        }
        static inline long max()
        {
            return 0x7FFFFFFF;
        }
    };

    template <> class numeric_limits<unsigned char> {
    public:
        static inline unsigned char min()
        {
            return 0x0;
        }
        static inline unsigned char max()
        {
            return 0xFF;
        }
    };

    template <> class numeric_limits<unsigned short> {
    public:
        static inline unsigned short min()
        {
            return 0x0;
        }
        static inline unsigned short max()
        {
            return 0xFFFF;
        }
    };

    template <> class numeric_limits<unsigned int> {
    public:
        static inline unsigned int min()
        {
            return 0x0;
        }
        static inline unsigned int max()
        {
            return 0xFFFFFFFF;
        }
    };

    template <> class numeric_limits<unsigned long> {
    public:
        static inline unsigned long min()
        {
            return 0x0;
        }
        static inline unsigned long max()
        {
            return 0xFFFFFFFF;
        }
    };

} // namespace std
#endif
#endif
