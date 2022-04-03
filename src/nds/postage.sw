#!/usr/local/bin/swgraph

# POSTAGE.SW:  Postal rate Streamwork Network Definition Example

(Rates  postage/getr/Rates ".58" "oz" )		-RateT  1> 	 (cp ComputePostage);
(Weight postage/getr/GetWeight "10" "oz")	-WeighT 2> 	1(cp);
(From   postage/addr/GetLoc "New York")		-AddressT> 	2(cp);
(To     postage/addr/GetLoc "LA" )		-AddressT> 	3(cp);
(cp)4					        -PostageT> 	 (print PrintLabel);
