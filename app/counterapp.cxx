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

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <signal.h>
#include "counter.hxx"

using namespace std;

static volatile int running = 1;

void signalHandler(int dummy) {
    running = 0;
}

int main(int argc, char* argv[])
{
    Counter counter(360);
    cout << "Hits are counting, press ^C to interrupt..." << endl;

    signal(SIGINT, signalHandler);

    time_t timestamp = time(NULL);
    while (running) {
        if (!counter.hit()) {
            cerr << "Failed to count a hit..." << endl;
            exit(1);
        }
    }
    cout << endl;
    int total = time(NULL) - timestamp;
    cout << "Total running time: " << total << "s" << endl;
    cout << endl;

    if (total >=1)
        cout << "Last second hits........:" << setw(14) << counter.analyze(1) << endl;
    if (total >=2)
        cout << "Last 2 seconds hits.....:" << setw(14) << counter.analyze(2) << endl;
    if (total >=5)
        cout << "Last 5 seconds hits.....:" << setw(14) << counter.analyze(5) << endl;
    if (total >=10)
        cout << "Last 10 seconds hits....:" << setw(14) << counter.analyze(10) << endl;
    if (total >=130)
        cout << "Last 30 seconds hits....:" << setw(14) << counter.analyze(30) << endl;
    if (total >=60)
        cout << "Last minute hits........:" << setw(14) << counter.analyze(60) << endl;
    if (total >=120)
        cout << "Last two minutes hits...:" << setw(14) << counter.analyze(120) << endl;
    if (total >=180)
        cout << "Last tree minutes hits..:" << setw(14) << counter.analyze(180) << endl;
    if (total >=360)
        cout << "Last five minutes hits..:" << setw(14) << counter.analyze(360) << endl;

    cout << endl;
    return 0;
}