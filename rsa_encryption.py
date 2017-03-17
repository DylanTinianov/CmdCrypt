import used_functions
import prime_generator
import sys
import os

KEY_STORE = "key_store.decr"


class PrivateKeyGen:

    def __init__(self):
        prime_bit_length = 128  # Prime lengths for a 1024 bit key
        self.p = prime_generator.generate_large_prime(prime_bit_length)
        self.q = prime_generator.generate_large_prime(prime_bit_length)
        while self.p == "Failed":   # In case there is a failed attempt
            self.p = prime_generator.generate_large_prime(prime_bit_length)
        while self.q == "Failed":
            self.p = prime_generator.generate_large_prime(prime_bit_length)

        self.n = self.p * self.q
        self.phi_func = (self.p - 1) * (self.q - 1)
        self.e = int()
        self.d = int()

    def public_exponent(self):
        # Officially secure e values
        secure_e_values = [3, 5, 17, 257, 65537]
        for i in secure_e_values:
            if self.n % i != 0 and self.phi_func % i != 0:
                self.e = i
                return True

        return False

    def private_exponent(self):
        self.d = used_functions.modInv(self.e, self.phi_func)

    def decrypt(self, encrypted_message):
        decrypted_text = list()

        for line in encrypted_message:
            for word in line:
                for letter in word:
                    try:
                        decrypted_text.append(
                            chr(pow(long(letter), self.d, self.n)))
                    except (OverflowError, ValueError):  # Ignore any errors
                        pass

        return decrypted_text


class PublicKey:

    def __init__(self, e, n):
        self.e = e
        self.n = n

    def print_key(self):
        print "Public Key:", self.e, self.n
        return self.e, self.n

    def encrypt(self, message):
        plain_text = list()
        number_text = list()
        number_text_encrypted = list()

        for line in message:
            for word in line:
                for letter in word:
                    plain_text.append(letter)
                #plain_text.append(' ')
            # plain_text.append("\n")

        for character in plain_text:
            number = ord(character)
            number_text.append(number)

        for num in number_text:
            number_text_encrypted.append(pow(num, self.e, self.n))

        return number_text_encrypted


def file_encrypt(data_in, write_file):
    key_out = open(os.path.join(os.path.dirname(__file__), KEY_STORE), "r+")
    out = write_file
    data = data_in
    # Generate key pair
    key_private = PrivateKeyGen()
    while not key_private.public_exponent():
        key_private = PrivateKeyGen()
        key_private.public_exponent()

    key_private.private_exponent()

    # Put key in key_store.txt
    key_out.write(str(key_private.d))
    key_out.write("\n")
    key_out.write(str(key_private.n))

    # Retrieve data to encrypt
    key_public = PublicKey(key_private.e, key_private.n)

    # Encrypt the data
    encryption = key_public.encrypt(data)
    print "Data encryption complete"
    for i in encryption:
        out.write(str(i))
        out.write(" ")


def file_decrypt(data_in, write_file):
    key_store = open(os.path.join(os.path.dirname(__file__), KEY_STORE), "r")

    tmp_key = list()
    for line in key_store:
        tmp_key.append(line)
    decr_key_e = int(tmp_key[0])
    decr_key_n = int(tmp_key[1])

    out = write_file
    data = data_in
    key_private = PrivateKeyGen()
    key_private.d = decr_key_e
    key_private.n = decr_key_n

    decryption = key_private.decrypt(data)
    for i in decryption:
        out.write(i)


def main():
    FILE_NAME = str(sys.argv[2])
    WRITE_FILE = str(sys.argv[3])

    data_file = open(os.path.join(os.path.dirname(__file__), FILE_NAME), "r")
    out = open(os.path.join(os.path.dirname(__file__), WRITE_FILE), "r+")

    data = list()
    for line in data_file:
        data.append(line.split())
    for i in range(len(data)):
        for n in range(len(data[i])):
            data[i][n] += " "
    data_file.close()

    if str(sys.argv[1]) == 'encrypt':
        file_encrypt(data_in=data, write_file=out)

    elif str(sys.argv[1]) == 'decrypt':
        file_decrypt(data_in=data, write_file=out)

    else:
        sys.exit()

    out.close()


if __name__ == '__main__':
    main()
