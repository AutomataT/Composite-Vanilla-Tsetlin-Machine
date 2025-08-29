#ifndef INCLUDEENCODEDSETUP_HOG_H
#define INCLUDEENCODEDSETUP_HOG_H
struct IncludeEncodedSetup_hog {
    static constexpr int THRESHOLD = 20;
    static constexpr int CLAUSES = 200;
    static constexpr int CLASSES = 10;
    static constexpr int FEATURES = 634;
    static constexpr int NUMBER_OF_STATES = 200;
    static constexpr int NUMBER_OF_TEST_EXAMPLES = 32;
    static constexpr int TEST_LENGTH_PER32 = 1;
    static constexpr const char* TEST_FEATURE_FILE = "FMNIST_REDRESS_Testfile32.txt";
    static constexpr const char* TEST_CLASSIFICATION_FILE = "FMNIST_REDRESS_classification_file32.txt";
    static constexpr int NUM_OF_INCLUDES = 35476;
    static constexpr const char* INCENC_TA_FILE = "FMNIST634_REDRESS_IncEncTA_C10_CL200_T20.txt";
    static constexpr const char* INC_PER_CLASS_FILE = "FMNIST634_REDRESS_Inc_per_class.txt";
    static constexpr int CLAUSE_POLARITY_BIT = 15;
    static constexpr int BIT_DEMARCATING_CLAUSE_CHANGE = 14;
    static constexpr int INT_VALUE_OF_ENCODING_BITS = 16383;
};
#endif