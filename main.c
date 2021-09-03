#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOWER_LEN strlen(lower_case_letters)
#define UPPER_LEN strlen(upper_case_letters)
#define DIGIT_LEN strlen(digits)
#define SPECIAL_LEN strlen(specials)

#define PASSWORD_LENGTH 12
#define FUNCTION_POINTER_LEN 4

const char* lower_case_letters = "abcdefghijklmnoprstquvwxyz";
const char* upper_case_letters = "ABCDEFGHIJKLMNOPRSTQUVWXYZ";
const char* digits = "0123456789";
const char* specials = "*?#$/.:,;!{}()[]-_";

// forward declaration
char get_random_lowercase_letter(void);
char get_random_uppercase_letter(void);
char get_random_digit(void);
char get_random_special_char(void);

// function pointer array is declared to make the generated password more random
char (*get_char[FUNCTION_POINTER_LEN]) (void) = {  
    &get_random_lowercase_letter,
    &get_random_uppercase_letter,
    &get_random_digit,
    &get_random_special_char
};

void init_randomness(void) {
    srand(time(NULL));
}

int generate_random_int(int x) {
    return rand() % x;
}

char get_random_lowercase_letter(void) {
    return lower_case_letters[generate_random_int(LOWER_LEN)];
}

char get_random_uppercase_letter(void) {
    return upper_case_letters[generate_random_int(UPPER_LEN)];
}

char get_random_digit(void) {
    return digits[generate_random_int(DIGIT_LEN)];
}

char get_random_special_char(void) {
    return specials[generate_random_int(SPECIAL_LEN)];
}

char* generate_secure_password(void) {
    char* password = malloc( sizeof(char) * PASSWORD_LENGTH );
    
    for ( int i=0; i<PASSWORD_LENGTH; ++i ) {
        int index = generate_random_int(FUNCTION_POINTER_LEN);
        password[i] = (*get_char[index])();   
    }

    return password;
}

int main(int argc, char** argv) {
    init_randomness();
    char* password = generate_secure_password();
    printf("%s\n", password);
    
    free(password);

    return EXIT_SUCCESS;
}
