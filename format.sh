#!/bin/bash

find . -type f -iname '*.h' -exec clang-format -i {} +
find . -type f -iname '*.hpp' -exec clang-format -i {} +
find . -type f -iname '*.cpp' -exec clang-format -i {} +
find . -type f -iname '*.ino' -exec clang-format -i {} +
