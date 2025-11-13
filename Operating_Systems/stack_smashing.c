#include <stdio.h>
#include <string.h>

void main() {
    char str1[6], str2[6] = "Shakil";
    strcpy(str1, "Mehedi_Hasan_");
    printf("%s %s\n", str1, str2);
}

/*
Here total bytes allocated is (6+6) or 12
Stack smashing occurs if number of characters exceed 12 (excluding null terminator)

For the the following example, smashing does not occur
strcpy(str1, "Mehedi_Hasan"); // Exactly 12 characters
Output: Mehedi_Hasan _Hasan

But the following leads to smashing
strcpy(str1, "Mehedi_Hasan_"); // 13 characters
Output:
Mehedi_Hasan_ _Hasan_
*** stack smashing detected ***: terminated
Aborted (core dumped)
*/