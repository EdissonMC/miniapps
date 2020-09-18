/* Lecture Code 1.2
 *
 * Hexadecimal file viewer.  Opens the file logo.gif and prints its
 * contents in hexadecimal (base 16) form.  As an interesting exercise,
 * try modifying this code so that you can load any file (including the
 * executable file itself!
 */
#include <iostream>
#include <string>
#include <fstream>  // For ifstream
#include <iomanip>  // For hex, dec, noskipws, setw, setfill
using namespace std;

/* Number of output columns (number of characters per line. */
const int kNumCols = 16;

int main()
{
	/* Open the file logo.gif.  We read the file in binary mode (ios::binary)
	 * so that we read all of the file's contents on a Windows system, rather
	 * than stopping at the first special EOF character embedded in the file.
	 * On Mac or Linux systems, this is not necessary.
	 */
	ifstream input("amazonlogo.gif", ios::binary);
	


	/* If we failed to open the file, report an error and quit the program.  Note
	 * that we use cerr to log the error - this special stream is reserved for error
	 * reporting.
	 */
	if(!input.is_open()) {
		cerr << "Can't find the file." << endl;
		return -1;
	}



	/* Track the number of characters we read from disk. */
	int numRead = 0;
	



	/* Keep reading characters and printing their hex equivalents. */
	while(true) {

		/* Read kNumCols characters and print them all on one line. */
		for(int i = 0; i < kNumCols; ++i) {

			/* We store the characters we read as unsigned chars.  This prevents
			 * sign errors where characters numbered above 127 become negative.
			 * Note that 'char' by itself can be signed or unsigned based on the
			 * particular C++ implementation; Windows systems tend to have signed
			 * chars by default, while on Mac/Linux they tend to be unsigned.
			 * Putting the explicit 'unsigned' keyword in forces the compiler to
			 * use the correct version.
			 */
			unsigned char ch;
			


			/* Read a character from the file.  The noskipws stream manipulator
			 * prevents the stream from ignoring whitespace characters.  We could
			 * alternatively have written input.get(ch).
			 */
			input >> noskipws >> ch;



			/* If we failed (input.fail()) due to no more data being available,
			 * record statistics about the read and quit.
			 */
			if(input.fail()) {
				/* Print a newline so that this data isn't on the same
				 * line as character data.
				 */
				cout << endl;
				
				/* Note that we have to use the dec manipulator here to set
				 * the stream to print in decimal.  Otherwise we print
				 * out hexadecimal values.
				 */
				cout << "Num chars: " << dec << numRead << endl;
				return 0;
			}

			++numRead;

			/* This line is tricky.... let's see exactly what's going on here.
			 * Our goal is to print out the two-character hexadecimal representation
			 * of the character.  If we just print out the character, we'll just see the
			 * pictorial representation of the character, not its ASCII value, so we insert
			 * a typecast to convert it from an unsigned char to an int.  The static_cast
			 * keyword performs this conversion; we'll discuss what static_cast does later
			 * in the quarter, but for now you can treat it as a longhand for (int)ch.
			 * The other manipulators on this line put the stream into hex mode (hex),
			 * tell the stream to pad the output to always be two characters (setw(2)),
			 * and to use 0 as the fill character (setfill('0')).  Whew!
			 */
			cout << hex << setfill('0') << setw(2) << static_cast<int>(ch) << ' ';
		}
		cout << endl;
	}
}