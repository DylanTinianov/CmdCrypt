// TODO: Change permissions to key_store to read only after encrypted, and add a password if possible
// TODO: Change key_store to key_store_encryptedFileName so they can have more then one for different files
// TODO: Allow to type in the location of the key_store_encryptedFileName file instead of needing it in this directory
// TODO: Fix decryption.
// TODO: Fix unit tests
// TODO: Set up Travis CI

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>

#define KEY_STORE "key_store.txt"

void help_print () {
	const std::vector<std::string> help_cmds = {
		"\nCmdCrypt",
		"A command line encryption and decryption tool",
		"\nMAIN ARGUMENTS:",
		"First argument:  encrypt or decrypt -> select between encryption or decryption modes",
		"Second argument: FileName -> enter the filename to be encrypted or decrypted ",
		"\nOPTIONAL ARGUMENTS:",
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

	std::ifstream user_file_test;
	user_file_test.open(FILE_NAME);
	if (user_file_test.fail()) {
		std::cerr << "Error, cannot open specified input text file." << std::endl;
		return EXIT_SUCCESS;
	}
	user_file_test.close();

	std::ifstream user_key_store_test;
	user_key_store_test.open(KEY_STORE);
	if (user_key_store_test.fail()) {
		std::cerr << "Error, cannot open specified input text file." << std::endl;
		return EXIT_SUCCESS;
	}
	user_key_store_test.close();

	std::ifstream output_file_test;
	output_file_test.open(OUTPUT_FILE);
	if (output_file_test.fail()) {
		std::cerr << "Error, cannot open specified output text file." << std::endl;
		return EXIT_SUCCESS;
	}
	output_file_test.close();


	// Get optional commands
	for (int i=2; i < argc; i++) {
		if (strcmp(argv[i], "-new") == 0) {
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


	std::string system_cmd;
	if (cmd == "encrypt") {
		system_cmd = "python ./rsa_encryption.py encrypt " + FILE_NAME + " " + OUTPUT_FILE;
		std::cout << "File encryption completed" << std::endl;
	}
	else if (cmd == "decrypt") {

		system_cmd = "python ./rsa_encryption.py decrypt " + FILE_NAME + " " + OUTPUT_FILE;
		std::cout << "File decryption completed" << std::endl;
	}

	const char *cstr = system_cmd.c_str();
	system(cstr); // run rsa_encryption.py

	return EXIT_SUCCESS;
}
