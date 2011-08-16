This document is a description on how to compile the openlima-engine and limabeans (= The test
project).

You should start with the chapter 'Preparation', which you should only do once per linux
installation.
Then you should continue with the chapter 'OpenLima', which will compile the engine.
After that, you can optionally test the engine using 'LimaBeans' - the test project for openlima.

Preparation:
	In this chapter you'll install the requirements of openlima.
	
	This will install some OpenGL-libraries and the boost framework:
		sudo apt-get install mesa-common-dev freeglut3-dev libboost-all-dev

OpenLima: (The engine)
	You should execute this command from the directory where this readme is:
	
	cd ./OpenLima;sudo ./compile.sh;cd ../
	
	If this didn't work, try to mark the compile.sh in the OpenLima-directory as an executable.

LimaBeans: (The program)
	You should execute this command from the directory where this readme is:
	
	cd ./LimaBeans;sudo ./compile.sh;cd ../
	
	If this didn't work, try to mark the compile.sh in the LimaBeans-directory as an executable.

If you want to test LimaBeans, go to the subdirectory "LimaBeans", and there to the subdirectory
"bin".
Here you can run the limabeans-executable.
If it worked: Congratulations!



Everything here is tested on Ubuntu 11.04 64- and 32-Bit.

Thanks for testing to:
	Max Theisen
	Daniel Seemaier