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

#include <cstdlib>
#include <iostream>
#include "../lib/counter_private.hxx"

#define VERIFY( EXPR )     \
    do {                   \
        if ( !(EXPR) ) {   \
            std::cerr << "Expression failed at " << __FILE__ << ":" << __LINE__ << std::endl; \
            std::exit(1);  \
        }                  \
    } while (false);

int main(int argc, char* argv[])
{
    {
        std::cout << "Counting 3 hits for last 3 second ... ";
        CounterPrivate counter(10);
        counter.hit(1);
        counter.hit(1);
        counter.hit(1);

        VERIFY(counter.analyze(3) == 3);
        std::cout << "OK" << std::endl;
    }
    {
        std::cout << "Counting 3 hits for last 5 seconds ... ";
        CounterPrivate counter(10);
        counter.hit(1);
        counter.hit(3);
        counter.hit(5);

        VERIFY(counter.analyze(5) == 3);
        std::cout << "OK" << std::endl;
    }
    {
        std::cout << "Counting 9 hits for last 5 seconds ... ";
        CounterPrivate counter(10);
        counter.hit(1);
        counter.hit(1);
        counter.hit(1);
        counter.hit(2);
        counter.hit(2);
        counter.hit(2);
        counter.hit(3);
        counter.hit(3);
        counter.hit(3);

        VERIFY(counter.analyze(5) == 9);
        std::cout << "OK" << std::endl;
    }
    {
        std::cout << "Counting wrong in interval ... ";
        CounterPrivate counter(10);
        counter.hit(1);

        VERIFY(counter.analyze(-1) == 0);
        std::cout << "OK" << std::endl;
    }
    {
        std::cout << "Counting sequentially with short buffer ... ";
        CounterPrivate counter(6);
        counter.hit(1);
        counter.hit(2);
        counter.hit(3);
        counter.hit(4);
        counter.hit(5);
        counter.hit(6);
        counter.hit(7);
        counter.hit(8);
        counter.hit(9);
        counter.hit(10);

        VERIFY(counter.analyze(3) == 3);
        std::cout << "OK" << std::endl;
    }
    {
        std::cout << "Counting with short buffer ... ";
        CounterPrivate counter(5);
        counter.hit(1);
        counter.hit(3);
        counter.hit(5);
        counter.hit(7);
        counter.hit(9);
        counter.hit(11);

        VERIFY(counter.analyze(5) == 3);
        std::cout << "OK" << std::endl;
    }

    {
        std::cout << "Counting with short buffer 2 ... ";
        CounterPrivate counter(6);
        counter.hit(1);
        counter.hit(3);
        counter.hit(5);
        counter.hit(7);
        counter.hit(9);
        counter.hit(9);
        counter.hit(9);
        counter.hit(10);
        counter.hit(11);
        VERIFY(counter.analyze(4) == 5);
        std::cout << "OK" << std::endl;
    }
    return 0;
}
