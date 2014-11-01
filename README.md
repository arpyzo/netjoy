# NetJoy

NetJoy is a program that captures basic data (timestamp, length, type, IPs, ports) about each packet traversing an ethernet interface, and stores this information in a postgres database. The data can then be used to display a variety of network traffic statistics.

## Current state

Early POC code has been largely cleaned up and the STL has been used to create a more readable program. The major pieces are in place: opening the NIC and retreiving packet info, timing packet capture so it plays nicely with the GUI, communicating with Postgres.

## wxWidgets

wxWidgets is being used to make development easier (and more fun!). Versions meant for service-based data collection will not include wxWidgets. Care has been taken to keep packet capture and storage separate from the wxWidgets GUI for maximum code reusability.

## Future

Eventually NetJoy will consist of a command line collector service that feeds packet information into a database, and a web-based display that reads from that database.

