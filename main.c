#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>

#define HEADER_SIZE 64
#define CHECKSUM_SIZE 8

typedef struct packetHeader {
	unsigned short version;
	unsigned int op_code;
	char* checksum;
	unsigned int payload_size;
	char* payload_checksum;
} PacketHeader;

/**
	Create a new Packet Header from args
*/
PacketHeader* create_packet_header(
	unsigned int version,
	unsigned short op_code,
	const char* checksum,
	unsigned int payload_size,
	const char* payload_checksum
) {
	PacketHeader* ptr = (PacketHeader*) malloc(sizeof(PacketHeader));
	ptr->version = version;
	ptr->op_code = op_code;
	ptr->payload_size = payload_size;

	ptr->checksum = (char*) malloc(CHECKSUM_SIZE);
	memcpy(ptr->checksum, checksum, CHECKSUM_SIZE);

	ptr->payload_checksum = (char*) malloc(CHECKSUM_SIZE);
	memcpy(ptr->payload_checksum, payload_checksum, CHECKSUM_SIZE);

	return ptr;
}

/**
	Print a packet
*/
void print_packet_header(PacketHeader* packet_header) {
	printf("PacketHeader v.%hu\n\nOP Code: %hd\nHeader Checksum: %s\nPayload Size: %hd\nPayload Checksum: %s\n", packet_header->version, packet_header->op_code, packet_header->checksum, packet_header->payload_size, packet_header->payload_checksum);
}

/**
	Build a string of Packet Header to send over network
*/
char* build_packet_header(PacketHeader packet_header) {
	char* out_str = (char*) malloc(HEADER_SIZE);
	char* ptr = out_str;
	char buffer[16];
	int len = 0;

	memset(out_str, 0x0, HEADER_SIZE);
	memset(buffer, 0x0, 16);

	// Version
	len = sprintf(buffer, "%hu", packet_header.version);
	memcpy(ptr, buffer, len);
	ptr += len;

	// OP Code
	memset(buffer, 0x0, 16);
	len = sprintf(buffer, "%hd", packet_header.op_code);
	memcpy(ptr, buffer, len);
	ptr += len;

	// Checksum
	memcpy(ptr, packet_header.checksum, CHECKSUM_SIZE);
	ptr += CHECKSUM_SIZE;

	// Payload Size
	memset(buffer, 0x0, 16);
	len = sprintf(buffer, "%hd", packet_header.payload_size);
	memcpy(ptr, buffer, len);
	ptr += len;

	// Checksum
	memcpy(ptr, packet_header.payload_checksum, CHECKSUM_SIZE);
	ptr += CHECKSUM_SIZE;

  return out_str;
}

int main() {
	PacketHeader* packet_header = create_packet_header(0x1, 0x1, "13245768", 0, "00000000");

	print_packet_header(packet_header);

	char* built_packet = build_packet_header(*packet_header);

	printf("\nBuilt packet header:\n%s\n\n", built_packet);
	free(built_packet);
	free(packet_header->checksum);
	free(packet_header->payload_checksum);
	free(packet_header);

	return 0;
}
