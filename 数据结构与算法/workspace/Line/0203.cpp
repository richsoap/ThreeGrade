# include <stdio.h>
# include <string.h>
int main() {
	char *str = new char[11];
	char *substr = new char[4];
	int length,max,index;
  bool times = false;
	while(true) {
    if(times) {
      printf("\n");
    }
    else {
      times = true;
    }
    index = scanf("%s %s",str,substr);
    if(index != 2) {
      break;
    }
    max = 0;
		index = 0;
		for(length = 0;length < 11;length ++) {
			if(str[length] == '\0') {
				break;
			}
			if(str[length] > max) {
				max = str[length];
				index = length;
			}
		}
		for(int i = 0;i < length;i ++) {
			printf("%c",str[i]);
			if(i == index) {
				printf("%s",substr);
			}
		}
	}
	return 0;

}
