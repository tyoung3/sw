#!/usr/local/bin/swgraph

# POSTAGE.SW:  Postal rate Streamwork Network Definition Example

$mod="postage";
(Rates  $mod/Rates ".58" "oz" )		-RateT  1> 	 (cp $mod/ComputePostage);
(Weight $mod/GetWeight "10" "oz")	-WeighT 2> 	1(cp);
(From   $mod/GetLoc "New York")		-AddressT> 	2(cp);
(To     $mod/GetLoc "LA" )				-AddressT> 	3(cp);
(cp)4					        -PostageT> 	 (print PrintLabel);
