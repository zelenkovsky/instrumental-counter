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

#include "counter_private.hxx"

using namespace std;

CounterPrivate::CounterPrivate(int d) : duration(d), counter(0)
{
    buffer.resize(duration);
    begin = end = buffer.begin();
    begin->id = 0;
    begin->count = 0;
}

bool CounterPrivate::hit(time_t time)
{
    time_t latest = end->id;
    if (time > latest) {
        // use next bucket
        if (++end == buffer.end())
            end = buffer.begin();

        // make sure begin is shifted correctly
        if (end == begin)
            if (++begin  == buffer.end())
                begin = buffer.begin();

        // this is first hit
        end->id = time;
        end->count = ++counter;

    } else if (time == latest) {
        // this is subsequent hit for this second
        end->count = ++counter;

    } else {
        // this is a hit for past
        return false;
    }
    return true;
}

unsigned long long CounterPrivate::analyze(time_t b, time_t e)
{
    return count(e) - count(b - 1);
}

unsigned long long CounterPrivate::count(std::time_t time)
{
    // timestamp is out of bounds
    if (time < begin->id || time > end->id)
        return 0;

    std::vector<BUCKET>::iterator b = begin, e = end;
    while (true) {

        if (e->id == time)
            return e->count;

        if (b->id == time)
            return b->count;

        if (b == e)
            return b->count;

        int d = e - b;
        vector<BUCKET>::iterator m = b + d/2;
        if (m->id < time)
            e = m;
        else if (m->id > time)
            b = m;
        else
            return m->count;
    }
    // never can happen
    return 0;
}