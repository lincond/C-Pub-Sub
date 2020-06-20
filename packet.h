#pragma once

typedef struct packetHeader {
	unsigned int version;
	unsigned short op_code;
	unsigned int payload_size;
	char* payload_checksum;
	char* checksum;
} PacketHeader;

PacketHeader* create_packet_header(
	unsigned int version,
	unsigned short op_code,
	unsigned int payload_size,
	const char* payload_checksum,
	const char* checksum
);
void print_packet_header(PacketHeader*);
char* build_packet_header(PacketHeader);
PacketHeader* parse_packet_header(char*);