#ifndef _REVERSE_H_
#define _REVERSE_H_

char* reverse(const char* s) {
	size_t n = strlen(s);
	char* rs = malloc(n + sizeof(char));

	for(int i = 0; s[i] != '\0'; i++) {
		rs[n-i-1] = s[i];
	}
	rs[n] = '\0';
	return rs;
}

#endif