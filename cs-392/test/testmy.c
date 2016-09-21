/* Test file

Daniel Heyman
I pledge my honor that I have abided by the Stevens Honor System.

*/ 
#include "my.h"

int main(int argc, char **argv) {
    
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
    char s[] = "hello";
    my_int(my_revstr(s));
    my_str("\t\t = 5\n");
    my_str(s);
    my_str("\t\t = olleh\n");
    
    my_str("\nmy_strcat tests:\n");
    char s2[13] = "";
    my_strcat(NULL, NULL);
    my_strcat(s2, NULL);
    my_strcat(s2, "a");
    my_strcat(s2, "bcdef");
    my_strcat(s2, "abcdef");
    my_str(s2);
    my_str("\t = abcdefabcdef\n");
    
    my_str("\nmy_strdup tests:\n");
    my_str(my_strdup(NULL));
    char s3[13] = "hello";
    char *s4 = my_strdup(s3);
    s3[0] = 'm';
    my_str(s3);
    my_str(s4);
    my_str("\t = mellohello\n");
    
    my_str("\nmy_strconcat tests:\n");
    char *temp = my_strconcat(NULL, NULL);
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
    char s5[] = "0";
    char s6[] = "2147483647";
    char s7[] = "-2147483648";
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
