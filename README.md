# Event logger

A simple utility to record a series of event. It is inspired by the [EventLogger](https://github.com/ceres-solver/ceres-solver/blob/1.14.x/internal/ceres/wall_time.h) class found in the ceres library.

# How to use in your project

## With cpm

If you are using cpm, enter the following command in your project directory:

```console
cpm add sl-event-logger
```

Then, it can be used inside a rule with the following labbel:

```
@sl-event-logger//:event-logger
```


## With Bazel


# How to use in your code


```cpp
#include "event-logger/event-logger.h"


...



```


