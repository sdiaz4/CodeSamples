/*
 Hangman Project
 -  The project is a rendition of the word game Hangman where the user gets a set amount of 
    times to guess a letter to inevitably guess a word. This project offers three modes, easy, regular, and hard. 
    With unique challenges to each, the goal is to guess the word within the alotted attempts.

This is the game logic that holds the main game loop and calls the necessary functions to play the game. 
It also holds the state of the game and updates it accordingly.
*/


namespace hangman {
	void Game::playGame() {
		IO::Input input;
		IO::Output output;
		State state;

		

		string difficulty = input.difficulty();
		string secretWord = input.secretWord();
		

		
			vector<char> rightLetter;
			bool gameOver = false;
			int mistakes = 0;
			vector<char> clues;
			vector<char> wrongLetters;
			
			
			size_t size;

			output.title();
			cout << endl << endl;
			auto mode = state.convertMode(difficulty);
			int totalMistakes = state.totalMistakes(mode);
			size = state.stringSize(secretWord);
			clues = state.clueLine(size);

			output.mistakes(mistakes, totalMistakes);
			cout << endl;
			output.clue(clues);

			cout << endl;
		
			while (gameOver != true) {
				
				char letter = input.guessLetter();
				output.guess(letter);
				cout << endl;

				if (state.letterFound(secretWord, letter)) {

					vector<int> locations = state.findLetter(secretWord, letter);
					state.changeClue(letter, locations, clues);

					if (!state.alreadyAsked(letter, rightLetter)) {
						state.addRightLetter(letter, rightLetter);
					}
					else if (state.isNormalOrHard(difficulty))  {
						state.addMistakes(mistakes);
					}
				}
					
				
				else {
					if (!state.alreadyAsked(letter, wrongLetters)) {
						state.addWrongLetter(letter, wrongLetters);
						state.addMistakes(mistakes);
					}
					else if (state.isNormalOrHard(difficulty)) {
						state.addMistakes(mistakes);
					}

				}
				
					

				if (!state.lostGame(mistakes, totalMistakes)) {
					if (!state.wonGame(secretWord, clues)) {
						output.mistakes(mistakes, totalMistakes);
						cout << endl;
						output.clue(clues);

						if (wrongLetters.size() > 0)
						{
							output.wrongLetters(wrongLetters);
						}

						cout << endl;
					}
				}

				if (state.wonGame(secretWord, clues)) {
					output.win(secretWord);
					gameOver = true;
				}
				else if (state.lostGame(mistakes, totalMistakes))
				{
					output.lost(secretWord);
					gameOver = true;
				}

			
		}

	}
}