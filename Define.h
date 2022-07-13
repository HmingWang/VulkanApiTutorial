//
// Created by 王海明 on 2022/7/13.
//

#pragma once

#include "cstdint"

typedef int64_t     int64;
typedef int32_t     int32;
typedef int16_t     int16;
typedef int8_t      int8;
typedef uint64_t    uint64;
typedef uint32_t    uint32;
typedef uint16_t    uint16;
typedef uint8_t     uint8;

//--------------------------------------------------------------
//Operating System
//--------------------------------------------------------------
#define OS_WINDOWS      1           //Windows system
#define OS_WIN_32       11          //32bit Windows
#define OS_WIN_64       12          //64bit Windows
#define OS_LINUX        2           //linux system
#define OS_MACOS        3           //MacOS system
#define OS_IOS          31          //iPhone iOS system
#define OS_UNDEF_APPLE  39          //undefined apple system
#define OS_UNIX         4           //unix system
#define OS_ANDROID      5           //android system
#define OS_UNKNOWN      9           //undefined system

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define SYSTEM_OS OS_WINDOWS
#ifdef _WIN64
#   define SYSTEM_OS OS_WIN_64
#else
#   define SYSTEM_OS OS_WIN_32
#endif

#elif __APPLE__

#include <TargetConditionals.h>

#if defined(TARGET_OS_OSX)
#define SYSTEM_OS OS_MACOS
#elif TARGET_OS_IPHONE
#define SYSTEM_OS OS_IOS
#else
#define SYSTEM_OS OS_UNDEF_APPLE
#endif

#elif __ANDROID__
#define SYSTEM_OS OS_ANDROID

#elif __linux__
#define SYSTEM_OS OS_LINUX

#elif __unix__
#define SYSTEM_OS OS_UNIX

#else
#define SYSTEM_OS OS_UNKNOWN
#endif

//--------------------------------------------------------------
//Compiler
//--------------------------------------------------------------
#define SYSTEM_COMPILER_MICROSOFT      1
#define SYSTEM_COMPILER_BORLAND        2
#define SYSTEM_COMPILER_INTEL          3
#define SYSTEM_COMPILER_GNU            4

#ifdef _MSC_VER
#  define SYSTEM_COMPILER SYSTEM_COMPILER_MICROSOFT
#elif defined( __BORLANDC__ )
#  define SYSTEM_COMPILER SYSTEM_COMPILER_BORLAND
#elif defined( __INTEL_COMPILER )
#  define SYSTEM_COMPILER SYSTEM_COMPILER_INTEL
#elif defined( __GNUC__ )
#  define SYSTEM_COMPILER SYSTEM_COMPILER_GNU
#  define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#  error "FATAL ERROR: Unknown compiler."
#endif
