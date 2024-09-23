#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK 1000

// Stack structure for storing opening parentheses, brackets, and braces
struct Stack {
    char items[MAX_STACK];
    int top;
};

// Function to initialize the stack
void initStack(struct Stack* s) {
    s->top = -1;
}

// Function to push an item onto the stack
void push(struct Stack* s, char c) {
    if (s->top < MAX_STACK - 1) {
        s->items[++(s->top)] = c;
    } else {
        printf("Stack overflow!\n");
        exit(1);
    }
}

// Function to pop an item from the stack
char pop(struct Stack* s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    }
    return '\0';  // Return null character if stack is empty
}

// Function to check if the stack is empty
int isEmpty(struct Stack* s) {
    return s->top == -1;
}

// Function to check if two characters are matching pairs
int isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

// Main function to check for syntax errors
int checkSyntax(FILE* file) {
    struct Stack s;
    initStack(&s);

    int inSingleQuote = 0;
    int inDoubleQuote = 0;
    int inComment = 0;
    int inEscapeSequence = 0;

    char prev = '\0';
    char current;
    while ((current = fgetc(file)) != EOF) {
        // Handle escape sequences inside quotes
        if (inEscapeSequence) {
            inEscapeSequence = 0;
            continue;
        }
        if (current == '\\' && (inSingleQuote || inDoubleQuote)) {
            inEscapeSequence = 1;
            continue;
        }

        // Handle single and double quotes
        if (!inComment) {
            if (current == '\'' && !inDoubleQuote) {
                inSingleQuote = !inSingleQuote;
            }
            if (current == '"' && !inSingleQuote) {
                inDoubleQuote = !inDoubleQuote;
            }
        }

        // Ignore everything inside comments
        if (prev == '/' && current == '*' && !inSingleQuote && !inDoubleQuote) {
            inComment = 1;
            prev = '\0';  // Prevent false matches
            continue;
        }
        if (prev == '*' && current == '/' && inComment) {
            inComment = 0;
            prev = '\0';  // Prevent false matches
            continue;
        }

        if (inSingleQuote || inDoubleQuote || inComment) {
            prev = current;
            continue;
        }

        // Handle opening parentheses, brackets, and braces
        if (current == '(' || current == '[' || current == '{') {
            push(&s, current);
        }
        // Handle closing parentheses, brackets, and braces
        else if (current == ')' || current == ']' || current == '}') {
            char lastOpened = pop(&s);
            if (!isMatchingPair(lastOpened, current)) {
                printf("Unmatched %c found.\n", current);
                return 0;  // Syntax error
            }
        }

        prev = current;
    }

    // After reading the file, check if stack is empty (no unclosed parentheses, brackets, or braces)
    if (!isEmpty(&s)) {
        printf("Unbalanced parentheses, brackets, or braces found.\n");
        return 0;  // Syntax error
    }

    // Check if we are still inside a quote or a comment
    if (inSingleQuote) {
        printf("Unclosed single quote found.\n");
        return 0;
    }
    if (inDoubleQuote) {
        printf("Unclosed double quote found.\n");
        return 0;
    }
    if (inComment) {
        printf("Unclosed comment found.\n");
        return 0;
    }

    printf("No syntax errors found!\n");
    return 1;  // No syntax errors
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_to_check.c>\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Error opening file: %s\n", argv[1]);
        return 1;
    }

    // Perform syntax checking
    int result = checkSyntax(file);

    fclose(file);
    return result;
}
