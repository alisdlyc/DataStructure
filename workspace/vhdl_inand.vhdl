library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;

entity inand is
	port(
		a,b,c,d:IN std_logic;
		re:OUT std_logic
	);
end inand;

architecture arc of inand is
 begin
	re<=(a and b and c and d);
end arc;

