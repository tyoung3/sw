# POSTAGE.SW:  Postal rate Streamwork Network Definition Example

(getr    postage/getr/Rates ".17" "oz" )	-rate 1> 	 (cp ComputePostage);
# (getloc  postage/addr/GetLoc "New York")	-address> 	1(cp);
(getdest postage/addr/GetDest "LA" )		-address> 	1(cp);
# (getws   postage/getr/GetWeight "10" "oz")	-weight 2> 	2(cp);
(cp)2					-postage> 	 (print PrintLabel);
