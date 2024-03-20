 #include <stdio.h>
#include <string.h>

#define MAX_DIGITS 1000

typedef struct {
    char sign; // '+' for positive, '-' for negative
    char digits[MAX_DIGITS];
} BigInt;

void remove_leading_zeros(BigInt* num) {
    while (num->digits[0] == '0' && strlen(num->digits) > 1) {
        memmove(num->digits, num->digits + 1, strlen(num->digits));
    }
}

BigInt big_int_subtract(const BigInt* a, const BigInt* b) {
    BigInt result;
    result.sign = '+';


    memset(result.digits, '0', MAX_DIGITS);
    result.digits[MAX_DIGITS - 1] = '\0';


    int carry = 0;
    int len_a = strlen(a->digits);
    int len_b = strlen(b->digits);
    int max_len = len_a > len_b ? len_a : len_b;

    for (int i = 0; i < max_len; ++i) {
        int digit_a = i < len_a ? a->digits[len_a - 1 - i] - '0' : 0;
        int digit_b = i < len_b ? b->digits[len_b - 1 - i] - '0' : 0;

        int diff = digit_a - digit_b - carry;
        if (diff < 0) {
            diff += 10;
            carry = 1;
        } else {
            carry = 0;
        }

        result.digits[MAX_DIGITS - 2 - i] = diff + '0';
    }


    if (carry) {
        result.sign = '-';
    }

    remove_leading_zeros(&result);

    return result;
}

int main() {
    BigInt num1 = { '+', "5482090" };
    BigInt num2 = { '+', "4813145" };

    BigInt result = big_int_subtract(&num1, &num2);

    printf("Result: %c%s\n", result.sign, result.digits);

    return 0;
}
