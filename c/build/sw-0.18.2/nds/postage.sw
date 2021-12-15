# POSTAGE.SW:  Postal rate Streamwork Network Definition Example

(getr    getr/Rates ".17" "oz" )	-rate 1> 	 (cp ComputePostage);
# (getloc  addr/GetLoc "New York")	-address> 	1(cp);
(getdest addr/GetDest "LA" )		-address> 	1(cp);
# (getws   getr/GetWeight "10" "oz")	-weight 2> 	2(cp);
(cp)2								-postage> 	 (print PrintLabel);
#(cp)2								-postage>	 (show Show);
