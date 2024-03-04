#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void swap(char *a, char *b) {
    char t = *a;
    *a = *b;
    *b = t;
}

struct number{
    char *num;
    int capacity;
    int length;
};

void createNo(struct number *no){
    no->num = NULL;
    no->capacity = 0;
    no->length = 0;
}

void takeInput(struct number *no){
    char ch;

    while((ch=getchar()) != '\n'){
        if(no->length+1>=no->capacity){
            no->capacity += 10;
            no->num = (char *)realloc(no->num, no->capacity * sizeof(char));
        }

        if(no->num==NULL){
            printf("Memory allocation failed.\n");
            return;
        }

        no->num[no->length++] = ch;
    }

}

void display(struct number *no){
    for(int i=0;i<no->length;i++){
        printf("%c",no->num[i]);
    }
}

void appendDigit(struct number *no, char digit) {
    if (no->length + 1 >= no->capacity) {
        no->capacity += 10;
        no->num = (char *)realloc(no->num, no->capacity * sizeof(char));
    }
    no->num[no->length++] = digit;
}

// Function to reverse the number
void reverseNumber(struct number *no) {
    for (int i = 0; i < no->length / 2; i++) {
        char temp = no->num[i];
        no->num[i] = no->num[no->length - i - 1];
        no->num[no->length - i - 1] = temp;
    }
}

// Function to add two numbers
struct number addNumbers(struct number *num1, struct number *num2) {
    struct number result;
    createNo(&result);

    int carry = 0;
    int i = num1->length - 1;
    int j = num2->length - 1;

    while (i >= 0 || j >= 0 || carry) {
        int digit_sum = carry;

        if (i >= 0)
            digit_sum += num1->num[i--] - '0';

        if (j >= 0)
            digit_sum += num2->num[j--] - '0';

        appendDigit(&result, (digit_sum % 10) + '0');
        carry = digit_sum / 10;
    }

    reverseNumber(&result);
    return result;
}



struct number subtractNumbers(struct number *num1, struct number *num2) {
    struct number result;
    createNo(&result);

    int borrow = 0;
    int i = num1->length - 1;
    int j = num2->length - 1;

    while (i >= 0 || j >= 0) {
        int digit_diff = borrow;

        if (i >= 0)
            digit_diff += num1->num[i--] - '0';

        if (j >= 0)
            digit_diff -= num2->num[j--] - '0';

        if (digit_diff < 0) {
            borrow = -1;
            digit_diff += 10;
        } else {
            borrow = 0;
        }

        appendDigit(&result, digit_diff + '0');
    }

    while (result.length > 1 && result.num[result.length - 1] == '0') {
        result.length--;
    }

    reverseNumber(&result);
    return result;
}

struct number divideNumbers(struct number *dividend, struct number *divisor) {
    struct number quotient, remainder, temp;
    createNo(&quotient);
    createNo(&remainder);
    createNo(&temp);

    // Copy dividend to remainder
    for (int i = 0; i < dividend->length; i++) {
        appendDigit(&remainder, dividend->num[i]);
    }

    // Set quotient length to 1
    appendDigit(&quotient, '0');

    // Divide until remainder is less than divisor
    while (strcmp(remainder.num, divisor->num) >= 0) {
        int count = 0;
        while (strcmp(remainder.num, divisor->num) >= 0) {
            // Subtract divisor from remainder
            temp = subtractNumbers(&remainder, divisor);
            if (temp.num[0] == '0' && temp.length == 1) {
                break;
            }

            // Update remainder
            for (int i = 0; i < temp.length; i++) {
                remainder.num[i] = temp.num[i];
            }
            remainder.length = temp.length;
            count++;
        }

        // Update quotient
        appendDigit(&quotient, count + '0');
    }

    // Free dynamically allocated memory
    free(temp.num);

    return quotient;
}


int main(){
    struct number no,no2;

    createNo(&no);
    createNo(&no2);
    takeInput(&no);
    takeInput(&no2);

    

    struct number n = addNumbers(&no,&no2);

    display(&n);
    printf("\n");

    n = subtractNumbers(&no,&no2);
    display(&n);
    printf("\n");

    n = divideNumbers(&no,&no2);
    display(&n);

    return 0;
}
//bina array aur linklist uuse kiye operations perform karna 
