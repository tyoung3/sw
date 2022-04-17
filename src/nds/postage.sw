#!/usr/local/bin/swgraph

# POSTAGE.SW:  Postal rate Streamwork Network Definition Example

$mod="postage";
(Rates  $mod/Rates ".58" "oz" )		-RateT  3> 	 3(cp $mod/ComputePostage);
(Weight $mod/GetWeight "10" "oz")	-WeighT 2> 	 2(cp);
(From   $mod/GetLoc "New York")		-> 					 0(cp);
(To     $mod/GetLoc "LA" )				-_> 			   1(cp);
(cp)4					        			      -PostageT> 	 (print PrintLabel);
