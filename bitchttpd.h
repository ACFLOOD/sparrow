#include "ev_loop.h"


// typedef struct sock_info {
// 	//int sockfd;
// 	int ffd;
// 	unsigned int write_pos;
// 	unsigned int read_pos;
// 	unsigned int total_len;
// 	char buf[MAXBUFSIZE];
// } sock_info_t;

void *accept_sock(ev_loop_t *loop, int sock, EV_TYPE events);
void *read_http(ev_loop_t *loop, int sock, EV_TYPE events);
void *write_http_header(ev_loop_t *loop, int sockfd, EV_TYPE events);
void *write_http_body(ev_loop_t *loop, int sockfd, EV_TYPE events);