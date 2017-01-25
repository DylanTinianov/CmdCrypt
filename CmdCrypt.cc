#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>


void help_print () {
	const std::vector<std::string> help_cmds = {
		"\nCmdCrypt",
		"A command line encryption and decryption tool",
		"\nMAIN ARGUMENTS:",
		"First argument:  encrypt or decrypt -> select between encryption or decryption modes",
		"Second argument: FileName -> enter the filename to be encrypted or decrypted ",
		"\nOPTIONAL ARGUMENTS:",
		"-key YOUR_KEY -> enter your known decryption key if in decryption mode; else be prompted for it",
		"-new NEW_FILE_NAME -> encrypt the contents into a new file NEW_FILE_NAME, and only read the second argument",
		""
	};
	for (int i=0; i < help_cmds.size(); i++) {
		std::cout << help_cmds.at(i) << std::endl;
	}
}


// First enter the cmd "encrypt" or "decrypt", then "FileName"
int main(int argc, char const *argv[]) {
	if (strcmp(argv[1], "help") == 0) {
		help_print();
		return EXIT_SUCCESS;
	}

	if (argc < 3) {
		std::cerr << "Error, not all command arguments were entered." << std::endl;
		return EXIT_SUCCESS;
	}

	const std::string cmd = argv[1];
	const std::string FILE_NAME = argv[2];

	std::ifstream user_file;
	user_file.open(FILE_NAME);
	if (user_file.fail()) {
		std::cerr << "Error, cannot open specified text file." << std::endl;
		return EXIT_SUCCESS;
	}


	if (cmd == "encrypt") {

	}

	else if (cmd == "decrypt") {
		std::string decr_key;
		if (argc == 4) {
			decr_key = argv[3];
		}
		else {
			std::cout << "Enter key for decryption: " << std::endl;
			std::cin >> decr_key;
		}

	}


	return EXIT_SUCCESS;
}
