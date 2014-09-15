#include <stdio.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#include "file.h"
#include "global.h"




int isItFolder(const char *path){
	struct stat s;
	if(0 == stat(path, &s)){
		if(S_ISDIR(s.st_mode))
			return 1;
	}
	return 0;
}

int isItFile(const char *path){
	struct stat s;
	if(0 == stat(path, &s)){
		if(S_ISREG(s.st_mode))
			return 1;
	}
	return 0;
}

int block_read(char *filename, char *buf, int max_size) {
	int n = 0;
	int fd = open(filename, O_RDONLY);
	if(fd == -1) {
		printf("error open %s\n", filename);
		return -1;
	}
	while(1) {
		int t;
		t = read(fd, buf, max_size - n);
		if(t > 0) {
			n +=t;
		} else if(t == -1) {
			printf("err read\n");
		} else if(t == 0) {
			//printf("here\n");
			break;
		}
	}
	
	buf[n] = '\0';
	return 0;
}


int dir_html_maker(char *buf, char *path) {
	struct dirent *temp_path;
	struct stat s;
	DIR *dir;
	char newpath[512];

	dir = opendir(path);
	if(dir == NULL){
		perror("opendir error");
		return -1;
	}

	char prefix[64];
	char *p = strrchr(path, '/');
	strcpy(prefix, p+1);
	int len = strlen(prefix);
	if(len != 0) {
		prefix[len] = '/';
		prefix[len+1] = '\0';
	}

	int pos = 0;
	int ret;
	printf("|||||||||path:%s-\n", path);
	if(strcmp(path, WORKING_DIR) != 0) {
		//add back operation
		if(len == 0) {
			ret = sprintf(buf+pos,"<div class=\"dir\"><a href=\"../\"><img src=\"/back.ico\">&nbsp;BACK</a></div>\n");
		} else {
			ret = sprintf(buf+pos,"<div class=\"dir\"><a href=\"../\"><img src=\"/back.ico\">&nbsp;BACK</a></div>\n");
		}
		pos +=ret;
	}

	while((temp_path = readdir(dir))!=NULL) {
		
		if(!strcmp(temp_path->d_name,".")||!strcmp(temp_path->d_name,".."))
			continue;

		if(path[strlen(path)-1]=='/')
			sprintf(newpath, "%s%s", path, temp_path->d_name);
		else
			sprintf(newpath, "%s/%s", path, temp_path->d_name);
		
		lstat(newpath, &s);
		
		//printf("||||||||prefix:%s==\n", prefix);
		//int ret = 0;
		
		if(S_ISDIR(s.st_mode)){
			ret = sprintf(buf+pos,"<div class=\"dir\"><a href=\"%s%s/\"><img src=\"/dir.png\">&nbsp;%s</a></div>\n", \
				/*newpath+strlen(WORKING_DIR)*/prefix, temp_path->d_name, temp_path->d_name);
			pos +=ret;
		}else if(S_ISREG(s.st_mode)){
			
			ret = sprintf(buf+pos,"<div class=\"file\"><a href=\"%s%s\"><img src=\"/file.ico\">&nbsp;%s</a></div>\n", \
				/*newpath+strlen(WORKING_DIR)*/prefix, temp_path->d_name, temp_path->d_name);
			pos +=ret;
		}
	}
	closedir(dir);
	return 0;
}