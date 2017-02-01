# CmdCrypt [![Build Status](https://travis-ci.org/DylanTinianov/CmdCrypt.svg?branch=master)]

A command line encryption and decryption tool

## Encryption

Encrypting a file will create a new key_store text file.

After the encryption is completed, the key_store file will be needed to decrypt the data.

key_store files should be kept safe and private on a secure external storage device

## Decryption

To decrypt a previously encrypted text file, the corresponding key_store file must be accessible.

Currently, you must place this file in the same directory as the software.

Future changes will allow for the location of the file to be entered by the user.

## How To Use

To encrypt a file type:

```
$ ./CmdCrypt encrypt "FILE_NAME"
```

To decrypt an encrypted file type:

```
$ ./CmdCrypt decrypt "FILE_NAME"
```

To encrypt or decrypt the contents into a new file, add the following argument:

```
-new NEW_FILE_NAME
```

For a list of command arguments, type:

```
$ ./CmdCrypt help
```
