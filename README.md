# Nine-mens-morris-strategies
Program that uses genetic algorithms and alpha/beta - killer algorithm to find the best possible strategy for playing 9 men morris

### :computer: Getting started

This version is mainly tested on Ubuntu and MacOS

* Setup enemies in 9MensMorrisGen.py ( use random generated or from the following [paper](http://dasconference.ro/papers/2008/B7.pdf))

* Go into src file and run
```
$ g++ *.cpp
```

### :joystick: Usage

If you are running the program for the first time:
```
$ python 9MensMorrisGen.py num_of_iterations -n
```
If you want to continue training the model from the last backup version
```
$ python 9MensMorrisGen.py num_of_iterations
```
Open log file to see the results of the execution
```
$ open information.log
```

## :wrench: Built using
* [Python](https://www.python.org/) - for genetic algorithm
* [C++](http://www.cplusplus.com/doc/tutorial/) - for alpha/beta - killer algorithm

## :mortar_board: Authors

* **Djordje Pantelić** - [djolf94](https://github.com/djolf94)

* **Nikola Dimić** -  [dimaria95](https://github.com/dimaria95/)

## :book: License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

 
