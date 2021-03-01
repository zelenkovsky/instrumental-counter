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
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>

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

unsigned long long CounterPrivate::analyze(time_t dur)
{
    if (dur <= 0 || duration < dur)
        return 0;

    return count(end->id) - count(max(end->id - dur, static_cast<time_t>(0)));
}

unsigned long long CounterPrivate::count(time_t time)
{
    // timestamp is out of bounds
    if (time < begin->id || time > end->id)
        return 0;

    vector<BUCKET>::iterator b = begin, e = end;
    while (true) {
#ifndef NDEBUG
        vis(b,e);
#endif
        if (e->id == time)
            return e->count;

        if (b->id == time)
            return b->count;

        if (b == e)
            return b->count;

        int d = e - b > 0 ? e - b : duration + (e - b);
        if (d == 1)
            return b->count;

        /*
         * Calculating difference between
         * 'beging' and 'end' markers in order to
         * find middle element and shift marker
         * for next iteration.
         */
        vector<BUCKET>::iterator m = buffer.end() - b > d/2 ?
            b + (d + 1)/2 :
            buffer.begin() + (d/2 - (buffer.end() - b));

        if (m->id < time)
            b = m;
        else if (m->id > time)
            e = m;
        else
            return m->count;
    }
    // never can happen
    return 0;
}

void CounterPrivate::vis(vector<BUCKET>::iterator b, vector<BUCKET>::iterator e)
{
    cout << endl;
    for (vector<BUCKET>::iterator i=buffer.begin(); i!=buffer.end(); ++i)
    {
        if (i == b)
            cout << setw(3) << "b";
        else if (i == e)
            cout << setw(3) << "e";
        else
            cout << setw(4);

        cout << i - buffer.begin();
    }

    cout << endl;

    for (vector<BUCKET>::iterator i=buffer.begin(); i!=buffer.end(); ++i)
    {
        cout << setw(4) << i->id;
    }

    cout << endl;
}