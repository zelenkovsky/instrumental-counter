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
unsigned long long total = count.analyze(std::time(NULL) - 200, std::time(NULL));
count << "Events counted: " << total << std::endl;
```

## How to build && run

In order to build this library you would need to have ```cmake``` version 3.5.1 or higher installed.

Run following commands:

```sh
$ cmake -f CMakeLists.txt
$ make
```

Execute unit test cases by entering following command:

```sh
$ ./tests/countertest
```

Start counter application by running following command:
```sh
$ ./app/counterapp
Hits are counting, press ^C to interrupt...
^C
Total running time: 25s

Last second hits........:     147472814
Last 2 seconds hits.....:     328049714
Last 5 seconds hits.....:     869628353
Last 10 seconds hits....:    1771771453

```
## BUGS

In case of bugs or questions, please submit **GitHub** issue.
