#ifndef benchmark_h
#define benchmark_h

struct Benchmark
{
    std::string detector;
    std::string descriptor;
    std::string matcher;
    std::string selector;

    int total_keypoints;
    int total_matches;
    int total_time;
};


#endif /* benchmark_h */