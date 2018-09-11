### Lab 2

* **regress**: remove the assumption that testfiles are in the current working directory, but change the specs so as to define the test results will be saved in basename.stdout, etc.
And teach them how to extract a basename from a pathname.
* **chill**
	* Note that chill takes float parameters and prints floating-point numbers.
	* Unfortunately, the examples in Lab2 show only integer arguments and the output have been rounded to integers.
	* prepare better examples, drawing on the solution.
* ***words***
	* remind them that stdin is a `FILE*` and thus can be used anywhere a `FILE*` is used
	* they were very confused about stdin, thinking that it means keyboard input - emphasize that stdin could be a file or pipe and indeed that's likely for this application. give examples.
* ***histo***
	* emphasize that reading input should be easy and simple-minded, using `scanf`.
* give better/clearer examples of README and TESTING files.
