#ifndef INCLUDEENCODEDSETUP_THRESH_H
#define INCLUDEENCODEDSETUP_THRESH_H
struct IncludeEncodedSetup {
    static constexpr int THRESHOLD = 10;
    static constexpr int CLAUSES = 200;
    static constexpr int CLASSES = 10;
    static constexpr int FEATURES = 784;
    static constexpr int NUMBER_OF_STATES = 200;
    static constexpr int NUMBER_OF_TEST_EXAMPLES = 32;
    static constexpr int TEST_LENGTH_PER32 = 1;
    static constexpr const char* TEST_FEATURE_FILE = "MNIST_REDRESS_Testfile32.txt";
    static constexpr const char* TEST_CLASSIFICATION_FILE = "MNIST_REDRESS_classification_file32.txt";
    static constexpr int NUM_OF_INCLUDES = 68599;
    static constexpr const char* INCENC_TA_FILE = "MNIST784_REDRESS_IncEncTA_C10_CL200_T10.txt";
    static constexpr const char* INC_PER_CLASS_FILE = "MNIST784_REDRESS_Inc_per_class.txt";
    static constexpr int CLAUSE_POLARITY_BIT = 15;
    static constexpr int BIT_DEMARCATING_CLAUSE_CHANGE = 14;
    static constexpr int INT_VALUE_OF_ENCODING_BITS = 16383;
};
#endif