Modified Newton-Raphson Method vs Classical Newton-Raphson

01. Overview

This project implements the Modified Newton-Raphson Method and compares it with the Classical Newton-Raphson Method in terms of speed and stability. Both methods are tested on:
Well-behaved functions (easy convergence)
Ill-conditioned functions (difficult convergence)
The goal is to demonstrate how modification of the Newton-Raphson iteration formula can improve stability and reduce sensitivity to poor initial guesses.

Methods Implemented
1. Classical Newton-Raphson Method

The standard iteration formula is:

 ​Xn+1=Xn-(f(Xn)/f'(Xn))

i. Fast convergence (quadratic) when the function is well-behaved.

ii. May fail or diverge if the derivative is very small or the function is ill-conditioned.


2. Modified Newton-Raphson Method

The modified iteration uses:

Xn+1=Xn-(f(Xn)f'(Xn))/([f'(Xn)]^2-f(Xn)f"(Xn))

i. Reduces instability near points where f'(x) is small.

ii. Often converges better for ill-conditioned problems.

iii. Can still converge quadratically for well-behaved cases.


02. Test Functions

i. Well-Behaved Function

f(X)=x^2-5x+2=0

**Smooth derivative, easy convergence to 2

ii. Ill-Conditioned Function

f(X)=x^3-2x+2

**Multiple roots and flat regions make convergence unstable.


03. Comparison

Criteria                       -------  Classical Newton-Raphson              


Speed (Well-Behaved)          -------   Very fast (quadratic)                

Stability (Well-Behaved)      ------   Stable                                

Speed (Ill-Conditioned)      -------    May fail or diverge                   

Stability (Ill-Conditioned)  -------    Unstable near flat derivative         


Criteria    -------                    Modified Newton-Raphson

Speed (Well-Behaved)      -------      Slightly slower, but still efficient

Stability (Well-Behaved)   -------     stable

Speed (Ill-Conditioned)       --------  slower but converges more reliable

Stability (Ill-Conditioned)   -------  More robust due to second derivative usage

04. Conclusion

The Classical Newton-Raphson method is faster for well-behaved functions.
The Modified Newton-Raphson method trades some speed for better stability and is more reliable for ill-conditioned problems.
This project highlights the importance of choosing the right root-finding method depending on the nature of the function.

