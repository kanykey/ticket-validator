CC= gcc
CFLAGS = -Wall -pedantic -ansi -std=c99

all: checksum check_location validate_input validate_ticket

checksum: checksum.c
check_location: check_location.c
validate_input: validate_input.c
validate_ticket: validate_ticket.c

clean: 
	rm -f checksum
	rm -f check_location
	rm -f validate_input
	rm -f validate_ticket
	rm -f error.log
	rm -f valid_locations.txt
	rm -f validated_locations.txt
	rm -f validated_barcodes.txt
