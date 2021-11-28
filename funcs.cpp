//https://contest.yandex.ru/contest/27794/problems/C/

#include "funcs.h"
#include <bits/stdc++.h>

//! @return raises from left to right, raises from right to left
std::pair<std::vector<int>,std::vector<int>>
    getRaises(const std::vector<int> & heights){
    std::pair<std::vector<int>,std::vector<int>> ans;
    ans.first.resize(heights.size());
    ans.second.resize(heights.size());

    int delta;
    for(int i = 1; i < heights.size(); ++i){
        delta = heights[i]-heights[i-1];
        if(delta>0)
            ans.first[i] = delta;
        else
            ans.second[i] = -delta;
    }
    return ans;
}

std::vector<long> getPrefixSums(const std::vector<int> & numbers){
    std::vector<long> ans(numbers.size());
    ans[0] = 0;
    long sum = 0;
    for(int i=0;i<numbers.size();++i){
        sum+=numbers[i];
        ans[i] = sum;
    }
    return ans;
}

void parseFile(std::istream & input, std::ostream & output){

    int peaksLen, tracesLen;

    input >> peaksLen;

    std::vector<int> peaks(peaksLen);
    for(int i=0; i<peaksLen; ++i){
        int x,y;
        input >> x >> y;
        peaks[i]=y;
    }

    input >> tracesLen;
    std::vector<std::pair<int,int>> traces(tracesLen);
    int iStart, iEnd;
    for(int i=0; i<tracesLen; ++i){
        input >> iStart >> iEnd;
        traces[i] = {iStart-1, iEnd-1};
    }

    auto [raises, descents] = getRaises(peaks);
    peaks.clear();

    auto raisesPrefixSums = getPrefixSums(raises);
    raises.clear();
    auto descentsPrefixSums = getPrefixSums(descents);
    descents.clear();

    std::vector<long int> ans(traces.size());

    for(int i = 0; i < traces.size(); ++i){
        const auto & trace = traces[i];

        if(trace.second >= trace.first){
            ans[i] = raisesPrefixSums[trace.second] - raisesPrefixSums[trace.first];
        } else {
            ans[i] = descentsPrefixSums[trace.first] - descentsPrefixSums[trace.second];
        }
    }

    std::copy(ans.begin(), ans.end(),
              std::ostream_iterator<long int>(output, "\n"));
}
