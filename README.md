Ticket Validator
================
This project is written as part of a university assignment at the University of Sydney. 

Description
----
This program validates a ticket so that the gate can open for passenger to walk through. Every ticket has a barcode which is exactly 12 digits. The format of the barcode is as follows:

* The first 4 digits is the location L
* The next 7 digits is the ticket number N
* The last digit is a checksum digit C

When it is presented to a program it is in the form: *LLLLNNNNNNNC*
The barcode is verified using the checksum and the provided `locations.txt` and `barcodes.txt` files which contain valid numbers which are allowed on the ticket. 
