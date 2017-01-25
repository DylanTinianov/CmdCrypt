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
		"-new NEW_FILE_NAME -> encrypt/ decrypt the contents into a new file NEW_FILE_NAME; don't write to the second argument",
		""
	};
	for (int i=0; i < help_cmds.size(); i++) {
		std::cout << help_cmds.at(i) << std::endl;
	}
}


int main(int argc, char const *argv[]) {
	if (strcmp(argv[1], "help") == 0) {
		help_print();
		return EXIT_SUCCESS;
	}
	if (argc < 3) {
		std::cerr << "Error, not all necessary command arguments were entered." << std::endl;
		return EXIT_SUCCESS;
	}

	const std::string cmd = argv[1];
	const std::string FILE_NAME = argv[2];
	std::string OUTPUT_FILE = FILE_NAME; // defult

	std::ifstream user_file;
	user_file.open(FILE_NAME);
	if (user_file.fail()) {
		std::cerr << "Error, cannot open specified text file." << std::endl;
		return EXIT_SUCCESS;
	}


	// Get optional commands
	std::string decr_key = "";
	for (int i=2; i < argc; i++) {
		if (strcmp(argv[i], "-key") == 0) {
			if (i + 1 < argc) {
				decr_key = argv[i+1];
				i++;
			}
			else {
				std::cerr << "Error, missing argument for YOUR_KEY." << std::endl;
				return EXIT_SUCCESS;
			}

		}


		else if (strcmp(argv[i], "-new") == 0) {
			if (i + 1 < argc) {
				OUTPUT_FILE = argv[i+1];
				i++;
			}
			else {
				std::cerr << "Error, missing argument for NEW_FILE_NAME." << std::endl;
				return EXIT_SUCCESS;
			}
		}
	}



	if (cmd == "encrypt") {
		// TODO: Implement encryption
		std::string line;

	}


	else if (cmd == "decrypt") {
		if (decr_key == "") {
			std::cout << "Enter key for decryption: " << std::endl;
			std::cin >> decr_key;
		}

		// TODO: Implement decryption
	}


	return EXIT_SUCCESS;
}
