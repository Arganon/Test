#include <time.h>
#include <pcap.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>

#define SIZE_ETHERNET 14
#define ETHER_ADDR_LEN	6
#define STRING_SIZE_IP 16
#define FNULL 0L

/* IP header */
struct sniff_ip {
        u_char  ip_vhl;                 /* version << 4 | header length >> 2 */
        u_char  ip_tos;                 /* type of service */
        u_short ip_len;                 /* total length */
        u_short ip_id;                  /* identification */
        u_short ip_off;                 /* fragment offset field */
        u_char  ip_ttl;                 /* time to live */
        u_char  ip_p;                   /* protocol */
        u_short ip_sum;                 /* checksum */
        struct  in_addr ip_src,ip_dst;  /* source and dest address */
} sniff_ip;

typedef struct fnode {				/* Structure for saving packets in binary tree */
	struct in_addr ip_address;		/* IP address */
	unsigned long packet;			/* Captured pakets quantity */
	unsigned long address;			/* Structyre address in the file */
	unsigned long left;				/* Address in the file for left branch */
	unsigned long right;			/* Address in the file for right branch */
	
} fnode;

FILE *out;
char *dev;		// device - eth0 or wlan0 or etc.
int packets_quantity = -1;	/* Number of packets to capture. 
							If negative value - sniff until an error occurs */

void add_node_to_the_binary_tree(fnode parent, fnode temp);
void error_print(const char *text, const char *errbuf);
void save_to_file(fnode parent, fnode temp);
fnode make_node(struct in_addr ip_address);
void show_nodes_in_file(fnode buff);
void add(struct in_addr ip_address);
void prepare_for_sniffing();
fnode load_from_file();
void start_sniff();
void end_sniffing();
void open_file_stream();

fnode make_node(struct in_addr ip_address) {		/* Node making method */
	fnode temp;
	temp.ip_address = ip_address;
	temp.packet = 1;
	temp.address = FNULL;			/* Node address in file */
	temp.left = FNULL;
	temp.right = FNULL;
	return temp;
}

void go_to_position_in_file_and_read(unsigned long address, fnode *fread_temp) {
	fseek(out, address, SEEK_SET);
	fread(&(*fread_temp), sizeof(fnode), 1, out);
}

void go_to_position_in_file_and_write(unsigned long address, fnode *fwrite_temp, int seek) {
	fseek(out, address, seek);
	fwrite(&(*fwrite_temp), sizeof(fnode), 1, out);
}

/* Add root node to the file. If node not first we calling add_node_to_the_binary_tree */
void add(struct in_addr ip_address) {
	fnode root;
	fseek(out, FNULL, SEEK_END);
	int size = ftell(out);
	if ( size == 0) {
		root = make_node(ip_address);
		go_to_position_in_file_and_write(FNULL, &root, SEEK_SET);
	} else {
		fnode temp = make_node(ip_address);
		go_to_position_in_file_and_read(FNULL, &root);
		add_node_to_the_binary_tree(root, temp);
	}
}

/* Process of building binary tree in the file and saving node on it */
void add_node_to_the_binary_tree(fnode parent, fnode temp) {
	if (parent.ip_address.s_addr > temp.ip_address.s_addr && parent.left != FNULL) {
		go_to_position_in_file_and_read(parent.left, &parent);
		add_node_to_the_binary_tree(parent, temp);		
	} else if (parent.ip_address.s_addr < temp.ip_address.s_addr && parent.right != FNULL) {
		go_to_position_in_file_and_read(parent.right, &parent);
		add_node_to_the_binary_tree(parent, temp);		
	} else {
		save_to_file(parent, temp);
	}
}

void save_to_file(fnode parent, fnode temp) {
	fseek(out, FNULL, SEEK_END);
	temp.address = ftell(out);

	if (parent.ip_address.s_addr == temp.ip_address.s_addr) {
		parent.packet += 1;
		go_to_position_in_file_and_write(parent.address, &parent, SEEK_SET);
	} else if (parent.ip_address.s_addr < temp.ip_address.s_addr) {
		parent.right = temp.address;
		go_to_position_in_file_and_write(parent.address, &parent, SEEK_SET);
		go_to_position_in_file_and_write(FNULL, &temp, SEEK_END);
	} else {
		parent.left = temp.address;
		go_to_position_in_file_and_write(parent.address, &parent, SEEK_SET);
		go_to_position_in_file_and_write(FNULL, &temp, SEEK_END);	
	}
}

void open_file_stream() {
	out = fopen("file.bin", "r+b");
	if (out == NULL) {
		out = fopen("file.bin", "w+b");
	}
}

void show() {
	out = fopen("file.bin", "r");
	fseek(out, FNULL, SEEK_SET);
	fnode buff;
	fread(&buff, sizeof(fnode), 1, out);
	show_nodes_in_file(buff);
	fclose(out);
}

void show_nodes_in_file(fnode buff) {
	fseek(out, FNULL, SEEK_END);
	long i = ftell(out);
	if (buff.address >= i - (long)sizeof(fnode)) {
		printf("IP: %s Packets: %lu\n", inet_ntoa(buff.ip_address), buff.packet);
		exit(EXIT_SUCCESS);
	} else {
		printf("IP: %s Packets: %lu\n", inet_ntoa(buff.ip_address), buff.packet);
		go_to_position_in_file_and_read(buff.address+(long)sizeof(fnode), &buff);
		show_nodes_in_file(buff);
	}
}

