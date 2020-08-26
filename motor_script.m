% Construct a serialport object.
s = serialport("COM5",115200);

clear data1;

% Read 10 numbers of "uint16" data from the serial port.
data1 = read(s,"string");

% Set the Terminator property
configureTerminator(s,"CR");

% Read ASCII-terminated string from the serial port.
%data2 = readline(s);


% Read binblock of "uint8" data from the serial port.
%data3 = readbinblock(s,"uint8");


% Disconnect and clear serialport connection
clear s;