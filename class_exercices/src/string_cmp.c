#include <stdio.h>

int strcasecmp( const char *ls, const char *rs );

int strcasecmp(const char *ls, const char *rs) {
	while (*ls && *rs) {
		char l = *ls;
		char r = *rs;
	
		// Convert all to lower case
		if (l >= 'A' && l <= 'Z') {
			l += 'a' - 'A';
		}
		if (r >= 'A' && r <= 'Z') {
			r += 'a' - 'A';
		}
		if (l != r) {
			return l - r;
		}
		ls++;
		rs++;
	}
	// Compare last char in case size of strings are different
	char l = *ls;
	char r = *rs;

	if (l >= 'A' && l <= 'Z') {
		l += 'a' - 'A';
	}
	if (r >= 'A' && r <= 'Z') {
		r += 'a' - 'A';
	}
	return l - r;

}

int main() {
	const char *ls = "Hello";
    const char *rs = "hello";

    int result = strcasecmp(ls, rs);

    if (result < 0) {
        printf("ls < rs\n");
    } else if (result == 0) {
        printf("ls = rs\n");
    } else {
        printf("ls > rs\n");
    }
}
