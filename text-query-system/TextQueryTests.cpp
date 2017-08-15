#include "Word.h"
#include "Line.h"
#include "Paragraph.h"
#include "FileReader.h"
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

const string PUNCTUATION = "~`!@#$%^&*()-_+={}[]\\|:;'<>?,./\"";
const string UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string LOWERCASE = "abcdefghijklmnopqrstuvwxyz";
const int MIN_SIZE_FOR_QUERY = 3;

// ----------------------------------------------------

// Test the null case first - cannot have an empty word
// These assertion types (CHECK_THROWS_AS, CHECK, CHECK_FALSE) are described in the doctest reference:
// https://github.com/onqtam/doctest/blob/master/doc/markdown/assertions.md
// Also see further examples at:
// https://github.com/onqtam/doctest/blob/master/examples/all_features/assertion_macros.cpp

TEST_CASE("Empty Word cannot be created") {	 
    CHECK_THROWS_AS(Word testword(""), WordContainsNoLetters);
}

TEST_CASE("Identical Words are equal") {
    Word word1("that");
	Word word2("that");
	CHECK(word1 == word2);    
}

TEST_CASE("Non-identical Words are not equal") {
	Word word1("this");
	Word word2("that");
	CHECK_FALSE(word1 == word2);
}

TEST_CASE("Case is ignored when comparing Words") {
	Word uppercase_word(UPPERCASE);
	Word lowercase_word(LOWERCASE);
	CHECK(lowercase_word == uppercase_word);
}

TEST_CASE("Punctuation is ignored when comparing Words") {
	Word word_with_punct(PUNCTUATION + "hel" + PUNCTUATION + "lo" + PUNCTUATION);
	Word word_without_punct("hello");
	CHECK(word_without_punct == word_with_punct);
}



TEST_CASE("Word cannot consist solely of punctuation") {
	CHECK_THROWS_AS(Word testword("$#@!"), WordContainsNoLetters);//Wrote method and put into constructor of Word
}

TEST_CASE("Word cannot contain a space") {
	CHECK_THROWS_AS(Word testword("hello there"), WordContainsSpace);//Wrote method and put into contructor of Word
}

TEST_CASE("Word is queryable if greater than or equal to a specific size") {
	string test_string;
	test_string.resize(MIN_SIZE_FOR_QUERY, 'a');
	Word test_word(test_string);
	CHECK(test_word.isQueryable());
}

TEST_CASE("Word is not queryable if less than a specific size") {
	int QUERY_LENGTH = 5;
	string test_string;
	test_string.resize(QUERY_LENGTH,'a');
	Word test_word(test_string);
	CHECK(test_word.isQueryableByCustomLength(QUERY_LENGTH));
}

// ----------------------------------------------------

// Test null case first - here, an empty line
TEST_CASE("Word cannot be found in empty Line") {
   Line testline("");
   Word searchword("hello");
   CHECK_FALSE(testline.contains(searchword));
}

TEST_CASE("Word can be found in a Line with a single Word") {
	Line testline("Stop");
	Word searchword("Stop");
	CHECK(testline.contains(searchword));
}

// It is always good to write tests which test boundary conditions
TEST_CASE("First and last Words in a Line can be found") {
	Line testline("Walking on water and developing software from a specification are easy if both are frozen.");
	Word first_word_in_line("Walking");
	CHECK(testline.contains(first_word_in_line));
	Word second_word_in_line("frozen");
	CHECK(testline.contains(second_word_in_line));
}

// Test not only success scenarios but also failure scenarios.
TEST_CASE("Word not in a Line cannot be found") {
	Line testline("I have always wished for my computer to be as easy to use as my telephone; my wish has come true because I can no longer figure out how to use my telephone.");
	Word word_not_in_line("cellphone");
	CHECK_FALSE(testline.contains(word_not_in_line));

}
TEST_CASE("Words are found irrespective of case") {
	Line testline("You can stand on the shoulders of giants or a BIG enough pile of dwarfs, works either way.");
	Word lower_case("big");
	CHECK(testline.contains(lower_case));
	Word uppercase("STAND");
	CHECK(testline.contains(uppercase));
}

TEST_CASE("Words are found irrespective of punctuation") {
	Line testline("How can you tell if a person is a programmer? They use nested parentheses in normal writing (at least I do (sometimes)).");
	Word punctuation_word_1("programmer");
	CHECK(testline.contains(punctuation_word_1));
	Word punctuation_word_2("sometimes");
	CHECK(testline.contains(punctuation_word_2));
}

TEST_CASE("Word which is not queryable cannot be found") {
   Line testline("Any fool can write code that a computer can understand. Good programmers write code that humans can understand.");
   Word too_small_to_query("a");
   CHECK_FALSE(testline.contains(too_small_to_query));
}

// ----------------------------------------------------

TEST_CASE("Word cannot be found in empty Paragraph") {
	Word testWord("Word");
	vector<int> line_nums;
	Paragraph testParagraph;
	CHECK_FALSE(testParagraph.contains(testWord, line_nums));
}

TEST_CASE("Word not present in Paragraph cannot be found") {
	Word testWord("Cookie");
        vector<int> line_nums;
	Line testLine("The word you are looking for will not be found in this line.");
        Paragraph testParagraph;
	testParagraph.addLine(testLine);
        CHECK_FALSE(testParagraph.contains(testWord, line_nums));
}

TEST_CASE("Line number of a Word appearing once in Paragraph is returned") {
	Word testWord("Cookie");
        vector<int> line_nums;
        Line testLine("Cookie is the first word in this first line.");
        Paragraph testParagraph;
        testParagraph.addLine(testLine);
	testParagraph.contains(testWord, line_nums);
        CHECK(line_nums[0]==1);
}

TEST_CASE("Line numbers of a Word appearing in multiple Lines of a Paragraph is returned") {
	 Word testWord("Cookie");
        vector<int> line_nums;
	Paragraph testParagraph;
        Line testLine("Cookie is the first word in this first line.");
	testParagraph.addLine(testLine);
	Line testLine2("The word is left out here.");
	testParagraph.addLine(testLine2);
	Line testLine3("Cookie is the first word on this second line.");
	testParagraph.addLine(testLine3);
	testParagraph.contains(testWord,line_nums);	
	
        CHECK(line_nums[0]==1);
	CHECK(line_nums[1]==3);
}

TEST_CASE("Line numbers returned account for an empty Line") {
// If the first line of the paragraph is empty, and the word being searched for
// is on the second line, the vector returned should be: [2]
	 Word testWord("Cookie");
        vector<int> line_nums;
        Paragraph testParagraph;
        Line testLine("");
        testParagraph.addLine(testLine);
        Line testLine2("Cookie is the first word on this second line.");
        testParagraph.addLine(testLine2);
        testParagraph.contains(testWord,line_nums);
        CHECK(line_nums[0]==2);
}
//
//// ----------------------------------------------------
//
//// Integration test - both Paragraph and File Reader are tested together
//TEST_CASE("File can be read into Paragraph and successfully searched") {
//	// make sure that alice.txt is in the right location for this to work!
//	FileReader filereader("alice.txt");
//	Paragraph paragraph;
//	filereader.readFileInto(paragraph);
//	Word search_word("Daddy");
//	vector<int> line_numbers;
//	CHECK(paragraph.contains(search_word, line_numbers));
//	vector<int> expected_line_numbers;
//	expected_line_numbers.push_back(1);
//	expected_line_numbers.push_back(4);
//	expected_line_numbers.push_back(6);
//	CHECK(expected_line_numbers == line_numbers);
//
