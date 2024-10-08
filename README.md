# Hasshu
## About
Hasshu is a simple password that is available for Linux. It takes a provided password hash and wordlist and returns if any word in the wordlist matches the hash. This is not a production made password cracker it's just a project I wanted to make and available for anyone to use.

## Dependencies
You will need the GCC compiler and OpenSSL version 3.3 or above installed.
```
gcc
openssl 3.3
```

## Installation 
```
git clone <HASHUU REPO LINK>
```
```
cd Hasshu
```
```
make
```

## Usage
To crack a password hash you will do the following
```
hasshu <HASH/HASH_FILE> -m <HASH_MODE> -w <WORDLIST>
```
```
SHOW OUTPUT
```
**NOTE**: The hash can be in a file or you can just put the hash itself as the argument. It also does not matter in which order you put it in the command. 
