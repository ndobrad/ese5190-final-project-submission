

#ifndef _NO_ML_EXAMPLE_SETTINGS_H
#define _NO_ML_EXAMPLE_SETTINGS_H

constexpr int kNumCols     = 96;
constexpr int kNumRows     = 96;
constexpr int kNumChannels = 1;

constexpr int kMaxImageSize = kNumCols * kNumRows * kNumChannels;

constexpr int      kCategoryCount   = 2;
constexpr int      kPersonIndex     = 1;
constexpr int      kNotAPersonIndex = 0;
extern const char *kCategoryLabels[kCategoryCount];

#endif