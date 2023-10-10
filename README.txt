Stefan Dujic 101254030

This program is a simple executable, that runs without any user input, and involves printing images using 
different encoding algorithms. More specifically, it will first print out the raw image and it's number of bytes,
then a function will pack all the bytes and will print out the image again. Lastly, another function will encode
the packed bytes and will print out again the image, after which it will also print out the total bytes that 
each image has.

a2-posted.c : main file of the program, written in C.
camera.o : object file that contains one function "take_photo", it needs to be linked to a2-posted.c when compilling in order for the
 	   the images to print correctly.

To compile the program, write the following in Linux: gcc -o filename a2-posted.c camera.o

To run the program, write the following in Linux: ./filename

No instructions are needed to operate the program. This is a simple executable that displays encoding algorithms on images

No generative AI has been used during this assignment		
