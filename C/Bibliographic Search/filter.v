///////////////////////////////////////////////////////////////////////////////
//
// module filter.v;
// Project: NF2.1
// Description: ipfileter,drop a special ip
//
//
///////////////////////////////////////////////////////////////////////////////

`timescale 1ns/1ps
`define	WAIT_FOR_PKT 3'b000
`define WAIT_FOR_HEADER 3'b001
`define IP_INPUT_1 3'b010
`define IP_INPUT_2 3'b011
`define IP_INPUT_3 3'b100
`define IP_INPUT_4 3'b101
`define WAIT_FOR_END 3'b110

module filter(
	input [7:0]	gmac_rx_data,
	input 		gmac_rx_dvld,
	input 		reset,
    input 		rxcoreclk,
	output reg	match
);

	reg [2:0]	state;
	reg [4:0]	counter;
	
	always@(posedge rxcoreclk)	begin
		if(reset) begin
			state<=`WAIT_FOR_PKT;
			counter<='h0;
			match<=1'b0;
		end
		else begin
			case(state)
				`WAIT_FOR_PKT:begin
					match<=1'b0;
					if(gmac_rx_dvld) begin
						state<=`WAIT_FOR_HEADER;
					end
				end
				`WAIT_FOR_HEADER:begin
					if(counter==5'd24) begin
						state<=`IP_INPUT_1;
						counter<='h0;
					end
					else counter<=counter+1'b1;
				end
				`IP_INPUT_1:begin
					if(gmac_rx_data=='hc0) state<=`IP_INPUT_2;
					else state<=`WAIT_FOR_END;
				end
				`IP_INPUT_2:begin
					if(gmac_rx_data=='ha8) state<=`IP_INPUT_3;
					else state<=`WAIT_FOR_END;
				end
				`IP_INPUT_3:begin
					if(gmac_rx_data=='h01) state<=`IP_INPUT_4;
					else state<=`WAIT_FOR_END;
				end
				`IP_INPUT_4:begin
					if(gmac_rx_data=='h78) match<=1'b1;
					state<=`WAIT_FOR_END;
				end
				`WAIT_FOR_END:begin
					if(~gmac_rx_dvld) begin
						state<=`WAIT_FOR_PKT;
					end
				end
			endcase
		end
	end

endmodule
