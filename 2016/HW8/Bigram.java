/*
This HW will be very similar to HW7 but it will be in Java.
You will write a class hierarchy for bigrams (2-Gram). A bigram is a specialization of N-Gram which
“is a contiguous sequence of N items from a given data sequence”. For the bigram we take N=2. For
example if we have a sequence of integers {1 4 6 3 7 1 4 7 2} then the number of {1 4} bigrams is 2,
the number of {4 6} bigrams is 1, and the number of {3 4} bigrams is 0. Similarly, if the sequence is
{qwe asd fgh sdf sdf} then the number of {qwe asd} bigrams is 1.
The java interface Bigram which will have the following methods. This class will not have any data
fields.
• readFile: takes a filename as a string parameter, reads the file, calculates all the bigrams.
Throws exceptions if there are problems with opening and reading the file.
• numGrams: returns the total number of bigrams calculated so far. For example, if we read
an integer sequence file that contains {1 234 346 343 7234 341 434 72 234}, then
numGrams() returns 8.
• numOfGrams: takes two elements as bigrams and returns the number of that bigram read so
far. For example, if we read an integer sequence file that contains {1 4 6 3 7 1 4 7 2}, then
numOfGrams(1,4) returns 2.
• toString prints all the bigrams and their occurences in decreasing occurency order.
You will extend 2 concrete classes from this inteface class. The first class is BigramMap, which uses
Java Collections Map class to implement all the methods above. The second class is BigramDyn
which does not use any standard classes or methods, it uses only Java arrays.
Write a test method that takes a Bigram reference and a file name, reads the file, runs all the member
methods catches any exceptions thrown (prints the exception error on the screen)
Write your main method that takes these command line parameters•
•
•
fılename: file that contains the sequence to read, there is no limit to the number of elements in
the sequence.
Data type: 1 for int, 2 for strings, 3 for doubles
Class type: 1 for BigramMap , 2 for BigramDyn
For example: java myProg datafile 1 2 will read file name datafile that should contain integers and
my program would use BigramDyn class to run all the tests. Your main method will call the test
method with suitable parameters.
*/
package zeytin;

import java.io.IOException;

public abstract class Bigram <T> {
	public void readFile( String filename ) throws IOException{};
	public int numGrams() { return 0; }
	public int numOfGrams( T p1, T p2) { return 0; }
	public String toString(){ return ""; }
}
