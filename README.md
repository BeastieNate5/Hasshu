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
git clone https://github.com/BeastieNate5/Hasshu
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
Options:
    -t                     Displays the available hashing modes
    -m <mode>              Sets the hashing mode
    -w <word_list_path>    Sets the wordlist that will be used
```
The following will be a valid way to use Hasshu 
```
hasshu secret -m 3 -w rockyou.txt
```
```
[+] Located Hash file (65 bytes)
[+] Successfully allocated (66 bytes)
[+] Wrote hash to allocated memory
[!] Setting up hashing algo
[!] Cracking password...
[+] Cracked hash: nate
[+] Password was cracked
```
**NOTE**: The hash can be in a file or you can just put the hash itself as the argument. It also does not matter in which order you put it in the command.

The hash mode determines what hashing algorithm that Hasshu will use. To get all hashing modes you will do the following
```
hasshu -t
```

## Contribution
I am open for contributions. If you want to contribute fork this repo and make your changes in a separate branch then submit a pull request.   

