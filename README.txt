Pieter Gerhard Serton
PGM Image Manipulation

To compile this program, simply run "make" to crate an executable named "Driver". To compile the catch tests, run "make catch" instead to create an executable named "CatchTests".

"CatchTests" Instructions:
	Simply run the executable to run the tests.

"Driver" Instructions:
The following commands can be run to the "Driver" executable. I1, I2, and Output are filenames, 
respectively.

	Driver -a I1 I2 Output (add I1 and I2)
	Driver -s I1 I2 Output (subtract I2 from I1)
	Driver -i I1 Output (invert I1)
	Driver -l I1 I2 Output (mask I1 with I2)
	Driver -t I1 f Output (threshold I1 with integer value f)

