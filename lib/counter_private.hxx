/**
 * MIT License
 *
 * Copyright (c) 2021 Dmitry Zelenkovsky
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __COUNTER_PRIVATE_HXX
#define __COUNTER_PRIVATE_HXX

#include <ctime>
#include <vector>
#include "counter.hxx"

typedef struct Bucket
{
    Bucket() : id(0), count(0) {}
    time_t id;
    unsigned long long count;
} BUCKET, *PBUCKET;

class CounterPrivate
{
public:
    CounterPrivate(int d);

    bool hit(std::time_t time);
    unsigned long long analyze(std::time_t begin, std::time_t end);
    unsigned long long count(std::time_t time);

    int duration;
    unsigned long long counter;
    std::vector<BUCKET> buffer;
    std::vector<BUCKET>::iterator begin;
    std::vector<BUCKET>::iterator end;
};

#endif