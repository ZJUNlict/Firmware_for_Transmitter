#Setup.tcl 
# Setup pin setting for EP1C6 main board 
set_global_assignment -name RESERVE_ALL_UNUSED_PINS "AS INPUT TRI-STATED" 
set_global_assignment -name ENABLE_INIT_DONE_OUTPUT OFF 
set_location_assignment PIN_149 -to clk                                

#led
#set_location_assignment PIN_1 -to led_on_board\[0\] 
#set_location_assignment PIN_2 -to led_on_board\[1\]
set_location_assignment PIN_186 -to led1
set_location_assignment PIN_188 -to led2
set_location_assignment PIN_194 -to led3

#SDRAM
set_location_assignment PIN_37 -to sd_data\[0\] 
set_location_assignment PIN_38 -to sd_data\[1\]
set_location_assignment PIN_39 -to sd_data\[2\] 
set_location_assignment PIN_41 -to sd_data\[3\]
set_location_assignment PIN_43 -to sd_data\[4\] 
set_location_assignment PIN_44 -to sd_data\[5\]
set_location_assignment PIN_45 -to sd_data\[6\] 
set_location_assignment PIN_46 -to sd_data\[7\]
set_location_assignment PIN_69 -to sd_data\[8\] 
set_location_assignment PIN_70 -to sd_data\[9\]
set_location_assignment PIN_65 -to sd_data\[10\] 
set_location_assignment PIN_68 -to sd_data\[11\]
set_location_assignment PIN_63 -to sd_data\[12\] 
set_location_assignment PIN_64 -to sd_data\[13\]
set_location_assignment PIN_56 -to sd_data\[14\] 
set_location_assignment PIN_57 -to sd_data\[15\]

set_location_assignment PIN_94 -to sd_addr\[0\] 
set_location_assignment PIN_95 -to sd_addr\[1\]
set_location_assignment PIN_98 -to sd_addr\[2\] 
set_location_assignment PIN_99 -to sd_addr\[3\]
set_location_assignment PIN_84 -to sd_addr\[4\] 
set_location_assignment PIN_83 -to sd_addr\[5\]
set_location_assignment PIN_82 -to sd_addr\[6\] 
set_location_assignment PIN_81 -to sd_addr\[7\]
set_location_assignment PIN_78 -to sd_addr\[8\] 
set_location_assignment PIN_80 -to sd_addr\[9\]
set_location_assignment PIN_93 -to sd_addr\[10\] 
set_location_assignment PIN_73 -to sd_addr\[11\]

set_location_assignment PIN_88 -to sd_ba\[0\] 
set_location_assignment PIN_87 -to sd_ba\[1\]

set_location_assignment PIN_49 -to sd_dqm\[0\] 
set_location_assignment PIN_72 -to sd_dqm\[1\]

set_location_assignment PIN_55 -to sd_cs
set_location_assignment PIN_52 -to sd_ras
set_location_assignment PIN_51 -to sd_cas
set_location_assignment PIN_50 -to sd_we 
set_location_assignment PIN_76 -to sd_cke
set_location_assignment PIN_71 -to sd_clk

#epcs------------------------------------------
set_location_assignment PIN_23 -to epcs_dclk
set_location_assignment PIN_14 -to epcs_ce 
set_location_assignment PIN_12 -to epcs_do
set_location_assignment PIN_24 -to epcs_data


#USE C1
set_location_assignment PIN_221 -to c1_clk
set_location_assignment PIN_216 -to c1_ce
set_location_assignment PIN_218 -to c1_dr
set_location_assignment PIN_224 -to c1_data
set_location_assignment PIN_230 -to c1_cs

#USE C2 
set_location_assignment PIN_164 -to c2_clk
set_location_assignment PIN_173 -to c2_ce
set_location_assignment PIN_161 -to c2_dr
set_location_assignment PIN_167 -to c2_data
set_location_assignment PIN_169 -to c2_cs

#UART
set_location_assignment PIN_195 -to RxD_usb
set_location_assignment PIN_196 -to TxD_usb

#iic
set_location_assignment PIN_106 -to clk_24
set_location_assignment PIN_108 -to data_24

#IIC
set_location_assignment PIN_111 -to scl_9557
set_location_assignment PIN_112 -to sda_9557
set_location_assignment PIN_120 -to reset_9557
