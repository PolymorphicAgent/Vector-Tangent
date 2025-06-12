# Vector Tangent: A Challenge Problem
****
Write an algorithm that calculates the tangent of any arbitrary angle (in degrees) with the following restrictions:
- The use of trigonometric functions is prohibited unless comparing the calculated value to the actual value returned by `std::tangent`.
- The use of the built-in square root function is prohibited.

**Your solution must use vectors.**
****
This was the prompt presented to me by my friend, and 5 days later, I finished the program displayed above that satisfies all of the requirements.
****
# Building
This program can be built with g++.
```
g++ -o Vector-Tangent main.cpp Vector.cpp
```
****
*Note: inputting unreasonably large numbers may cause undesired outputs due to the use of floating-point numbers.*
