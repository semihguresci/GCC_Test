#ifndef GTEST_COMMON_HPP
#define GTEST_COMMON_HPP

#include <gtest/gtest.h>

#if defined(__clang__)  
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wanalyzer-malloc-leak"
#endif



#if defined(__clang__)  
#pragma clang diagnostic pop
#endif

#endif  // GTEST_COMMON_HPP