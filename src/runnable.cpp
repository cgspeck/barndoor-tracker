#include "runnable.h"

Runnable::Runnable() {
    nextRunnable = headRunnable;
    headRunnable = this;
};
