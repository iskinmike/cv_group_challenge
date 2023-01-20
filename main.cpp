#include <iostream>
#include <vector>


typedef std::vector<int> Series;

std::vector<Series> tests{
    {5, 15, 14, 13, 12, 16, 10},
    {5},
    {},
    {1,2,3},
    {3,2,1},
    {3,2,1,2,3},
    {1,2,1},
    {1,2,2,2,1},
    {5, 5, 5, 5, 5, 16, 10, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 16, 10, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 16, 10, 5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 16, 10},
    {5, -15, -14, -13, -12, 16, 10},
    {5, -12, -13, -14, -15, 16, 10},
    {5, 15, 14, 13, 12, 16, 10, 15, 14, 13, 12, 11, 10, 15, 14, 13, 12, 11, 10, 9, -10, -20},
    {5, 15, 14, 13, 12, 16, 10, 15, 14, 13, 12, 11, 10, 15, 14, 13, 12, 11, 10, 9, -10, -20, 2, 3},
    {5, 15, 14, 13, 12, 16, 10, 15, 14, 13, 12, 13, 12, 11, 10, 9, -10, -20, 11, 10, 15, 14}
};

struct Result{
    size_t start = 0;
    size_t stop = 0;
    size_t len = 0; 
};

Result find_longest_series(const Series& series){
    for (auto val : series){
        std::cout << val << ", ";
    }
    std::cout << std::endl;

    Result res;

    size_t start = 0;
    size_t stop = 0;
    size_t len = 0;
    bool trend_up = false;
    bool trend_down = false;

    for (auto curr = 1; curr < series.size(); ++curr) {
        auto prev = curr-1;
        auto diff = series[curr] - series[prev];
        bool new_trend_up = true;
        bool new_trend_down = true;
        if (diff > 0) {
            new_trend_down = false; // decide that trend is not down
        } else if (diff < 0) {
            new_trend_up = false; // decide that trend is not up
        }
        
        if ((new_trend_up && trend_up) || 
            (new_trend_down && trend_down) || 
            (new_trend_down == new_trend_up)) 
        {
            len += 1;
            stop = curr;
        } else {
            if (len > res.len) {
                res.len = len;
                res.start = start;
                res.stop = stop;
            }
            start = prev;
            stop = curr;
            len = 1;
            trend_up = new_trend_up;
            trend_down = new_trend_down;
        }
    }

    if (len > res.len) {
        res.len = len;
        res.start = start;
        res.stop = stop;
    }

    std::cout << "res [" << res.start << ", " << res.stop << "]  len:" << res.len << std::endl;
    return res;
}


int main(int argc, char const *argv[])
{
    
    std::cout << "Challenge accepted!" << std::endl;

    for (auto& test : tests) {
        find_longest_series(test);
    }

    return 0;
}
