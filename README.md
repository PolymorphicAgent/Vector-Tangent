# Vector Tangent: A Challenge Problem

Write an algorithm that calculates the tangent of any arbitrary angle (in degrees) with the following restrictions:
- The use of trigonometric functions is prohibited unless comparing the calculated value to the actual value returned by `std::tan`.
- The use of the built-in square root function is prohibited.

**Your solution must use vectors.**
****
This was the prompt presented to me by a friend, my response to which is the program displayed above.
****
# Building
This program can be built with g++.
```
g++ -o Vector-Tangent main.cpp Vector.cpp
```

*Note: inputting unreasonably large numbers may cause undesired outputs due to the use of floating-point numbers.*
