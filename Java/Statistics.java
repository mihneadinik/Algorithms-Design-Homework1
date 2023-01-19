import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Scanner;


public class Statistics {
	public Character letter = 'a';
	public Integer N;
	public ArrayList<String> words = new ArrayList<>();

	// Function that reads the input file
	public void read() throws FileNotFoundException {
		File input = new File("statistics.in");
		Scanner scanner = new Scanner(input);
		this.N = scanner.nextInt();

		for (int i = 0; i < this.N; i++) {
			this.words.add(scanner.next());
		}

		scanner.close();
	}

	// Function that counts the number of occurrences of a letter in a word
	public int numberApparitions(String word) {
		int apparitions = 0;
		for (int i = 0; i < word.length(); i++) {
			if (this.letter == word.charAt(i)) {
				apparitions++;
			}
		}
		return apparitions;
	}

	// Function that checks if a letter is contained by any of the words
	public Boolean containsLetter() {
		for (String word : this.words) {
			if (numberApparitions(word) > 0) {
				return true;
			}
		}
		return false;
	}

	// Function that computes the number of good letters a word provides
	// in contrast to the number of any other letters
	public int letterDifference(String word) {
		int ap = numberApparitions(word);
		return 2 * ap - word.length();
	}

	public int simulateLetter() {
		// sort the vector according to letterDifference function
		Collections.sort(this.words, new Comparator<String>() {
			@Override
			public int compare(String o1, String o2) {
				return letterDifference(o2) - letterDifference(o1);
			}
		});

		int totalLength = 0, totalWords = 0, letterApparitions = 0;

		// add words while the letter remains in majority
		// (it has more occurrences than half the total size)
		int i = 0;
		do {
			totalWords++;
			totalLength += this.words.get(i).length();
			letterApparitions += numberApparitions(this.words.get(i));
			i++;
		} while (2 * letterApparitions > totalLength && i < this.words.size());

		if (i == this.words.size() && 2 * letterApparitions > totalLength) {
			return i;
		}

		return --i;
	}

	// Driver function that solves the problem
	public int solve() {
		int maxWords = -1;

		// go from a to z
		while (this.letter <= 'z') {
			if (!containsLetter()) {
				letter++;
				continue;
			}

			int totalWords = simulateLetter();

			// check if we have a new maximum
			if (totalWords > maxWords && totalWords != 0) {
				maxWords = totalWords;
			}

			letter++;
		}

		return maxWords;
	}

	public static void main(String[] args) throws IOException {
		Statistics pb = new Statistics();
		pb.read();

		PrintWriter printWriter = new PrintWriter(new FileWriter("statistics.out"));
		printWriter.println(pb.solve());
		printWriter.close();
	}
}
