# Instrumental Counter

This library allows to register and store events/hits efficiently in memory while providing a quick way of calculating them within a specified timeframe.

## How to use

The example below shows how to initialize the counter, how to register events/hits and how to calculate a total number of events/hits during the last 200 seconds.

```cpp
#include <counter.hxx>

// initialize counter
Counter count(300);

// register event/hit
count.hit();
.
.
.
count.hit();

// getting total number of events/hits
unsigned long long total = count.analyze(200);
count << "Events counted: " << total << std::endl;
```

## How to build

In order to build this library you would need to have ```cmake``` version 3.5.1 or higher installed.

Run following commands to build and run unit tests:

```sh
$ cmake -f CMakeLists.txt -DCMAKE_BUILD_TYPE=Release
$ make
$ ctest
```

Execute unit tests with debug output by running executable without parameters separately from ```CTest``` framework:

```sh
$ ./tests/countertest
Counting 3 hits for last 3 second ... OK
Counting 3 hits for last 5 seconds ... OK
Counting 9 hits for last 5 seconds ... OK
Counting wrong in interval ... OK
Counting sequentially with short buffer ... OK
Counting with short buffer ... OK
Counting with short buffer 2 ... OK
```

## How to run

Now you are ready to start counter application by running the following command:
```sh
$ ./app/counterapp
Hits are counting, press ^C to interrupt...
^C
Total running time: 64s

Last second hits........:      95316868
Last 2 seconds hits.....:     273548829
Last 5 seconds hits.....:     806379218
Last 10 seconds hits....:    1695184550
Last minute hits........:   10637107473
```
## BUGS

In case of bugs or questions, please submit **GitHub** issue.