void set_pid(pid_t pid) {
	pid = fork();
	if (pid != 0) {
		FILE *pid_file = fopen("a.pid", "w");	/* file where we writing daemon process number */
		fprintf(pid_file, "%d\n", pid);
	}
	if (pid < 0) {
		end_sniffing();
		exit(EXIT_FAILURE);
	}
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}
}

void set_sid(pid_t sid) {
	sid = setsid();

	if (sid < 0) {
		error_print("Can't start Daemon.\n", NULL);
		end_sniffing();
		exit(EXIT_FAILURE);
	}
}

void end_sniffing() {
	int del_pid_file = remove("a.pid");
	fclose(out);
	exit(EXIT_SUCCESS);
}

void close_standart_file_descriptor() {
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void change_root_directory() {
	if ((chdir("/")) < 0) {
		exit(EXIT_FAILURE);
	}
}

void build_sniffing_process(pid_t pid, pid_t sid) {
	set_pid(pid);
	umask(0);		/* full access to the files generated by the daemon */
	set_sid(sid);
	//close_standart_file_descriptor(); /* close input/output CLI (uncomment if needed) */
	//change_root_directory();	/* uncoment if needed */
	start_sniff();
	end_sniffing();
}

void stop_daemon(pid_t pid) {
	int len;
	char pid_buf[20];
	int pid_num = open("a.pid", O_RDONLY);
	if (pid != 0) {
		len = read(pid_num, pid_buf, 16);
		pid_buf[len] = 0;
		pid = atoi(pid_buf);
		kill(pid, SIGUSR2);
		end_sniffing();
	} else {
		exit(EXIT_FAILURE);
	}
}

void read_arg_from_main(char *argv[]) {
	pid_t pid, sid;
	if (strcmp(argv[1], "-stop") == 0) {
		stop_daemon(pid);
	}
	if (strcmp(argv[1], "-show") == 0) {
		show();
		exit(EXIT_SUCCESS);
	}
	if (strcmp(argv[1], "-select") == 0 && strcmp(argv[2], "iface") == 0) {
		dev = argv[3];
		build_sniffing_process(pid, sid);
		exit(EXIT_SUCCESS);
	}
	if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-h") == 0) {
		printf("You can use next argument:\n-start\n-stop\n-show\n-select iface [iface] (without brackets[])\n-h or -help or --help\n");
		exit(EXIT_SUCCESS);
	}
	if(strcmp(argv[1], "-start") == 0) {
		int pid_num = open("a.pid", O_RDONLY);
		if (pid_num > 0) {
			error_print("Daemon is already work\n", NULL);
			exit(EXIT_FAILURE);
		} else {
			dev = NULL;
			build_sniffing_process(pid, sid);
			exit(EXIT_SUCCESS);
		}
	}
	printf("Arguments is not correct.\n");
	exit(EXIT_FAILURE);
}

// Print error to the file.
void error_print(const char *text, const char *errbuf) {
	FILE *outEr = fopen("error.txt", "a+");
	time_t t = time(NULL);
	struct tm *tm = localtime(&t);
	fprintf(outEr, "%s: %s %s\n--------------------------------\n", 
	asctime(tm), text, errbuf);
	fclose(outEr);
}

void take_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
	const struct sniff_ip *ip;		/* The IP header */
	ip = (struct sniff_ip*)(packet + SIZE_ETHERNET); /* define/compute ip header offset */
	struct in_addr ip_address = ip->ip_src;
	add(ip_address);		/* add source IP addresses to the binary tree */
}

void start_sniff() {
	char errbuf[PCAP_ERRBUF_SIZE];	/* error buffer */
	char filter_exp[] = "ip";		/* filter expression */
	struct bpf_program filter;		/* compiled filter program (expression) */
	bpf_u_int32 mask;				/* subnet mask */
	bpf_u_int32 net;				/* ip */
	pcap_t *handle;					/* packet capture handle */	

	/* find a capture device. If we not chose any device system will choose default device */
	if (dev == NULL) {
		dev = pcap_lookupdev(errbuf);
	}

	/* If pcap_lookupdev method return NULL */
	if (dev == NULL) {
		error_print("Can't find device", errbuf);
		end_sniffing();
		exit(EXIT_FAILURE);
	}

	/* get network number and mask associated with capture device */
	if (pcap_lookupnet(dev, &net, &mask, errbuf) == -1) {
		error_print("Couldn't find mask and net", errbuf);
		net = 0;
		mask = 0;
		end_sniffing();
		exit(EXIT_FAILURE);
	}

	/* open capture device */
	handle = pcap_open_live(dev, BUFSIZ, 1, 10, errbuf);
	if (handle == NULL) {
		error_print("Couldn't open device", errbuf);
		end_sniffing();
		exit(EXIT_FAILURE);
	}

	/* compile the filter expression */
	if (pcap_compile(handle, &filter, filter_exp, 0, net) == -1) {
		error_print("Couldn't parse filter", NULL);
		end_sniffing();
		exit(EXIT_FAILURE);
	}

	/* apply the compiled filter */
	if (pcap_setfilter(handle, &filter) == -1) {
		error_print("Couldn't install filter", NULL);
		end_sniffing();
		exit(EXIT_FAILURE);
	}
	/* callback function */
	open_file_stream();
	pcap_loop(handle, packets_quantity, take_packet, NULL);
	pcap_freecode(&filter);
	pcap_close(handle);
	end_sniffing();
}

int main(int argc,char *argv[]) {
	if (argc > 1) {
		read_arg_from_main(argv);
	} else {
		printf("Please, add parameters.\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
