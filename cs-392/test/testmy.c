/* Test file

Carla Noshi and Daniel Heyman
I pledge my honor that I have abided by the Stevens Honor System.

*/ 
#include "my.h"

int main(int argc, char **argv) {
    char s[] = "hello";
    char s2[13] = "";
    char s3[13] = "hello";
    char *temp = my_strconcat(NULL, NULL);
    char *s4 = my_strdup(s3);
    char s5[] = "0";
    char s6[] = "2147483647";
    char s7[] = "-2147483648";
    char* test;
    
    my_str("my_char tests:\n");
    my_char('F');
    my_str("\t = F\n");
    
    my_str("\nmy_str tests:\n");
    my_str("");
    my_str(NULL);
    my_str("hello");
    my_str("\t = hello\n");
    
    my_str("\nmy_int tests:\n");
    my_int(0);
    my_str("\t\t = 0\n");
    my_int(500);
    my_str("\t\t = 500\n");
    my_int(-500);
    my_str("\t\t = -500\n");
    my_int(2147483647);
    my_str("\t = 2147483647\n");
    my_int(-2147483648);
    my_str("\t = -2147483648\n");
    
    my_str("\nmy_num_base tests:\n");
    my_num_base(9, "RTFM");
    my_str("\t\t\t = FT\n");
    my_num_base(22, "RTFM");
    my_str("\t\t\t = TTF\n");
    my_num_base(22, "");
    my_str("\t\t = Invalid String\n");
    my_num_base(-22, "RTFM");
    my_str("\t\t\t = -TTF\n");
    my_num_base(2147483647, "RTFM");
    my_str("\t = TMMMMMMMMMMMMMMM\n");
    my_num_base(-2147483648, "RTFM");
    my_str("\t = -FRRRRRRRRRRRRRRR\n");
    my_num_base(4, "R");
    my_str("\t\t\t = RRRR\n");
    my_num_base(-4, "R");
    my_str("\t\t\t = -RRRR\n");
    my_num_base(0, "RT");
    my_str("\t\t\t = R\n");
    
    my_str("\nmy_alpha tests:\n");
    my_alpha();
    my_str("\t = ABCDEFGHIJKLMNOPQRSTUVWXYZ\n");
    
    my_str("\nmy_digits tests:\n");
    my_digits();
    my_str("\t\t = 0123456789\n");
    
    my_str("\nmy_strindex tests:\n");
    my_int(my_strindex("", 'o'));
    my_str("\t\t = -1\n");
    my_int(my_strindex("hello", 'l'));
    my_str("\t\t = 2\n");
    my_int(my_strindex("hello", 'g'));
    my_str("\t\t = -1\n");
    
    my_str("\nmy_strrindex tests:\n");
    my_int(my_strrindex("", 'o'));
    my_str("\t\t = -1\n");
    my_int(my_strrindex("hello", 'l'));
    my_str("\t\t = 3\n");
    my_int(my_strrindex("hello", 'g'));
    my_str("\t\t = -1\n");
    
    my_str("\nmy_strlen tests:\n");
    my_int(my_strlen(NULL));
    my_str("\t\t = -1\n");
    my_int(my_strlen(""));
    my_str("\t\t = 0\n");
    my_int(my_strlen("hello"));
    my_str("\t\t = 5\n");
    
    my_str("\nmy_revstr tests:\n");
    my_int(my_revstr(NULL));
    my_str("\t\t = -1\n");
    my_int(my_revstr(""));
    my_str("\t\t = 0\n");
    my_int(my_revstr(s));
    my_str("\t\t = 5\n");
    my_str(s);
    my_str("\t\t = olleh\n");

    /*Assignment 2*/

    my_str("\nmy_strfind tests:\n");
    test = my_strfind("hello", 'l'); 
    my_str(test);
    my_str("\t\t = llo\n");
    test = my_strfind("hello", 'p'); 
    my_str(test);
    my_str("\t\t = nothing\n");
    test = my_strfind(NULL, 'r');
    my_str("\t\t = nothing\n");

    my_str("\nmy_strrfind tests:\n");
    test = my_strrfind("hello", 'l'); 
    my_str(test);
    my_str("\t\t = lo\n");
    test = my_strrfind("hello", 'p'); 
    my_str(test);
    my_str("\t\t = nothing\n");
    test = my_strrfind(NULL, 'r');
    my_str("\t\t = nothing\n");

    my_str("\nmy_strcmp tests:\n");
    my_int(my_strcmp("aaa", "bbb"));
    my_str("\t\t = -1\n");
    my_int(my_strcmp("aaa", "aaa"));
    my_str("\t\t = 0\n");
    my_int(my_strcmp("bbb", "aaa"));
    my_str("\t\t = 1\n");
    my_int(my_strcmp(NULL, NULL));
    my_str("\t\t = 0\n");
    my_int(my_strcmp(NULL, "aaa"));
    my_str("\t\t = -1\n");
    my_int(my_strcmp("bbb", NULL));
    my_str("\t\t = 1\n");
    my_int(my_strcmp("water", "weather"));
    my_str("\t\t = -4\n");
    my_int(my_strcmp("weather", "water"));
    my_str("\t\t = 4\n");

    my_str("\nmy_strncmp tests:\n");
    my_int(my_strncmp("water", "weather", 2));
    my_str("\t\t = -4\n");
    my_int(my_strncmp("wet", "weather", 2));
    my_str("\t\t = 0\n");
    my_int(my_strncmp("weather", "water", 2));
    my_str("\t\t = 4\n");
    my_int(my_strncmp(NULL, NULL, 3));
    my_str("\t\t = 0\n");
    my_int(my_strncmp(NULL, "aaa", 3));
    my_str("\t\t = -1\n");
    my_int(my_strncmp("bbb", NULL, 3));
    my_str("\t\t = 1\n");
    my_int(my_strncmp("bbb", "aaa", 0));
    my_str("\t\t = 0\n");

    my_str("\nmy_strcpy tests:\n");
    test = my_strdup("$$$$$$$$$$$$$$$");
    my_str(my_strcpy(test, "ABCD")); 
    my_str("\t\t = ABCD\n");
    free(test);
    test = my_strdup("Test");
    my_str(my_strcpy(test, "")); 
    my_str("\t\t = nothing\n");
    my_str(my_strcpy(test, NULL)); 
    my_str("\t\t = nothing\n");
    my_str(my_strcpy(NULL, "Test"));
    my_str("\t\t = nothing\n");
    my_str(my_strcpy(test, "ABCDE"));
    my_str("\t\t = ABCDE\n");
    free(test);

    my_str("\nmy_strncpy tests:\n");
    test = my_strdup("$$$$$$$$$$$$$$$");
    my_str(my_strncpy(test, "Test", 5)); 
    my_str("\t\t = Test\n");
    my_str(my_strncpy(test, "Test", 2)); 
    my_str("\t\t = Te\n");
    free(test);
    test = my_strdup("Test");
    my_str(my_strncpy(test, "", 5)); 
    my_str("\t\t = nothing\n");
    my_str(my_strncpy(test, NULL, 5)); 
    my_str("\t\t = nothing\n");
    my_str(my_strncpy(NULL, "Hello", 5)); 
    my_str("\t\t = nothing\n");
    free(test);
    test = my_strdup("Hello");
    my_str(my_strncpy(test, "Tests", 5)); 
    free(test);
    my_str("\t\t = Tests\n");

    my_str("\nmy_strcat tests:\n");
    my_strcat(NULL, NULL);
    my_strcat(s2, NULL);
    my_strcat(s2, "a");
    my_strcat(s2, "bcdef");
    my_strcat(s2, "abcdef");
    my_str(s2);
    my_str("\t = abcdefabcdef\n");
    
    my_str("\nmy_strdup tests:\n");
    my_str(my_strdup(NULL));
    s3[0] = 'm';
    my_str(s3);
    my_str(s4);
    my_str("\t = mellohello\n"); 
    
    my_str("\nmy_strconcat tests:\n");
    free(temp);
    temp = my_strconcat(s3, NULL);
    my_str(temp);
    free(temp);
    my_str("\t\t = mello\n");
    temp = my_strconcat(NULL, s4);
    my_str(temp);
    free(temp);
    my_str("\t\t = hello\n");
    temp = my_strconcat(s3, s4);
    my_str(temp);
    free(temp);
    my_str("\t = mellohello\n");
    
    my_str("\nmy_strnconcat tests:\n");
    
    temp = my_strnconcat(NULL, NULL, 10);
    free(temp);
    temp = my_strnconcat(s3, NULL, 10);
    my_str(temp);
    free(temp);
    my_str("\t\t = mello\n");
    temp = my_strnconcat(NULL, s4, 10);
    my_str(temp);
    free(temp);
    my_str("\t\t = hello\n");
    temp = my_strnconcat(s3, s4, 10);
    my_str(temp);
    free(temp);
    my_str("\t = mellohello\n");
    temp = my_strnconcat(s3, s4, 2);
    my_str(temp);
    free(temp);
    my_str("\t\t = mellohe\n");
    free(s4);
    
    my_str("\nmy_atoi tests:\n");
    my_int(my_atoi(s5));
    my_str("\t\t = 0\n");
    my_int(my_atoi(NULL));
    my_str("\t\t = 0\n");
    my_int(my_atoi(s6));
    my_str("\t = 2147483647\n");
    my_int(my_atoi(s7));
    my_str("\t = -2147483648\n");
    
    
    return 0;
}
