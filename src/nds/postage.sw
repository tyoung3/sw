#!/usr/local/bin/swgraph

# POSTAGE.SW:  Postal rate Streamwork Network Definition Example

(getr      postage/getr/Rates ".17" "oz" )	-RateT 1> 	 (cp ComputePostage);
# (getloc  postage/addr/GetLoc "New York")	-AddressT> 	1(cp);
(getdest   postage/addr/GetDest "LA" )		-AddressT> 	1(cp);
# (getws   postage/getr/GetWeight "10" "oz")	-WeighT 2> 	2(cp);
(cp)2					-PostageT> 	 (print PrintLabel);
