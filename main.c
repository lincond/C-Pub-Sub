#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>

#include "packet.h"

int main() {
	PacketHeader* packet_header = create_packet_header(0x1, 0x1, 0, "00000000", "13245768");

	print_packet_header(packet_header);

	char* built_packet = build_packet_header(*packet_header);

	printf("\nBuilt packet header:\n%s\n\n", built_packet);
	free_packet_header(packet_header);

	packet_header = parse_packet_header(built_packet);
	free(built_packet);
	print_packet_header(packet_header);

	free_packet_header(packet_header);
	return 0;
}

